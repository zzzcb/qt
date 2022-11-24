#pragma once

#include <QWidget>


class MyWidget :public QWidget
{
public:
	MyWidget(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setStyleSheet("background:green;");
	}
	//  sizeHint vs minimumSizeHint
	//	When the widget is created the system uses sizeHint for how to big to make at start.
	//	When the widget is resized(by layout, by user dragging) the minimumSizeHint is used to
	//	make sure it never becomes smaller than that.
	QSize sizeHint() const override
	{
		return QSize(100, 50);
	}
	QSize minimumSizeHint() const override
	{
		return QSize(50, 25);
	}
};


class Demo : public QWidget
{
    Q_OBJECT

public:
    Demo(QWidget *parent = nullptr);
    ~Demo();

};
