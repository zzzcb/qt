#include "lxgraphicsscene.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

LxGraphicsScene::LxGraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
{
}

LxGraphicsScene::~LxGraphicsScene()
{
}

void LxGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
