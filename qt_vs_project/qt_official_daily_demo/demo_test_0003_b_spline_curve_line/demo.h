#pragma once

#include <QtWidgets/QWidget>
#include "ui_demo.h"
#include  <QVector>
class Demo : public QWidget
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

protected:
	virtual void    mousePressEvent(QMouseEvent *event);
	virtual   void  mouseReleaseEvent(QMouseEvent *event);
	virtual   void  mouseDoubleClickEvent(QMouseEvent *event);
	virtual   void  mouseMoveEvent(QMouseEvent *event);
	virtual   void  paintEvent(QPaintEvent *event);
private:
    Ui::DemoClass ui;

	void  drawSpline();
	qreal N(int  k, int  i, qreal u);
	qreal N1(int  i, qreal u);
	qreal N2(int  i, qreal u);
	qreal N3(int  i, qreal u);

	QVector <QPointF> m_ctrlPoints;        // control point
	QVector <QPointF> m_curvePoints;       // point on the curve
};
