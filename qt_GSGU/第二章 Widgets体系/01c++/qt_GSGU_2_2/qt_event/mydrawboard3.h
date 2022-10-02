#pragma once

#include <QWidget>
#include <QVector>

class MyDrawboard3  : public QWidget
{
	Q_OBJECT

public:
	MyDrawboard3(QWidget *parent = nullptr);

protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;

private slots:
	void slot_clearBoard();

private:
	QVector<QPoint> m_vPoint;
};
