#pragma once

#include <QGraphicsView>

class lxQGraphicsScene;

class lxQGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	lxQGraphicsView(QWidget *parent);
	~lxQGraphicsView();


	lxQGraphicsScene* m_pScene;

protected:
	void dragEnterEvent(QDragEnterEvent *event) override;
	void dragMoveEvent(QDragMoveEvent *event) override;
	void dropEvent(QDropEvent *event) override;

	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

	void mousePressEvent(QMouseEvent *event) override;

signals:
	void signal_itemAdded(QGraphicsItem *item, QGraphicsScene *scene);

private:
	void scaleView(qreal scaleFactor);
	void translateViewY(qreal dy);

	bool mb_ctrl = false;
};
