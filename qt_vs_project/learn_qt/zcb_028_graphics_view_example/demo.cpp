#pragma execution_character_set("utf-8")
#include "demo.h"
#include "QGraphicsItem"
#include "QKeyEvent"
#include "qdebug.h"
#include "QDateTime"
#include "QInputDialog"
#include "QColorDialog"
#include "QFontDialog"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	setCentralWidget(ui.graphicsView);

	labViewPos = new QLabel("view坐标:");
	labViewPos->setMinimumWidth(150);
	ui.statusBar->addWidget(labViewPos);

	labScenePos = new QLabel("scene坐标:");
	labScenePos->setMinimumWidth(150);
	ui.statusBar->addWidget(labScenePos);

	labItemPos = new QLabel("item坐标:");
	labItemPos->setMinimumWidth(150);
	ui.statusBar->addWidget(labItemPos);

	labItemInfo = new QLabel("item信息:");
	labItemInfo->setMinimumWidth(150);
	ui.statusBar->addWidget(labItemInfo);

	ui.graphicsView->setMouseTracking(true); // 如果想要重写 mouseMoveEvent,需要打开tracking   

	connect(ui.graphicsView, &MyGraphicsView::mouseMovePoint, this, &Demo::on_mouseMovePoint);
	connect(ui.graphicsView, &MyGraphicsView::mousePressPoint, this, &Demo::on_mousePressPoint);
	connect(ui.graphicsView, &MyGraphicsView::mouseDoubleClickPoint, this, &Demo::on_mouseDoubleClickPoint);
	connect(ui.graphicsView, &MyGraphicsView::keyPress, this, &Demo::on_keyPress);

	initGraphicsView();
	
	qsrand(QTime::currentTime().second()); // 创建随机数种子 

}

void Demo::initGraphicsView()
{
	QRectF sceneRect(-300, -200, 600, 400);
	scene = new QGraphicsScene(sceneRect);

	QGraphicsRectItem* item1 = new QGraphicsRectItem(sceneRect);// 可视化 scene,scene 就这么大 

	scene->addItem(item1);
	ui.graphicsView->setScene(scene);

	ui.graphicsView->setDragMode(QGraphicsView::RubberBandDrag); // 可以区域选择 item 
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
		labItemInfo->setText(item->data(ItemDesc).toString() + ", ItemId=" +
			item->data(ItemId).toString());
	}

}
template <typename T>
void setBrushColor(T* item)
{
	QColor color = item->brush().color();
	color = QColorDialog::getColor(color, NULL, "选择填充颜色");
	if (color.isValid())
		item->setBrush(QBrush(color));
}
void Demo::on_mouseDoubleClickPoint(QPoint point)
{
	QPointF pointScene = ui.graphicsView->mapToScene(point); //转换到Scene坐标
	QGraphicsItem  *item = NULL;
	item = scene->itemAt(pointScene, ui.graphicsView->transform()); //获取光标下的绘图项

	if (item == NULL) //没有绘图项
		return;

	switch (item->type())  //绘图项的类型
	{
	case    QGraphicsRectItem::Type: //矩形框
	{ //强制类型转换
		QGraphicsRectItem *theItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);
		setBrushColor(theItem);
		break;
	}
	case    QGraphicsEllipseItem::Type: //椭圆和圆都是 QGraphicsEllipseItem
	{
		QGraphicsEllipseItem *theItem;
		theItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
		setBrushColor(theItem);
		break;
	}

	case    QGraphicsPolygonItem::Type: //梯形和三角形
	{
		QGraphicsPolygonItem *theItem = qgraphicsitem_cast<QGraphicsPolygonItem*>(item);
		setBrushColor(theItem);
		break;
	}
	case    QGraphicsLineItem::Type: //直线，设置线条颜色
	{
		QGraphicsLineItem *theItem = qgraphicsitem_cast<QGraphicsLineItem*>(item);
		QPen    pen = theItem->pen();
		QColor  color = theItem->pen().color();
		color = QColorDialog::getColor(color, this, "选择线条颜色");
		if (color.isValid())
		{
			pen.setColor(color);
			theItem->setPen(pen);
		}
		break;
	}
	case    QGraphicsTextItem::Type: //文字，设置字体
	{
		QGraphicsTextItem *theItem = qgraphicsitem_cast<QGraphicsTextItem*>(item);
		QFont font = theItem->font();
		bool ok = false;
		font = QFontDialog::getFont(&ok, font, this, "设置字体");
		if (ok)
			theItem->setFont(font);
		break;
	}
	}
}
void Demo::on_keyPress(QKeyEvent* event)
{
	if (scene->selectedItems().count() == 0)
		return; 
	QList<QGraphicsItem*> items = scene->selectedItems();

	for (auto item : items)
	{
		if (event->key() == Qt::Key_Delete)//删除
			scene->removeItem(item);
		else if (event->key() == Qt::Key_Space) //顺时针旋转90度
			item->setRotation(90 + item->rotation());
		else if (event->key() == Qt::Key_PageUp)//放大
			item->setScale(0.1 + item->scale());
		else if (event->key() == Qt::Key_PageDown) //缩小
			item->setScale(-0.1 + item->scale());
		else if (event->key() == Qt::Key_Left)  //左移
			item->setX(-1 + item->x());
		else if (event->key() == Qt::Key_Right) //右移
			item->setX(1 + item->x());
		else if (event->key() == Qt::Key_Up) //上移
			item->setY(-1 + item->y());
		else if (event->key() == Qt::Key_Down) //下移
			item->setY(1 + item->y());
	}
}

