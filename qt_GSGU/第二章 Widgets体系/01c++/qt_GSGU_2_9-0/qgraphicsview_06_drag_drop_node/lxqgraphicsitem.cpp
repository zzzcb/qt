#pragma execution_character_set("utf-8")
#include "lxqgraphicsitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QApplication>
#include <QDebug>


/** ============================ucp item============================*/

lxQGraphicsUCPItem::lxQGraphicsUCPItem(QGraphicsItem*parent /*= nullptr*/)
	:QGraphicsItem(parent)
{
}

void lxQGraphicsUCPItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	painter->drawRect(-3, -3, 6, 6);
}

QRectF lxQGraphicsUCPItem::boundingRect() const
{
	return QRectF(-5, -5, 10, 10);
}



/** ============================dcp item============================*/

lxQGraphicsDCPItem::lxQGraphicsDCPItem(QGraphicsItem*parent /*= nullptr*/)
	:QGraphicsItem(parent)
{
	setFlag(GraphicsItemFlag::ItemIsSelectable);
}

void lxQGraphicsDCPItem::setDCPText(QString text)
{
	for (int i = 1; i < text.size(); i += 2)
		text.insert(i, '\n');
	mstr_text = text;
}

void lxQGraphicsDCPItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	if (mstr_text != "")
	{
		painter->save();

		QFont font;
		font.setPixelSize(10);
		font.setBold(true);
		painter->setFont(font);
		painter->drawRect(-5, -5, 10, 10);
		painter->drawText(0, 5, 10, 30, Qt::AlignLeft | Qt::AlignTop, mstr_text);
		painter->restore();
	}
	else
	{
		painter->drawRect(-5, -5, 10, 10);
	}
}

QRectF lxQGraphicsDCPItem::boundingRect() const
{
	return QRectF(-5, -5, 15, 40);
}

void lxQGraphicsDCPItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

	mt_startPt = scenePos();

	/**该dcp已经有了一个line,需要删除已有的line*/  
	if (mp_line != nullptr)
	{
		mp_line->getDstItem()->removeLine(mp_line);

		scene()->removeItem(mp_line);
		delete mp_line;
		mp_line = nullptr;
	}

	mp_line = new lxQGrphicsCurveLineItem(this, nullptr);
	scene()->addItem(mp_line);


	QGraphicsItem::mousePressEvent(event);
}

void lxQGraphicsDCPItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	mt_endPt = mapToScene(event->pos());

	mp_line->setSrcDstPt(mt_startPt, mt_endPt);

	QGraphicsItem::mouseMoveEvent(event);
}

void lxQGraphicsDCPItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF releasePt = mapToScene(event->pos());

	bool lineValid = false;
	lxQGraphicsUCPItem* dstItem;
	for (auto item : scene()->items(releasePt))
	{
		if (dstItem = qgraphicsitem_cast<lxQGraphicsUCPItem*>(item))
		{
			lineValid = true;
			break;
		}
	}

	if (!lineValid)
	{
		scene()->removeItem(mp_line);
		delete mp_line;
		mp_line = nullptr;
	}
	else
	{
		/**连线成功*/
		dstItem->addLine(mp_line);   // 记录该line 到dstItem 
		mp_line->setDstItem(dstItem);
	}

	scene()->update();

	QGraphicsItem::mouseReleaseEvent(event);
}



/**============================ curve line item =================================*/

lxQGrphicsCurveLineItem::lxQGrphicsCurveLineItem(lxQGraphicsDCPItem* srcItem, lxQGraphicsUCPItem*dstItem, QGraphicsItem*parent/*=nullptr*/)
	:QGraphicsItem(parent)
{
	mp_srcItem = srcItem;
	mp_dstItem = dstItem;
}

void lxQGrphicsCurveLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	if (!mb_valid)
		return;

	if (mp_srcItem != nullptr && mp_dstItem != nullptr)
	{
		mt_srcPt = mapFromItem(mp_srcItem, 0, 0);
		mt_dstPt = mapFromItem(mp_dstItem, 0, 0);
	}


	QPainterPath path(mt_srcPt);
	
	QPointF c1;
	QPointF c2;

	/**c1 控制start 点 c2控制end点*/
	qreal dX = mt_dstPt.x() - mt_srcPt.x();
	qreal dY = mt_dstPt.y() - mt_srcPt.y();
	/**目标点在下方*/
	if (dY >= 0)
	{
		c1 = QPointF(mt_srcPt.x(), mt_srcPt.y() + dY / 2);
		c2 = QPointF(mt_dstPt.x(), mt_srcPt.y() + dY / 2);
	}
	else
	{
		c1 = QPointF(mt_srcPt.x() + dX / 2, mt_srcPt.y() - dY);
		c2 = QPointF(mt_dstPt.x() - dX / 2, mt_dstPt.y() + dY);
	}

	/**draw curve line */
	path.cubicTo(c1, c2, mt_dstPt);

	painter->setPen(Qt::red);
	painter->drawPath(path);

}

