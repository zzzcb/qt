#pragma execution_character_set("utf-8")
#include "lxqgraphicsitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QApplication>
#include <QStyleOptionGraphicsItem>
#include <QLabel>
#include <QDebug>

void itemHighlight(QPainter *painter, QPainterPath path, const QStyleOptionGraphicsItem *option)
{
	QPen pen;
	pen.setWidth(1);
	pen.setColor(QColor(239, 61, 84));
	painter->setPen(pen);
	painter->drawPath(path);
}

/** ============================ucp item============================*/

lxQGraphicsUCPItem::lxQGraphicsUCPItem(QGraphicsItem*parent /*= nullptr*/)
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

//LxGraphicsDCPItem::~LxGraphicsDCPItem()
//{
//	mLine->getDstItem()->removeLine(mLine);
//
//	scene()->removeItem(mLine);
//	delete mLine;
//	mLine = nullptr;
//}

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

	//mStartPt = mapToScene(event->pos());
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

	qDebug() << "mouse move ... end pt " << mt_endPt;

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
		dstItem->addLine(mp_line);   ///< 记录该line 到dstItem 
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

	//qDebug() << "line paint ................";
	//painter->drawRect(boundingRect());

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

	m_tPath = path;

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

void lxQGrphicsCurveLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_listAnmiItem.size() == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			auto anmi = new lxQGraphicsAnimItem;
			scene()->addItem(anmi);
			anmi->startAnimation(nullptr, m_tPath, i*0.02, 1000, -1, false);

			m_listAnmiItem.push_back(anmi);
		}
	}
	else
	{
		for (auto anmi : m_listAnmiItem)
		{
			scene()->removeItem(anmi);
			delete anmi;
		}
		m_listAnmiItem.clear();
	}
	QGraphicsItem::mousePressEvent(event);
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

void lxQGraphicsBodyItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_listAnmiItem.size() == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			auto anmi = new lxQGraphicsAnimItem;
			scene()->addItem(anmi);
			anmi->startAnimation(this, shape(), 0.02*i, 2000);

			m_listAnmiItem.push_back(anmi);
		}
	}
}


QPainterPath lxQGraphicsBodyItem::shape() const
{
	QPainterPath path;

	if (mn_shape == 0)
		path.addRoundedRect(boundingRect(), 10, 10);
	else if (mn_shape == 1)
		path.addEllipse(boundingRect());

	return path;
}

/**============================ viz item =================================*/

lxQGraphicsVizItem::lxQGraphicsVizItem(lxQVizItemType itemType,QGraphicsItem*parent /*= nullptr*/)
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
		qDebug() << "bodyItem " << bodyItem;
		qDebug() << "upItem " << upItem;
		qDebug() << "downItem1 " << downItem1;
		qDebug() << "downItem2 " << downItem2;
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

void lxQGraphicsVizItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	//painter->drawRect(boundingRect());
}

QRectF lxQGraphicsVizItem::boundingRect() const
{
	//return QRectF(-35, -35, 70, 70);
	return QRectF();
}

/**============================ anmi item =================================*/

lxQGraphicsAnimItem::lxQGraphicsAnimItem(QGraphicsItem*parent /*= nullptr*/)
{
	m_tRect = QRectF(-2, -2, 4, 4);
	m_tColor = QColor(Qt::red);

	m_pAnimationGroup = new QParallelAnimationGroup(this);
	m_pPosAnimation = new QPropertyAnimation(this, "pos");
	m_pScaleAnimation = new QPropertyAnimation(this, "scale");
}

bool priorThan(const QPointF& pt1, const QPointF& pt2)
{
	QLineF vec1(QPointF(0, 0), pt1);
	QLineF vec2(QPointF(0, 0), pt2);
	QLineF y(QPointF(0, 0), QPointF(0, -1.0));

	return vec1.angleTo(y) < vec2.angleTo(y);
}

void lxQGraphicsAnimItem::startAnimation(QGraphicsItem* parentItem, QPainterPath path, double beginPercent /*= 0.0*/, int duration /*= 1000*/, int loopCnt /*= -1*/, bool enableSort /*= true*/)
{
	if (parentItem && !parentItem->scene())
		return;

	setParentItem(parentItem);

	double scaleMin = 0.5;
	double scaleMax = 2.0;
	int pathPointNum = 100;

	QVector<QPointF> vecPt;

	for (double i = 0; i < 0.99; i += 1.0/pathPointNum)
		vecPt.push_back(path.pointAtPercent(i));

	if (enableSort)
	{
		// 对vecPt 进行排序 
		qSort(vecPt.begin(), vecPt.end(), priorThan);
	}

	int beginIdx = beginPercent * pathPointNum;
	vecPt = vecPt.mid(beginIdx);

	for (int i = 0; i < vecPt.size(); i++)
	{
		auto pt = vecPt[i];
		auto scale = (beginPercent + 0.01*i)*(scaleMax - scaleMin) + scaleMin;

		if (i == 0)
		{
			m_pPosAnimation->setStartValue(pt);
			m_pScaleAnimation->setStartValue(scale);
		}
		else if (i == vecPt.size() - 1)
		{
			m_pPosAnimation->setEndValue(pt);
			m_pScaleAnimation->setEndValue(scale);
		}
		else
		{
			m_pPosAnimation->setKeyValueAt(i*1.0 / vecPt.size(), pt);
			m_pScaleAnimation->setKeyValueAt(i*1.0 / vecPt.size(), scale);
		}
	}

	m_pAnimationGroup->addAnimation(m_pPosAnimation);
	m_pAnimationGroup->addAnimation(m_pScaleAnimation);

	for (int i = 0; i < m_pAnimationGroup->animationCount(); ++i)
	{
		QPropertyAnimation *anim = qobject_cast<QPropertyAnimation *>(m_pAnimationGroup->animationAt(i));
		anim->setDuration(duration);
		//anim->setEasingCurve(QEasingCurve::InOutQuad);
	}

	m_pAnimationGroup->setLoopCount(loopCnt);
	m_pAnimationGroup->start();
}



void lxQGraphicsAnimItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(QBrush(m_tColor));
	painter->drawEllipse(m_tRect);
}
QRectF lxQGraphicsAnimItem::boundingRect() const
{
	return m_tRect.adjusted(-10, -10, 10, 10);;
}
QPainterPath lxQGraphicsAnimItem::shape() const
{
	QPainterPath path;
	path.addEllipse(m_tRect);
	return path;
}
void lxQGraphicsAnimItem::slot_finished()
{
	if (scene())
	{
		scene()->removeItem(this);
	}
}
