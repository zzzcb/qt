#pragma once

#include <QGraphicsScene>

class lxQGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	lxQGraphicsScene(QObject *parent=nullptr);
	~lxQGraphicsScene();

protected:
	//void drawBackground(QPainter *painter, const QRectF &rect) override;

	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

};
