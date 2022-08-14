#pragma once

#include <QObject>
#include <QGraphicsItem>
#include <QMimeData>
#include <QDebug>

template<typename BaseType = QGraphicsItem>
class lxQAbstractGraphicsItem : public BaseType
{
public:
	explicit lxQAbstractGraphicsItem(QGraphicsItem* parent = nullptr)
		:BaseType(parent)
	{
	}

	virtual QGraphicsItem * duplicate() const { return nullptr; }
};

/** 更方便使用*/
typedef lxQAbstractGraphicsItem<QGraphicsItem> AbstractGraphicsItem;

class lxQShapeMimeData :public QMimeData
{
	Q_OBJECT
public:
	lxQShapeMimeData(QList<QGraphicsItem*> items);
	~lxQShapeMimeData();
	QList<QGraphicsItem*> getItems() const;

private:
	QList<QGraphicsItem*> m_vpItem;

};

/* 真实世界mm与像素的比值,例如1000mm = 1000/mm2PixelRatio pixel */
static qreal mm2PixelRatio = 3.0;

class lxQGraphicsPalletItem : public AbstractGraphicsItem
{
public:
	explicit lxQGraphicsPalletItem(qreal l = 1120, qreal w = 1000, QGraphicsItem* parent = nullptr);

	QGraphicsItem *duplicate() const override;
	void rotateAngle(qreal degree);

	enum { Type = UserType + 1 };
	int type()const override { return Type; };

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;

private:
	qreal md_l, md_w;  ///< 像素长宽
};

class lxQGraphicsBoxItem : public AbstractGraphicsItem
{
public:
	explicit lxQGraphicsBoxItem(qreal l = 500, qreal w = 300,QGraphicsItem* parent = nullptr);

	void rotateAngle(qreal degree);
	QGraphicsItem *duplicate() const override;

	enum { Type = UserType + 2 };
	int type()const override { return Type; };

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;

private:
	qreal md_l, md_w;  ///< 像素长宽

};

class lxQGraphicsBucketItem : public AbstractGraphicsItem
{
public:
	explicit lxQGraphicsBucketItem(qreal d = 200,QGraphicsItem* parent = nullptr);
	QGraphicsItem *duplicate() const override;

	enum { Type = UserType + 3 };
	int type()const override { return Type; };
protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;


private:
	qreal md_d;  ///< 像素直径
};

class lxQGraphicsRotateRing : public AbstractGraphicsItem
{
public:
	static lxQGraphicsRotateRing * getInstance()
	{
		if (m_pInstance == nullptr) 
			m_pInstance = new lxQGraphicsRotateRing();
		return m_pInstance;
	}
	enum { Type = UserType + 4 };
	int type()const override { return Type; };

	void setRotatedObj(QGraphicsItem* rotatedObj) { mt_rotatedObj = rotatedObj; };

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

	void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;


private:
	lxQGraphicsRotateRing(qreal d = 150, qreal t = 5, QGraphicsItem* parent = nullptr);
	static lxQGraphicsRotateRing *m_pInstance;

	qreal md_d;  ///< 像素 直径
	qreal md_t;  ///< 像素 环厚度

	bool  mb_hover=false;   ///< 鼠标是否在旋转环上
	
	bool  mb_rotate = false;///< 是否进行旋转
	QPointF mt_startPt;     ///< 开始旋转的起始点 item pos
	QPointF mt_circlePt;    ///< 鼠标旋转过程中在圆上相交的点 item pos 
	QPointF mt_curPt;       ///< 鼠标旋转过程中当前的点位 item pos
	qreal   md_curAngle;    ///< 鼠标旋转过程中当前的角度 弧度
	qreal   md_arrowSize=20;///< 箭头大小
	qreal   md_rotateAngle; ///< 旋转的角度 弧度

	QGraphicsItem* mt_rotatedObj; ///< 当前旋转的对象 
	
};

class lxQGraphicsTransCross : public AbstractGraphicsItem
{
public:
	static lxQGraphicsTransCross * getInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new lxQGraphicsTransCross();
		return m_pInstance;
	}

	enum { Type = UserType + 5};
	int type()const override { return Type; };

	void setTransObj(QGraphicsItem* transObj) { mt_transObj = transObj; };

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

	void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;


private:
	lxQGraphicsTransCross(qreal length = 100, QGraphicsItem* parent = nullptr);
	static lxQGraphicsTransCross *m_pInstance;

	qreal md_length;  ///< 像素 长度

	bool  mb_hoverx = false;   ///< 鼠标是否在移动工具上
	bool  mb_hovery = false;   ///< 鼠标是否在移动工具上
	bool  mb_hoverxy = false;  ///< 鼠标是否在移动工具上

	QPointF mt_startPt;     ///< 开始移动的起始点 item pos

	QPointF mt_curPt;       ///< 鼠标移动过程中当前的点位 item pos

	bool  mb_transx = false;   ///< 是否进行x移动
	bool  mb_transy = false;   ///< 是否进行y移动
	bool  mb_transxy = false;   ///< 是否进行y移动
							  
	QGraphicsItem* mt_transObj; ///< 当前移动的对象 
	QTransform mt_curTrans;   ///< 开始拖拽时的transform 
};


class lxQGraphicsItemGroup : public lxQAbstractGraphicsItem<QGraphicsItemGroup>
{
public:
	explicit lxQGraphicsItemGroup(QGraphicsItem* parent=nullptr);

	enum { Type = UserType + 6 };
	int type()const override { return Type; };

	/** 在new 出该类对象后,要手动调用此接口来更新边界*/
	void updateBoundingRect();

	QGraphicsItem *duplicate() const override;

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;


	QRectF m_tGroupBounding  = QRectF();
};


