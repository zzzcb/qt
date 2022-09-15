#pragma once

#include <QtWidgets/QWidget>
#include "ui_demo.h"

class Demo : public QWidget
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

private:
	void paintEvent(QPaintEvent *event) override;

    Ui::DemoClass ui;
};
