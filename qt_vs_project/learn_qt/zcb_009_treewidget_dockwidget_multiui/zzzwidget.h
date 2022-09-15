#pragma once

#include <QWidget>
#include "ui_zzzwidget.h"

class ZZZWidget : public QWidget
{
	Q_OBJECT

public:
	ZZZWidget(QWidget *parent = Q_NULLPTR);
	~ZZZWidget();
protected:
	void mouseDoubleClickEvent(QMouseEvent *event);


private:
	Ui::ZZZWidget ui;
};
