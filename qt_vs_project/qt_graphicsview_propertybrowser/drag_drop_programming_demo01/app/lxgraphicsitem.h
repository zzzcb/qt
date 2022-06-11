#pragma once


#include <QObject>
#include <QGraphicsItem>

#include "common.h"

class LxGrphicsCurveLineItem;

// ucp : up connect point 
class LxGraphicsUCPItem : public QGraphicsItem
{
public:
	LxGraphicsUCPItem(QGraphicsItem*parent = nullptr);
	//~LxGraphicsUCPItem();

	enum { Type = UserType + 2 };
	int type()const override { return Type; };

	void addLine(LxGrphicsCurveLineItem* line) { mvLine.push_back(line); };
	void removeLine(LxGrphicsCurveLineItem* line) { mvLine.removeAll(line); };

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;

private:
	QList<LxGrphicsCurveLineItem*> mvLine;   // 一个ucp 可能有多条line 进入

};

// dcp : down connect point 
class LxGraphicsDCPItem : public QGraphicsItem
{
public:
	LxGraphicsDCPItem(QGraphicsItem*parent = nullptr);
	//~LxGraphicsDCPItem();
	void setDCPText(QString text);
	void clearLine() { mLine = nullptr; };
protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;


	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


private:
	QString mText = "";
	QPointF mStartPt, mEndPt;
	LxGrphicsCurveLineItem* mLine = nullptr;   // 一个dcp 只有一条line 出去
};


// curve line
class LxGrphicsCurveLineItem :public QGraphicsItem
{
public:
	LxGrphicsCurveLineItem(LxGraphicsDCPItem* srcItem, LxGraphicsUCPItem*dstItem,QGraphicsItem*parent=nullptr);

	enum {Type = UserType + 1};
	int type()const override { return Type;  };

	void setSrcDstPt(QPointF srcPt, QPointF dstPt) { mSrcPt = srcPt; mDstPt = dstPt; mbValid = true; update(); };
	void setDstItem(LxGraphicsUCPItem* dstItem) { mDstItem = dstItem; };

	LxGraphicsDCPItem* getSrcItem() { return mSrcItem; };
	LxGraphicsUCPItem* getDstItem() { return mDstItem; };
protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;

private:
	LxGraphicsDCPItem* mSrcItem;
	LxGraphicsUCPItem* mDstItem;
	QPointF mSrcPt, mDstPt;
	bool mbValid = false;             // line 是否有效,当有起点和终点的时候才为有效
};



// body item  
class LxGraphicsBodyItem : public QGraphicsItem
{
public:
	LxGraphicsBodyItem(int shape=0,QGraphicsItem*parent=nullptr);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;


private:
	int mShape=0; // 0 rect,1 circle
};

// viz item 
class LxGraphicsVizItem : public QGraphicsItem
{
public:
	LxGraphicsVizItem(LxVizItemType itemType,QGraphicsItem*parent = nullptr);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;

};



// vis item 
//class LxGraphicsVisItem : public QGraphicsItem
//{
//public:
//	LxGraphicsVisItem(QGraphicsItem*parent = nullptr);
//
//protected:
//	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
//	QRectF boundingRect() const override;
//};
