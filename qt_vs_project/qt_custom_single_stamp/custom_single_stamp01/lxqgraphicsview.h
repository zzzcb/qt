#pragma once

#include <QGraphicsView>

class lxQButtonGroup;

class lxQGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	lxQGraphicsView(QWidget *parent);
	~lxQGraphicsView();

protected:
	void dragEnterEvent(QDragEnterEvent *event) override;
	void dragMoveEvent(QDragMoveEvent *event) override;
	void dropEvent(QDropEvent *event) override;

	void mousePressEvent(QMouseEvent *event) override;

	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	
	void drawBackground(QPainter *painter, const QRectF &rect);

private:
	void scaleView(qreal scaleFactor);
	void translateViewY(qreal dy);

	bool mb_ctrl = false;
	lxQButtonGroup* mt_btnGroup;
};
