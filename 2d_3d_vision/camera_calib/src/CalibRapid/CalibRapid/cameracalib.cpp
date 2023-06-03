#include "cameracalib.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QQuaternion>

#include <QDebug>

class CameraCalib_OpenCV::Impl
{
public:
	Impl() = delete;

	/**支持单通道灰度图/三通道彩图传入*/
	static bool findCorners(std::vector<cv::Point2f> &corners, cv::Mat &imgMat, CalibBoardInfo& boardInfo)
	{
		if (imgMat.empty())
			return false;

		// 1 convert color to gray
		cv::Mat imgGray;
		if (imgMat.channels() == 1)
		{
			imgGray = imgMat;
		}
		else
		{
			cv::cvtColor(imgMat, imgGray, cv::COLOR_BGR2GRAY);
		}

		// 2 使用opencv函数查找角点
		bool bCornerFounded = cv::findChessboardCorners(imgGray, boardInfo.m_tSize, corners);

		// 3 优化角点位置（只用于棋盘格）提高角点精度
		if (bCornerFounded && boardInfo.m_tType == CalibBoardType::CHESSBOARD)
		{
			cv::TermCriteria criteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1);
			cv::cornerSubPix(imgGray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);
		}
		return bCornerFounded;
	}

	/**获取标定板在世界坐标系下的3D坐标(一般,取标定板本身的平面为世界的xy,原点设置在第一个角点,z轴 垂直图案面朝里,x轴 朝右,y轴 朝下)*/
	static void getBoardWorldPoints(std::vector<cv::Point3f> &points, CalibBoardInfo& boardInfo)
	{
		if (boardInfo.m_tType == CalibBoardType::CHESSBOARD)
		{
			for (int i = 0; i < boardInfo.m_tSize.height; ++i)		//row
				for (int j = 0; j < boardInfo.m_tSize.width; ++j)		//col 
					points.push_back(cv::Point3f(j * boardInfo.m_nEleLenth, i * boardInfo.m_nEleLenth, 0));
		}
		else if (boardInfo.m_tType == CalibBoardType::SYM_CIRCLE)
		{

		}
		else if (boardInfo.m_tType == CalibBoardType::ASYM_CIRCLE)
		{

		}
		else
		{

		}
	}

	static bool calcGripper2Base(std::vector<cv::Mat>& vGripper2Base_R, std::vector<cv::Mat>& vGripper2Base_t,std::vector<RobotCalibFrame> vInfo)
	{
		for (auto info : vInfo)
		{
			if(info.m_tPos.size() != cv::Size(4,4))
				continue;

			cv::Mat xyz = info.m_tPos;

			cv::Mat t = (cv::Mat_<double>(3, 1) << xyz.at<double>(0, 3), xyz.at<double>(1, 3), xyz.at<double>(2, 3));
			cv::Mat R = (cv::Mat_<double>(3, 3) << 
				xyz.at<double>(0, 0), xyz.at<double>(0, 1), xyz.at<double>(0, 2),
				xyz.at<double>(1, 0), xyz.at<double>(1, 1), xyz.at<double>(1, 2),
				xyz.at<double>(2, 0), xyz.at<double>(2, 1), xyz.at<double>(2, 2));

			vGripper2Base_R.push_back(R);
			vGripper2Base_t.push_back(t);
		}

		return true;
	}

	/**计算标定板在相机坐标系下的旋转矩阵(3x3)和平移向量(3x1)*/
	static bool calcTarget2Cam(std::vector<cv::Mat>& vTarget2Cam_R, std::vector<cv::Mat>& vTarget2Cam_t, std::vector<int>& vImgIdxNoValid, std::vector<cv::Mat> vImg, cv::Mat cameraMat, cv::Mat distCoeff,CalibBoardInfo& boardInfo)
	{
		if (vImg.size() == 0)
			return false;

		std::vector<cv::Point3f> objectPoints;
		getBoardWorldPoints(objectPoints, boardInfo);

		// 调用solvePnP计算target2cam 
		int i = 0;
		for (auto img : vImg)
		{
			std::vector<cv::Point2f> vCorner;
			if (!Impl::findCorners(vCorner, img,boardInfo))
			{
				vImgIdxNoValid.push_back(i);
				std::cout << "未找到角点" << std::endl;
				continue;
			}

			cv::Mat rvec = cv::Mat::zeros(3, 1, CV_64FC1); // 旋转向量
			cv::Mat tvec = cv::Mat::zeros(3, 1, CV_64FC1); // 平移向量

			if (!cv::solvePnP(objectPoints, vCorner, cameraMat, distCoeff, rvec, tvec))
			{
				vImgIdxNoValid.push_back(i);
				std::cout << "PnP求解失败" << std::endl;
				continue;
			}

			cv::Mat target2Cam_R;
			cv::Rodrigues(rvec, target2Cam_R); // 将rvec旋转向量 转成 旋转矩阵

			vTarget2Cam_R.push_back(target2Cam_R);
			vTarget2Cam_t.push_back(tvec / 1000.);

			i++;
		}

		if (vTarget2Cam_R.size() == 0)
			return false;

		return true;
	}
};
bool CameraCalib_OpenCV::drawCorners(cv::Mat& inImgMat, CalibBoardInfo& boardInfo)
{
	std::vector<cv::Point2f> corners;
	// 1 查找角点
	bool bFind =  Impl::findCorners(corners, inImgMat, boardInfo);

	// 2 将角点画在 inImgMat 上
	if(bFind)
		cv::drawChessboardCorners(inImgMat, boardInfo.m_tSize, corners, bFind);

	return bFind;
}
bool CameraCalib_OpenCV::calibInter(cv::Mat& camMat, cv::Mat& distCoeff, std::vector<cv::Mat>& vImgMat, CalibBoardInfo& boardInfo)
{
	if (vImgMat.size() == 0)
		return false;

	std::vector<std::vector<cv::Point2f>> imagePoints; // 所有 像素坐标系下的点
	std::vector<std::vector<cv::Point3f>> objectPoints; //所有 世界坐标系下的点

	//1. 标定板 世界坐标系坐标
	std::vector<cv::Point3f> points;
	Impl::getBoardWorldPoints(points, boardInfo);

	for (auto img : vImgMat)
	{
		//2. 查找角点
		std::vector<cv::Point2f> corners;
		bool isFound = Impl::findCorners(corners, img,boardInfo);

		if (isFound)
		{
			imagePoints.push_back(corners);
			objectPoints.push_back(points);
		}
		else
			return false;
	}

	if (imagePoints.size() == 0)
		return false;

	// 3 标定
	//cv::Mat cameraMatrix;		// 相机内参  fx fy u0 v0
	//cv::Mat distCoeffs;		// 畸变参数 k1 k2 p1 p2 k3  
	std::vector<cv::Mat> rvecs; // 在相机坐标系的哪里 发现了 棋盘 (姿态)
	std::vector<cv::Mat> tvecs; // 在相机坐标系的哪里 发现了 棋盘 (位置)

	double r_mse = cv::calibrateCamera(objectPoints, imagePoints, vImgMat.front().size(), camMat, distCoeff, rvecs, tvecs);

	// 4 检查结果 
	if (cv::checkRange(camMat) && cv::checkRange(distCoeff))
		return true;
	else
		return false;
}

