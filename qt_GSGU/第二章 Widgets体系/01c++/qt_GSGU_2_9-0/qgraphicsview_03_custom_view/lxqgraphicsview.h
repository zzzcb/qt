#pragma once

#include <QGraphicsView>

class lxQGraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	lxQGraphicsView(QWidget *parent = nullptr);

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

private:

	bool m_bCtrl = false;			

	/** 视图缩放操作 */
	void scaleView(qreal scaleFactor);
	void translateViewY(qreal dy);
};
