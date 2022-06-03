#pragma once

#include <QGraphicsObject>

class RobotPart : public QGraphicsObject
{
public:
	RobotPart(QGraphicsItem* parent=0);


protected:

	void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
	void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;

	void dropEvent(QGraphicsSceneDragDropEvent *event) override;

	QColor mColor;
	bool mbDrag;

};

class RobotTorso:public RobotPart
{
public:
	RobotTorso(QGraphicsItem* parent=0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;
};

class RobotLimb :public RobotPart
{
public:
	RobotLimb(QGraphicsItem* parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;
};

class RobotHead :public RobotPart
{
public:
	RobotHead(QGraphicsItem* parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;

protected:
	void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
	void dropEvent(QGraphicsSceneDragDropEvent *event) override;
private:
	QPixmap mHeadImg;
};



class Robot :public QGraphicsObject
{
public:
	Robot();

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;
	QRectF boundingRect() const override;
};


