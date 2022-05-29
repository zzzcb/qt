#include "edge.h"
#include "node.h"

#include <QPainter>
#include <qmath.h>
#include <QDebug>

Edge::Edge(Node* srcNode, Node* dstNode)
	:mArrowSize(10)
{
	mSrcNode = srcNode;
	mDstNode = dstNode;
	mSrcNode->addEdge(this);
	mDstNode->addEdge(this);
	adjust();

}

Edge::~Edge()
{
}

void Edge::adjust()
{
	if (!mSrcNode || !mDstNode)
		return;

	QLineF line(mapFromItem(mSrcNode, 0, 0), mapFromItem(mDstNode, 0, 0));
	qreal length = line.length();

	prepareGeometryChange();
	if (length > qreal(20.))
	{
		// 10sin  10cos 
		QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
		mSrcPt = line.p1() + edgeOffset;
		mDstPt = line.p2() - edgeOffset;
	}
	else
	{
		mSrcPt = mDstPt = line.p1();
	}


}

Node* Edge::sourceNode() const
{
	return mSrcNode;
}

Node* Edge::destNode() const
{
	return mDstNode;
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	if (!mSrcNode || !mDstNode)
		return;

	QLineF line(mSrcPt, mDstPt);
	if (qFuzzyCompare(line.length(), qreal(0.)))
		return;

	
	// draw line 
	painter->drawLine(line);

	// draw arrow 
	double angle = std::atan2(-line.dy(), line.dx());
	QPointF sourceArrowP1 = mSrcPt + QPointF(sin(angle + M_PI / 3) * mArrowSize,
		cos(angle + M_PI / 3) * mArrowSize);
	QPointF sourceArrowP2 = mSrcPt + QPointF(sin(angle + M_PI - M_PI / 3) * mArrowSize,
		cos(angle + M_PI - M_PI / 3) * mArrowSize);
	QPointF destArrowP1 = mDstPt + QPointF(sin(angle - M_PI / 3) * mArrowSize,
		cos(angle - M_PI / 3) * mArrowSize);
	QPointF destArrowP2 = mDstPt + QPointF(sin(angle - M_PI + M_PI / 3) * mArrowSize,
		cos(angle - M_PI + M_PI / 3) * mArrowSize);

	painter->setBrush(Qt::black);
	painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
	painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}

QRectF Edge::boundingRect() const
{
	if (!mSrcNode || !mDstNode)
		return QRectF();

	qreal penWidth = 1;
	qreal extra = (penWidth + mArrowSize) / 2.0;

	return QRectF(mSrcPt, QSize(mDstPt.x() - mSrcPt.x(), mDstPt.y() - mSrcPt.y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
}
