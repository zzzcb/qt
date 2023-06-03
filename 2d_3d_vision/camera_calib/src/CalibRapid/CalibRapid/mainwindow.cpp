#pragma execution_character_set("utf-8")
#include "mainwindow.h"

#include <QMenuBar>
#include <QToolBar>
#include <QIcon>
#include <QActionGroup>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QSplitter>
#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QScrollArea>
#include <QTextBrowser>
#include <QMessageBox>
#include <QMovie>
#include <QLabel>
#include <QListWidget>
#include <QApplication>

#include "imageflowviewer.h"

#define DEGREE2RAD (180.0/3.1415926)
#define BOARD_INFO_FIELD_NUM 4

/**四元数的顺序是 w,x,y,z*/
Eigen::Matrix3d quat2RotateMatrix(std::vector<double> vQuad)
{

	if (vQuad.size() != 4)
		return Eigen::Matrix3d();

	Eigen::Quaterniond quaternion(vQuad[0], vQuad[1], vQuad[2], vQuad[3]);

	return quaternion.toRotationMatrix();
}
/**欧拉角顺序是 Rz,Ry,Rx*/
Eigen::Matrix3d euler2RotateMatrix(std::vector<double> vEuler)
{
	if (vEuler.size() != 3)
		return Eigen::Matrix3d();

	Eigen::AngleAxisd yawAngle(Eigen::AngleAxisd(vEuler[0], Eigen::Vector3d::UnitZ()));
	Eigen::AngleAxisd pitchAngle(Eigen::AngleAxisd(vEuler[1], Eigen::Vector3d::UnitY()));
	Eigen::AngleAxisd rollAngle(Eigen::AngleAxisd(vEuler[2], Eigen::Vector3d::UnitX()));

	Eigen::Matrix3d rotation_matrix;
	rotation_matrix = yawAngle * pitchAngle*rollAngle;

	return rotation_matrix;
}

/**保存相机内参到文件中*/
void saveInterParamToFile(const std::string& file, cv::Mat intMat, cv::Mat distMat)
{
	cv::FileStorage fs(file, cv::FileStorage::WRITE);
	fs << "calibration_time" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
	fs << "camera_matrix" << intMat;
	fs << "dist_coeffs" << distMat;
	fs.release();
}

/**保存相机外参到文件中*/
void saveExternalParamToFile(std::string file, cv::Mat result)
{
	cv::FileStorage fs(file, cv::FileStorage::WRITE);
	fs << "calibration_time" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
	fs << "camera_to_world_matrix" << result;
	fs << "world_to_camera_matrix" << result.inv();
	fs.release();
}

/**保存相机双目关系到文件中*/
void saveStereoParamToFile(std::string file, cv::Mat result)
{
	cv::FileStorage fs(file, cv::FileStorage::WRITE);
	fs << "calibration_time" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
	fs << "cam1_in_cam2" << result;
	fs.release();
}

void saveMatToDir(QList<std::vector<uchar>> listImgData)
{
	if (listImgData.isEmpty()) return;

	QString dir = QFileDialog::getExistingDirectory(nullptr, "请选择要保存的文件夹");
	
	int i = 0;
	for (auto& imgData : listImgData)
	{
		QString imgName = QString("%1-%2.png").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss"), QString::number(++i));
		imgName = QDir::cleanPath(dir + QDir::separator() + imgName);

		std::ofstream os(imgName.toStdString(), std::ios::binary);
		os.write(reinterpret_cast<char*>(imgData.data()), imgData.size());
		os.close();
	}
}

void doReport(QWidget*parent, lxReportLevel level, lxReportCode code)
{
	QString title, detail;
	switch (code)
	{
	case em_FindCornerFailed:
	{
		title = "查找角点失败";
		detail = "请检查【①步骤】是否与所选图片匹配\n原始图片角点是否完整可见";
		break;
	}
	case em_Inter_CalibSuccess:
	{
		title = "相机内参标定成功";
		detail = "标定结果文件已经默认放在桌面";
		break;
	}
	case em_Inter_CalibFailed:
	{
		title = "相机内参标定失败";
		detail = "请检查【相机内参】中各个步骤是否正确\n图片显示是否为空\n标定板类型是否与图片一致\n角点图片是否正确等";
		break;
	}
	case em_Inter_ImgDirNotFound:
	{
		title = "图片文件夹不存在";
		detail = "请在【相机内参 > ③步骤】检查路径的正确性";
		break;
	}
	case em_Inter_CalibBoardNotSelect:
	{
		title = "未选择标定板类型";
		detail = "请在【相机内参 > ①步骤】中进行选择";
		break;
	}
	case em_Exter_CalibSuccess:
	{
		title = "相机外参标定成功";
		detail = "标定结果文件已经默认放在桌面";
		break;
	}
	case em_Exter_CalibFailed:
	{
		title = "相机外参标定失败";
		detail = "请检查【相机内参】中各个步骤是否正确,标定板类型是否与图片一致";
		break;
	}
	case em_Exter_CalibBoardNotSelect:
	{
		title = "未选择标定板类型";
		detail = "请在【相机外参 > ①步骤】中进行选择";
		break;
	}
	case em_Exter_HandEyeNotSelect:
	{
		title = "未选择手眼类型";
		detail = "请在【相机外参 > ③步骤】中进行选择";
		break;
	}
	case em_Exter_RobotPoseNotFound:
	{
		title = "机器人拍照文件不存在";
		detail = "请在【相机外参 > ④步骤】中进行选择";
		break;
	}
	case em_Exter_RobotPoseParseError:
	{
		title = "机器人拍照文件解析失败";
		detail = "请在【相机外参 > ④步骤】中文件的内容是否满足格式要求";
		break;
	}
	case em_Exter_CamInterFileNotFound:
	{
		title = "相机内参文件不存在";
		detail = "请在【相机外参 > ⑤步骤】中进行选择";
		break;
	}
	case em_Exter_CamInterFileParseError:
	{
		title = "相机内参文件解析失败";
		detail = "请检查【相机外参 > ⑤步骤】中文件的内容是否满足格式要求";
		break;
	}
	case em_Stereo_CalibSuccess:
	{
		title = "相机双目标定成功";
		detail = "标定结果文件已经默认放在桌面";
		break;
	}
	case em_Stereo_CalibFailed:
	{
		title = "相机双目标定失败";
		detail = "请检查【相机双目标定】中各个步骤是否正确,标定板类型是否与图片一致,以及两个相机照片是否大小一致";
		break;
	}
	case em_Stereo_CalibBoardNotSelect:
	{
		title = "标定板类型未选择";
		detail = "请检查【相机双目标定 > ①步骤】是否选择了标定板";
		break;
	}
	case em_Stereo_Cam1ImgDirNotFound:
	{
		title = "相机1的照片路径不存在";
		detail = "请检查【相机双目标定 > ②步骤】是否正确";
		break;
	}
	case em_Stereo_Cam2ImgDirNotFound:
	{
		title = "相机2的照片路径不存在";
		detail = "请检查【相机双目标定 > ③步骤】是否正确";
		break;
	}
	case em_WorkMode_Err:
	{
		title = "工作模式错误";
		detail = "请检查【②步骤】是否正确,当前为在线标定模式,不允许手动查看图片";
		break;
	}
	default:
		break;
	}

	switch (level)
	{
	case INFO:
		QMessageBox::information(parent, title, detail);
		break;
	case WARN:
		QMessageBox::warning(parent, title, detail);
		break;
	case CRITICAL:
		QMessageBox::critical(parent, title, detail);
		break;
	case QUESTION:
		QMessageBox::question(parent, title, detail);
		break;
	default:
		break;
	}
}