bool CameraCalib_OpenCV::calibExter(cv::Mat& result, std::vector<RobotCalibFrame>& vRobotInfo, cv::Mat& camMat, cv::Mat& distCoeff, CalibBoardInfo& boardInfo, HandEyeType handEyeType /*= lxHandEyeType::EYE_OUT_HAND*/)
{
	std::vector<std::string> vImgPath;			// 所有图片的路径
	std::vector<int>		 vImgIdxNoValid;	// 未找到角点的图片索引 

	// 1 计算gripper 在 base 中的位置和姿态
	std::vector<cv::Mat> vGripper2Base_R;
	std::vector<cv::Mat> vGripper2Base_t;
	if (!Impl::calcGripper2Base(vGripper2Base_R, vGripper2Base_t, vRobotInfo))
		return false;

	// 2 计算target 在 cam 中的位置和姿态
	std::vector<cv::Mat> vTarget2Cam_R;
	std::vector<cv::Mat> vTarget2Cam_t;
	std::vector<cv::Mat> vImg;
	for (auto info : vRobotInfo)
	{
		vImg.push_back(info.m_tImg);
	}
	if (!Impl::calcTarget2Cam(vTarget2Cam_R, vTarget2Cam_t, vImgIdxNoValid, vImg, camMat, distCoeff, boardInfo))
		return false;

	// 如果有不符合的 需要过滤一下
	for (int noValidIdx : vImgIdxNoValid)
	{
		vGripper2Base_R.erase(vGripper2Base_R.begin() + noValidIdx);
		vGripper2Base_t.erase(vGripper2Base_t.begin() + noValidIdx);
	}
	if (vGripper2Base_R.size() != vTarget2Cam_R.size())
		return false;
	if (vGripper2Base_R.size() < 3)
		return false;
	if (handEyeType == HandEyeType::EYE_TO_HAND_ARTIC)
	{
		// 需要求逆
		for (int i = 0; i < vGripper2Base_R.size(); i++)
		{
			vGripper2Base_R[i] = vGripper2Base_R[i].t();
			vGripper2Base_t[i] = -vGripper2Base_R[i] * vGripper2Base_t[i];
		}
	}

	// 3 计算外参
	cv::Mat cam2Base_R;
	cv::Mat cam2Base_t;
	cv::calibrateHandEye(vGripper2Base_R, vGripper2Base_t, vTarget2Cam_R, vTarget2Cam_t, cam2Base_R, cam2Base_t,
		cv::HandEyeCalibrationMethod::CALIB_HAND_EYE_DANIILIDIS);


	// 4 输出外参
	Eigen::Matrix4d mat;
	mat << cam2Base_R.at<double>(0, 0), cam2Base_R.at<double>(0, 1), cam2Base_R.at<double>(0, 2), cam2Base_t.at<double>(0, 0)*1000,
		cam2Base_R.at<double>(1, 0), cam2Base_R.at<double>(1, 1), cam2Base_R.at<double>(1, 2), cam2Base_t.at<double>(1, 0)*1000,
		cam2Base_R.at<double>(2, 0), cam2Base_R.at<double>(2, 1), cam2Base_R.at<double>(2, 2), cam2Base_t.at<double>(2, 0)*1000,
		0, 0, 0, 1;

	cv::eigen2cv(mat, result);

	return true;
}

