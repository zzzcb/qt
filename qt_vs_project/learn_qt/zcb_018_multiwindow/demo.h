#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *event) override;

private:
    Ui::DemoClass ui;
private slots:
	void on_action_widget_triggered();
	void on_action_widget_2_triggered();
	void on_action_widget_3_triggered();
	void on_action_widget_4_triggered();

	void on_tabWidget_tabCloseRequested(int index);
};
