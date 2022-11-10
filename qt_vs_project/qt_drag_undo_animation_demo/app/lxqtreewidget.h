#pragma once

#include <QTreeWidget>

class lxQTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	lxQTreeWidget(QWidget *parent);
	~lxQTreeWidget();
protected:
	void mouseMoveEvent(QMouseEvent *event) override;

private:
	void addItem();
};
