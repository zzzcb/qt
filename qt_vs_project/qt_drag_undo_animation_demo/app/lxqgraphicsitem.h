#pragma once

#include <QObject>
#include <QGraphicsItem>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

#include "common.h"

class lxQGrphicsCurveLineItem;

/** ucp : up connect point*/  
class lxQGraphicsUCPItem : public QGraphicsItem
{
public:
	lxQGraphicsUCPItem(QGraphicsItem*parent = nullptr);
	//~LxGraphicsUCPItem();

	enum { Type = UserType + 2 };
	int type()const override { return Type; };

	void addLine(lxQGrphicsCurveLineItem* line) { mlist_Line.push_back(line); };
	void removeLine(lxQGrphicsCurveLineItem* line) { mlist_Line.removeAll(line); };

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;

private:
	QList<lxQGrphicsCurveLineItem*> mlist_Line;   ///< 一个ucp 可能有多条line 进入

};

/** dcp : down connect point */
class lxQGraphicsDCPItem : public QGraphicsItem
{
public:
	lxQGraphicsDCPItem(QGraphicsItem*parent = nullptr);
	//~LxGraphicsDCPItem();
	void setDCPText(QString text);
	void clearLine() { mp_line = nullptr; };
protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;


	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


private:
	QString mstr_text = "";
	QPointF mt_startPt, mt_endPt;
	lxQGrphicsCurveLineItem* mp_line = nullptr;   ///< 一个dcp 只有一条line 出去
};
class lxQGraphicsAnimItem;

/** curve line*/
class lxQGrphicsCurveLineItem :public QGraphicsItem
{
public:
	lxQGrphicsCurveLineItem(lxQGraphicsDCPItem* srcItem, lxQGraphicsUCPItem*dstItem,QGraphicsItem*parent=nullptr);

	enum {Type = UserType + 1};
	int type()const override { return Type;  };

	void setSrcDstPt(QPointF srcPt, QPointF dstPt) { mt_srcPt = srcPt; mt_dstPt = dstPt; mb_valid = true; update(); };
	void setDstItem(lxQGraphicsUCPItem* dstItem) { mp_dstItem = dstItem; };

	lxQGraphicsDCPItem* getSrcItem() { return mp_srcItem; };
	lxQGraphicsUCPItem* getDstItem() { return mp_dstItem; };
protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;

	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
	lxQGraphicsDCPItem* mp_srcItem;
	lxQGraphicsUCPItem* mp_dstItem;
	QPointF mt_srcPt, mt_dstPt;
	bool mb_valid = false;             ///< line 是否有效,当有起点和终点的时候才为有效

	lxQGraphicsAnimItem* m_pAnmiItem = nullptr;
	QList<lxQGraphicsAnimItem*> m_listAnmiItem;
	QPainterPath m_tPath;
};




/**body item */ 
class lxQGraphicsBodyItem : public QGraphicsItem
{
public:
	lxQGraphicsBodyItem(int shape=0,QGraphicsItem*parent=nullptr);

	QPainterPath shape() const override;

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;

	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
	int mn_shape=0; ///< 0 rect,1 circle

	QList<lxQGraphicsAnimItem*> m_listAnmiItem;
};

/** anmi item */
class lxQGraphicsAnimItem : public QGraphicsObject
{
public:
	lxQGraphicsAnimItem(QGraphicsItem*parent = nullptr);
	void startAnimation(QGraphicsItem* parentItem, QPainterPath path, double beginPercent = 0.0, int duration = 1000, int loopCnt = -1, bool enableSort = true);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

private slots:
	void slot_finished();
private:
	QRectF m_tRect;
	QColor m_tColor;
	QPainterPath m_tPath;
	QParallelAnimationGroup* m_pAnimationGroup;
	QPropertyAnimation * m_pScaleAnimation;
	QPropertyAnimation * m_pPosAnimation;
};


/** viz item */
class lxQGraphicsVizItem : public QGraphicsItem
{
public:
	lxQGraphicsVizItem(lxQVizItemType itemType,QGraphicsItem*parent = nullptr);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;
};


