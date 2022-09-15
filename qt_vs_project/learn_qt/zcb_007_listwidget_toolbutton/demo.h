#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

private:
    Ui::DemoClass ui;
private slots:
	void on_toolBox_currentChanged(int index);

	void on_actionInit_triggered();
	void on_actionClear_triggered();
	void on_actionInsert_triggered();
	void on_actionAdd_triggered();
	void on_actionDelete_triggered();

	void on_actionItem_triggered();

	void on_actionAll_triggered();
	void on_actionNone_triggered();
	void on_actionInverse_triggered();

	void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

	void on_listWidget_customContextMenuRequested(const QPoint &pos); 

};
