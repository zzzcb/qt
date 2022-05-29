#include "demo.h"
#include <QPainter>

Demo::Demo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

void Demo::paintEvent(QPaintEvent *event)
{
	QPoint c1(100, 100);
	QPoint c2(200, 200);
	

	// 绘制贝塞尔三次曲线;
	//QPainter painter(this);
	//QPainterPath path;
	//path.cubicTo(c1, c2,);
	//painter.drawPath(path);

	/*
	QPoint startPoint(100, 100);
	QPoint endPoint(200, 200);
	int hSpace = 15;
	int radius = 8;

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	// 判断是上弧线还是下弧线;
	if (endPoint.y() < startPoint.y())
	{
		// 绘制横线;
		painter.drawLine(startPoint, startPoint + QPoint(hSpace, 0));

		// 绘制竖线;
		startPoint += QPoint(hSpace, 0);
		QPoint vTopPoint = QPoint(startPoint.x(), endPoint.y() + radius);
		painter.drawLine(startPoint, vTopPoint);

		// 绘制上弧线;
		startPoint = vTopPoint;
		QPoint hTopPoint = QPoint(startPoint.x() + radius, endPoint.y());

		QPainterPath path(startPoint);
		// 绘制贝塞尔三次曲线;
		QPointF c1 = QPointF(startPoint.x(), hTopPoint.y());
		QPointF c2 = QPointF(startPoint.x() + 2, hTopPoint.y() + 2);
		path.cubicTo(c2, c2, hTopPoint);
		painter.drawPath(path);

		// 绘制横线;
		startPoint = hTopPoint;
		painter.drawLine(startPoint, endPoint);
	}
	else if (endPoint.y() > startPoint.y())
	{
		// 绘制横线;
		painter.drawLine(startPoint, startPoint + QPoint(hSpace, 0));

		// 绘制竖线;
		startPoint += QPoint(hSpace, 0);
		QPoint vBottomPoint = QPoint(startPoint.x(), endPoint.y() - radius);
		painter.drawLine(startPoint, vBottomPoint);

		// 绘制下弧线;
		startPoint = vBottomPoint;
		QPoint hBottomPoint = QPoint(startPoint.x() + radius, endPoint.y());

		QPainterPath path(startPoint);
		// 绘制贝塞尔三次曲线;
		QPointF c1 = QPointF(startPoint.x() + 2, hBottomPoint.y() - 2);
		QPointF c2 = QPointF(startPoint.x() + 2, hBottomPoint.y() + 2);
		path.cubicTo(c1, c1, hBottomPoint);
		painter.drawPath(path);

		// 绘制横线;
		startPoint = hBottomPoint;
		painter.drawLine(startPoint, endPoint);
	}
	else
	{
		// 绘制直线;
		painter.drawLine(startPoint, endPoint);
	}
	*/

}

