﻿#pragma once

#include <QObject>
#include <QGraphicsItem>

#include "common.h"

class lxQGrphicsCurveLineItem;

/** ucp : up connect point*/  
class lxQGraphicsUCPItem : public QGraphicsItem
{
public:
	lxQGraphicsUCPItem(QGraphicsItem*parent = nullptr);

	enum { Type = UserType + 2 };
	int type()const override { return Type; };

	void addLine(lxQGrphicsCurveLineItem* line) { mlist_Line.push_back(line); };
	void removeLine(lxQGrphicsCurveLineItem* line) { mlist_Line.removeAll(line); };

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	QRectF boundingRect() const override;

private:
	QList<lxQGrphicsCurveLineItem*> mlist_Line;   // 一个ucp 可能有多条line 进入
};

/** dcp : down connect point */
class lxQGraphicsDCPItem : public QGraphicsItem
{
public:
	lxQGraphicsDCPItem(QGraphicsItem*parent = nullptr);
	void setDCPText(QString text);
	void clearLine() { mp_line = nullptr; };
protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	QRectF boundingRect() const override;


	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


private:
	QString mstr_text = "";
	QPointF mt_startPt, mt_endPt;
	lxQGrphicsCurveLineItem* mp_line = nullptr;   // 一个dcp 只有一条line 出去
};


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

private:
	lxQGraphicsDCPItem* mp_srcItem;
	lxQGraphicsUCPItem* mp_dstItem;
	QPointF mt_srcPt, mt_dstPt;
	bool mb_valid = false;             // line 是否有效,当有起点和终点的时候才为有效
};



/**body item */ 
class lxQGraphicsBodyItem : public QGraphicsItem
{
public:
	lxQGraphicsBodyItem(int shape=0,QGraphicsItem*parent=nullptr);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	QRectF boundingRect() const override;

private:
	int mn_shape=0; // 0 rect,1 circle
};

/** node item */
class lxQGraphicsNodeItem : public QGraphicsItem
{
public:
	lxQGraphicsNodeItem(lxQVizItemType itemType,QGraphicsItem*parent = nullptr);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;
};
