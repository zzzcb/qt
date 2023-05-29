#pragma once

#include <QGraphicsItem>
#include <QMimeData>

class lxQGraphicsMimeData :public QMimeData
{
	Q_OBJECT
public:
	lxQGraphicsMimeData(QList<QGraphicsItem*> items);
	~lxQGraphicsMimeData();
	QList<QGraphicsItem*> getItems() const;

private:
	QList<QGraphicsItem*> m_listItem;
};

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