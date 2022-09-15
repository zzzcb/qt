#pragma once

#include <QWidget>
#include "ui_mystatusbar.h"

class MyStatusBar : public QWidget
{
	Q_OBJECT

public:
	MyStatusBar(QWidget *parent = Q_NULLPTR);
	~MyStatusBar();

private:
	Ui::MyStatusBar ui;
};
