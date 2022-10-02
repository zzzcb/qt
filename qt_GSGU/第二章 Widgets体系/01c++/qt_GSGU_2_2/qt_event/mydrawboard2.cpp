#include "mydrawboard2.h"

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

MyDrawboard2::MyDrawboard2(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(400, 400);
}

void MyDrawboard2::mouseMoveEvent(QMouseEvent *event)
{
	if (event->x() < 0 || event->y() < 0 || event->x() > 400 || event->y() > 400)
		return;

	m_vPoint.push_back(QPoint(event->x(), event->y()));

	update();
}

void MyDrawboard2::mousePressEvent(QMouseEvent *event)
{
	if (event->x() < 0 || event->y() < 0 || event->x() > 400 || event->y() > 400)
		return;

	qDebug() << "--------------> mouse press event";

	m_vPoint.push_back(QPoint(event->x(),event->y()));
}

void MyDrawboard2::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	QPen pen;
	pen.setWidth(10);
	pen.setColor(Qt::red);

	painter.setPen(pen);

	painter.drawPoints(QPolygon(m_vPoint));
}
