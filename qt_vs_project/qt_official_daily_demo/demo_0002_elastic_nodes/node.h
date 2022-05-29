#pragma once

#include <QGraphicsItem>
#include <QGraphicsRectItem>

class GraphWidget;
class QGraphicsSceneMouseEvent;
class Edge;

class Node : public QGraphicsItem
{
public:
	Node(GraphWidget *graphWidget);
	~Node();

	void addEdge(Edge* edge);
	void calcForces();
	bool advancePos();

	
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	enum { Type = UserType + 1 };
	int type() const override { return Type; };


protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
	QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;


private:
	GraphWidget * mpGraphWidget;
	QList<Edge*> mlistEdge;
	QPointF mpNewPos;

};