// MatrixDisplay 
MatrixDisplay::MatrixDisplay(QWidget* parent /*= nullptr*/)
	:QDialog(parent)
{
	// h layout
	QHBoxLayout* pMainLayout = new QHBoxLayout(this);
	pMainLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(pMainLayout);

	QScrollArea *scrollArea = new QScrollArea;
	scrollArea->setWidgetResizable(true); // very important
	pMainLayout->addWidget(scrollArea);

	// real container
	QWidget* realContainer = new QWidget;
	scrollArea->setWidget(realContainer);

	m_pHLayout = new QHBoxLayout(realContainer);
	realContainer->setLayout(m_pHLayout);

	resize(700, 140);
}

void MatrixDisplay::showResult(QList<cv::Mat> listMat, QList<QString> listMsg)
{
	if (listMat.size() != listMsg.size())
		return;

	auto mat2QString = [](cv::Mat& mat)->QString
	{
		QString result;
		for (int i = 0; i < mat.rows; i++)
		{
			for (int j = 0; j < mat.cols; j++)
			{
				result += QString::number(mat.at<double>(i, j), 'e', 8) + "   ";
			}
			result += "\n";
		}
		return result;
	};


	for (int i = 0; i < listMat.size(); i++)
	{
		QVBoxLayout * vLayout = new QVBoxLayout;
		vLayout->setAlignment(Qt::AlignVCenter);

		QLabel* lbTitle = new QLabel(listMsg[i]);
		QTextBrowser * browser = new QTextBrowser;
		browser->setText(mat2QString(listMat[i]));

		vLayout->addWidget(lbTitle);
		vLayout->addWidget(browser);

		m_pHLayout->addLayout(vLayout);

		if (i != listMat.size() - 1)
		{
			auto vLine = new QFrame; vLine->setObjectName("vLine"); vLine->setFrameShape(QFrame::VLine); vLine->setFrameShadow(QFrame::Sunken);
			m_pHLayout->addWidget(vLine);
		}
	}

	show();
}

AbstractCalibWidget::AbstractCalibWidget(QWidget* parent /*= nullptr*/)
	:QWidget(parent)
{
	QHBoxLayout* mainLayout = new QHBoxLayout(this);
	mainLayout->setMargin(0);

	m_pSplitter = new QSplitter(this);
	m_pSplitter->setHandleWidth(5);
	m_pSplitter->setChildrenCollapsible(true);

	mainLayout->addWidget(m_pSplitter);
}

AbstractCalibWidget::~AbstractCalibWidget()
{
}

void AbstractCalibWidget::addLeftSubWidget()
{
	m_pSplitter->addWidget(leftSubWidget());
}

void AbstractCalibWidget::addMidSubWidget()
{
	m_pSplitter->addWidget(midSubWidget());
}

void AbstractCalibWidget::addRightSubWidget()
{
	m_pSplitter->addWidget(rightSubWidget());
}

void AbstractCalibWidget::setSizes(const QList<int>& sizes)
{
	m_pSplitter->setSizes(sizes);
}

void AbstractCalibWidget::setAlgo(int algoIdx)
{
	m_nCurAlgo = algoIdx;
}

IntrinsicWidget::IntrinsicWidget(QWidget* parent /*= nullptr*/)
	:AbstractCalibWidget(parent)
{
	addLeftSubWidget();
	addMidSubWidget();
	addRightSubWidget();

	setSizes({ 1000,2000,2000 });

	/** 使用定时器 定时更新界面 */
	m_pUpdateUiTimer = new QTimer(this);
	connect(m_pUpdateUiTimer, &QTimer::timeout, [&]() {
		if(!m_tMatQueue.isEmpty())
		{
			auto result = m_tMatQueue.dequeue();
			m_pSrcImgViewer->pushNewMat({ result[0] });
			m_pCornerImgViewer->pushNewMat({ result[1] });
		}
	});
	m_pUpdateUiTimer->start(100);

	/**右键菜单栏设置*/
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &IntrinsicWidget::customContextMenuRequested, this, &IntrinsicWidget::slot_customContextMenu);
}

IntrinsicWidget::~IntrinsicWidget()
{

}

bool IntrinsicWidget::eventFilter(QObject *watched, QEvent *event)
{
	/** 离线模式先才允许选择本地图片 */
	if (watched == m_pInterImageFiles)
	{
		if (event->type() == QEvent::MouseButtonDblClick)
		{
			m_pInterImageFiles->setText(QFileDialog::getOpenFileNames(this, "请选择图片文件", ".", "Images (*.png *.bmp *.jpg)").join(";"));
			return true;
		}
	}


	return AbstractCalibWidget::eventFilter(watched, event);
}

QWidget* IntrinsicWidget::leftSubWidget()
{
	/** control panel box */
	QGroupBox* ctrlPanel = new QGroupBox;
	QFormLayout* ctrlLayout = new QFormLayout(ctrlPanel);
	
	QList<QString> listCtrlLabel = {"①","②","③","④","⑤","⑥","⑦","⑧","⑨","⑩"};
	m_pCalibBoard = new QComboBox;
	m_pCalibBoard->addItems(g_listBoardType);
	
	/** add to ctrl layout */ 
	ctrlLayout->addRow(listCtrlLabel[0], m_pCalibBoard);
	m_pInterImageFiles = new QLineEdit; 
	m_pInterImageFiles->setPlaceholderText("鼠标双击选择图片");
	
	QHBoxLayout* hLayout = new QHBoxLayout;
	m_pViewImgBtn = new QPushButton("查看图片");
	QPushButton* calibBtn = new QPushButton("标定");
	hLayout->addWidget(m_pViewImgBtn);
	hLayout->addWidget(calibBtn);

	ctrlLayout->addRow(listCtrlLabel[2], m_pInterImageFiles);
	ctrlLayout->addRow(listCtrlLabel[3], hLayout);

	/** event filter */ 
	m_pInterImageFiles->installEventFilter(this);
	
	/** signal slot */
	connect(m_pViewImgBtn, &QPushButton::clicked, this, &IntrinsicWidget::slot_btnInterViewImg);
	connect(calibBtn, &QPushButton::clicked, this, &IntrinsicWidget::slot_btnInterCalib);

	return ctrlPanel;
}

QWidget* IntrinsicWidget::midSubWidget()
{
	m_pSrcImgViewer = new ImageFlowViewer(QSize(170, 170));
	return m_pSrcImgViewer;
}

QWidget* IntrinsicWidget::rightSubWidget()
{
	m_pCornerImgViewer = new ImageFlowViewer(QSize(170, 170));
	return m_pCornerImgViewer;
}

