#include "lxqgraphicsscene.h"
#include "lxqundocommands.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QGraphicsItem>
#include <QDebug>

lxQGraphicsScene::lxQGraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
{
}

lxQGraphicsScene::~lxQGraphicsScene()
{
}

void lxQGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mousePressEvent(event);
	if (selectedItems().size() <= 0)
		return;

	m_tOldPos = selectedItems().first()->scenePos();
} 

void lxQGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsScene::mouseMoveEvent(event);
}

void lxQGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseReleaseEvent(event);
	if (selectedItems().size() <= 0)
		return;
	m_tNewPos = selectedItems().first()->scenePos();
	if (QLineF(m_tOldPos, m_tNewPos).length() > QApplication::startDragDistance())
	{
		//qDebug() << "item move. from " << m_tOldPos << " to " << m_tNewPos;
		emit signal_itemMoved((QGraphicsScene*)this, m_tNewPos - m_tOldPos);
	}

}

void lxQGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{

	QGraphicsScene::drawBackground(painter, rect);
	painter->fillRect(sceneRect(), Qt::gray);
}
