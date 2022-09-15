#include "demo.h"
#include "QPainter"

Demo::Demo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

	setPalette(QPalette(Qt::white));
	this->resize(300, 300);
}

void Demo::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);


	int W = width();
	int H = height();

	int side = qMin(W, H);//取长和宽的小值
	QRect rect((W - side) / 2, (H - side) / 2, side, side); //viewport矩形区
	painter.drawRect(rect); //Viewport大小

	painter.setViewport(rect);//设置Viewport,如果不设置的话,默认的viewport是整个widget区域 
	painter.setWindow(-100, -100, 200, 200); // 设置窗口大小，逻辑坐标

	for (int i = 0; i < 36; i++)
	{
		painter.drawEllipse(QPoint(50, 0), 50, 50);
		painter.rotate(10);
	}


}
