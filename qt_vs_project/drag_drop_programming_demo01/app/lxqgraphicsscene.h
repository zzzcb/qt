#pragma once

#include <QGraphicsScene>

class lxQGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	lxQGraphicsScene(QObject *parent=nullptr);
	~lxQGraphicsScene();

protected:
	void drawBackground(QPainter *painter, const QRectF &rect) override;

	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
	void signal_itemMoved(QGraphicsScene*scene,const QPointF &offset);

private:
	QPointF m_tOldPos;
	QPointF m_tNewPos;

};
