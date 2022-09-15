#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFileDialog>
#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

private:
    Ui::DemoClass ui;

private slots:
	void on_actionDockShow_triggered(bool checked);
	void on_actionDockFloat_triggered(bool checked);
	void on_dockWidget_topLevelChanged(bool topLevel);
	void on_dockWidget_visibilityChanged(bool visible);

	void on_actionNewDir_triggered(bool checked);
	
};
