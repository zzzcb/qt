#pragma execution_character_set("utf-8")
#include "lxqmainwindow.h"
#include "lxqgraphicsview.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDebug>

lxQMainWindow::lxQMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	initQSS();

	QWidget* centerWidget = new QWidget(this);
	setCentralWidget(centerWidget);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	QHBoxLayout* toolBtnLayout = new QHBoxLayout(this);

	mainLayout->addLayout(toolBtnLayout);
	centralWidget()->setLayout(mainLayout);

	/**view*/ 
	m_pGraphicsView = new lxQGraphicsView;
	mainLayout->addWidget(m_pGraphicsView);
	mainLayout->setContentsMargins(0,0,0,0);

	/**scene*/  
	m_pGraphisScene = new QGraphicsScene(QRectF(-350, -350, 700, 700), this);
	m_pGraphicsView->setScene(m_pGraphisScene);

	resize(800, 800);
}

lxQMainWindow::~lxQMainWindow()
{
}

void lxQMainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
	QMainWindow::mouseDoubleClickEvent(event);
	QStringList imgPaths = QFileDialog::getOpenFileNames(this, "请选取图片", "./", "Images (*.jpg *.png *.bmp)");

	if (imgPaths.isEmpty())
		return;

	for (auto& img : imgPaths)
	{
		QPixmap pixmap(img);
		pixmap = pixmap.scaledToWidth(300);

		QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);
		pixmapItem->setFlags(QGraphicsPixmapItem::ItemIsMovable| QGraphicsPixmapItem::ItemIsSelectable);
		pixmapItem->setOffset(-pixmap.width() / 2., -pixmap.height() / 2.);
		pixmapItem->setPos(0, 0);

		m_pGraphisScene->addItem(pixmapItem);
	}
}

void lxQMainWindow::initQSS()
{
	QString qss = R"(
QGraphicsView{
	background: #3f3f46;
	border: none;
}
)";
	setStyleSheet(qss);
}

