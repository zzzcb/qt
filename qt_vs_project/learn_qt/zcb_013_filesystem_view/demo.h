#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileSystemModel>
#include <QtCore/QDir>
#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);
	QFileSystemModel* mFileSysModel;

private slots:
	void on_treeView_clicked(const QModelIndex &index);




private:
    Ui::DemoClass ui;

};
