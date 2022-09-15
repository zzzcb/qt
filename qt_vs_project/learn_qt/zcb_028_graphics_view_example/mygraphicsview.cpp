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

void MyGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit mouseDoubleClickPoint(event->pos());
	}
	QGraphicsView::mouseDoubleClickEvent(event);

}

void MyGraphicsView::keyPressEvent(QKeyEvent *event)
{
	emit keyPress(event);
	QGraphicsView::keyPressEvent(event);  
}
