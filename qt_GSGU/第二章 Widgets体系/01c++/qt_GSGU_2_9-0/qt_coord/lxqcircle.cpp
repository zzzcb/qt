#include "lxqcircle.h"

#include <QPainter>

lxQCircle::lxQCircle(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(200, 200);  
}

void lxQCircle::paintEvent(QPaintEvent *event)
{	
	QPainter painter(this);
	QPen pen;
	pen.setCosmetic(true);
	painter.setPen(pen);

	painter.setWindow(-10, -10, 20, 20);
	painter.drawEllipse(0, 0, 10, 10);
}

