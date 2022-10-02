#pragma once

#include <QWidget>
#include <QVector>

class MyDrawboard  : public QWidget
{
	Q_OBJECT

public:
	MyDrawboard(QWidget *parent = nullptr);

protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;

private:
	QVector<QPoint> m_vPoint;
};
