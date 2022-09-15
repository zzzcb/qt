#pragma execution_character_set("utf-8")
#include "demo.h"
#include "myplaineditor.h"
#include "QMdiSubWindow"
#include "QDir"
#include "QFileDialog"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	setCentralWidget(ui.mdiArea);
}

// 新建文档
void Demo::on_action_triggered()
{
	MyPlainEditor* subWindow = new MyPlainEditor(this);
	ui.mdiArea->addSubWindow(subWindow);
	subWindow->show();

	ui.action_4->setEnabled(true);
	ui.action_5->setEnabled(true);
	ui.action_6->setEnabled(true);
	ui.action_7->setEnabled(true);
}

// 打开文档
void Demo::on_action_2_triggered()
{
	bool needNew = false;// 是否需要新建子窗口

	MyPlainEditor *subWindow;
	if (ui.mdiArea->subWindowList().count() > 0)
	{
		subWindow = (MyPlainEditor*)ui.mdiArea->activeSubWindow()->widget();
		needNew = subWindow->isFileOpened();
	}
	else
		needNew = true;

	QString curPath = QDir::currentPath();
	QString aFileName = QFileDialog::getOpenFileName(this, tr("打开一个文件"), curPath,
		"C++文件(*.h *cpp);;文本文件(*.txt);;所有文件(*.*)");
	if (aFileName.isEmpty())
		return; //如果未选择文件，退出

	if (needNew) //需要新建子窗口
	{
		subWindow = new MyPlainEditor(this);
		ui.mdiArea->addSubWindow(subWindow);
	}
	subWindow->loadFile(aFileName); //打开文件
	subWindow->show();

	ui.action_4->setEnabled(true);
	ui.action_5->setEnabled(true);
	ui.action_6->setEnabled(true);
	ui.action_7->setEnabled(true);
}

// 关闭全部文档
void Demo::on_action_3_triggered()
{
	ui.mdiArea->closeAllSubWindows();
}
// 字体设置
void Demo::on_action_4_triggered()
{
	MyPlainEditor* formDoc = (MyPlainEditor*)ui.mdiArea->activeSubWindow()->widget();
	formDoc->setEditFont();
}
// 剪切
void Demo::on_action_5_triggered()
{
	MyPlainEditor* formDoc = (MyPlainEditor*)ui.mdiArea->activeSubWindow()->widget();
	formDoc->textCut();
}
// 复制
void Demo::on_action_6_triggered()
{
	MyPlainEditor* formDoc = (MyPlainEditor*)ui.mdiArea->activeSubWindow()->widget();
	formDoc->textCopy();
}
// 拷贝
void Demo::on_action_7_triggered()
{
	MyPlainEditor* formDoc = (MyPlainEditor*)ui.mdiArea->activeSubWindow()->widget();
	formDoc->textPaste();
}
// mdi模式
void Demo::on_action_8_triggered(bool checked)
{
	if (checked) //Tab多页显示模式
	{
		ui.mdiArea->setViewMode(QMdiArea::TabbedView); //Tab多页显示模式
		ui.mdiArea->setTabsClosable(true); //页面可关闭
		ui.action_10->setEnabled(false);
		ui.action_9->setEnabled(false);
	}
	else //子窗口模式
	{
		ui.mdiArea->setViewMode(QMdiArea::SubWindowView); //子窗口模式
		ui.action_10->setEnabled(true); 
		ui.action_9->setEnabled(true);
	}
}

// 级联展开
void Demo::on_action_10_triggered()
{
	ui.mdiArea->tileSubWindows();
}
// 平铺展开
void Demo::on_action_9_triggered()
{
	ui.mdiArea->cascadeSubWindows();
}


void Demo::on_mdiArea_subWindowActivated(QMdiSubWindow *window)
{
	// 若 子窗口为0 
	if (ui.mdiArea->subWindowList().count() == 0)
	{
		ui.action_4->setEnabled(false);
		ui.action_5->setEnabled(false);
		ui.action_6->setEnabled(false);
		ui.action_7->setEnabled(false);
	}
}
