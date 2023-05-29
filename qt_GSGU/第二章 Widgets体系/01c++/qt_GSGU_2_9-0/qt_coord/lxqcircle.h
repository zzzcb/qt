#pragma once

#include <QWidget>

class lxQCircle : public QWidget
{
	Q_OBJECT

public:
	lxQCircle(QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *event) override;
};

