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
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
signals:
	void mouseMovePoint(QPoint point);
	void mousePressPoint(QPoint point);
	void mouseDoubleClickPoint(QPoint point); 
	void keyPress(QKeyEvent* event); 
};