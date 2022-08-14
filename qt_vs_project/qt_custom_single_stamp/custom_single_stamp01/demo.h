#pragma once

#include <QtWidgets/QWidget>
#include "ui_demo.h"

class Demo : public QWidget
{
    Q_OBJECT

public:
    Demo(QWidget *parent = nullptr);
    ~Demo();

private:
    Ui::DemoClass ui;
};
