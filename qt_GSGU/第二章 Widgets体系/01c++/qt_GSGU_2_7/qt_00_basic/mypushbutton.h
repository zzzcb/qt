#pragma once

#include <QAbstractButton>
#include <QPushButton>
class QStyleOptionButton;

class MyPushButton : public QAbstractButton
{
	Q_OBJECT

public:
	MyPushButton(QWidget *parent = nullptr);
	~MyPushButton();

	/** ���Ŵ�С����С��С */
	QSize sizeHint() const override;
	QSize minimumSizeHint() const override;

protected:
	void paintEvent(QPaintEvent *e) override;
	void initStyleOption(QStyleOptionButton *option) const;

private:
};


class MyPushButton2 : public QPushButton
{
	Q_OBJECT

public:
	MyPushButton2(QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *e) override;

private:
};
