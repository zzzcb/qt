#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo.h"

#include <QTextEdit>

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = nullptr);
    ~Demo();

private:

	void initRootFrameFormat();
	void insertRightFrame(QString text);
	void insertLeftFrame(QString text);

	void foreachDoc();
	void foreachFrame(QTextFrame* frame);
	void foreachBlock();

    Ui::DemoClass ui;
	QTextEdit* m_pTextEdit;
};
