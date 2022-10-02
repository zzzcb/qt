#pragma once

#include <QWidget>
#include <QVector>

class MyDrawboard2  : public QWidget
{
	Q_OBJECT

public:
	MyDrawboard2(QWidget *parent = nullptr);

protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;

private:
	QVector<QPoint> m_vPoint;
};
