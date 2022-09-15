#include "demo.h"
#include <QPainter>

Demo::Demo(QWidget *parent)
    : QWidget(parent)
{
	setWindowTitle("qt coord");
	setFixedSize(200, 200);
}

void Demo::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setViewport(-100, -100, 200, 200);
	painter.setWindow(-100, -100, 200, 200);
	painter.drawEllipse(0, 0, 100, 100);
}