void Demo::on_actItem_Rect_triggered()
{
	QGraphicsRectItem   *item = new QGraphicsRectItem(-50, -25, 100, 50);// scene 坐标系下 
	item->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);
	item->setBrush(QBrush(Qt::yellow));
	item->setPos(-50 + (qrand() % 100), -50 + (qrand() % 100));    // 设置 item 中心的位置,如果item没有parent那么就是在scene坐标系下的位置。
	item->setZValue(++frontZ);

	item->setData(ItemId, ++seqNum);
	item->setData(ItemDesc, "矩形");

	scene->addItem(item);
	scene->clearSelection(); // 取消选中scene 中的其他item
	item->setSelected(true); // 选中新添加的item 
}

void Demo::on_actItem_Ellipse_triggered()
{
	QGraphicsEllipseItem   *item = new QGraphicsEllipseItem(-50, -30, 100, 60);// scene 坐标系下 
	item->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);
	item->setBrush(QBrush(Qt::blue));
	item->setPos(-50 + (qrand() % 100), -50 + (qrand() % 100));    // 设置 item 中心的位置,如果item没有parent那么就是在scene坐标系下的位置。
	item->setZValue(++frontZ);

	item->setData(ItemId, ++seqNum);
	item->setData(ItemDesc, "椭圆");

	scene->addItem(item);
	scene->clearSelection(); // 取消选中scene 中的其他item
	item->setSelected(true); // 选中新添加的item 

}

void Demo::on_actItem_Circle_triggered()
{
	QGraphicsEllipseItem   *item = new QGraphicsEllipseItem(-50, -50, 100, 100);
	item->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);
	item->setBrush(QBrush(Qt::cyan));
	item->setZValue(++frontZ);
	item->setPos(-50 + (qrand() % 100), -50 + (qrand() % 100));

	item->setData(ItemId, ++seqNum);
	item->setData(ItemDesc, "圆形");

	scene->addItem(item);
	scene->clearSelection();
	item->setSelected(true);
}

void Demo::on_actItem_Triangle_triggered()
{
	QGraphicsPolygonItem   *item = new QGraphicsPolygonItem;
	QPolygonF   points;
	points.append(QPointF(0, -40));
	points.append(QPointF(60, 40));
	points.append(QPointF(-60, 40));
	item->setPolygon(points);
	item->setPos(-50 + (qrand() % 100), -50 + (qrand() % 100));

	item->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);
	item->setBrush(QBrush(Qt::magenta));
	item->setZValue(++frontZ);

	item->setData(ItemId, ++seqNum);
	item->setData(ItemDesc, "三角形");

	scene->addItem(item);
	scene->clearSelection();
	item->setSelected(true);
}

void Demo::on_actItem_Line_triggered()
{
	QGraphicsLineItem   *item = new QGraphicsLineItem(-100, 0, 100, 0);
	item->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);

	QPen    pen(Qt::red);
	pen.setWidth(3);
	item->setPen(pen);

	item->setZValue(++frontZ);
	item->setPos(-50 + (qrand() % 100), -50 + (qrand() % 100));

	item->setData(ItemId, ++seqNum);
	item->setData(ItemDesc, "直线");

	scene->addItem(item);
	scene->clearSelection();
	item->setSelected(true);
}

void Demo::on_actItem_Polygon_triggered()
{
	QGraphicsPolygonItem   *item = new QGraphicsPolygonItem;

	QPolygonF   points;
	points.append(QPointF(-40, -40));
	points.append(QPointF(40, -40));
	points.append(QPointF(100, 40));
	points.append(QPointF(-100, 40));
	item->setPolygon(points);
	item->setPos(-50 + (qrand() % 100), -50 + (qrand() % 100));

	item->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);
	item->setBrush(QBrush(Qt::green));
	item->setZValue(++frontZ);

	item->setData(ItemId, ++seqNum);
	item->setData(ItemDesc, "梯形");

	scene->addItem(item);
	scene->clearSelection();
	item->setSelected(true);
}

