#pragma once

#include <QWidget>
#include <QAbstractButton>
#include <QPaintEvent>
#include <QPushButton>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QDebug>
#include <QVector>
#include <QLabel>
#include <QVBoxLayout>

class MyButton :public QWidget
{
public:
	MyButton(int l, int w,QString iconPath, QString btnId, QWidget*parent = nullptr);
	~MyButton();

	QString id();
	bool checked();
	void setPenWidth(int width);
	void setBackgroundColor(bool enable);
	void setCheckable(bool enable);
	void setDragable(bool enable);

protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;


private:
	int mn_l, mn_w;
	int mn_penWidth;
	QString mstr_iconPath;
	QString mstr_btnId;
	
	bool mb_moving = false;
	bool mb_checkable = false;
	bool mb_dragable = false;
	QPointF m_pressPoint;

	bool mb_check = false;
};


class lxQButtonGroup : public QWidget
{
	Q_OBJECT

public:
	lxQButtonGroup(QWidget *parent = nullptr);
	~lxQButtonGroup();

	void setButtonsDir(bool bHor);
	void setButtonSize(int l, int w);

	void addButton(QString iconPath, QString toolTip="",bool bCheckable=false,bool bDragable=false);
	bool buttonChecked(QString btnId);


protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

private slots:

private:
	void updateButtons();

	bool mb_hor;
	int mn_l, mn_w;

	QVector<MyButton*> mvp_button;

	MyButton* mp_activeBtn;
};


