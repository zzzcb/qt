#pragma execution_character_set("utf-8")
#include "demo.h"
#include "QDir"
#include "QFileDialog"
#include "QTextStream"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	setCentralWidget(ui.tabWidget);
}

void Demo::on_actOpen_IODevice_triggered()
{
	QString curPath = QDir::currentPath();//获取系统当前目录
	QString dlgTitle = "打开一个文�; //对话框标�
	QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文�*.*)"; //文件过滤�
	QString fileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

	if (fileName.isEmpty())
		return;

	openTextByIODevice(fileName);
}

void Demo::on_actOpen_TextStream_triggered()
{
	QString curPath = QDir::currentPath();//获取系统当前目录
	QString dlgTitle = "打开一个文�; //对话框标�
	QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文�*.*)"; //文件过滤�
	QString fileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

	if (fileName.isEmpty())
		return;

	openTextByStream(fileName);
}

void Demo::on_actSave_IODevice_triggered()
{
	QString curPath = QDir::currentPath();//获取系统当前目录
	QString dlgTitle = "另存为一个文�; //对话框标�
	QString filter = "h文件(*.h);;c++文件(*.cpp);;文本文件(*.txt);;所有文�*.*)"; //文件过滤�
	QString fileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);

	if (fileName.isEmpty())
		return;

	saveTextByIODevice(fileName);
}

void Demo::on_actSave_TextStream_triggered()
{
	QString curPath = QDir::currentPath();//获取系统当前目录
	QString dlgTitle = "另存为一个文�; //对话框标�
	QString filter = "h文件(*.h);;c++文件(*.cpp);;文本文件(*.txt);;所有文�*.*)"; //文件过滤�
	QString fileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);

	if (fileName.isEmpty())
		return;

	saveTextByStream(fileName);
}

bool Demo::openTextByIODevice(QString fileName)
{
	QFile   file(fileName);

	if (!file.exists()) //文件不存�
		return false;

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) // 打开失败
		return false;

	ui.pTEIoDevice->setPlainText(file.readAll());
	
	file.close();
	ui.tabWidget->setCurrentIndex(0);

	return  true;
}

bool Demo::openTextByStream(QString fileName)
{
	QFile   file(fileName);

	if (!file.exists()) //文件不存�
		return false;

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) // 打开失败
		return false;

	QTextStream stream(&file); //用文本流读取文件

	ui.pTETextStream->setPlainText(stream.readAll());

	file.close();
	ui.tabWidget->setCurrentIndex(1);

	return  true;
}

bool Demo::saveTextByIODevice(QString fileName)
{
	QFile   file(fileName);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	QString str = ui.pTEIoDevice->toPlainText();//整个内容作为字符�

	QByteArray  strBytes = str.toUtf8();//转换为字节数�

	file.write(strBytes, strBytes.length());  //写入文件

	file.close();
	ui.tabWidget->setCurrentIndex(0);
	return  true;
}

bool Demo::saveTextByStream(QString fileName)
{
	QFile   file(fileName);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	QTextStream aStream(&file); //用文本流读取文件

	QString str = ui.pTETextStream->toPlainText(); //转换为字符串

	aStream << str; //写入文本�

	file.close();//关闭文件

	return  true;
}
