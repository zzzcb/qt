#include "mydrawboard.h"

#include <QMouseEvent>
#include <QPainter>

MyDrawboard::MyDrawboard(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(400, 400);
}

void MyDrawboard::mouseMoveEvent(QMouseEvent *event)
{
	if (event->x() < 0 || event->y() < 0 || event->x() > 400 || event->y() > 400)
		return;

	m_vPoint.push_back(QPoint(event->x(), event->y()));

	update();
}

void MyDrawboard::mousePressEvent(QMouseEvent *event)
{
	if (event->x() < 0 || event->y() < 0 || event->x() > 400 || event->y() > 400)
		return;

	m_vPoint.push_back(QPoint(event->x(),event->y()));
}

void MyDrawboard::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	QPen pen;
	pen.setWidth(10);
	pen.setColor(Qt::red);

	painter.setPen(pen);

	painter.drawPoints(QPolygon(m_vPoint));
}