void IntrinsicWidget::intrFindCorner(QList<cv::Mat>& allMat)
{
	if (allMat.size() == 0) return;

	/** 解析标定板类型 */
	auto listBoardInfo = m_pCalibBoard->currentText().split("x");
	if (listBoardInfo.size() < BOARD_INFO_FIELD_NUM)
		return;

	/** 提交异步线程 */
	QFuture<QMap<int, QList<cv::Mat>>> future = QtConcurrent::run([=]()
	{
		QMap<int, QList<cv::Mat>> resultMap;

		for (int i = 0; i < allMat.size(); i++)
		{
			cv::Mat imgCornerMat;
			allMat[i].copyTo(imgCornerMat);
			CalibBoardInfo boardInfo(CalibBoardType(listBoardInfo[3].toInt()), cv::Size(listBoardInfo[0].toInt(), listBoardInfo[1].toInt()), listBoardInfo[2].toDouble());
			
			/** 选择当前的算法进行标定 */
			if (m_nCurAlgo == 0)
			{
				if (CameraCalib_OpenCV::drawCorners(imgCornerMat, boardInfo))
				{
					resultMap.insert(i, { allMat[i],imgCornerMat });
				}
			}
			else if (m_nCurAlgo == 1)
			{
				
			}
		}

		return resultMap;
	});

	/** 拿到异步线程结果,后不直接操作UI,使用定时器定时处理 */
	QFutureWatcher<QMap<int, QList<cv::Mat>>>* pFutureWatch = new QFutureWatcher<QMap<int, QList<cv::Mat>>>();
	connect(pFutureWatch, &QFutureWatcher<QMap<int, QList<cv::Mat>>>::finished, [=]()
	{
		auto resultMap = future.result();
		for (int i = 0; i < allMat.size(); i++)
		{
			if (resultMap.contains(i))
			{
				m_tMatQueue.enqueue(resultMap.value(i));
			}
		}

		/** 异步计算完毕 */
		emit signal_loading(false);

		if (resultMap.size() != allMat.size())
		{
			doReport(this, lxReportLevel::WARN, lxReportCode::em_FindCornerFailed);
		}

		// free memmory
		pFutureWatch->deleteLater();
	});
	pFutureWatch->setFuture(future);

}

void IntrinsicWidget::slot_btnInterViewImg()
{
	/** 获取所有的图片 */
	QList<cv::Mat> listMat;
	for (auto img : m_pInterImageFiles->text().split(";"))
	{
		if (!QFileInfo::exists(img))
		{
			doReport(this, lxReportLevel::WARN, lxReportCode::em_Inter_ImgDirNotFound);
			return;
		}
		QFile imgFile(img);
		if (imgFile.open(QIODevice::ReadOnly))
		{
			QByteArray imgBA = imgFile.readAll();
			std::vector<uchar> vImgData(imgBA.data(), imgBA.data() + imgBA.size());

			listMat.push_back(cv::imdecode(vImgData, cv::IMREAD_COLOR));
		}
	}

	/** 开始异步计算 */
	emit signal_loading(true);
	intrFindCorner(listMat);
}

void IntrinsicWidget::slot_btnInterCalib()
{
	/** 解析标定板类型 */
	auto listBoardInfo = m_pCalibBoard->currentText().split("x");
	if (listBoardInfo.size() < BOARD_INFO_FIELD_NUM)
		return;

	/** 图片为空 */
	if (m_pSrcImgViewer->isEmpty())
	{
		doReport(this, lxReportLevel::CRITICAL, em_Inter_CalibFailed);
		return;
	}

	/** 提交异步线程,计算内参 */
	QFuture<QList<cv::Mat>> future = QtConcurrent::run([=]()
	{
		emit signal_loading(true);

		cv::Mat camMat;
		cv::Mat distCoeff;
		cv::Mat error;
		std::vector<cv::Mat> vImg = m_pSrcImgViewer->getAllMat().toVector().toStdVector();
		CalibBoardInfo boardInfo(CalibBoardType(listBoardInfo[3].toInt()), cv::Size(listBoardInfo[0].toInt(), listBoardInfo[1].toInt()), listBoardInfo[2].toInt());

		QList<cv::Mat> result;
		if (m_nCurAlgo == 0)
		{
			if (CameraCalib_OpenCV::calibInter(camMat, distCoeff, vImg, boardInfo))
			{
				result = { camMat,distCoeff };
			}
		}
		else if (m_nCurAlgo == 1)
		{
			
		}

		return result;
	});

	/** 拿到异步线程结果 */
	QFutureWatcher<QList<cv::Mat>>* pFutureWatch = new QFutureWatcher<QList<cv::Mat>>();
	connect(pFutureWatch, &QFutureWatcher<QList<cv::Mat>>::finished, [=]()
	{
		emit signal_loading(false);

		auto result = future.result();
		if (result.isEmpty())
		{
			doReport(this, lxReportLevel::CRITICAL, em_Inter_CalibFailed);
		}
		else
		{
			MatrixDisplay* matDisp = new MatrixDisplay;
			matDisp->setAttribute(Qt::WA_DeleteOnClose);
			matDisp->setWindowTitle("相机内参标定结果");
			if(m_nCurAlgo == 0)
				matDisp->showResult({ result[0],result[1] }, { "相机内参(3x3矩阵,fx fy u0 v0)","畸变系数(k1 k2 p1 p2 k3)" });
			else 
				matDisp->showResult({ result[0],result[1] ,result[2]}, { "相机内参(3x3矩阵,fx fy u0 v0)","畸变系数(k1 k2 p1 p2 k3)","重映射误差(一般要<0.1)" });

			/** 保存内参文件到桌面 */
			QString sDesktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
			QString sDirPath = sDesktopPath + "/Calib_Result/" + QDate::currentDate().toString("yyyy-MM-dd");

			QDir dir;
			dir.mkpath(sDirPath);

			saveInterParamToFile(sDirPath.toStdString() + "/camera_intr_param.yaml", result[0], result[1]);
		}

		// free memmory
		pFutureWatch->deleteLater();
	});
	pFutureWatch->setFuture(future);
}
void IntrinsicWidget::slot_customContextMenu(const QPoint &point)
{
	QMenu menu;

	QAction *pActClear = menu.addAction("清空图片");
	QAction *pActSaveOrigin = menu.addAction("保存原始图");
	QAction *pActSaveCorner = menu.addAction("保存角点图");

	connect(pActClear, &QAction::triggered, this, &IntrinsicWidget::slot_clear_img);
	connect(pActSaveOrigin, &QAction::triggered, this, &IntrinsicWidget::slot_save_originImg);
	connect(pActSaveCorner, &QAction::triggered, this, &IntrinsicWidget::slot_save_cornerImg);

	/** action使能 */
	bool empty = m_pSrcImgViewer->isEmpty();
	pActClear->setEnabled(!empty);
	pActSaveOrigin->setEnabled(!empty);
	pActSaveCorner->setEnabled(!empty);

	/** 是否在右键具体的picture widget */
	m_pCurPicture = nullptr;
	if(m_pCurPicture = qobject_cast<PictureWidget*>(childAt(point)))
	{
		/** 菜单栏分割线 */
		menu.addSeparator();

		QAction *pActDelThis = menu.addAction("删除该帧");
		connect(pActDelThis, &QAction::triggered, this, &IntrinsicWidget::slot_del_thisImg);
	}

	menu.exec(this->mapToGlobal(point));
}

