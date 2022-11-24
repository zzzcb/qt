#pragma once

#include <QWidget>

class FlowLayout;

class GreenWidget :public QWidget
{
public:
	GreenWidget(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setStyleSheet("background:green;");
		setFixedSize(50, 50);
	}
};

class MyWidget : public QWidget
{
    Q_OBJECT

public:
	MyWidget(QWidget*parent=nullptr);

private slots:
    void slot_addBtn();

private:
    FlowLayout* m_pFlowLayout;
};

