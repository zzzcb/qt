#pragma once

#include <QGraphicsScene>

class lxQGraphicsItemGroup;

class lxQGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	lxQGraphicsScene(QObject *parent=nullptr);
	~lxQGraphicsScene();

	lxQGraphicsItemGroup * createGroup(const QList<QGraphicsItem *> &items, bool bAdd /*= true*/);
	void destroyGroup(lxQGraphicsItemGroup* group);

protected:
	void drawBackground(QPainter *painter, const QRectF &rect) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

	void keyPressEvent(QKeyEvent *event) override;



};
