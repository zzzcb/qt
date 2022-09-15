#include "mygraphicsview.h"
#include "QMouseEvent"

MyGraphicsView::MyGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
}

MyGraphicsView::~MyGraphicsView()
{
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
	emit mouseMovePoint(event->pos());  // view 坐标系下的坐标
	QGraphicsView::mouseMoveEvent(event);  
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit mousePressPoint(event->pos());  // view 坐标系下的坐标
	}
	QGraphicsView::mousePressEvent(event);
}
