#include "demo.h"

#include  <QMouseEvent>
#include  <QPainter>
#include  <cmath>

Demo::Demo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}





void  Demo::mousePressEvent(QMouseEvent *event)
{
	// 单击鼠标左键获取控制点
	if (event->buttons() == Qt::LeftButton) {
		m_ctrlPoints.push_back(event->pos());
	}
	// 单击鼠标右键清空控制点
	else   if (event->buttons() == Qt::RightButton) {
		m_ctrlPoints.clear();
	}
	update();
}

void  Demo::mouseReleaseEvent(QMouseEvent *event)
{

}

void  Demo::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void  Demo::mouseMoveEvent(QMouseEvent *event)
{

}

void  Demo::paintEvent(QPaintEvent *event)
{
	drawSpline();
}

void  Demo::drawSpline()
{
	QPainter painter(this);
	int  currentK = 3;        // 阶数
	m_curvePoints.clear();
	for (qreal u = currentK; u < m_ctrlPoints.size(); u += 0.01) {
		QPointF pt(0.0, 0.0);
		for (int i = 0; i < m_ctrlPoints.size(); ++i) {
			QPointF pts = m_ctrlPoints[i];
			pts *= N(currentK, i, u);
			pt += pts;
		}
		m_curvePoints.push_back(pt);
	}

	// draw control points
	QPen ctrlPen1(QColor(0, 0, 255));
	ctrlPen1.setWidth(5);
	painter.setPen(ctrlPen1);
	for (int i = 0; i < m_ctrlPoints.size(); ++i) {
		painter.drawPoint(m_ctrlPoints[i]);
	}
	// draw control lines
	QPen ctrlPen2(QColor(255, 0, 0));
	ctrlPen2.setWidth(1);
	ctrlPen2.setStyle(Qt::DashDotDotLine);
	painter.setPen(ctrlPen2);
	for (int i = 0; i < m_ctrlPoints.size() - 1; ++i) {
		painter.drawLine(m_ctrlPoints[i], m_ctrlPoints[i + 1]);
	}
	// draw spline curve
	QPen curvePen(QColor(0, 0, 0));
	curvePen.setWidth(2);
	painter.setPen(curvePen);
	for (int i = 0; i < m_curvePoints.size() - 1; ++i) {
		painter.drawLine(m_curvePoints[i], m_curvePoints[i + 1]);
	}
}

qreal Demo::N(int  k, int  i, qreal u)
{
	switch (k) {
	case   1:
		return  N1(i, u);
	case   2:
		return   N2(i, u);
	case   3:
		return   N3(i, u);
	default:
		break;
	}
}

qreal Demo::N1(int  i, qreal u)
{
	qreal t = u - i;
	if (0 <= t && t < 1) {
		return  t;
	}
	if (1 <= t && t < 2) {
		return   2 - t;
	}
	return   0;
}

qreal Demo::N2(int  i, qreal u)
{
	qreal t = u - i;
	if (0 <= t && t < 1) {
		return   0.5 * t * t;
	}
	if (1 <= t && t < 2) {
		return   3 * t - t * t - 1.5;
	}
	if (2 <= t && t < 3) {
		return   0.5 * pow(3 - t, 2);
	}
	return   0;
}

qreal Demo::N3(int  i, qreal u)
{
	qreal t = u - i;
	qreal a = 1.0 / 6.0;
	if (0 <= t && t < 1) {
		return  a * t * t * t;
	}
	if (1 <= t && t < 2) {
		return  a * (-3 * pow(t - 1, 3) + 3 * pow(t - 1, 2) + 3 * (t - 1) + 1);
	}
	if (2 <= t && t < 3) {
		return  a * (3 * pow(t - 2, 3) - 6 * pow(t - 2, 2) + 4);
	}
	if (3 <= t && t < 4) {
		return  a * pow(4 - t, 3);
	}
	return   0;
}
