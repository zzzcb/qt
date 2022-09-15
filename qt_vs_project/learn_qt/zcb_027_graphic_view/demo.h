#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

private:
    Ui::DemoClass ui;

	QLabel* labViewPos;
	QLabel* labScenePos;
	QLabel* labItemPos;
	
	QGraphicsScene* scene;
	void initGraphicsView();

private slots:
	void on_mouseMovePoint(QPoint point);
	void on_mousePressPoint(QPoint point);
};
