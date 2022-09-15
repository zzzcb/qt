#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = nullptr);
    ~Demo();

private:
	

    Ui::DemoClass ui;
};
