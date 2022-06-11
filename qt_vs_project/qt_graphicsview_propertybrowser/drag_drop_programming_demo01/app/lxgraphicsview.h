#pragma once

#include <QGraphicsView>

class LxGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	LxGraphicsView(QWidget *parent);
	~LxGraphicsView();

protected:
	void dragEnterEvent(QDragEnterEvent *event) override;
	void dragMoveEvent(QDragMoveEvent *event) override;
	void dropEvent(QDropEvent *event) override;

	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

	void mousePressEvent(QMouseEvent *event) override;

private:
	void scaleView(qreal scaleFactor);
	void translateViewY(qreal dy);

	bool mbCtrl = false;

};
