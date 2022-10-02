#pragma execution_character_set("utf-8")
#include "mydrawboard3.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QDebug>


MyDrawboard3::MyDrawboard3(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(400, 400);
	QPushButton *pBtn = new QPushButton("ÇåÀí»­²¼",this);
	connect(pBtn, &QPushButton::clicked, this, &MyDrawboard3::slot_clearBoard);
}

void MyDrawboard3::mouseMoveEvent(QMouseEvent *event)
{
	if (event->x() < 0 || event->y() < 0 || event->x() > 400 || event->y() > 400)
		return;

	m_vPoint.push_back(QPoint(event->x(), event->y()));

	update();
}

void MyDrawboard3::mousePressEvent(QMouseEvent *event)
{
	if (event->x() < 0 || event->y() < 0 || event->x() > 400 || event->y() > 400)
		return;

	m_vPoint.push_back(QPoint(event->x(),event->y()));
}

void MyDrawboard3::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	QPen pen;
	pen.setWidth(10);
	pen.setColor(Qt::red);

	painter.setPen(pen);

	painter.drawPoints(QPolygon(m_vPoint));
}

void MyDrawboard3::slot_clearBoard()
{
	m_vPoint.clear();
	update();
}