void IntrinsicWidget::slot_clear_img()
{
	/** 同步清空图片 */
	m_pSrcImgViewer->clear();
	m_pCornerImgViewer->clear();
}

void IntrinsicWidget::slot_save_originImg()
{
	saveMatToDir(m_pSrcImgViewer->getAllImgData());
}

void IntrinsicWidget::slot_save_cornerImg()
{
	saveMatToDir(m_pCornerImgViewer->getAllImgData());
}

void IntrinsicWidget::slot_del_thisImg()
{
	if (!m_pCurPicture) return;

	m_pSrcImgViewer->remove(m_pCurPicture->getIndex());
	m_pCornerImgViewer->remove(m_pCurPicture->getIndex());
}

ExtrinsicWidget::ExtrinsicWidget(QWidget* parent /*= nullptr*/)
	:AbstractCalibWidget(parent)
{
	addLeftSubWidget();
	addMidSubWidget();
	addRightSubWidget();

	setSizes({ 1000,2000,2000 });

	/** 使用定时器 定时更新界面 */
	m_pUpdateUiTimer = new QTimer(this);
	connect(m_pUpdateUiTimer, &QTimer::timeout, [&]() {
		if (!m_tMatQueue.isEmpty())
		{
			auto result = m_tMatQueue.dequeue();
			m_pSrcImgViewer->pushNewMat({ result.listMat[0] }, { result.xyz }, { result.orient });
			m_pCornerImgViewer->pushNewMat({ result.listMat[1] }, { result.xyz }, { result.orient });
		}
	});
	m_pUpdateUiTimer->start(100);

	/**右键菜单栏设置*/
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &ExtrinsicWidget::customContextMenuRequested, this, &ExtrinsicWidget::slot_customContextMenu);
}

ExtrinsicWidget::~ExtrinsicWidget()
{

}

bool ExtrinsicWidget::eventFilter(QObject *watched, QEvent *event)
{


		if (watched == m_pExterRobotPose)
		{
			if (event->type() == QEvent::MouseButtonDblClick)
			{
				m_pExterRobotPose->setText(QFileDialog::getOpenFileName(this, "请选择机械臂拍照文件"));
				return true;
			}
		}
		else if (watched == m_pExterInterFile)
		{
			if (event->type() == QEvent::MouseButtonDblClick)
			{
				m_pExterInterFile->setText(QFileDialog::getOpenFileName(this, "请选择相机内参文件"));
				return true;
			}
		}
	

	return AbstractCalibWidget::eventFilter(watched, event);
}

QWidget* ExtrinsicWidget::leftSubWidget()
{
	/** control panel box */
	QGroupBox* ctrlPanel = new QGroupBox;
	QFormLayout* ctrlLayout = new QFormLayout(ctrlPanel);

	QList<QString> listCtrlLabel = { "①","②","③","④","⑤","⑥","⑦","⑧","⑨","⑩" };
	m_pCalibBoard = new QComboBox;
	m_pCalibBoard->addItems(g_listBoardType);

	/** add to ctrl layout */
	m_pHandEyeType = new QComboBox; m_pHandEyeType->addItems({ "眼在手上","眼在手外" });
	m_pExterRobotPose = new QLineEdit; m_pExterRobotPose->setPlaceholderText("鼠标双击选择机械臂拍照文件");
	m_pExterInterFile = new QLineEdit; m_pExterInterFile->setPlaceholderText("鼠标双击选择相机内参文件");
	
	QHBoxLayout* hLayout = new QHBoxLayout;
	m_pViewImgBtn = new QPushButton("查看图片");
	QPushButton* calibBtn = new QPushButton("标定");
	hLayout->addWidget(m_pViewImgBtn);
	hLayout->addWidget(calibBtn);
	
	ctrlLayout->addRow(listCtrlLabel[0], m_pCalibBoard);
	ctrlLayout->addRow(listCtrlLabel[2], m_pHandEyeType);
	ctrlLayout->addRow(listCtrlLabel[3], m_pExterRobotPose);
	ctrlLayout->addRow(listCtrlLabel[4], m_pExterInterFile);
	ctrlLayout->addRow(listCtrlLabel[5], hLayout);
	
	/** event filter */
	m_pExterRobotPose->installEventFilter(this);
	m_pExterInterFile->installEventFilter(this);

	/** signal slot */
	connect(m_pViewImgBtn, &QPushButton::clicked, this, &ExtrinsicWidget::slot_btnExterViewImg);
	connect(calibBtn, &QPushButton::clicked, this, &ExtrinsicWidget::slot_btnExterCalib);

	return ctrlPanel;
}

QWidget* ExtrinsicWidget::midSubWidget()
{
	m_pSrcImgViewer = new ImageFlowViewer(QSize(170, 170));
	return m_pSrcImgViewer;
}

QWidget* ExtrinsicWidget::rightSubWidget()
{
	m_pCornerImgViewer = new ImageFlowViewer(QSize(170, 170));
	return m_pCornerImgViewer;
}

void ExtrinsicWidget::extrFindCorner(QList<cv::Mat>& allMat, QList<std::vector<double>> allXyz, QList<std::vector<double>> allOrient)
{
	if (allMat.size() == 0) return;

	/** 解析标定板类型 */
	auto listBoardInfo = m_pCalibBoard->currentText().split("x");
	if (listBoardInfo.size() < BOARD_INFO_FIELD_NUM)
		return;

	/** 提交异步线程 */
	QFuture<QMap<int, QList<cv::Mat>>> future = QtConcurrent::run([=]()
	{
		QMap<int, QList<cv::Mat>> resultMap;

		for (int i = 0; i < allMat.size(); i++)
		{
			cv::Mat imgCornerMat;
			allMat[i].copyTo(imgCornerMat);
			CalibBoardInfo boardInfo(CalibBoardType(listBoardInfo[3].toInt()), cv::Size(listBoardInfo[0].toInt(), listBoardInfo[1].toInt()), listBoardInfo[2].toDouble());

			if (m_nCurAlgo == 0)
			{
				if (CameraCalib_OpenCV::drawCorners(imgCornerMat, boardInfo))
				{
					resultMap.insert(i, { allMat[i],imgCornerMat });
				}
			}
			else if (m_nCurAlgo == 1)
			{
				
			}
		}

		return resultMap;
	});

	/** 拿到异步线程结果,后不直接操作UI,使用定时器定时处理 */
	QFutureWatcher<QMap<int, QList<cv::Mat>>>* pFutureWatch = new QFutureWatcher<QMap<int, QList<cv::Mat>>>();
	connect(pFutureWatch, &QFutureWatcher<QMap<int, QList<cv::Mat>>>::finished, [=]()
	{
		auto resultMap = future.result();
		for (int i = 0; i < allMat.size(); i++)
		{
			if (resultMap.contains(i))
			{
				ImgAndPose data;
				data.listMat = resultMap.value(i);
				data.xyz = allXyz[i];
				data.orient = allOrient[i];
				m_tMatQueue.enqueue(data);
			}
		}

		/** 异步计算完毕 */
		emit signal_loading(false);

		if (resultMap.size() != allMat.size())
		{
			doReport(this, lxReportLevel::WARN, lxReportCode::em_FindCornerFailed);
		}

		// free memmory
		pFutureWatch->deleteLater();
	});
	pFutureWatch->setFuture(future);
}

