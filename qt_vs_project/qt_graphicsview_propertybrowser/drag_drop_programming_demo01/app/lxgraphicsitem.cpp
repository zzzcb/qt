#pragma execution_character_set("utf-8")
#include "lxgraphicsitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDebug>


// ============================ ucp item =================================

LxGraphicsUCPItem::LxGraphicsUCPItem(QGraphicsItem*parent /*= nullptr*/)
	:QGraphicsItem(parent)
{

}

//LxGraphicsUCPItem::~LxGraphicsUCPItem()
//{
//	for (auto line : mvLine)
//	{
//		line->getSrcItem()->clearLine();
//
//		scene()->removeItem(line);
//		delete line;
//		line = nullptr;
//	}
//}

void LxGraphicsUCPItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	painter->drawRect(-3, -3, 6, 6);
}

QRectF LxGraphicsUCPItem::boundingRect() const
{
	return QRectF(-5, -5, 10, 10);
}



// ============================ dcp item =================================

LxGraphicsDCPItem::LxGraphicsDCPItem(QGraphicsItem*parent /*= nullptr*/)
	:QGraphicsItem(parent)
{
	setFlag(GraphicsItemFlag::ItemIsSelectable);
}

//LxGraphicsDCPItem::~LxGraphicsDCPItem()
//{
//	mLine->getDstItem()->removeLine(mLine);
//
//	scene()->removeItem(mLine);
//	delete mLine;
//	mLine = nullptr;
//}

void LxGraphicsDCPItem::setDCPText(QString text)
{
	for (int i = 1; i < text.size(); i += 2)
		text.insert(i, '\n');
	mText = text;
}

void LxGraphicsDCPItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	if (mText != "")
	{
		painter->save();

		QFont font;
		font.setPixelSize(10);
		font.setBold(true);
		painter->setFont(font);
		painter->drawRect(-5, -5, 10, 10);
		painter->drawText(0, 5, 10, 30, Qt::AlignLeft | Qt::AlignTop, mText);
		painter->restore();
	}
	else
	{
		painter->drawRect(-5, -5, 10, 10);
	}
}

QRectF LxGraphicsDCPItem::boundingRect() const
{
	return QRectF(-5, -5, 15, 40);
}

void LxGraphicsDCPItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

	//mStartPt = mapToScene(event->pos());
	mStartPt = scenePos();

	// 该dcp已经有了一个line,需要删除已有的line  
	if (mLine != nullptr)
	{
		mLine->getDstItem()->removeLine(mLine);

		scene()->removeItem(mLine);
		delete mLine;
		mLine = nullptr;
	}

	mLine = new LxGrphicsCurveLineItem(this, nullptr);
	scene()->addItem(mLine);


	QGraphicsItem::mousePressEvent(event);
}

void LxGraphicsDCPItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	mEndPt = mapToScene(event->pos());

	qDebug() << "mouse move ... end pt " << mEndPt;

	mLine->setSrcDstPt(mStartPt, mEndPt);

	QGraphicsItem::mouseMoveEvent(event);
}

void LxGraphicsDCPItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF releasePt = mapToScene(event->pos());

	bool lineValid = false;
	LxGraphicsUCPItem* dstItem;
	for (auto item : scene()->items(releasePt))
	{
		if (dstItem = qgraphicsitem_cast<LxGraphicsUCPItem*>(item))
		{
			lineValid = true;
			break;
		}
	}

	if (!lineValid)
	{
		scene()->removeItem(mLine);
		delete mLine;
		mLine = nullptr;
	}
	else
	{
		// 连线成功
		dstItem->addLine(mLine);   // 记录该line 到dstItem 
		mLine->setDstItem(dstItem);
	}

	scene()->update();

	QGraphicsItem::mouseReleaseEvent(event);
}



// ============================ curve line item =================================

LxGrphicsCurveLineItem::LxGrphicsCurveLineItem(LxGraphicsDCPItem* srcItem, LxGraphicsUCPItem*dstItem, QGraphicsItem*parent/*=nullptr*/)
	:QGraphicsItem(parent)
{
	mSrcItem = srcItem;
	mDstItem = dstItem;
}

void LxGrphicsCurveLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	if (!mbValid)
		return;

	qDebug() << "line paint ................";
	//painter->drawRect(boundingRect());

	if (mSrcItem != nullptr && mDstItem != nullptr)
	{
		mSrcPt = mapFromItem(mSrcItem, 0, 0);
		mDstPt = mapFromItem(mDstItem, 0, 0);
	}


	QPainterPath path(mSrcPt);
	
	QPointF c1;
	QPointF c2;

	// c1 控制start 点 c2控制end点
	qreal dX = mDstPt.x() - mSrcPt.x();
	qreal dY = mDstPt.y() - mSrcPt.y();
	// 目标点在下方
	if (dY >= 0)
	{
		c1 = QPointF(mSrcPt.x(), mSrcPt.y() + dY / 2);
		c2 = QPointF(mDstPt.x(), mSrcPt.y() + dY / 2);
	}
	else
	{
		c1 = QPointF(mSrcPt.x() + dX / 2, mSrcPt.y() - dY);
		c2 = QPointF(mDstPt.x() - dX / 2, mDstPt.y() + dY);
	}

	
	path.cubicTo(c1, c2, mDstPt);

	painter->setPen(Qt::red);
	painter->drawPath(path);

}

