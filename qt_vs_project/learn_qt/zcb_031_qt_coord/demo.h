#pragma once

#include <QtWidgets/QWidget>

class Demo : public QWidget
{
    Q_OBJECT
public:
    Demo(QWidget *parent = Q_NULLPTR);
protected:
	void paintEvent(QPaintEvent *event) override;
};
