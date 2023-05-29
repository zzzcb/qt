#pragma execution_character_set("utf-8")
#include "lxqgraphicsitem.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

#define TOP_Z_INDEX 1000000
#define BOTTOM_Z_INDEX -1

/**======================================= common =====================================*/
static void itemHighlight(QPainter *painter, QPainterPath path, const QStyleOptionGraphicsItem *option)
{
	QPen pen;
	pen.setWidth(2.5);
	pen.setColor(QColor(239, 61, 84));
	painter->setPen(pen);
	painter->drawPath(path);
}

/**======================================= mime data =====================================*/
lxQGraphicsMimeData::lxQGraphicsMimeData(QList<QGraphicsItem*> items)
{
	for (const auto&item : items)
	{
		if (auto _item = qgraphicsitem_cast<lxQGraphicsPixmapItem*>(item))
		{
			m_listItem.push_back(_item->duplicate());
		}
	}
}

lxQGraphicsMimeData::~lxQGraphicsMimeData()
{
	for (auto& item : m_listItem)
		delete item;

	m_listItem.clear();
}

QList<QGraphicsItem*> lxQGraphicsMimeData::getItems() const
{
	return m_listItem;
}

/**======================================= item =====================================*/

// lxQGraphicsPixmapItem
lxQGraphicsPixmapItem::lxQGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent)
	:QGraphicsItem(parent), m_tPixmap(pixmap)
{
	setFlags(QGraphicsPixmapItem::ItemIsMovable | QGraphicsPixmapItem::ItemIsSelectable);
}

QGraphicsItem * lxQGraphicsPixmapItem::duplicate()
{
	lxQGraphicsPixmapItem * item = new lxQGraphicsPixmapItem(m_tPixmap);
	item->setTransform(sceneTransform());
	item->setScale(scale());
	item->setZValue(zValue() + 0.1);
	return item;
}

QRectF lxQGraphicsPixmapItem::boundingRect() const
{
	//return m_tPixmap.rect();
	return QRectF(-m_tPixmap.width() / 2, -m_tPixmap.height() / 2., m_tPixmap.width(), m_tPixmap.height());
}

void lxQGraphicsPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->drawPixmap(boundingRect().toRect(),m_tPixmap);

	QPainterPath path;
	path.addRect(boundingRect());

	if (option->state & QStyle::State_Selected)
	{
		itemHighlight(painter, path, option);
	}
}

void lxQGraphicsPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	// 首先重置所有的item的zvalue 
	for (auto item : scene()->items())
		item->setZValue(TOP_Z_INDEX);

	setZValue(TOP_Z_INDEX + 1);

	QGraphicsItem::mousePressEvent(event);
}
