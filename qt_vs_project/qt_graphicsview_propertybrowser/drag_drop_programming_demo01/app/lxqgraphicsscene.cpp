#include "lxqgraphicsscene.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

lxQGraphicsScene::lxQGraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
{
}

lxQGraphicsScene::~lxQGraphicsScene()
{
}

void lxQGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	update();
	QGraphicsScene::mouseMoveEvent(event);
}

//void LxGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
//{
//
//	QGraphicsScene::drawBackground(painter, rect);
//	painter->fillRect(sceneRect(), Qt::white);
//}
