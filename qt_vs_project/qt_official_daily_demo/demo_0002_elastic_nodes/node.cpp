#include "node.h"
#include "graphwidget.h"
#include "edge.h"

#include <QGraphicsSceneMouseEvent>
#include <QStyleOption>
#include <QDebug>

Node::Node(GraphWidget *graphWidget)
	:mpGraphWidget(graphWidget)
{
	setFlag(GraphicsItemFlag::ItemIsMovable);
	setFlag(GraphicsItemFlag::ItemSendsGeometryChanges);
	setZValue(-1);
}

Node::~Node()
{
}

void Node::addEdge(Edge* edge)
{
	mlistEdge << edge;
	edge->adjust();

	
}

void Node::calcForces()
{
	if (!scene() || scene()->mouseGrabberItem() == this)
	{
		mpNewPos = pos();
		return;
	}

	qreal xvel = 0;
	qreal yvel = 0;
	const QList<QGraphicsItem *> items = scene()->items();
	for (QGraphicsItem *item : items) {
		Node *node = qgraphicsitem_cast<Node *>(item);
		if (!node)
			continue;

		QPointF vec = mapToItem(node, 0, 0);
		qreal dx = vec.x();
		qreal dy = vec.y();
		double l = 2.0 * (dx * dx + dy * dy);
		if (l > 0) {
			xvel += (dx * 150.0) / l;
			yvel += (dy * 150.0) / l;
		}
	}
	double weight = (mlistEdge.size() + 1) * 10;
	for (const Edge *edge : qAsConst(mlistEdge)) {
		QPointF vec;
		if (edge->sourceNode() == this)
			vec = mapToItem(edge->destNode(), 0, 0);
		else
			vec = mapToItem(edge->sourceNode(), 0, 0);
		xvel -= vec.x() / weight;
		yvel -= vec.y() / weight;
	}
	if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
		xvel = yvel = 0;

	QRectF sceneRect = scene()->sceneRect();
	mpNewPos = pos() + QPointF(xvel, yvel);
	mpNewPos.setX(qMin(qMax(mpNewPos.x(), sceneRect.left() + 10), sceneRect.right() - 10));
	mpNewPos.setY(qMin(qMax(mpNewPos.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));

}

bool Node::advancePos()
{
	if (mpNewPos == pos())
		return false;

	setPos(mpNewPos);
	return true;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	//draw shadow
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::darkGray);
	painter->drawEllipse(-7, -7, 20, 20);

	QRadialGradient rGradient(-3, -3, 10);
	if (option->state & QStyle::State_Sunken)
	{
		rGradient.setCenter(3, 3);
		rGradient.setFocalPoint(3, 3);
		rGradient.setColorAt(1, QColor(Qt::yellow).lighter(120));
		rGradient.setColorAt(0, QColor(Qt::darkYellow).lighter(120));
	}
	else
	{
		rGradient.setColorAt(0, Qt::yellow);
		rGradient.setColorAt(1, Qt::darkYellow);
	}
	painter->setBrush(rGradient);
	painter->setPen(QPen(Qt::black,0));
	painter->drawEllipse(-10, -10, 20, 20);

}

QRectF Node::boundingRect() const
{
	qreal adjust = 2;
	return QRectF(-10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath Node::shape() const
{
	QPainterPath path;
	path.addEllipse(-10, -10, 20, 20);
	return path;
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}

QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
	switch (change)
	{
	case QGraphicsItem::ItemPositionHasChanged:
		for (auto edge : qAsConst(mlistEdge))
			edge->adjust();

		mpGraphWidget->itemMoved(); // 开启 移动定时器
		break;
	default:
		break;
	}
	return QGraphicsItem::itemChange(change, value);
}
