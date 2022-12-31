#include "myplaineditor.h"
#include "QTextStream"
#include "QFileInfo"
#include "QFontDialog"

MyPlainEditor::MyPlainEditor(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

MyPlainEditor::~MyPlainEditor()
{
}

void MyPlainEditor::loadFile(QString &fileName)
{
	QFile aFile(fileName);  //以文件方式读出
	if (aFile.open(QIODevice::ReadOnly | QIODevice::Text)) //以只读文本方式打开文件
	{
		QTextStream aStream(&aFile); //用文本流读取文件
		ui.plainTextEdit->clear();
		ui.plainTextEdit->setPlainText(aStream.readAll()); 
		aFile.close();

		mCurFileName = fileName;
		QFileInfo   fileInfo(fileName); //文件信息
		QString str = fileInfo.fileName(); //去除路径后的文件名
		setWindowTitle(str);
		mFileOpened = true;
	}
}

bool MyPlainEditor::isFileOpened()
{
	return mFileOpened;
}

void MyPlainEditor::setEditFont()
{
	QFont   font;
	font = ui.plainTextEdit->font();

	bool    ok;
	font = QFontDialog::getFont(&ok, font);
	ui.plainTextEdit->setFont(font);
}

void MyPlainEditor::textCut()
{
	ui.plainTextEdit->cut();
}

void MyPlainEditor::textCopy()
{
	ui.plainTextEdit->copy();
}

void MyPlainEditor::textPaste()
{
	ui.plainTextEdit->paste();
}
