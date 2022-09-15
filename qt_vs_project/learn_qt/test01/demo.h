#pragma once

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include "ui_demo.h"


class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

private:
    Ui::DemoClass ui;
};