void Demo::on_actItem_Text_triggered()
{
	QString str = QInputDialog::getText(this, "输入文字", "请输入文字");
	if (str.isEmpty())
		return;

	QGraphicsTextItem   *item = new QGraphicsTextItem(str);

	QFont   font = this->font();
	font.setPointSize(20);
	font.setBold(true);
	item->setFont(font);

	item->setFlags(QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable
		| QGraphicsItem::ItemIsFocusable);
	item->setPos(-50 + (qrand() % 100), -50 + (qrand() % 100));
	item->setZValue(++frontZ);

	item->setData(ItemId, ++seqNum);
	item->setData(ItemDesc, "文字");

	scene->addItem(item);
	scene->clearSelection();
	item->setSelected(true);
}

void Demo::on_actZoomIn_triggered()
{
	// 放大
	int cnt = scene->selectedItems().count();
	if (cnt == 1)
	{
		QGraphicsItem   *item;
		item = scene->selectedItems().at(0);
		item->setScale( item->scale() + 0.1);
	}
	else
		ui.graphicsView->scale(1.1, 1.1);
}

void Demo::on_actZoomOut_triggered()
{
	// 缩小
	int cnt = scene->selectedItems().count();
	if (cnt == 1)
	{
		QGraphicsItem   *item;
		item = scene->selectedItems().at(0);
		item->setScale(item->scale()-0.1);
	}
	else
		ui.graphicsView->scale(0.9,0.9);
}

void Demo::on_actRestore_triggered()
{
	// 恢复
	int cnt = scene->selectedItems().count();
	if (cnt == 1)
	{
		QGraphicsItem* item = scene->selectedItems().at(0);
		item->setRotation(0);
		item->setScale(1.0);
	}
	else
		ui.graphicsView->resetTransform();
}

void Demo::on_actRotateLeft_triggered()
{
	int cnt = scene->selectedItems().count();
	if (cnt == 1)
	{
		QGraphicsItem* item = scene->selectedItems().at(0);
		item->setRotation(-30 + item->rotation());
	}
	else
		ui.graphicsView->rotate(-30);
}

void Demo::on_actRotateRight_triggered()
{
	int cnt = scene->selectedItems().count();
	if (cnt == 1)
	{
		QGraphicsItem* item = scene->selectedItems().at(0);
		item->setRotation(+30 + item->rotation());
	}
	else
		ui.graphicsView->rotate(+30);

}

void Demo::on_actEdit_Front_triggered()
{
	//前置 前置到最前
	int cnt = scene->selectedItems().count();
	if (cnt > 0)
	{ //只处理选中的第1个绘图项
		QGraphicsItem* item = scene->selectedItems().at(0);
		item->setZValue(++frontZ);
	}
}

void Demo::on_actEdit_Back_triggered()
{
	// 后置 后置到最后
	int cnt = scene->selectedItems().count();
	if (cnt > 0)
	{   //只处理选中的第1个绘图项
		QGraphicsItem* item = scene->selectedItems().at(0);
		item->setZValue(--backZ);
	}

}

void Demo::on_actGroup_triggered()
{
	// 组合 
	int cnt = scene->selectedItems().count();
	if (cnt > 1)
	{
		QGraphicsItemGroup* group = new QGraphicsItemGroup; //创建组合
		scene->addItem(group); //组合添加到场景中

		for (int i = 0; i < cnt; i++)
		{
			QGraphicsItem* item = scene->selectedItems().at(0);
			item->setSelected(false); //清除选择虚线框
			item->clearFocus();
			group->addToGroup(item); //添加到组合
		}
		group->setFlags(QGraphicsItem::ItemIsMovable
			| QGraphicsItem::ItemIsSelectable
			| QGraphicsItem::ItemIsFocusable);

		group->setZValue(++frontZ);
		// group->clearFocus();
		scene->clearSelection();
		group->setSelected(true);
	}
}

void Demo::on_actGroupBreak_triggered()
{
	// 打散 
	int cnt = scene->selectedItems().count();
	if (cnt == 1)
	{
		QGraphicsItemGroup  *group;
		QGraphicsItem*item = scene->selectedItems().at(0);
		if (item->type() == QGraphicsItemGroup::Type)
		{
			group = (QGraphicsItemGroup*)item;
			scene->destroyItemGroup(group);
		}

	}

}

void Demo::on_actEdit_Delete_triggered()
{
	int cnt = scene->selectedItems().count();
	if (cnt > 0)
		for (int i = 0; i < cnt; i++)
		{
			QGraphicsItem*  item = scene->selectedItems().at(0);
			scene->removeItem(item);
		}
}
