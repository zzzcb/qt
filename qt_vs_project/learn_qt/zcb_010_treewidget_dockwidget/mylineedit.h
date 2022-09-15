#pragma once

#include <QLineEdit>
#include <QFileDialog>
#include <QFileInfo>
#include <qdebug.h>

class MyLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	MyLineEdit(QWidget *parent = Q_NULLPTR);
	~MyLineEdit();
protected:
	void mouseDoubleClickEvent(QMouseEvent *event);
private slots:
	void on_lineEdit_returnPressed();
signals:
	void chooseDirCompleted();
private:
	
};
