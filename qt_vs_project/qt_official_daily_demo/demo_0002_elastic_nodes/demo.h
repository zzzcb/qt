#pragma once

#include <QtWidgets/QMainWindow>

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

protected:
	void paintEvent(QPaintEvent *event) override;


private:
};
