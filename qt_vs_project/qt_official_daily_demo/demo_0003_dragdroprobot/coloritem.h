#pragma once

#include <QGraphicsItem>

class ColorItem : public QGraphicsItem
{
public:
	ColorItem();
	~ColorItem();

public:

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
	QColor mColor;

};
