#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QTableWidgetItem>
#include <QtWidgets/QMenu>
#include "ui_demo.h"

class Demo : public QWidget
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

private:
    Ui::DemoClass ui;
private slots:
	void on_pushButton_clicked();
	void on_pushButton2_clicked();
	void on_pushButton3_clicked();
	void on_tableWidget_customContextMenuRequested(const QPoint &pos);
	void on_actionCenter_toggled(bool checked /*= false*/);
};
