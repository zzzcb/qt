#pragma once

#include <QGraphicsScene>

class LxGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	LxGraphicsScene(QObject *parent=nullptr);
	~LxGraphicsScene();

protected:
	//void drawBackground(QPainter *painter, const QRectF &rect) override;

	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

};
