#pragma once

#include <QTreeWidget>

class LxTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	LxTreeWidget(QWidget *parent);
	~LxTreeWidget();
protected:
	void mouseMoveEvent(QMouseEvent *event) override;

private:
	void addItem();
};
