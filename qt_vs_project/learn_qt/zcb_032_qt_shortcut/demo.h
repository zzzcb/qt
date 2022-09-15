#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = nullptr);
    ~Demo();

private:
	void createActions();
	void createMenus();

    Ui::DemoClass ui;
	
	QAction* m_pNewAct;
	QAction* m_pOpenAct;
	QAction* m_pOpenAndFreezeAct;
};
