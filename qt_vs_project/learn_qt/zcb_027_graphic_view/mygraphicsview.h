#pragma once

#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	MyGraphicsView(QWidget *parent);
	~MyGraphicsView();
protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
signals:
	void mouseMovePoint(QPoint point);
	void mousePressPoint(QPoint point);
};
