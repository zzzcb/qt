#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = nullptr);
    ~Demo();

protected:
	void mousePressEvent(QMouseEvent *event) override;

	void keyPressEvent(QKeyEvent *event) override;

	void paintEvent(QPaintEvent *event) override;

private:
    Ui::DemoClass ui;

	QLabel* m_pLabel6;
};