void ExtrinsicWidget::slot_btnExterViewImg()
{
	/** 获取所有的图片 及 机械臂姿态 */
	QString file = m_pExterRobotPose->text();
	if (!QFileInfo::exists(file))
	{
		doReport(this, lxReportLevel::WARN, lxReportCode::em_Exter_RobotPoseNotFound);
		return;
	}
	QFile f(file);
	if (!f.open(QFile::ReadOnly))
		return;

	/** 解析该文件 */  
	QJsonParseError err;
	QJsonDocument jDoc = QJsonDocument::fromJson(f.readAll(), &err);
	if (err.error != QJsonParseError::NoError)
	{
		doReport(this, lxReportLevel::CRITICAL, lxReportCode::em_Exter_RobotPoseParseError);
		return;
	}

	auto jRootArr = jDoc.array();
	if (jRootArr.empty())
	{
		doReport(this, lxReportLevel::CRITICAL, lxReportCode::em_Exter_RobotPoseParseError);
		return;
	}

	/** 获取机械臂拍照文件中的所有图片及其对应机械臂姿态 */
	QList<cv::Mat> listMat;
	QList<std::vector<double>> listXyz;
	QList<std::vector<double>> listOrient;
	for (auto arr : jRootArr)
	{
		auto obj = arr.toObject();
		
		// img_path 
		QString img_path = obj["img_path"].toString();
		img_path = QDir::cleanPath(QFileInfo(file).absolutePath() + QDir::separator() + img_path);

		if (!QFileInfo::exists(img_path))
		{
			doReport(this, lxReportLevel::WARN, lxReportCode::em_Exter_RobotPoseParseError);
			return;
		}
		QFile imgFile(img_path);
		if (imgFile.open(QIODevice::ReadOnly))
		{
			QByteArray imgBA = imgFile.readAll();
			std::vector<uchar> vImgData(imgBA.data(), imgBA.data() + imgBA.size());

			listMat.push_back(cv::imdecode(vImgData, cv::IMREAD_COLOR));
		}

		// xyz 
		auto xyz = obj["xyz"].toArray();
		if (xyz.size() != 3)
			return;
		listXyz.push_back({ xyz[0].toDouble() / 1000.,xyz[1].toDouble() / 1000.,xyz[2].toDouble() / 1000. });

		// orient 
		auto orient = obj["orient"].toArray();
		if (orient.size() == 4)	// quat 
			listOrient.push_back({ orient[0].toDouble(), orient[1].toDouble(),orient[2].toDouble(),orient[3].toDouble() });
		else if (orient.size() == 3)// euler 
			listOrient.push_back({ orient[0].toDouble() / DEGREE2RAD,orient[1].toDouble() / DEGREE2RAD, orient[2].toDouble() / DEGREE2RAD });
		else
			return;
	}

	/** 开始异步计算 */
	emit signal_loading(true);
	extrFindCorner(listMat,listXyz,listOrient);
}

void ExtrinsicWidget::slot_btnExterCalib()
{
	/** 解析标定板类型 */
	auto listBoardInfo = m_pCalibBoard->currentText().split("x");
	if (listBoardInfo.size() < BOARD_INFO_FIELD_NUM)
		return;

	/** 获取内参矩阵和畸变系数 */
	QString interParamFile = m_pExterInterFile->text();
	if (!QFileInfo::exists(interParamFile))
	{
		doReport(this, lxReportLevel::WARN, lxReportCode::em_Exter_CamInterFileNotFound);
		return;
	}

	cv::Mat cameraMat;
	cv::Mat distCoeff;
	cv::FileStorage fs(interParamFile.toStdString(), cv::FileStorage::READ);
	fs["camera_matrix"] >> cameraMat;
	fs["dist_coeffs"] >> distCoeff;
	fs.release();

	/** 图片为空 */
	if (m_pSrcImgViewer->isEmpty())
	{
		doReport(this, lxReportLevel::CRITICAL, em_Inter_CalibFailed);
		return;
	}

	/** 提交异步线程,计算外参 */
	QFuture<QList<cv::Mat>> future = QtConcurrent::run([=]()
	{
		emit signal_loading(true);

		QList<cv::Mat> result;
		std::vector<RobotCalibFrame> vInfo;
		for (auto pPicture : m_pSrcImgViewer->getAllPictureWidget())
		{
			RobotCalibFrame frame;

			frame.m_tImg = pPicture->getMat();

			std::vector<double> pos;
			std::vector<double> orient;
			pPicture->getRobotPose(pos,orient);

			Eigen::Matrix3d matrix;
			if (orient.size() == 4)// quat 
				matrix = quat2RotateMatrix({ orient[0],orient[1],orient[2],orient[3]});
			else if (orient.size() == 3)// euler 
				matrix = quat2RotateMatrix({ orient[0],orient[1],orient[2] });

			Eigen::Matrix4d mat = Eigen::Matrix4d::Identity();
			mat.block(0, 0, 3, 3) << matrix;
			mat.block(0, 3, 3, 1) << pos[0], pos[1], pos[2];

			cv::Mat R4x4;
			cv::eigen2cv(mat, R4x4);
			frame.m_tPos = R4x4;

			vInfo.push_back(frame);
		}

		CalibBoardInfo boardInfo(CalibBoardType(listBoardInfo[3].toInt()), cv::Size(listBoardInfo[0].toInt(), listBoardInfo[1].toInt()), listBoardInfo[2].toInt());

		cv::Mat cameraMat_ = cameraMat;
		cv::Mat distCoeff_ = distCoeff;
		cv::Mat error;

		cv::Mat extrMat;
		if (m_nCurAlgo == 0)
		{
			CameraCalib_OpenCV::calibExter(extrMat, vInfo, cameraMat_, distCoeff_, boardInfo, HandEyeType(m_pHandEyeType->currentIndex()));
			result = { extrMat };
		}
		else if (m_nCurAlgo == 1)
		{
			
		}

		return result;
	});

	/** 拿到异步线程结果 */
	QFutureWatcher<QList<cv::Mat>>* pFutureWatch = new QFutureWatcher<QList<cv::Mat>>();
	connect(pFutureWatch, &QFutureWatcher<QList<cv::Mat>>::finished, [=]()
	{
		emit signal_loading(false);

		auto result = future.result();

		if (result.size() == 0)
		{
			doReport(this, lxReportLevel::CRITICAL, em_Inter_CalibFailed);
		}
		else
		{
			MatrixDisplay* matDisp = new MatrixDisplay;
			matDisp->setAttribute(Qt::WA_DeleteOnClose);
			matDisp->setWindowTitle("相机外参标定结果");
			if (m_nCurAlgo == 0)
				matDisp->showResult({ result[0] }, { "相机外参(4x4矩阵)" });
			else
				matDisp->showResult({ result[0],result[1] }, { "相机外参(4x4矩阵)","长尺寸链反算误差(一般<5)" });

			/** 保存外参文件到桌面 */
			QString sDesktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
			QString sDirPath = sDesktopPath + "/Calib_Result/" + QDate::currentDate().toString("yyyy-MM-dd");

			QDir dir;
			dir.mkpath(sDirPath);

			saveExternalParamToFile(sDirPath.toStdString() + "/camera_exter_param.yaml", result[0]);
		}

		// free memmory
		pFutureWatch->deleteLater();
	});

	pFutureWatch->setFuture(future);
}


