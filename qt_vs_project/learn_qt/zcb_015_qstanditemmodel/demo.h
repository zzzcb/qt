#pragma once

#include <QtWidgets/QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);
	
	QStandardItemModel* mpStdItemModel;
	QItemSelectionModel*  mpItemSelModel;


private slots:
	void on_pushButton_clicked();

private:
    Ui::DemoClass ui;


};
