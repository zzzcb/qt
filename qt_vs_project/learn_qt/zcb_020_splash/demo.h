#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

private:
    Ui::DemoClass ui;
private slots:
	void on_action_triggered();
	void on_action_2_triggered();
	void on_action_3_triggered();
	void on_action_4_triggered();
	void on_action_5_triggered();
	void on_action_6_triggered();
	void on_action_7_triggered();
	void on_action_8_triggered(bool checked);
	void on_action_9_triggered();
	void on_action_10_triggered();
	
	void on_mdiArea_subWindowActivated(QMdiSubWindow *window);
};
