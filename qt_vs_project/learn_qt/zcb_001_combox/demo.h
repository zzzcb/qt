#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QListView>
#include <QtWidgets/QStyledItemDelegate>
#include "qdebug.h"

#include "ui_demo.h"

class Demo : public QWidget
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

private:
    Ui::DemoClass ui;

private slots:

};
