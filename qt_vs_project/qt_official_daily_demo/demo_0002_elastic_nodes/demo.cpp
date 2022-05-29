#include "demo.h"

#include <QPainter>

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
}


void Demo::paintEvent(QPaintEvent *event)
{
	QPainter pr(this);
	//QRadialGradient g(QPointF(166, 166), 100);
	//g.setColorAt(0, QColor(255, 255, 255));	//开始颜色(白色)
	//g.setColorAt(0.5, QColor(111, 1, 1));  	//中间颜色(红色)
	//g.setColorAt(1, QColor(255, 255, 1));  	//终点颜色(黄色)
	//g.setSpread(QGradient::RepeatSpread);	//传播方式(重复)
	//QBrush bs(g);    
	//pr.setBrush(bs);
	//pr.drawRect(1, 1, 333, 333);

	//QPen pen;
	//pen.setCosmetic(true);
	//pr.setPen(pen);
	//int len = qMin(width(), height())-20;
	//pr.setViewport(10, 10,len,len);
	//pr.setWindow(-7, -7, 20, 20);
	//pr.drawEllipse(-7, -7, 20, 20);

	//QPen pen(Qt::red,0);
	//pr.setPen(pen);
	//pr.drawEllipse(-7, -7, 20, 20);


	//pr.setWindow(-10,-10,40,40);
	//pr.setPen(Qt::NoPen);
	//pr.setBrush(Qt::darkGray);
	//pr.drawEllipse(-7, -7, 20, 20);
	//QRadialGradient gradient(-3, -3, 10);
	//gradient.setColorAt(0, Qt::yellow);
	//gradient.setColorAt(1, Qt::darkYellow);
	//pr.setBrush(gradient);
	//pr.setPen(QPen(Qt::black, 0));
	//pr.drawEllipse(-10, -10, 20, 20);





}
