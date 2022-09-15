#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);
private slots:
	void on_actOpen_IODevice_triggered();
	void on_actOpen_TextStream_triggered();

	void on_actSave_IODevice_triggered();
	void on_actSave_TextStream_triggered();

private:
    Ui::DemoClass ui;
	bool openTextByIODevice(QString fileName);
	bool openTextByStream(QString fileName);
	bool saveTextByIODevice(QString fileName);
	bool saveTextByStream(QString fileName);
};
