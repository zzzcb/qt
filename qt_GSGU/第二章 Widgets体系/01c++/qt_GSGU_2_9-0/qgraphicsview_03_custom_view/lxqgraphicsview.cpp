#pragma execution_character_set("utf-8")
#include "lxqgraphicsview.h"

#include <QGraphicsItem>
#include <QKeyEvent>
#include <QDebug>

lxQGraphicsView::lxQGraphicsView(QWidget *parent)
	:QGraphicsView(parent)
{
	setDragMode(QGraphicsView::RubberBandDrag);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(QGraphicsView::NoAnchor);
}

void lxQGraphicsView::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control)
	{
		m_bCtrl = true;
	}

	switch (event->key())
	{
	case Qt::Key_A:
		if (m_bCtrl)
		{
			for (auto item : scene()->items())
				item->setSelected(true);
		}
		break;
	default:
		break;
	}

	QGraphicsView::keyPressEvent(event);
}

void lxQGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control)
	{
		m_bCtrl = false;
	}

	QGraphicsView::keyReleaseEvent(event);
}

void lxQGraphicsView::wheelEvent(QWheelEvent *event)
{
	if (m_bCtrl)
		scaleView(std::pow(2, event->delta() / 500.0));
	else
		translateViewY(event->delta() / 10.);
}

void lxQGraphicsView::scaleView(qreal scaleFactor)
{
	qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

	if (factor < 0.07 || factor > 100)
		return;

	scale(scaleFactor, scaleFactor);
}

void lxQGraphicsView::translateViewY(qreal dy)
{
	translate(0, dy);
}
