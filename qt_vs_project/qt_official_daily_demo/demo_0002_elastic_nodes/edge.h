#pragma once

#include <QGraphicsItem>

class Node;
class Edge : public QGraphicsItem
{
public:
	Edge(Node* srcNode,Node* dstNode);
	~Edge();

	void adjust();
	Node* sourceNode() const;
	Node* destNode() const;



	enum {Type = UserType+2};
	int type() const override { return Type; };
protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;

private:
	Node* mSrcNode, *mDstNode;
	qreal mArrowSize;
	QPointF mSrcPt;
	QPointF mDstPt;

};
