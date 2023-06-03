#pragma once
#include <vector>
#include <QList>
#include "opencv2/opencv.hpp"

/** @brief 标定板类型 */
enum CalibBoardType
{
	CHESSBOARD,						///< 棋盘格
	SYM_CIRCLE,						///< 对称圆
	ASYM_CIRCLE,					///< 非对称圆
};

/** @brief 手眼类型 */
enum HandEyeType
{
	EYE_IN_HAND_ARTIC,					///< 六轴眼在手上
	EYE_TO_HAND_ARTIC,					///< 六轴眼在手外
	EYE_IN_HAND_SCARA,					///< SCARA 眼在手上
	EYE_TO_HAND_SCARA,					///< SCARA 眼在手外
};


/** @brief 弹窗报警级别 */
enum lxReportLevel
{
	INFO,
	WARN,
	CRITICAL,
	QUESTION
};

/** @brief 弹窗报警码 */
enum lxReportCode
{
	em_FindCornerFailed = 0,				 ///< 查找角点 失败

	em_Inter_CalibSuccess = 100,			 ///< 内参标定  成功
	em_Inter_CalibFailed = 101,				 ///< 内参标定  失败
	em_Inter_CalibBoardNotSelect = 102,		 ///< 内参标定  未选择标定板
	em_Inter_ImgDirNotFound = 103,			 ///< 内参标定  图片文件夹不存在

	em_Exter_CalibSuccess = 200,			 ///< 外参标定  成功
	em_Exter_CalibFailed = 201,				 ///< 外参标定  失败
	em_Exter_CalibBoardNotSelect = 202,		 ///< 外参标定  未选择标定板
	em_Exter_HandEyeNotSelect = 203,		 ///< 外参标定  未选择手眼类型
	em_Exter_RobotPoseNotFound = 204,		 ///< 外参标定  机械臂拍照文件未选择
	em_Exter_CamInterFileNotFound = 205,	 ///< 外参标定  相机内参文件未选择
	em_Exter_RobotPoseParseError = 206,		 ///< 外参标定  解析机械臂拍照文件失败
	em_Exter_CamInterFileParseError = 207,	 ///< 外参标定  解析相机内参文件失败

	em_Stereo_CalibSuccess = 300,			 ///< 双目标定  成功
	em_Stereo_CalibFailed = 301,			 ///< 双目标定  失败
	em_Stereo_CalibBoardNotSelect = 302,	 ///< 双目标定  未选择标定板
	em_Stereo_Cam1ImgDirNotFound = 303,		 ///< 双目标定  相机1图片文件夹不存在
	em_Stereo_Cam2ImgDirNotFound = 304,		 ///< 双目标定  相机2图片文件夹不存在

	em_WorkMode_Err = 400,					 ///< 工作模式  错误

};

/** @brief 标定板类型 */
const QList<QString> g_listBoardType =
{
	"8x5x60x0","8x5x45x0","6x9x20x0","22x24x10x0","24x23x15x0"
};


/** @brief 标定板信息结构体 */
struct CalibBoardInfo
{
	CalibBoardInfo(){}
	CalibBoardInfo(CalibBoardType type, cv::Size size, double eleLen)
	{
		m_tType = type;
		m_tSize = size;
		m_nEleLenth = eleLen;
	};

	CalibBoardType  m_tType;			///< 标定板类型
	cv::Size		  m_tSize;			///< 标定板size
	double			  m_nEleLenth;		///< 标定板上单元长度
};

/** @brief 机器人标定的数据帧定义
		   (一帧数据包含一组法兰位姿以及一张图片) */
struct RobotCalibFrame
{
	RobotCalibFrame(){}
	RobotCalibFrame(cv::Mat pos, cv::Mat img)
	{
		m_tPos = pos;
		m_tImg = img;
	}

	cv::Mat m_tPos;		///< 机器人位姿
	cv::Mat m_tImg;		///< 图片
};
