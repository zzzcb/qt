#pragma execution_character_set("utf-8")
#include "demo.h"
#include "qdebug.h"
#include "QGraphicsItem"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	
	labViewPos = new QLabel("view坐标:");
	labViewPos->setMinimumWidth(150); 
	ui.statusBar->addWidget(labViewPos); 

	labScenePos = new QLabel("scene坐标:");
	labScenePos->setMinimumWidth(150);
	ui.statusBar->addWidget(labScenePos);

	labItemPos = new QLabel("item坐标:");
	labItemPos->setMinimumWidth(150);
	ui.statusBar->addWidget(labItemPos);
	
	ui.graphicsView->setMouseTracking(true); // 如果想要重写 mouseMoveEvent,需要打开tracking   

	connect(ui.graphicsView, &MyGraphicsView::mouseMovePoint, this, &Demo::on_mouseMovePoint);
	connect(ui.graphicsView, &MyGraphicsView::mousePressPoint, this, &Demo::on_mousePressPoint);

	initGraphicsView();

}

void Demo::initGraphicsView()
{
	// scene 坐标系 默认在view的中心处   
	scene = new QGraphicsScene(-200, -100, 400, 200); // scene 坐标系下坐标  // 如果scene不设置scenerect 的话，它回随着content的增加而增加,而且不会回退

	
	QGraphicsRectItem* item1 = new QGraphicsRectItem(-200, -100, 400, 200);// scene 坐标系下坐标 // 可视化 scene,scene 就这么大 

	// 椭圆 
	QGraphicsEllipseItem* item2 = new QGraphicsEllipseItem(-100,-50,200,100);// scene 坐标系下坐标
	item2->setBrush(QBrush(Qt::blue));
	item2->setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable ); //可以聚焦和可选中和可移动


	scene->addItem(item1);
	scene->addItem(item2);
	ui.graphicsView->setScene(scene);
}

void Demo::on_mouseMovePoint(QPoint point)
{
	labViewPos->setText(QString::asprintf("view坐标:%d,%d", point.x(), point.y()));  
	
	QPointF pInScene = ui.graphicsView->mapToScene(point); // view -> scene  
	labScenePos->setText(QString::asprintf("scene坐标:%.0f,%.0f", pInScene.x(), pInScene.y()));
}

void Demo::on_mousePressPoint(QPoint point)
{
	QPointF pInScene = ui.graphicsView->mapToScene(point);
	QGraphicsItem* item = NULL;
	item = scene->itemAt(pInScene, ui.graphicsView->transform());
	if (item) { // 有item 
		QPointF pInItem = item->mapFromScene(pInScene);
		labItemPos->setText(QString::asprintf("item坐标:%.0f,%.0f", pInItem.x(), pInItem.y()));
	}

}
