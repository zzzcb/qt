#pragma once

#include <QtWidgets/QMainWindow>
#include <QtCore/QStringListModel>
#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);
	QStringListModel* mStrListModel;
private slots:
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
private:
    Ui::DemoClass ui;
};
