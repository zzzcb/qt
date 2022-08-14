#include "lxqgraphicsscene.h"
#include "lxqgraphicsitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

lxQGraphicsScene::lxQGraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
{

}

lxQGraphicsScene::~lxQGraphicsScene()
{
}

lxQGraphicsItemGroup * lxQGraphicsScene::createGroup(const QList<QGraphicsItem *> &items, bool bAdd /*= true*/)
{
	if (items.size() == 0)
		return nullptr;

	/** Create a new group*/
	lxQGraphicsItemGroup *group = new lxQGraphicsItemGroup;
	if (bAdd)
		addItem(group);

	for (auto item:items)
	{
		item->setSelected(false);

		auto g = qgraphicsitem_cast<lxQGraphicsItemGroup*>(item->parentItem());
		/** 如果 当前选定的item的父亲 是个group item,那么就不用操作该item了,操作group就行了 */
		if (!g)
		{
			group->addToGroup(item);
		}
	}

	group->setSelected(true);
	group->updateBoundingRect();

	/**这才是 groupScenePos的获取方式,其他都是bug*/
	//auto rect = group->sceneBoundingRect();
	//auto groupScenePos = rect.topLeft() + QPointF(rect.width(), rect.height()) / 2.;

	return group;
}

void lxQGraphicsScene::destroyGroup(lxQGraphicsItemGroup* group)
{
	group->setSelected(false);
	for (const auto&item : group->childItems())
	{
		item->setSelected(true);
		group->removeFromGroup(item);
	}
	removeItem(group);
	delete group;
}

void lxQGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsScene::mouseMoveEvent(event);
}

#include <QKeyEvent>
void lxQGraphicsScene::keyPressEvent(QKeyEvent *event)
{
	qreal dx, dy = 0;
	switch (event->key())
	{	
	case Qt::Key_Up:
		dx = 0;
		dy = -1;
		break;
	case Qt::Key_Down:
		dx = 0;
		dy = 1;
		break;
	case Qt::Key_Left:
		dx = -1;
		dy = 0;
		break;
	case Qt::Key_Right:
		dx = 1;
		dy = 0;
		break;
	default:
		break;
	}

	for (const auto & item : selectedItems())
	{
		item->moveBy(dx, dy);
	}

	update();

	QGraphicsScene::keyPressEvent(event);

}

void lxQGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{

	QGraphicsScene::drawBackground(painter, rect);
	painter->fillRect(sceneRect(),QColor(37,37,37));

	painter->setPen(Qt::black);
	painter->drawLine(QPointF(0, -300), QPointF(0, 300));  ///< y axis 
	painter->drawLine(QPointF(-400, 0), QPointF(400, 0));  ///< x axis 

}
