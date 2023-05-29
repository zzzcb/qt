#pragma execution_character_set("utf-8")
#include "lxqmainwindow.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
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

	/**tool*/
	m_pAddViewBtn = new QPushButton("新增View");
	m_pAddSceneBtn = new QPushButton("新增Scene");
	m_pClearItemBtn = new QPushButton("清空图片");
	m_pSwitchSceneBtn = new QComboBox(this); m_pSwitchSceneBtn->addItem("1");
	toolBtnLayout->addWidget(m_pAddViewBtn);
	toolBtnLayout->addWidget(m_pAddSceneBtn);
	toolBtnLayout->addWidget(m_pClearItemBtn);
	toolBtnLayout->addWidget(m_pSwitchSceneBtn);

	/**view*/ 
	m_pGraphicsView = new QGraphicsView;
	mainLayout->addWidget(m_pGraphicsView);
	mainLayout->setContentsMargins(0,0,0,0);

	/**scene*/  
	QGraphicsScene* scene = new QGraphicsScene(QRectF(-350, -350, 700, 700), this);
	m_pGraphicsView->setScene(scene);
	m_listGraphicsScene.push_back(scene);

	resize(800, 800);

	/**signal-slot*/
	connect(m_pAddViewBtn, &QPushButton::clicked, this, &lxQMainWindow::slot_toolBtn_handle);
	connect(m_pAddSceneBtn, &QPushButton::clicked, this, &lxQMainWindow::slot_toolBtn_handle);
	connect(m_pClearItemBtn, &QPushButton::clicked, this, &lxQMainWindow::slot_toolBtn_handle);
	connect(m_pSwitchSceneBtn, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &lxQMainWindow::slot_toolBtn_handle);
	
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
		pixmapItem->setFlags(QGraphicsPixmapItem::ItemIsMovable);
		pixmapItem->setOffset(-pixmap.width() / 2., -pixmap.height() / 2.);
		pixmapItem->setPos(0, 0);

		m_listGraphicsScene[m_pSwitchSceneBtn->currentIndex()]->addItem(pixmapItem);
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

void lxQMainWindow::slot_toolBtn_handle(int data)
{
	if (sender() == m_pClearItemBtn)
	{
		for(auto& scene:m_listGraphicsScene)
			scene->clear();
	}
	else if (sender() == m_pAddViewBtn)
	{
		QDialog* pNewViewDialog = new QDialog(this);
		QVBoxLayout* vlayout = new QVBoxLayout(pNewViewDialog);
		pNewViewDialog->setAttribute(Qt::WA_DeleteOnClose);
		pNewViewDialog->setLayout(vlayout);

		QGraphicsView* pNewView = new QGraphicsView(pNewViewDialog);
		vlayout->addWidget(pNewView);

		pNewView->setScene(m_listGraphicsScene[m_pSwitchSceneBtn->currentIndex()]);
		pNewViewDialog->resize(800, 800);
		pNewViewDialog->show();
	}
	else if (sender() == m_pAddSceneBtn)
	{
		QGraphicsScene* scene = new QGraphicsScene(QRectF(-350, -350, 700, 700), this);
		m_pGraphicsView->setScene(scene);
		m_listGraphicsScene.push_back(scene);
		m_pSwitchSceneBtn->addItem(QString::number(m_pSwitchSceneBtn->count()+1));
		m_pSwitchSceneBtn->setCurrentIndex(m_pSwitchSceneBtn->count()-1);
	}
	else if (sender() == m_pSwitchSceneBtn)
	{
		if (data<0 || data > m_listGraphicsScene.size()-1)
			return;

		m_pGraphicsView->setScene(m_listGraphicsScene[data]);
	}
}