QRectF lxQGrphicsCurveLineItem::boundingRect() const
{
	if (!mb_valid)
		return QRectF();

	qreal penWidth = 1;
	//qreal extra = (penWidth + mArrowSize) / 2.0;
	qreal extra = 5;

	return QRectF(mt_srcPt, QSize(mt_dstPt.x() - mt_srcPt.x(), mt_dstPt.y() - mt_srcPt.y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
}



/**============================  body item =================================*/

lxQGraphicsBodyItem::lxQGraphicsBodyItem(int shape,QGraphicsItem*parent/*=nullptr*/)
	:QGraphicsItem(parent),mn_shape(shape)
{
	setFlags(GraphicsItemFlag::ItemIsMovable | GraphicsItemFlag::ItemIsSelectable | GraphicsItemFlag::ItemSendsGeometryChanges);
}

void lxQGraphicsBodyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	if(mn_shape == 0)
		painter->drawRoundedRect(-30, -30, 60, 60, 10, 10);
	else if(mn_shape == 1)
		painter->drawEllipse(-30, -30, 60, 60);
}

QRectF lxQGraphicsBodyItem::boundingRect() const
{
	return QRectF(-30,-30,60,60);
}


/**============================ node item =================================*/

lxQGraphicsNodeItem::lxQGraphicsNodeItem(lxQVizItemType itemType,QGraphicsItem*parent /*= nullptr*/)
{
	switch (itemType)
	{
	case Start:
	{
		lxQGraphicsBodyItem* bodyItem = new lxQGraphicsBodyItem(1, this);
		lxQGraphicsUCPItem* upItem = new lxQGraphicsUCPItem(bodyItem);
		lxQGraphicsDCPItem* downItem1 = new lxQGraphicsDCPItem(bodyItem);
		upItem->setPos(0, -33);
		downItem1->setPos(0, 35);
		break;
	}
	case CheckDI:
	{
		lxQGraphicsBodyItem* bodyItem = new lxQGraphicsBodyItem(0, this);
		lxQGraphicsUCPItem* upItem = new lxQGraphicsUCPItem(bodyItem);
		lxQGraphicsDCPItem* downItem1 = new lxQGraphicsDCPItem(bodyItem);
		lxQGraphicsDCPItem* downItem2 = new lxQGraphicsDCPItem(bodyItem);
		upItem->setPos(0, -33);
		downItem1->setPos(-12, 35);
		downItem2->setPos(12, 35);
		downItem1->setDCPText("0");
		downItem2->setDCPText("1");
		break;
	}
	case WaitDI:
	{
		lxQGraphicsBodyItem* bodyItem = new lxQGraphicsBodyItem(0, this);
		lxQGraphicsUCPItem* upItem = new lxQGraphicsUCPItem(bodyItem);
		lxQGraphicsDCPItem* downItem1 = new lxQGraphicsDCPItem(bodyItem);
		lxQGraphicsDCPItem* downItem2 = new lxQGraphicsDCPItem(bodyItem);
		upItem->setPos(0, -33);
		downItem1->setPos(-12, 35);
		downItem2->setPos(12, 35);
		downItem1->setDCPText("0");
		downItem2->setDCPText("1");
		break;
	}
	case SetDO:
	{
		lxQGraphicsBodyItem* bodyItem = new lxQGraphicsBodyItem(0, this);
		lxQGraphicsUCPItem* upItem = new lxQGraphicsUCPItem(bodyItem);
		lxQGraphicsDCPItem* downItem1 = new lxQGraphicsDCPItem(bodyItem);
		lxQGraphicsDCPItem* downItem2 = new lxQGraphicsDCPItem(bodyItem);
		upItem->setPos(0, -33);
		downItem1->setPos(-12, 35);
		downItem2->setPos(12, 35);
		downItem1->setDCPText("0");
		downItem2->setDCPText("1");
		break;
	}
	case RelMove:
	{
		lxQGraphicsBodyItem* bodyItem = new lxQGraphicsBodyItem(0, this);
		lxQGraphicsUCPItem* upItem = new lxQGraphicsUCPItem(bodyItem);
		lxQGraphicsDCPItem* downItem1 = new lxQGraphicsDCPItem(bodyItem);
		lxQGraphicsDCPItem* downItem2 = new lxQGraphicsDCPItem(bodyItem);
		upItem->setPos(0, -33);
		downItem1->setPos(-12, 35);
		downItem2->setPos(12, 35);
		downItem1->setDCPText("成功");
		downItem2->setDCPText("失败");
		break;
	}
	case Move:
	{
		lxQGraphicsBodyItem* bodyItem = new lxQGraphicsBodyItem(0, this);
		lxQGraphicsUCPItem* upItem = new lxQGraphicsUCPItem(bodyItem);
		lxQGraphicsDCPItem* downItem1 = new lxQGraphicsDCPItem(bodyItem);
		upItem->setPos(0, -33);
		downItem1->setPos(0, 35);
		break;
	}
	default:
		break;
	}

}

void lxQGraphicsNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
}

QRectF lxQGraphicsNodeItem::boundingRect() const
{
	return QRectF();
}



