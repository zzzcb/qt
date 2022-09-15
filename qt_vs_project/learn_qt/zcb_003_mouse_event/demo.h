#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

	void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::DemoClass ui;
};
