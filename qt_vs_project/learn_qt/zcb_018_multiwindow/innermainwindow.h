#pragma once

#include <QMainWindow>
#include "ui_innermainwindow.h"

class InnerMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	InnerMainWindow(QWidget *parent = Q_NULLPTR);
	~InnerMainWindow();

private:
	Ui::InnerMainWindow ui;
};
