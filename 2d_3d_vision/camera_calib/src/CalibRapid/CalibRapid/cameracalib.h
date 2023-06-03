#pragma once
#include <Eigen/Eigen>  
#include "opencv2/opencv.hpp"
#include "opencv2/core/eigen.hpp"	///< opencv 和 eigen 互转
#include "cameracalib_common.h"

class CameraCalib_OpenCV
{
public:
	CameraCalib_OpenCV() = delete;

	/**画出角点*/
	static bool drawCorners(cv::Mat& inImgMat, CalibBoardInfo& boardInfo);

	/**内参标定,输出camMat为3x3矩阵为相机内参,输出distCoeff为5x1列向量*/
	static bool calibInter(cv::Mat& camMat, cv::Mat& distCoeff, std::vector<cv::Mat>& vImgMat, CalibBoardInfo& boardInfo);

	/**外参标定,输出result为4x4矩阵,为cam to base 的变换*/
	static bool calibExter(cv::Mat& result, std::vector<RobotCalibFrame>& vRobotInfo,cv::Mat& camMat, cv::Mat& distCoeff,
		CalibBoardInfo& boardInfo,
		HandEyeType handEyeType = HandEyeType::EYE_TO_HAND_ARTIC);
	
	/**双目标定,输出result为4x4矩阵,为cam1 to cam2 的变换*/ 
	//static bool calibStereo(cv::Mat& result, std::string cam1ImgDir, std::string cam2ImgDir, lxCalibBoardInfo_OpenCV& boardInfo);

private:
	class Impl;
};
