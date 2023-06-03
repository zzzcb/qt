#pragma once

#include "cameracalib_common.h"
#include "cameracalib.h"

#include <QDialog>
#include <QMainWindow>
#include <QQueue>

class QComboBox;
class QCheckBox;
class QHBoxLayout;
class QLineEdit;
class QSplitter;
class QTimer;

class PictureWidget;
class ImageFlowViewer;

/** @brief		矩阵结果展示
	@details
*/
class MatrixDisplay :public QDialog
{
	Q_OBJECT
public:
	MatrixDisplay(QWidget* parent = nullptr);

	void showResult(QList<cv::Mat> listMat, QList<QString> listMsg);

private:
	QHBoxLayout* m_pHLayout;
};

/** @brief		抽象统一标定页面基类,标定的界面分为左中右三部分,子类必须重写3个纯虚函数
	@details
*/
class AbstractCalibWidget :public QWidget
{
	Q_OBJECT
public:
	AbstractCalibWidget(QWidget* parent = nullptr);
	virtual ~AbstractCalibWidget();

	/** 添加面板 */
	void addLeftSubWidget();
	void addMidSubWidget();
	void addRightSubWidget();

	/** 设置各个部分的比例 */
	void setSizes(const QList<int>& sizes);

	/** 切换标定算法 */
	void setAlgo(int algoIdx);

protected:
	virtual QWidget* leftSubWidget() = 0;			///< 左侧部分,一般显示控制面板
	virtual QWidget* midSubWidget() = 0;			///< 中间部分,显示源图片

	virtual QWidget* rightSubWidget() = 0;			///< 右侧部分,显示角点图片
	int			m_nCurAlgo = 0;						///< 当前标定算法 0:OpenCV 

private:
	QSplitter*	m_pSplitter;						///< splitter 分割器

signals:
	void signal_loading(bool bWorking);				///< 用于显示、关闭加载效果
};

/** @brief		内参标定界面
	@details
*/
class IntrinsicWidget :public AbstractCalibWidget
{
	Q_OBJECT
public:
	IntrinsicWidget(QWidget* parent = nullptr);
	~IntrinsicWidget();
protected:
	bool eventFilter(QObject *watched, QEvent *event) override;
	
private:
	QWidget* leftSubWidget() override;
	QWidget* midSubWidget()override;
	QWidget* rightSubWidget()override;

	/** 异步查找角点,并将结果放入m_tMatQueue队列中 */
	void intrFindCorner(QList<cv::Mat>& allMat);

	/** 左侧控制元素 */
	QComboBox*				m_pCalibBoard;  
	QLineEdit*				m_pInterImageFiles;
	QPushButton*			m_pViewImgBtn;

	ImageFlowViewer*		m_pSrcImgViewer;
	ImageFlowViewer*		m_pCornerImgViewer;

	/** 定时器-用于逐步更新界面UI(避免一次更新过多导致界面卡顿) */
	QTimer*				   m_pUpdateUiTimer;
	QQueue<QList<cv::Mat>> m_tMatQueue;

	/** 当前右键的图片 */
	PictureWidget*			m_pCurPicture;

private slots:

	/** 查看图片 */
	void slot_btnInterViewImg();
	/** 进行内参标定 */
	void slot_btnInterCalib();
	/** 右键菜单栏 */
	void slot_customContextMenu(const QPoint &point);

	/** 清空图片(会同步清空源图和角点图) */
	void slot_clear_img();
	/** 保存源图 */
	void slot_save_originImg();
	/** 保存角点图 */
	void slot_save_cornerImg();
	/** 删除具体帧 */
	void slot_del_thisImg();
};

/** @brief		外参标定界面
	@details
*/
class ExtrinsicWidget :public AbstractCalibWidget
{
	Q_OBJECT
public:
	ExtrinsicWidget(QWidget* parent = nullptr);
	~ExtrinsicWidget();
protected:
	bool eventFilter(QObject *watched, QEvent *event) override;

private:
	QWidget* leftSubWidget() override;
	QWidget* midSubWidget()override;
	QWidget* rightSubWidget()override;
	
	/** 异步查找角点,并将结果放入m_tMatQueue队列中(且会将对应位姿放入) */
	void extrFindCorner(QList<cv::Mat>& allMat,QList<std::vector<double>> allXyz,QList<std::vector<double>> allOrient);

	/** 左侧控制元素 */
	QComboBox*					m_pCalibBoard;
	QComboBox*					m_pHandEyeType;
	QLineEdit*					m_pExterRobotPose;
	QLineEdit*					m_pExterInterFile;
	QPushButton*				m_pViewImgBtn;

	ImageFlowViewer*			m_pSrcImgViewer;
	ImageFlowViewer*			m_pCornerImgViewer;

	/** 定时器-用于逐步更新界面UI(避免一次更新过多导致界面卡顿) */
	struct ImgAndPose
	{
		QList<cv::Mat>			listMat;
		std::vector<double>		xyz;
		std::vector<double>		orient;
	};
	QTimer*						m_pUpdateUiTimer;
	QQueue<ImgAndPose>			m_tMatQueue;		

	/** 当前右键的图片 */
	PictureWidget*				m_pCurPicture;

private slots:
	/** 查看图片 */
	void slot_btnExterViewImg();
	/** 进行外参标定 */
	void slot_btnExterCalib();
	/** 右键菜单栏 */
	void slot_customContextMenu(const QPoint &point);

	/** 清空图片(会同步清空源图和角点图) */
	void slot_clear_img();
	/** 保存源图 */
	void slot_save_originImg();
	/** 保存角点图 */
	void slot_save_cornerImg();
	/** 删除具体帧 */
	void slot_del_thisImg();
};

/** @brief		双目标定界面(暂未实现)
	@details
*/
class StereoWidget :public AbstractCalibWidget
{
	Q_OBJECT
public:
	StereoWidget(QWidget* parent = nullptr);
	~StereoWidget();

private:
	QWidget* leftSubWidget() override;
	QWidget* midSubWidget()override;
	QWidget* rightSubWidget()override;
};

/** @brief		主窗口界面
	@details
*/
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

protected:
	void resizeEvent(QResizeEvent *event) override;
	void closeEvent(QCloseEvent *event) override;

	bool eventFilter(QObject *watched, QEvent *event) override;

private:
	class Implui;
	Implui* implui;

	void initUi();

private slots:
	/** 处理加载效果 */
	void slot_loading(bool bWorking);
};
