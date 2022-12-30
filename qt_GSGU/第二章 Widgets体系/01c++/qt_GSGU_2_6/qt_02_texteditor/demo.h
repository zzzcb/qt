#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo.h"

class QTextEdit;
class QAction;
class QComboBox;
class QFontComboBox;

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = nullptr);
    ~Demo();

	bool load(const QString& fileName);

public slots:
	void newFile();

private slots:
	void openFile();
	void saveFile();
	void saveAsFile();

	void boldText();
	void italicText();
	void underlineText();
	void textAlign(QAction *action);
	void colorText();

	void textStyle(int styleIndex);
	void textFamily(const QString &family);
	void textSize(const QString &size);

	void about();

private:

	void setupFileAct();
	void setupEditAct();
	void setupTextFormatAct();
	void setupTextFontAct();

	void setCurrentFileName(const QString &fileName);

    Ui::DemoClass ui;

	QTextEdit *m_pTextEdit;

	QAction*   m_pCutAct;
	QAction*   m_pCopyAct;
	QAction*   m_pPasteAct;

	QAction*   m_pTextBoldAct;
	QAction*   m_pTextItalicAct;
	QAction*   m_pTextUnderlineAct;
	QAction*   m_pAlignLeft;
	QAction*   m_pAlignRight;
	QAction*   m_pAlignCenter;
	QAction*   m_pColorText;

	QComboBox* m_pTextStyleComboBox;
	QFontComboBox* m_pFontComboBox;
	QComboBox* m_pFontSizeComboBox;

	QString m_strFileName;

};
