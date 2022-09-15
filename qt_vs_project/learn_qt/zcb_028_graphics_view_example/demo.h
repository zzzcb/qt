#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo.h"
#include "QLabel"
#include "QGraphicsScene"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);
	void initGraphicsView();


private slots:
	void on_mouseMovePoint(QPoint point);
	void on_mousePressPoint(QPoint point);
	void on_mouseDoubleClickPoint(QPoint point);
	void on_keyPress(QKeyEvent* event);

	void on_actItem_Rect_triggered();
	void on_actItem_Ellipse_triggered();
	void on_actItem_Circle_triggered();
	void on_actItem_Triangle_triggered();
	void on_actItem_Line_triggered();
	void on_actItem_Polygon_triggered();
	void on_actItem_Text_triggered();

	void on_actZoomIn_triggered();
	void on_actZoomOut_triggered();
	void on_actRestore_triggered();
	void on_actRotateLeft_triggered();
	void on_actRotateRight_triggered();

	void on_actEdit_Front_triggered();
	void on_actEdit_Back_triggered();

	void on_actGroup_triggered();
	void on_actGroupBreak_triggered();

	void on_actEdit_Delete_triggered();
private:

    Ui::DemoClass ui;

	QLabel* labViewPos;
	QLabel* labScenePos;
	QLabel* labItemPos;
	QLabel* labItemInfo;

	QGraphicsScene* scene;

	static const int ItemId = 1;    //自定义数据的key
	static const int ItemDesc = 2;  //自定义数据的key

	int seqNum = 0;                 // item id value
	int backZ = 0;
	int frontZ = 0;


};
