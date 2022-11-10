#include "lxqgraphicsview.h"
#include "lxqgraphicsscene.h"
#include "lxqtreewidget.h"
#include "lxqgraphicsitem.h"

#include "common.h"

#include <QDebug>
#include <QDropEvent>
#include <QSharedPointer>


lxQGraphicsView::lxQGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	m_pScene = new lxQGraphicsScene(this);
	m_pScene->setSceneRect(-400, -300, 800, 600);
	setScene(m_pScene);

	/**设置scene的背景色为gray,此时会填满整个 view，可以通过重写scene的drawbackgroud来标识scene*/
	//scene->setBackgroundBrush(Qt::darkGray);

	setAcceptDrops(true);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(QGraphicsView::NoAnchor);
}

lxQGraphicsView::~lxQGraphicsView()
{
}

void lxQGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
	event->setAccepted(true);
}


void lxQGraphicsView::dragMoveEvent(QDragMoveEvent *event)
{

}

void lxQGraphicsView::dropEvent(QDropEvent *event)
{
	lxQTreeWidget* srcWidget = qobject_cast<lxQTreeWidget*>(event->source());
	if (!srcWidget)
		return;

	QVariant vizItemType = srcWidget->currentItem()->data(0, gn_vizItemTypeRole);

	if (!vizItemType.isValid())
		return;

	//qDebug() << "source is " << srcWidget->currentItem()->text(0);
	//qDebug() << " role data is " << srcWidget->currentItem()->data(0, itemTypeRole);
	//qDebug() << "viz item type is " << vizItemType;

	QPointF pos = mapToScene(event->pos());

	lxQGraphicsVizItem* vizItem = new lxQGraphicsVizItem(lxQVizItemType(vizItemType.toInt()));
	vizItem->setPos(pos);
	scene()->addItem(vizItem);

	emit signal_itemAdded((QGraphicsItem*)vizItem, (QGraphicsScene*)m_pScene);

	qDebug() <<"drop item size "  << scene()->items().size();

}

void lxQGraphicsView::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control)
	{
		mb_ctrl = true;
	}
	switch (event->key())
	{
	case Qt::Key_Delete:

		break;
	default:
		break;
	}

}

void lxQGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control)
	{
		mb_ctrl = false;
	}
}

void lxQGraphicsView::wheelEvent(QWheelEvent *event)
{
	/**
		ctrl +  zoom in
		ctrl -  zoom out
	*/
	if (mb_ctrl)
		scaleView(std::pow(2, event->delta() / 240.0));
	else
		translateViewY(event->delta()/10.);
}

void lxQGraphicsView::mousePressEvent(QMouseEvent *event)
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

void lxQGraphicsView::scaleView(qreal scaleFactor)
{
	qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

	if (factor < 0.07 || factor > 100)
		return;

	scale(scaleFactor, scaleFactor);
}

void lxQGraphicsView::translateViewY(qreal dy)
{
	translate(0,dy);
}
