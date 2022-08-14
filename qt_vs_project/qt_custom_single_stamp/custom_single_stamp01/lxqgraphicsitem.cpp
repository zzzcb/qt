#pragma execution_character_set("utf-8")
#include "lxqgraphicsitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QtMath>
#include <QStyleOptionGraphicsItem>
#include <QDebug>


static void itemHighlight(QPainter *painter, QPainterPath path, const QStyleOptionGraphicsItem *option)
{
	QPen pen;
	pen.setWidth(3);
	pen.setColor(QColor(237, 149, 47));
	painter->setPen(pen);
	painter->drawPath(path);
}


/* ============================ pallet item =================================*/
lxQGraphicsPalletItem::lxQGraphicsPalletItem(qreal l /*= 1120*/, qreal w /*= 1000*/, QGraphicsItem* parent /*= nullptr*/)
	:AbstractGraphicsItem(parent)
{
	md_l = l / mm2PixelRatio;
	md_w = w / mm2PixelRatio;

	setFlags( GraphicsItemFlag::ItemIsSelectable);
	setZValue(-1);
}


QGraphicsItem * lxQGraphicsPalletItem::duplicate() const
{
	lxQGraphicsPalletItem * item = new lxQGraphicsPalletItem(md_l*mm2PixelRatio,md_w*mm2PixelRatio);
	item->setPos(pos().x(), pos().y());
	item->setTransform(transform());
	item->setTransformOriginPoint(transformOriginPoint());
	item->setRotation(rotation());
	item->setScale(scale());
	item->setZValue(zValue() + 0.1);
	return item;
}

void lxQGraphicsPalletItem::rotateAngle(qreal degree)
{
	setRotation(degree);
}

void lxQGraphicsPalletItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	painter->fillRect(boundingRect(), Qt::green);

	QPainterPath path;
	path.addRect(boundingRect());
	if (option->state & QStyle::State_Selected)
	{
		itemHighlight(painter, path, option);
	}
}

QRectF lxQGraphicsPalletItem::boundingRect() const
{
	return QRectF(-md_l / 2, -md_w / 2, md_l, md_w);
}



lxQGraphicsBoxItem::lxQGraphicsBoxItem(qreal l /*= 500*/, qreal w /*= 300*/, QGraphicsItem* parent /*= nullptr*/)
	:AbstractGraphicsItem(parent)
{
	md_l = l / mm2PixelRatio;
	md_w = w / mm2PixelRatio;

	setFlags(GraphicsItemFlag::ItemIsSelectable);
}


void lxQGraphicsBoxItem::rotateAngle(qreal degree)
{
	setRotation(degree);
}

QGraphicsItem * lxQGraphicsBoxItem::duplicate() const
{
	lxQGraphicsBoxItem * item = new lxQGraphicsBoxItem(md_l*mm2PixelRatio, md_w*mm2PixelRatio);
	item->setPos(pos().x(), pos().y());
	item->setTransform(transform());
	item->setTransformOriginPoint(transformOriginPoint());
	item->setRotation(rotation());
	item->setScale(scale());
	item->setZValue(zValue() + 0.1);
	return item;
}

/* ============================ box item =================================*/

void lxQGraphicsBoxItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	painter->fillRect(boundingRect(), Qt::red);

	QPainterPath path;
	path.addRect(boundingRect());
	if (option->state & QStyle::State_Selected)
	{
		itemHighlight(painter, path, option);
	}
}

QRectF lxQGraphicsBoxItem::boundingRect() const
{
	return QRectF(-md_l / 2, -md_w / 2, md_l, md_w);
}

/* ============================ bucket item =================================*/

lxQGraphicsBucketItem::lxQGraphicsBucketItem(qreal d /*= 200*/, QGraphicsItem* parent /*= nullptr*/)
	:AbstractGraphicsItem(parent)
{
	md_d = d / mm2PixelRatio;

	setFlags( GraphicsItemFlag::ItemIsSelectable);

}

QGraphicsItem * lxQGraphicsBucketItem::duplicate() const
{
	lxQGraphicsBucketItem * item = new lxQGraphicsBucketItem(md_d*mm2PixelRatio);
	item->setPos(pos().x(), pos().y());
	item->setTransform(transform());
	item->setTransformOriginPoint(transformOriginPoint());
	item->setRotation(rotation());
	item->setScale(scale());
	item->setZValue(zValue() + 0.1);
	return item;
}

void lxQGraphicsBucketItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	QPainterPath path;
	path.addEllipse(QPointF(0, 0), md_d / 2, md_d / 2);
	painter->fillPath(path, Qt::blue);

	if (option->state & QStyle::State_Selected)
	{
		itemHighlight(painter, path, option);
	}
}

