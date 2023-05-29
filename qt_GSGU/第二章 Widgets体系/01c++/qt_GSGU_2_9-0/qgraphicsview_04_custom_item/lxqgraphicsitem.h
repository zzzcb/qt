#pragma once

#include <QGraphicsItem>

// lxQGraphicsPixmapItem 
class lxQGraphicsPixmapItem : public QGraphicsItem
{
public:
	lxQGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);

	QGraphicsItem * duplicate();
	QRectF boundingRect() const override;

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

	QPixmap m_tPixmap;
};