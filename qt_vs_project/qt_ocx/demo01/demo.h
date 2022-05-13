#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo.h"
#include "xgxlib.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

private:
    Ui::DemoClass ui;
	XGXLib::XGX * xgx;
private slots:
	void on_pushButton_clicked();
};
