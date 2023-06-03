#pragma execution_character_set("utf-8")

#include "imageflowviewer.h"

#include "flowlayout.h"

#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QVector>
#include <QDir>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMenu>
#include <QFileDialog>

#include <QDebug>

QPixmap mat2QPixmap(const cv::Mat& mat)
{
	if (mat.empty())
	{
		return QPixmap();
	}

	QImage image;
	switch (mat.type())
	{
	case CV_8UC1:
	{
		image = QImage((const uchar*)(mat.data),
			mat.cols, mat.rows, mat.step,
			QImage::Format_Grayscale8);
		return QPixmap::fromImage(image.copy());
	}

	case CV_8UC3:
	{
		const uchar *pSrc = (const uchar*)mat.data;
		image = QImage(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return QPixmap::fromImage(image.rgbSwapped());
	}
	case CV_32FC3:
	{
		cv::Mat normalize_mat;
		normalize(mat, normalize_mat, 0, 255, cv::NORM_MINMAX, -1);
		normalize_mat.convertTo(normalize_mat, CV_8U);
		const uchar *pSrc = (const uchar*)normalize_mat.data;
		image = QImage(pSrc, normalize_mat.cols, normalize_mat.rows, normalize_mat.step, QImage::Format_RGB888);
		return QPixmap::fromImage(image.rgbSwapped());
	}
	default:
	{
		//qDebug() << "mat.type not match. mat type is " << mat.type();
		return QPixmap();
	}


	}
}

//PictureProcessPanel
PictureProcessPanel::PictureProcessPanel(QPixmap pixmap, QWidget* parent /*= nullptr*/)
	:QDialog(parent)
{
	// view
	m_pView = new QGraphicsView(this);
	m_pView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // disable scroll area's scroll bar
	m_pView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pView->setRenderHint(QPainter::Antialiasing);
	m_pView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	m_pView->viewport()->installEventFilter(this);

	// scene 
	m_pScene = new QGraphicsScene(QRectF(-350, -350, 700, 700), this);
	m_pView->setScene(m_pScene);

	// v layout
	QVBoxLayout* m_pVLayout = new QVBoxLayout(this);
	m_pVLayout->setMargin(0);
	m_pVLayout->setAlignment(Qt::AlignHCenter);
	m_pVLayout->addWidget(m_pView);
	setLayout(m_pVLayout);


	// 将pixmapItem加入场景中
	pixmap = pixmap.scaledToWidth(700);
	QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);

	pixmapItem->setFlags(QGraphicsPixmapItem::ItemIsMovable);
	pixmapItem->setOffset(-pixmap.width() / 2., -pixmap.height() / 2.);
	pixmapItem->setPos(0, 0);

	m_pScene->addItem(pixmapItem);
}

bool PictureProcessPanel::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == m_pView->viewport()) // disable scroll area mouse wheel
	{
		if (event->type() == QEvent::Wheel)
		{
			return true;
		}
	}

	return QDialog::eventFilter(watched, event);
}

void PictureProcessPanel::wheelEvent(QWheelEvent *event)
{
	scaleView(std::pow(2, event->delta() / 240.0));
}

void PictureProcessPanel::scaleView(qreal scaleFactor)
{
	qreal factor = m_pView->transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

	if (factor < 0.07 || factor > 100)
		return;

	m_pView->scale(scaleFactor, scaleFactor);
}

//PictureWidget
PictureWidget::PictureWidget(QSize pictureSize, cv::Mat srcMat,int imgIdx, QWidget* parent)
	:QLabel(parent), m_nImgIdx(imgIdx)
{
	setFixedSize(pictureSize);

	/** 将cv::Mat压缩 */
	cv::imencode(".jpg", srcMat, m_vImgData);
}

cv::Mat PictureWidget::getMat()
{
	/** 将cv::Mat解压 */
	return cv::imdecode(m_vImgData, cv::IMREAD_COLOR);
}

std::vector<uchar> PictureWidget::getImgData()
{
	return m_vImgData;
}

void PictureWidget::setIndex(int idx)
{
	m_nImgIdx = idx;
}

int PictureWidget::getIndex()
{
	return m_nImgIdx;
}

void PictureWidget::setRobotPose(std::vector<double> pos, std::vector<double> orient)
{
	m_vPos = pos;
	m_vOrient = orient;
}

void PictureWidget::getRobotPose(std::vector<double>& pos, std::vector<double>& orient)
{
	pos = m_vPos;
	orient = m_vOrient;
}

void PictureWidget::paintEvent(QPaintEvent * event)
{
	/** 先调用父类的paintEvent */
	QLabel::paintEvent(event); 

	QPainter painter(this);
	QFont font;
	font.setFamily("Microsoft Yahei");
	font.setBold(true);
	QPen pen;
	pen.setColor("#1296db");
	painter.setFont(font);
	painter.setPen(pen);

	painter.drawText(QPoint(5, 15),QString::number(getIndex()+1));
}