QRectF lxQGraphicsBucketItem::boundingRect() const
{
	return QRectF(-md_d / 2, -md_d / 2, md_d, md_d);
}

QPainterPath lxQGraphicsBucketItem::shape() const
{
	QPainterPath path;
	path.addEllipse(QPointF(0, 0), md_d / 2, md_d / 2);
	return path;
}


/* ============================ rotate ring item =================================*/
lxQGraphicsRotateRing* lxQGraphicsRotateRing::m_pInstance = nullptr;

lxQGraphicsRotateRing::lxQGraphicsRotateRing(qreal d /*= 150*/, qreal t /*= 5*/, QGraphicsItem* parent /*= nullptr*/)
	:AbstractGraphicsItem(parent)
{
	md_d = d;
	md_t = t;

	setFlag(GraphicsItemFlag::ItemIsSelectable);
	setAcceptHoverEvents(true);

	setZValue(10000);
}

void lxQGraphicsRotateRing::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	QPainterPath path;
	path.addEllipse(QPointF(0, 0), md_d / 2, md_d / 2);
	path.addEllipse(QPointF(0, 0), (md_d-2*md_t) / 2, (md_d - 2 * md_t) / 2);
	
	if(!mb_hover)
		painter->fillPath(path,QColor(103,137,199));     /// 浅
	else 
		painter->fillPath(path, QColor(60,142, 247));    /// 深

	QPen pen;
	if (mb_rotate)
	{
		/**初始点与圆心的连线*/
		painter->save();
		pen.setColor(QColor(103, 137, 199));
		painter->setPen(pen);
		painter->drawLine(QPointF(0, 0), mt_startPt);
		painter->restore();

		/**交点与圆心的连线*/
		painter->save();
		pen.setWidth(md_t);
		pen.setColor(QColor(60, 142, 247));
		painter->setPen(pen);
		painter->drawLine(QPointF(0, 0), mt_circlePt);
		painter->restore();

		/**当前点与圆心的连线*/
		painter->save();
		pen.setWidth(md_t/2.);
		pen.setColor(QColor(0, 0, 0));
		QVector<qreal> dashes;
		qreal space = 4;
		dashes << 3 << space;
		pen.setDashPattern(dashes);
		painter->setPen(pen);
		painter->drawLine(QPointF(0, 0), mt_curPt);
		painter->restore();

		// 在当前点画两个箭头
		//painter->save();

		//painter->restore();
	}



}

QRectF lxQGraphicsRotateRing::boundingRect() const
{
	return QRectF(-md_d / 2, -md_d / 2, md_d, md_d);
}

QPainterPath lxQGraphicsRotateRing::shape() const
{
	QPainterPath path;
	path.addEllipse(QPointF(0, 0), md_d / 2, md_d / 2);
	path.addEllipse(QPointF(0, 0), (md_d - 2 * (md_t+5)) / 2, (md_d - 2 * (md_t+5)) / 2);
	return path;
}

void lxQGraphicsRotateRing::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	mb_rotate = true;
	//mt_startPt = event->pos();
	mt_startPt = QPointF(md_d/2.,0);

	/***由于group item scenePos有问题所以这里要特殊处理下*/
	if (qgraphicsitem_cast<lxQGraphicsItemGroup*>(mt_rotatedObj))
	{
		auto rect = mt_rotatedObj->sceneBoundingRect();
		auto scenePos = rect.topLeft() + QPointF(rect.width(), rect.height()) / 2.;

		mt_rotatedObj->setTransformOriginPoint(mt_rotatedObj->transform().inverted().map(scenePos));
	}

	QGraphicsItem::mousePressEvent(event);
}

#include <QApplication>
void lxQGraphicsRotateRing::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (!mb_rotate)// || QLineF(event->pos(), mt_startPt).length() < QApplication::startDragDistance())
		return;

	mt_curPt = event->pos();
	md_curAngle = qAtan2(mt_curPt.y(), mt_curPt.x());
	qreal r = md_d / 2.;
	mt_circlePt = QPointF(r*qCos(md_curAngle),r*qSin(md_curAngle));

	md_rotateAngle = md_curAngle - qAtan2(mt_startPt.y(), mt_startPt.x());

	if (mt_rotatedObj)
	{
		mt_rotatedObj->setRotation(md_rotateAngle * 180.0 / M_PI);
	}

	QGraphicsItem::mouseMoveEvent(event);
}

#include "lxqadddialog.h"
void lxQGraphicsRotateRing::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	mb_rotate = false;

	lxQAddDialog rotateAngleDialog;
	rotateAngleDialog.initEditor("设置精准的旋转角度(degree)",{ {"旋转角度","QLineEdit",QString::number(md_rotateAngle*180.0 / M_PI) } });
	if (rotateAngleDialog.exec())
	{
		 auto vRes = rotateAngleDialog.getEditorResult();

		 mt_rotatedObj->setRotation(vRes[0].toDouble());
	}
}

