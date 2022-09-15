#pragma once

#include <QWidget>
#include "ui_myplaineditor.h"

class MyPlainEditor : public QWidget
{
	Q_OBJECT

public:
	MyPlainEditor(QWidget *parent = Q_NULLPTR);
	~MyPlainEditor();
	
	void loadFile(QString &fileName);
	bool isFileOpened(); // 当前是否有文件已经打开

	void setEditFont();
	void textCut();
	void textCopy();
	void textPaste();
private:
	Ui::MyPlainEditor ui;
	QString mCurFileName;
	bool mFileOpened = false;
};
