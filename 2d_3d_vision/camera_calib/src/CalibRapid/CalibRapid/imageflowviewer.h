#pragma once

#include "opencv2/opencv.hpp"

#include <QLabel>
#include <QDialog>

class QGraphicsView;
class QGraphicsScene;
class QMenu;
class QAction;

class PictureProcessPanel :public QDialog
{
	Q_OBJECT
public:
	PictureProcessPanel(QPixmap pixmap, QWidget* parent = nullptr);

protected:
	bool eventFilter(QObject *watched, QEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

private:
	void scaleView(qreal scaleFactor);

	QGraphicsView *  m_pView;
	QGraphicsScene*  m_pScene;
};


class PictureWidget :public QLabel
{
	Q_OBJECT
public:
	PictureWidget(QSize pictureSize, cv::Mat srcMat, int imgIdx, QWidget* parent = nullptr);

	cv::Mat getMat();
	std::vector<uchar> getImgData();

	void	setIndex(int idx);
	int		getIndex();

	void setRobotPose(std::vector<double> pos, std::vector<double> orient);
	void getRobotPose(std::vector<double>& pos, std::vector<double>& orient);

protected:
	void paintEvent(QPaintEvent * event) override;

private:
	int								m_nImgIdx;			///< 当前图片的索引(在viewer中)
	std::vector<uchar>				m_vImgData;			///< 一张图片数据,通过imencode/imdecode来转换
	std::vector<double>				m_vPos;				///< 该帧图片对应机械臂的位置
	std::vector<double>				m_vOrient;			///< 该帧图片对应机械臂的姿态
};

/** @brief		流式布局图片查看器,支持通过文件夹名、通过QPixmap数据等更新
	@details
*/
class FlowLayout;
class ImageFlowViewer : public QWidget
{
	Q_OBJECT

public:
	ImageFlowViewer(QSize pictureSize, QWidget *parent = nullptr);

	int  count();
	bool isEmpty();
	void clear();
	void remove(int idx);

	void pushNewMat(QList<cv::Mat> listMat);
	void pushNewMat(QList<cv::Mat> listMat, std::vector<std::vector<double>> vvPos, std::vector<std::vector<double>> vvOrient);

	QList<cv::Mat>				getAllMat();
	QList<std::vector<uchar>>	getAllImgData();
	QList<PictureWidget*>		getAllPictureWidget();

protected:
	void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
	void adjustPictureWidgetIndex();

	QWidget*				m_pChildWidget;		///< real container

	QSize					m_tPictureSize;		///< 图片的缩略图大小 
	FlowLayout*			m_pFlowLayout;		///< 流式布局
	QList<PictureWidget*>	m_listPictureWidget;///< 图片(含图片数据和位姿)
};