QRectF LxGrphicsCurveLineItem::boundingRect() const
{
	if (!mbValid)
		return QRectF();
	qDebug() << "line boundingRect ................";

	qreal penWidth = 1;
	//qreal extra = (penWidth + mArrowSize) / 2.0;
	qreal extra = 5;

	return QRectF(mSrcPt, QSize(mDstPt.x() - mSrcPt.x(), mDstPt.y() - mSrcPt.y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
}



// ============================  body item =================================

LxGraphicsBodyItem::LxGraphicsBodyItem(int shape,QGraphicsItem*parent/*=nullptr*/)
	:QGraphicsItem(parent),mShape(shape)
{
	setFlags(GraphicsItemFlag::ItemIsMovable | GraphicsItemFlag::ItemIsSelectable);
}

void LxGraphicsBodyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	if(mShape == 0)
		painter->drawRoundedRect(-30, -30, 60, 60, 10, 10);
	else if(mShape == 1)
		painter->drawEllipse(-30, -30, 60, 60);
}

QRectF LxGraphicsBodyItem::boundingRect() const
{
	return QRectF(-30,-30,60,60);
}

// ============================ viz item =================================

LxGraphicsVizItem::LxGraphicsVizItem(LxVizItemType itemType,QGraphicsItem*parent /*= nullptr*/)
{
	switch (itemType)
	{
	case Start:
	{
		LxGraphicsBodyItem* bodyItem = new LxGraphicsBodyItem(1, this);
		LxGraphicsUCPItem* upItem = new LxGraphicsUCPItem(bodyItem);
		LxGraphicsDCPItem* downItem1 = new LxGraphicsDCPItem(bodyItem);
		upItem->setPos(0, -33);
		downItem1->setPos(0, 35);
		break;
	}
	case CheckDI:
	{
		LxGraphicsBodyItem* bodyItem = new LxGraphicsBodyItem(0, this);
		LxGraphicsUCPItem* upItem = new LxGraphicsUCPItem(bodyItem);
		LxGraphicsDCPItem* downItem1 = new LxGraphicsDCPItem(bodyItem);
		LxGraphicsDCPItem* downItem2 = new LxGraphicsDCPItem(bodyItem);
		upItem->setPos(0, -33);
		downItem1->setPos(-12, 35);
		downItem2->setPos(12, 35);
		downItem1->setDCPText("0");
		downItem2->setDCPText("1");
		qDebug() << "bodyItem " << bodyItem;
		qDebug() << "upItem " << upItem;
		qDebug() << "downItem1 " << downItem1;
		qDebug() << "downItem2 " << downItem2;
		break;
	}
	case WaitDI:
	{
		LxGraphicsBodyItem* bodyItem = new LxGraphicsBodyItem(0, this);
		LxGraphicsUCPItem* upItem = new LxGraphicsUCPItem(bodyItem);
		LxGraphicsDCPItem* downItem1 = new LxGraphicsDCPItem(bodyItem);
		LxGraphicsDCPItem* downItem2 = new LxGraphicsDCPItem(bodyItem);
		upItem->setPos(0, -33);
		downItem1->setPos(-12, 35);
		downItem2->setPos(12, 35);
		downItem1->setDCPText("0");
		downItem2->setDCPText("1");
		break;
	}
	case SetDO:
	{
		LxGraphicsBodyItem* bodyItem = new LxGraphicsBodyItem(0, this);
		LxGraphicsUCPItem* upItem = new LxGraphicsUCPItem(bodyItem);
		LxGraphicsDCPItem* downItem1 = new LxGraphicsDCPItem(bodyItem);
		LxGraphicsDCPItem* downItem2 = new LxGraphicsDCPItem(bodyItem);
		upItem->setPos(0, -33);
		downItem1->setPos(-12, 35);
		downItem2->setPos(12, 35);
		downItem1->setDCPText("0");
		downItem2->setDCPText("1");
		break;
	}
	case RelMove:
	{
		LxGraphicsBodyItem* bodyItem = new LxGraphicsBodyItem(0, this);
		LxGraphicsUCPItem* upItem = new LxGraphicsUCPItem(bodyItem);
		LxGraphicsDCPItem* downItem1 = new LxGraphicsDCPItem(bodyItem);
		LxGraphicsDCPItem* downItem2 = new LxGraphicsDCPItem(bodyItem);
		upItem->setPos(0, -33);
		downItem1->setPos(-12, 35);
		downItem2->setPos(12, 35);
		downItem1->setDCPText("成功");
		downItem2->setDCPText("失败");
		break;
	}
	case Move:
	{
		LxGraphicsBodyItem* bodyItem = new LxGraphicsBodyItem(0, this);
		LxGraphicsUCPItem* upItem = new LxGraphicsUCPItem(bodyItem);
		LxGraphicsDCPItem* downItem1 = new LxGraphicsDCPItem(bodyItem);
		upItem->setPos(0, -33);
		downItem1->setPos(0, 35);
		break;
	}
	default:
		break;
	}

}

void LxGraphicsVizItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	//painter->drawRect(boundingRect());
}

QRectF LxGraphicsVizItem::boundingRect() const
{
	//return QRectF(-35, -35, 70, 70);
	return QRectF();
}