void lxQGraphicsRotateRing::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	setToolTip("\n 旋转选中的对象 \n");
	mb_hover = true;
	update();   ///<  will call paint function to update color
}

void lxQGraphicsRotateRing::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	mb_hover = false;
}


/* ============================ trans cross item =================================*/
lxQGraphicsTransCross* lxQGraphicsTransCross::m_pInstance = nullptr;

lxQGraphicsTransCross::lxQGraphicsTransCross(qreal length /*= 100*/, QGraphicsItem* parent /*= nullptr*/)
	:AbstractGraphicsItem(parent)
{
	md_length = length;

	setZValue(10000);
	setFlag(GraphicsItemFlag::ItemIsSelectable);
	setAcceptHoverEvents(true);
}

#include <QDesktopWidget>
void lxQGraphicsTransCross::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	if (!mb_transx && !mb_transy && !mb_transxy)
	{
		painter->save();
		/** 绘制x轴箭头*/
		QPainterPath path;
		qreal arrowL = 10;
		qreal arrowW = 7;
		qreal lineW = 4;
		path.addPolygon(QPolygonF() <<
			QPointF(0, 0) << QPointF(0, -lineW / 2.) << QPointF(md_length - arrowL, -lineW / 2.) << QPointF(md_length - arrowL, -arrowW / 2.) << QPointF(md_length, 0) <<
			QPointF(md_length - arrowL, arrowW / 2.) << QPointF(md_length - arrowL, lineW / 2.) << QPointF(0, lineW / 2.) << QPointF(0,0));
		if(mb_hoverx)
			painter->fillPath(path,QBrush(QColor(241,88,105).lighter(150)));    ///< light color 
		else 
			painter->fillPath(path, QBrush(QColor(241, 88, 105)));


		/** 绘制y轴箭头*/
		painter->rotate(90);
		if (mb_hovery)
			painter->fillPath(path, QBrush(QColor(143, 210, 76).lighter(150)));
		else
			painter->fillPath(path, QBrush(QColor(143, 210, 76)));

		painter->restore();
		/** 绘制xy移动方块*/
		if(mb_hoverxy)
			painter->fillRect(md_length / 2., md_length / 2., 20, 20, QColor(141, 159, 200).lighter(150));
		else 
			painter->fillRect(md_length / 2., md_length / 2., 20, 20, QColor(141, 159, 200));

	}
	else
	{
		auto avaScreenSize = QApplication::desktop()->availableGeometry().size();
		QPen pen;

		if (mb_transx || mb_hoverxy)
		{
			painter->save();
			pen.setColor(QColor(241, 88, 105));
			painter->setPen(pen);
			painter->drawLine(QPointF(-avaScreenSize.width(), 0), QPointF(avaScreenSize.width(), 0));
			painter->restore();

		}
		
		if (mb_transy || mb_hoverxy)
		{
			painter->save();
			pen.setColor(QColor(143, 210, 76));
			painter->setPen(pen);
			painter->drawLine(QPointF(0, -avaScreenSize.height()), QPointF(0, avaScreenSize.height()));
			painter->restore();
		}
	}

}

QRectF lxQGraphicsTransCross::boundingRect() const
{
	return QRectF(0,0,md_length,md_length);
}

QPainterPath lxQGraphicsTransCross::shape() const
{
	QPainterPath path;
	qreal arrowL = 10+2;  ///< 更大区域 以更好的选择
	qreal arrowW = 7+2;
	qreal lineW = 4+2;
	path.addPolygon(QPolygonF() <<
		QPointF(0, 0) << QPointF(0, -lineW / 2.) << QPointF(md_length - arrowL, -lineW / 2.) << QPointF(md_length - arrowL, -arrowW / 2.) << QPointF(md_length, 0) <<
		QPointF(md_length - arrowL, arrowW / 2.) << QPointF(md_length - arrowL, lineW / 2.) << QPointF(0, lineW / 2.) << QPointF(0, 0));

	path.addPolygon(QPolygonF() <<
		QPointF(0, 0) << QPointF(-lineW / 2.,0) << QPointF( -lineW / 2., md_length - arrowL) << QPointF(-arrowW / 2., md_length - arrowL) << QPointF(0, md_length) <<
		QPointF( arrowW / 2.,md_length - arrowL) << QPointF( lineW / 2., md_length - arrowL) << QPointF(lineW / 2.,0) << QPointF(0, 0));


	path.addRect(md_length / 2., md_length / 2., 20, 20);

	return path;
}

