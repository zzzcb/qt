#pragma once

#include <QWidget>
#include "ui_innerwidget.h"

class InnerWidget : public QWidget
{
	Q_OBJECT

public:
	InnerWidget(QWidget *parent = Q_NULLPTR);
	~InnerWidget();

private:
	Ui::InnerWindow ui;
};
