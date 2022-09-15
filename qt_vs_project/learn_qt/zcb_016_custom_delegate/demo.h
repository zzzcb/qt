#pragma once

#include <QtWidgets/QWidget>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "ui_demo.h"

class Demo : public QWidget
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

	QStandardItemModel* mpStdItemModel;
	QItemSelectionModel*  mpItemSelModel;
private:
    Ui::DemoClass ui;
};
