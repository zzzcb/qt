#include "lxgraphicsview.h"
#include "lxgraphicsscene.h"
#include "lxtreewidget.h"
#include "lxgraphicsitem.h"

#include "common.h"

#include <QDebug>
#include <QDropEvent>
#include <QSharedPointer>


LxGraphicsView::LxGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	LxGraphicsScene* scene = new LxGraphicsScene(this);
	scene->setSceneRect(-300, -400, 600, 800);
	setScene(scene);

	//// 设置scene的背景色为gray,此时会填满整个 view，可以通过重写scene的drawbackgroud来标识scene
	//scene->setBackgroundBrush(Qt::darkGray);

	setAcceptDrops(true);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(QGraphicsView::NoAnchor);
}

LxGraphicsView::~LxGraphicsView()
{
}

void LxGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
	event->setAccepted(true);
}


void LxGraphicsView::dragMoveEvent(QDragMoveEvent *event)
{

}

void LxGraphicsView::dropEvent(QDropEvent *event)
{
	LxTreeWidget* srcWidget = qobject_cast<LxTreeWidget*>(event->source());
	if (!srcWidget)
		return;

	QVariant vizItemType = srcWidget->currentItem()->data(0, vizItemTypeRole);

	if (!vizItemType.isValid())
		return;

	//qDebug() << "source is " << srcWidget->currentItem()->text(0);
	//qDebug() << " role data is " << srcWidget->currentItem()->data(0, itemTypeRole);

	//qDebug() << "viz item type is " << vizItemType;

	QPointF pos = mapToScene(event->pos());

	LxGraphicsVizItem* vizItem = new LxGraphicsVizItem(LxVizItemType(vizItemType.toInt()));
	vizItem->setPos(pos);
	scene()->addItem(vizItem);

	qDebug() <<"drop item size "  << scene()->items().size();

}

void LxGraphicsView::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control)
	{
		mbCtrl = true;
	}
	switch (event->key())
	{
	case Qt::Key_Delete:

		break;
	default:
		break;
	}

}

void LxGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control)
	{
		mbCtrl = false;
	}
}

void LxGraphicsView::wheelEvent(QWheelEvent *event)
{
	// ctrl +  zoom in 
	// ctrl -  zoom out 
	if (mbCtrl)
		scaleView(std::pow(2, event->delta() / 240.0));
	else
		translateViewY(event->delta()/10.);
}

void LxGraphicsView::mousePressEvent(QMouseEvent *event)
{
	// test curve line 
	//for (auto item : scene()->items())
	//{
	//	if (LxGrphicsCurveLineItem* line = qgraphicsitem_cast<LxGrphicsCurveLineItem*>(item))
	//	{
	//		line->setDstPt(mapToScene(event->pos()));
	//		scene()->update();
	//	}
	//}

	qDebug() << "view scene pos " << mapToScene(event->pos());
	qDebug() << "scene is " << scene();


	QGraphicsView::mousePressEvent(event);
}

void LxGraphicsView::scaleView(qreal scaleFactor)
{
	qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

	if (factor < 0.07 || factor > 100)
		return;

	scale(scaleFactor, scaleFactor);
}

void LxGraphicsView::translateViewY(qreal dy)
{
	translate(0,dy);
}
