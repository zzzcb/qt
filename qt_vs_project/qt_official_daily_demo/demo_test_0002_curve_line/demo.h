#pragma once

#include <QtWidgets/QWidget>
#include "ui_demo.h"

class Demo : public QWidget
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

protected:
	void paintEvent(QPaintEvent *event) override;


private:
    Ui::DemoClass ui;
};