void ExtrinsicWidget::slot_customContextMenu(const QPoint &point)
{
	QMenu menu;

	QAction *pActClear = menu.addAction("清空图片");
	QAction *pActSaveOrigin = menu.addAction("保存原始图");
	QAction *pActSaveCorner = menu.addAction("保存角点图");

	connect(pActClear, &QAction::triggered, this, &ExtrinsicWidget::slot_clear_img);
	connect(pActSaveOrigin, &QAction::triggered, this, &ExtrinsicWidget::slot_save_originImg);
	connect(pActSaveCorner, &QAction::triggered, this, &ExtrinsicWidget::slot_save_cornerImg);

	/** action使能 */
	bool empty = m_pSrcImgViewer->isEmpty();
	pActClear->setEnabled(!empty);
	pActSaveOrigin->setEnabled(!empty);
	pActSaveCorner->setEnabled(!empty);

	/** 是否在右键具体的picture widget */
	m_pCurPicture = nullptr;
	if (m_pCurPicture = qobject_cast<PictureWidget*>(childAt(point)))
	{
		/** 菜单栏分割线 */
		menu.addSeparator();

		QAction *pActDelThis = menu.addAction("删除该帧");
		connect(pActDelThis, &QAction::triggered, this, &ExtrinsicWidget::slot_del_thisImg);
	}

	menu.exec(this->mapToGlobal(point));
}

void ExtrinsicWidget::slot_clear_img()
{
	/** 同步清空图片 */
	m_pSrcImgViewer->clear();
	m_pCornerImgViewer->clear();
}

void ExtrinsicWidget::slot_save_originImg()
{
	saveMatToDir(m_pSrcImgViewer->getAllImgData());
}

void ExtrinsicWidget::slot_save_cornerImg()
{
	saveMatToDir(m_pCornerImgViewer->getAllImgData());
}

void ExtrinsicWidget::slot_del_thisImg()
{
	if (!m_pCurPicture) return;

	m_pSrcImgViewer->remove(m_pCurPicture->getIndex());
	m_pCornerImgViewer->remove(m_pCurPicture->getIndex());
}

StereoWidget::StereoWidget(QWidget* parent /*= nullptr*/)
	:AbstractCalibWidget(parent)
{
	addLeftSubWidget();
	addMidSubWidget();
	addRightSubWidget();

	setSizes({ 1000,2000,2000 });
}

StereoWidget::~StereoWidget()
{

}

QWidget* StereoWidget::leftSubWidget()
{
	return new QWidget;

}

QWidget* StereoWidget::midSubWidget()
{
	return new QWidget;

}

QWidget* StereoWidget::rightSubWidget()
{
	return new QWidget;

}

class MainWindow::Implui
{

public:
	Implui(QMainWindow* w)
	{
		m_pMW = nullptr;
		m_pMW = w;
	}
	/** 窗口初始化 */
	void init()
	{
		if (!m_pMW) return;

		/** 初始化主窗口 */
		m_pMW->setWindowTitle("相机标定软件");
		m_pMW->resize(1200, 600);

		/** 初始化StackWidget */
		m_pStackWidget = new QStackedWidget(m_pMW);
		m_pIntrWidget = new IntrinsicWidget;
		m_pExtrWidget = new ExtrinsicWidget;
		m_pStereoWidget = new StereoWidget;
		QLabel* lb = new QLabel("未完待续..."); 
		lb->setAlignment(Qt::AlignCenter);

		m_pStackWidget->addWidget(m_pIntrWidget);
		m_pStackWidget->addWidget(m_pExtrWidget);
		m_pStackWidget->addWidget(lb); //m_pStackWidget->addWidget(m_pStereoWidget);

		m_pMW->setCentralWidget(m_pStackWidget);

		/** loading 效果gif */
		m_pLoadingGif = new QLabel(m_pStackWidget);
		m_pLoadingMovie = new QMovie(":./images/loading.gif");

		/** 启停一下,为了能正确计算gifSize */
		m_pLoadingMovie->start();
		m_pLoadingMovie->stop();

		QSize gifSize = m_pLoadingMovie->currentPixmap().size();
		m_pLoadingGif->setStyleSheet("background: transparent;");
		m_pLoadingGif->setGeometry(0, 0, gifSize.width(), gifSize.height());
		m_pLoadingGif->setMovie(m_pLoadingMovie);
		
		stopLoading();
	}
	
	/** 菜单栏初始化 */
	void initMenuBar()
	{
		if (!m_pMW) return;

		QMenu* file = m_pMW->menuBar()->addMenu("File");
		//file->addAction("打开文件");

		QMenu* edit = m_pMW->menuBar()->addMenu("Edit");
		//edit->addAction("剪切");

	}
	