//bool CameraCalib_OpenCV::calibStereo(cv::Mat& result, std::string cam1ImgDir, std::string cam2ImgDir, lxCalibBoardInfo& boardInfo)
//{
//	std::vector<cv::String> vCam1ImgFile;
//	std::vector<cv::String> vCam2ImgFile;
//
//	cv::glob(cam1ImgDir + "/*", vCam1ImgFile);
//	cv::glob(cam2ImgDir + "/*", vCam2ImgFile);
//	if (vCam1ImgFile.size() != vCam2ImgFile.size())
//		return false;
//
//	// 0 准备object point 准备cam1 img point 准备cam2 img point 
//	std::vector<std::vector<cv::Point3f>> vvObjectPoints;	// 所有 世界坐标系下的点
//	std::vector<std::vector<cv::Point2f>> imagePoints1;		// cam1 像素坐标系下的点
//	std::vector<std::vector<cv::Point2f>> imagePoints2;		// cam2 像素坐标系下的点
//
//	std::vector<cv::Point3f> vObjectPoints;
//	Impl::getBoardWorldPoints(vObjectPoints,boardInfo);
//
//	cv::Size imgSize;
//	for (int i = 0; i < vCam1ImgFile.size(); i++)
//	{
//		cv::Mat img1 = cv::imread(vCam1ImgFile[i]);
//		cv::Mat img2 = cv::imread(vCam2ImgFile[i]);
//
//		//1. 查找角点
//		std::vector<cv::Point2f> corners1;
//		std::vector<cv::Point2f> corners2;
//		bool isFound1 = Impl::findCorners(corners1, img1, boardInfo);
//		bool isFound2 = Impl::findCorners(corners2, img2, boardInfo);
//
//		if (isFound1 && isFound2)
//		{
//			imagePoints1.push_back(corners1);
//			imagePoints2.push_back(corners2);
//			vvObjectPoints.push_back(vObjectPoints);
//
//			imgSize = img1.size();
//		}
//	}
//
//	// 2 进行双目标定 
//	cv::Mat cameraMatrix1;
//	cv::Mat distCoeffs1;
//	cv::Mat cameraMatrix2;
//	cv::Mat distCoeffs2;
//	cv::Mat cam12Cam2_R;		// 相机1在相机2的旋转矩阵
//	cv::Mat cam12Cam2_T;		// 相机1在相机2的平移向量
//	cv::Mat E;
//	cv::Mat F;
//	cv::stereoCalibrate(vvObjectPoints, imagePoints1, imagePoints2, cameraMatrix1, distCoeffs1, cameraMatrix2, distCoeffs2,
//		imgSize, cam12Cam2_R, cam12Cam2_T, E, F);
//
//	// 3 输出外参
//	Eigen::Matrix4d mat;
//	mat << cam12Cam2_R.at<double>(0, 0), cam12Cam2_R.at<double>(0, 1), cam12Cam2_R.at<double>(0, 2), cam12Cam2_T.at<double>(0, 0),
//		cam12Cam2_R.at<double>(1, 0), cam12Cam2_R.at<double>(1, 1), cam12Cam2_R.at<double>(1, 2), cam12Cam2_T.at<double>(1, 0),
//		cam12Cam2_R.at<double>(2, 0), cam12Cam2_R.at<double>(2, 1), cam12Cam2_R.at<double>(2, 2), cam12Cam2_T.at<double>(2, 0),
//		0, 0, 0, 1;
//
//	cv::eigen2cv(mat, result);
//	return true;
//}