void lxQGraphicsTransCross::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	auto pos = event->pos();

	if (QRectF(md_length / 2. - 5, md_length / 2. - 5, 20 + 5, 20 + 5).contains(pos))
	{
		mb_transx = false;
		mb_transy = false;
		mb_transxy = true;
	}
	else
	{
		if (qAbs(pos.x()) > qAbs(pos.y()))
		{
			mb_transx = true;
			mb_transy = false;
			mb_transxy =false;
		}
		else
		{
			mb_transx = false;
			mb_transy = true;
			mb_transxy = false;
		}

	}

	mt_startPt = event->pos();
	mt_curTrans = mt_transObj->transform();


	QGraphicsItem::mousePressEvent(event);

}

void lxQGraphicsTransCross::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	//if ((!mb_transx && !mb_transy && !mb_transxy) || QLineF(event->pos(), mt_startPt).length() < QApplication::startDragDistance())
	if ((!mb_transx && !mb_transy && !mb_transxy))
		return;

	mt_curPt = event->pos();

	auto dis = mt_curPt - mt_startPt;

	if (mt_transObj)
	{
		if (mb_transx)
		{
			mt_curTrans.translate(dis.x(), 0);
		}
		else if (mb_transy)
		{
			mt_curTrans.translate(0, dis.y());
		}
		else if (mb_transxy)
		{
			mt_curTrans.translate(dis.x(), dis.y());
		}

		mt_transObj->setTransform(mt_curTrans);
	}

	mt_startPt = mt_curPt;

	QGraphicsItem::mouseMoveEvent(event);
}

void lxQGraphicsTransCross::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	mb_transx = false;
	mb_transy = false;
	mb_transxy = false;

	auto toolScenePos = mt_transObj->scenePos();
	/***由于group item scenePos有问题所以这里要特殊处理下*/
	if (qgraphicsitem_cast<lxQGraphicsItemGroup*>(mt_transObj))
	{
		auto rect = mt_transObj->sceneBoundingRect();
		toolScenePos = rect.topLeft() + QPointF(rect.width(), rect.height()) / 2.;
	}
	setPos(toolScenePos);

	QGraphicsItem::mouseReleaseEvent(event);

}

void lxQGraphicsTransCross::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	setToolTip("\n 移动选中的对象 \n");
	auto pos = event->pos();

	if (QRectF(md_length / 2.-5, md_length / 2.-5, 20+5, 20+5).contains(pos))
	{
		mb_hoverx = false;
		mb_hovery = false;
		mb_hoverxy = true;
	}
	else
	{
		if (qAbs(pos.x()) > qAbs(pos.y()))
		{
			mb_hoverx = true;
			mb_hovery = false;
			mb_hoverxy = false;
		}
		else
		{
			mb_hoverx = false;
			mb_hovery = true;
			mb_hoverxy = false;
		}

	}

	update();   ///<  will call paint function to update color

	QGraphicsItem::hoverMoveEvent(event);

}

void lxQGraphicsTransCross::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	mb_hoverx = false;
	mb_hovery = false;
	mb_hoverxy = false;

	QGraphicsItem::hoverLeaveEvent(event);

}

lxQGraphicsItemGroup::lxQGraphicsItemGroup(QGraphicsItem* parent)
	:lxQAbstractGraphicsItem<QGraphicsItemGroup>(parent)
{
	setFlags(GraphicsItemFlag::ItemIsSelectable);
}

void lxQGraphicsItemGroup::updateBoundingRect()
{
	/** isnull 非nullptr，而是空对象*/
	if (m_tGroupBounding.isNull())
	{
		qDebug() << "before " << m_tGroupBounding;
		m_tGroupBounding = QGraphicsItemGroup::boundingRect();
		qDebug() << "after " << m_tGroupBounding;
	}
}

QGraphicsItem * lxQGraphicsItemGroup::duplicate() const
{
	return nullptr;
}

void lxQGraphicsItemGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	painter->drawRect(boundingRect());

	QPainterPath path;
	path.addRect(boundingRect());
	if (option->state & QStyle::State_Selected)
	{
		itemHighlight(painter, path, option);
	}
}

QRectF lxQGraphicsItemGroup::boundingRect() const
{
	return m_tGroupBounding;
}

lxQShapeMimeData::lxQShapeMimeData(QList<QGraphicsItem*> items)
{
	for (const auto&item : items)
	{
		if (auto _item = qgraphicsitem_cast<lxQAbstractGraphicsItem<>*>(item))
		{
			m_vpItem.push_back(_item->duplicate());
		}
	}
}

lxQShapeMimeData::~lxQShapeMimeData()
{
	for (auto& item : m_vpItem)
		delete item;

	m_vpItem.clear();
}
QList<QGraphicsItem*> lxQShapeMimeData::getItems() const
{
	return m_vpItem;
}