	/** 工具栏(侧边栏)初始化 */
	void initToolBar()
	{
		if (!m_pMW) return;

		/** Part1.0 侧边栏 */
		QToolBar* sideBar = new QToolBar(m_pMW);
		QAction* intrAct = new QAction(QIcon(":./images/intrinsic.png"), "相机内参");
		QAction* extrAct = new QAction(QIcon(":./images/extrinsic.png"), "相机外参");
		QAction* stereoAct = new QAction(QIcon(":./images/stereo.png"), "相机双目");
		sideBar->setObjectName("sideBar");
		sideBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
		sideBar->setMovable(false);
		m_pMW->addToolBar(Qt::LeftToolBarArea, sideBar);

		/** 使用QActionGroup包含所有的QAction,主要为了单选效果 */
		m_pSideBarAction = new QActionGroup(m_pMW);
		m_pSideBarAction->addAction(intrAct);
		m_pSideBarAction->addAction(extrAct);
		m_pSideBarAction->addAction(stereoAct);
		for (auto& aciton : m_pSideBarAction->actions())
		{
			aciton->setCheckable(true);
		}
		sideBar->addActions(m_pSideBarAction->actions());
		QWidget *vSpacer = new QWidget;
		vSpacer->setStyleSheet("background: transparent;");
		vSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		sideBar->addWidget(vSpacer);

		/** 当前算法 */
		m_pAlgoWidget = new QWidget;
		m_pAlgoWidget->setObjectName("algo");
		QVBoxLayout* algoLayout = new QVBoxLayout(m_pAlgoWidget);
		QLabel* algoLabel = new QLabel("当前算法");
		m_pCurAlgo = new QLabel("OpenCV");
		m_pCurAlgo->setObjectName("curAlgo");
		algoLayout->addWidget(algoLabel);
		algoLayout->addWidget(m_pCurAlgo);
		m_pAlgoWidget->installEventFilter(m_pMW);

		sideBar->addWidget(m_pAlgoWidget);

		/** 算法面板 */
		m_pAlgoPanel = new QWidget(m_pMW);
		m_pAlgoPanel->setFixedSize(300, 150);
		m_pAlgoPanel->setObjectName("algoPanel");
		m_pAlgoPanel->installEventFilter(m_pMW);
		QVBoxLayout* panelLayout = new QVBoxLayout(m_pAlgoPanel);
		panelLayout->setMargin(0);
		panelLayout->setSpacing(0);
		QLabel* algoListDesc = new QLabel("OpenCV使用开源标定算法,图片3张即可\XXX-Inner为XXX内部自研算法,图片需>=4张且需要插入加密狗");
		m_pAlgoList = new QListWidget;
		m_pAlgoList->addItems({ "OpenCV","XXX-Inner" });
		panelLayout->addWidget(algoListDesc);
		panelLayout->addWidget(m_pAlgoList);
		m_pAlgoPanel->hide();

		connect(m_pSideBarAction, &QActionGroup::triggered, [=](QAction* action) {slot_sideBar_changed(action); });
		connect(m_pAlgoList, &QListWidget::currentTextChanged, [=](const QString& text) {slot_algo_changed(text); });

		/** 默认选中第一个侧边栏action */
		intrAct->setChecked(true);
	}
	
	/** 状态栏初始化 */
	void initStatusBar()
	{
		if (!m_pMW) return;
		
		m_pMW->statusBar();
	}
	
	/** 调整加载gif的位置 */
	void adjustLoading()
	{
		m_pLoadingGif->move(m_pStackWidget->rect().center() - m_pLoadingGif->rect().center());
	}

	/** 调整算法面板的位置 */
	void adjustAlgoPanel()
	{
		QPoint bottomLeft = m_pMW->centralWidget()->geometry().bottomLeft();
		m_pAlgoPanel->move(bottomLeft + QPoint(0, -m_pAlgoPanel->height()));
	}

	/** 开启loading效果 */
	void startLoading()
	{
		m_pLoadingGif->show();
		m_pLoadingGif->raise();
		m_pLoadingMovie->start();
	}
	
	/** 关闭loading效果 */
	void stopLoading()
	{
		m_pLoadingGif->hide();
		m_pLoadingMovie->stop();
	}
	
	/** 侧边栏发生变化时处理逻辑-匿名槽函数 */
	void slot_sideBar_changed(QAction* action)
	{
		int sideBarIdx = m_pSideBarAction->actions().indexOf(action);
		if (sideBarIdx < 0 || sideBarIdx > m_pSideBarAction->actions().size() - 1)
			return;

		m_pStackWidget->setCurrentIndex(sideBarIdx);
	}

	/** 算法库变化时处理逻辑-匿名槽函数 */
	void slot_algo_changed(const QString& text)
	{
		m_pCurAlgo->setText(text);

		int curAlgo = m_pAlgoList->currentRow();
		m_pIntrWidget->setAlgo(curAlgo);
		m_pExtrWidget->setAlgo(curAlgo);

		m_pAlgoPanel->hide();
	}

	/** 主窗口 */
	QMainWindow*			m_pMW;
	QActionGroup*			m_pSideBarAction;
	QStackedWidget*			m_pStackWidget;

	/** 标定页面 */
	IntrinsicWidget*		m_pIntrWidget;
	ExtrinsicWidget*		m_pExtrWidget;
	StereoWidget*			m_pStereoWidget;

	/** 加载gif相关 */
	QLabel*					m_pLoadingGif;
	QMovie*					m_pLoadingMovie;

	/** 当前标定算法 */
	QWidget*				m_pAlgoWidget;
	QLabel*					m_pCurAlgo;

	QWidget*				m_pAlgoPanel;
	QListWidget*			m_pAlgoList;
};

// lxCalibFast_MainWindow
MainWindow::MainWindow(QWidget *parent /*= nullptr*/)
	:QMainWindow(parent)
{
	initUi();
}

MainWindow::~MainWindow()
{
	//qDebug() << "~lxCalibFast_MainWindow";
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	if (implui)
	{
		implui->adjustLoading();
		implui->adjustAlgoPanel();
	}
	QMainWindow::resizeEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	/** 如果有new出来的单独窗口,qApp->quit()可以将其同主窗口一起关闭 */
	//qApp->quit();	
	QMainWindow::closeEvent(event);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == implui->m_pAlgoWidget)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			/** 切换显示 */
			if (!implui->m_pAlgoPanel->isHidden())
			{
				implui->m_pAlgoPanel->hide();
				return true;
			}

			/** 寻找当前算法的索引 */
			int curIdx = -1;
			QListWidget *list = implui->m_pAlgoList;
			for (int i = 0; i < list->count(); i++)
			{
				if (list->item(i)->text() == implui->m_pCurAlgo->text())
				{
					curIdx = i;
					break;
				}
			}
			if (curIdx == -1) 
				return true;

			/** 设置当前算法高亮 */
			implui->m_pAlgoList->setCurrentRow(curIdx);
			implui->m_pAlgoList->setFocus();

			QPoint bottomLeft = this->centralWidget()->geometry().bottomLeft();

			implui->m_pAlgoPanel->move(bottomLeft + QPoint(0,-implui->m_pAlgoPanel->height()));
			implui->m_pAlgoPanel->show();
			implui->m_pAlgoPanel->raise();
			return true;
		}
	}

	return QMainWindow::eventFilter(watched, event);
}

void MainWindow::initUi()
{
	/** 初始化implui */
	implui = new Implui(this);
	
	implui->init();
	implui->initMenuBar();
	implui->initToolBar();
	implui->initStatusBar();

	connect(implui->m_pIntrWidget, &AbstractCalibWidget::signal_loading, this, &MainWindow::slot_loading);
	connect(implui->m_pExtrWidget, &AbstractCalibWidget::signal_loading, this, &MainWindow::slot_loading);
	connect(implui->m_pStereoWidget, &AbstractCalibWidget::signal_loading, this, &MainWindow::slot_loading);
}

void MainWindow::slot_loading(bool bWorking)
{
	setEnabled(!bWorking);

	if (bWorking)
	{
		implui->startLoading();
	}
	else
	{
		implui->stopLoading();
	}
}

