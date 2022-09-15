#pragma once

#include <QtWidgets/QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "ui_demo.h"
#include "myDialog1.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

private:
    Ui::DemoClass ui;

	QStandardItemModel* mpStdItemModel;
	QItemSelectionModel*  mpItemSelModel;

private slots:
	void on_action_triggered();
	void on_action_2_triggered();
	void on_action_3_triggered();
};