//lxQImageFlowViewer
ImageFlowViewer::ImageFlowViewer(QSize pictureSize, QWidget *parent /*= nullptr*/)
	:QWidget(parent), m_tPictureSize(pictureSize)
{
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	
	/** 图片展示区 */
	QScrollArea *scrollArea = new QScrollArea;
	scrollArea->setWidgetResizable(true); // very important

	m_pChildWidget = new QWidget;
	m_pFlowLayout = new FlowLayout(m_pChildWidget, 0);
	m_pChildWidget->setLayout(m_pFlowLayout);

	scrollArea->setWidget(m_pChildWidget);

	mainLayout->addWidget(scrollArea);
}

int ImageFlowViewer::count()
{
	return m_listPictureWidget.count();
}

bool ImageFlowViewer::isEmpty()
{
	return m_listPictureWidget.isEmpty();
}

void ImageFlowViewer::clear()
{
	for (auto picture : m_listPictureWidget)
	{
		m_pFlowLayout->removeWidget(picture);
		picture->deleteLater();
	}
	m_listPictureWidget.clear();
}

void ImageFlowViewer::remove(int idx)
{
	auto item = m_pFlowLayout->takeAt(idx);
	item->widget()->deleteLater();
	delete item;

	/** 移除控件 */ 
	m_listPictureWidget.removeAt(idx);

	/** 重新设置控件的索引 */
	adjustPictureWidgetIndex();

	/** 立即刷新,先使布局失效,再触发窗口重绘 */
	m_pFlowLayout->invalidate();
	update(); 
}

QList<cv::Mat> ImageFlowViewer::getAllMat()
{
	QList<cv::Mat> listMat;
	for (auto&picWidget : getAllPictureWidget())
	{
		listMat.push_back(picWidget->getMat());
	}

	return listMat;
}

QList<std::vector<uchar>> ImageFlowViewer::getAllImgData()
{
	QList<std::vector<uchar>> listImg;
	for (auto&picWidget : getAllPictureWidget())
	{
		listImg.push_back(picWidget->getImgData());
	}

	return listImg;
}

void ImageFlowViewer::pushNewMat(QList<cv::Mat> listMat)
{
	int idx = m_listPictureWidget.size();
	for (auto &mat : listMat)
	{
		QPixmap pixmap = mat2QPixmap(mat);

		auto picture = new PictureWidget(m_tPictureSize, mat, idx++);
		picture->setPixmap(pixmap.scaledToWidth(m_tPictureSize.width()));

		m_pFlowLayout->addWidget(picture);
		m_listPictureWidget.push_back(picture);
	}
}

void ImageFlowViewer::pushNewMat(QList<cv::Mat> listMat,std::vector<std::vector<double>> vvPos, std::vector<std::vector<double>> vvOrient)
{
	int idx = m_listPictureWidget.size();
	int cnt = 0;
	for (auto &mat : listMat)
	{
		QPixmap pixmap = mat2QPixmap(mat);

		auto picture = new PictureWidget(m_tPictureSize, mat, idx++);
		picture->setRobotPose(vvPos[cnt], vvOrient[cnt]);
		picture->setPixmap(pixmap.scaledToWidth(m_tPictureSize.width()));

		m_pFlowLayout->addWidget(picture);

		m_listPictureWidget.push_back(picture);

		cnt++;
	}
}

QList<PictureWidget*> ImageFlowViewer::getAllPictureWidget()
{
	return m_listPictureWidget;
}

void ImageFlowViewer::mouseDoubleClickEvent(QMouseEvent *event)
{
	PictureWidget* curPic = qobject_cast<PictureWidget*>(childAt(event->pos()));
	if (curPic)
	{
		//std::vector<double> vPos;
		//std::vector<double> vOrient;
		//curPic->getRobotPose(vPos, vOrient);
		//qDebug() << "pos " << QVector<double>::fromStdVector(vPos);
		//qDebug() << "orient " << QVector<double>::fromStdVector(vOrient);

		PictureProcessPanel* processPanel = new PictureProcessPanel(mat2QPixmap(curPic->getMat()));
		processPanel->setWindowTitle(QString("第%1帧 总:%2帧").arg(curPic->getIndex() + 1).arg(m_listPictureWidget.size()));
		processPanel->setAttribute(Qt::WA_DeleteOnClose);
		processPanel->show();
	}
}

void ImageFlowViewer::adjustPictureWidgetIndex()
{
	for (int i = 0; i < m_listPictureWidget.size(); i++)
	{
		m_listPictureWidget[i]->setIndex(i);
	}
}