//bool lxCalibFast_MainWindow::eventFilter(QObject *watched, QEvent *event)
//{m_pHandEyeType
//if (watched == m_pStereoImageDir1)
//	{
//		if (event->type() == QEvent::MouseButtonDblClick)
//		{
//			m_pStereoImageDir1->setText(QFileDialog::getExistingDirectory(this, "请选择相机1的照片文件夹"));
//			return true;
//		}
//	}
//	else if (watched == m_pStereoImageDir2)
//	{
//		if (event->type() == QEvent::MouseButtonDblClick)
//		{
//			m_pStereoImageDir2->setText(QFileDialog::getExistingDirectory(this, "请选择相机2的照片文件夹"));
//			return true;
//		}
//	}
//
//	return QMainWindow::eventFilter(watched, event);
//}
//void lxCalibFast_MainWindow::slot_btnStereoViewImg1()
//{
//	qDebug() << "slot_btnStereoViewImg1";
//
//}
//
//void lxCalibFast_MainWindow::slot_btnStereoViewImg2()
//{
//	qDebug() << "slot_btnStereoViewImg2";
//
//}
//
//void lxCalibFast_MainWindow::slot_btnStereoCalib()
//{
//	qDebug() << "slot_btnStereoCalib";
//}
//void lxCalibFast_MainWindow::initCtrlPanelUi()
//{
//	// control panel box 
//	QGroupBox* ctrlPanel = new QGroupBox;
//	QFormLayout* ctrlLayout = new QFormLayout(ctrlPanel);
//
//	// common element 
//	QList<QString> listCtrlLabel = {"①","②","③","④","⑤","⑥","⑦","⑧","⑨","⑩"};
//	m_pCalibBoard = new QComboBox;
//	m_pCalibBoard->addItems(g_listBoardType);
//	m_pOnline = new QCheckBox("是否在线标定");
//	QPushButton* calibBtn = new QPushButton("标定");
//
//	// add to ctrl layout 
//	ctrlLayout->addRow(listCtrlLabel[0], m_pCalibBoard);
//	ctrlLayout->addRow(listCtrlLabel[1], m_pOnline);
//	else if (m_nWorkType == 2)
//	{
//		m_pStereoImageDir1 = new QLineEdit; m_pStereoImageDir1->setPlaceholderText("双击选择相机1标定图片文件夹");
//		m_pStereoImageDir2 = new QLineEdit; m_pStereoImageDir2->setPlaceholderText("双击选择相机2标定图片文件夹");
//
//		QHBoxLayout* hLayout = new QHBoxLayout;
//		QPushButton* viewImgBtn1 = new QPushButton("查看相机1图片");
//		QPushButton* viewImgBtn2 = new QPushButton("查看相机2图片");
//		QPushButton* calibBtn = new QPushButton("标定");
//		hLayout->addWidget(viewImgBtn1);
//		hLayout->addWidget(viewImgBtn2);
//		hLayout->addWidget(calibBtn);
//
//		ctrlLayout->addRow(listCtrlLabel[2], m_pStereoImageDir1);
//		ctrlLayout->addRow(listCtrlLabel[3], m_pStereoImageDir2);
//		ctrlLayout->addRow(listCtrlLabel[4], hLayout);
//
//		// signal slot
//		connect(viewImgBtn1, &QPushButton::clicked, this, &lxCalibFast_MainWindow::slot_btnStereoViewImg1);
//		connect(viewImgBtn2, &QPushButton::clicked, this, &lxCalibFast_MainWindow::slot_btnStereoViewImg2);
//		connect(calibBtn, &QPushButton::clicked, this, &lxCalibFast_MainWindow::slot_btnStereoCalib);
//
//		// event filter 
//		m_pStereoImageDir1->installEventFilter(this);
//		m_pStereoImageDir2->installEventFilter(this);
//	}
//
//	QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
//	ctrlLayout->addItem(verticalSpacer);
//	ctrlPanel->setLayout(ctrlLayout);
//
//	m_pSplitter->addWidget(ctrlPanel);
//
//	//signal slot 
//	connect(m_pOnline, &QCheckBox::stateChanged, this, &lxCalibFast_MainWindow::slot_onlineStateChanged);
//
//}
//
//void lxCalibFast_MainWindow::initSrcImgViewerUi()
//{
//	QWidget* widget = new QWidget;
//	QVBoxLayout* vLayout = new QVBoxLayout(widget);
//	else if (m_nWorkType == 2)
//	{
//		QLabel* label1 = new QLabel("源图片1");
//		QLabel* label2 = new QLabel("源图片2");
//
//		QSplitter* innerSplitter = new QSplitter;
//		innerSplitter->setHandleWidth(5);
//		innerSplitter->setChildrenCollapsible(true);
//		innerSplitter->setOrientation(Qt::Vertical);
//		vLayout->addWidget(innerSplitter);
//
//		QWidget* upPanel = new QWidget;
//		QWidget* downPanel = new QWidget;
//		QVBoxLayout* vLayoutUp = new QVBoxLayout(upPanel);
//		QVBoxLayout* vLayoutDown = new QVBoxLayout(downPanel);
//		upPanel->setLayout(vLayoutUp);
//		downPanel->setLayout(vLayoutDown);
//
//		// add widget to inner splitter
//		m_pSrcImgViewer = new lxQImageFlowViewer(QSize(170, 170));
//		vLayoutUp->addWidget(label1);
//		vLayoutUp->addWidget(m_pSrcImgViewer);
//
//		m_pSrcImgViewer2 = new lxQImageFlowViewer(QSize(170, 170));
//		vLayoutDown->addWidget(label2);
//		vLayoutDown->addWidget(m_pSrcImgViewer2);
//
//		innerSplitter->addWidget(upPanel);
//		innerSplitter->addWidget(downPanel);
//	}
//
//	widget->setLayout(vLayout);
//	m_pSplitter->addWidget(widget);
//}
//
//void lxCalibFast_MainWindow::initCornerImgViewerUi()
//{
//	QWidget* widget = new QWidget;
//	QVBoxLayout* vLayout = new QVBoxLayout(widget);
//	else if (m_nWorkType == 2)
//	{
//		QLabel* label1 = new QLabel("角点图片1");
//		QLabel* label2 = new QLabel("角点图片2");
//
//		QSplitter* innerSplitter = new QSplitter;
//		innerSplitter->setHandleWidth(5);
//		innerSplitter->setChildrenCollapsible(true);
//		innerSplitter->setOrientation(Qt::Vertical);
//		vLayout->addWidget(innerSplitter);
//
//		QWidget* upPanel = new QWidget;
//		QWidget* downPanel = new QWidget;
//		QVBoxLayout* vLayoutUp = new QVBoxLayout(upPanel);
//		QVBoxLayout* vLayoutDown = new QVBoxLayout(downPanel);
//		upPanel->setLayout(vLayoutUp);
//		downPanel->setLayout(vLayoutDown);
//
//		// add widget to inner splitter
//		m_pCornerImgViewer = new lxQImageFlowViewer(QSize(170, 170));
//		vLayoutUp->addWidget(label1);
//		vLayoutUp->addWidget(m_pCornerImgViewer);
//
//		m_pCornerImgViewer2 = new lxQImageFlowViewer(QSize(170, 170));
//		vLayoutDown->addWidget(label2);
//		vLayoutDown->addWidget(m_pCornerImgViewer2);
//
//		innerSplitter->addWidget(upPanel);
//		innerSplitter->addWidget(downPanel);
//	}
//
//	widget->setLayout(vLayout);
//	m_pSplitter->addWidget(widget);
//}
