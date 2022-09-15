#pragma execution_character_set("utf-8")
#include "demo.h"
#include "qdebug.h"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	initStatusBar();
	mDisImg = new QPixmap;
}

void Demo::getFitImg(QPixmap& fittedImg,double areaW,double areaH,double realW,double realH)
{
	double realImgRatio = realW / realH;
	double areaRatio = areaW / areaH;

	// 先尝试 scaledToHeight 
	fittedImg = mDisImg->scaledToHeight(areaH - 30);
	double scaledWidth = fittedImg.height()*realImgRatio;

	if (areaRatio > realImgRatio && areaW > scaledWidth)
		return;
	else
		fittedImg = mDisImg->scaledToWidth(areaW - 30);
}

void Demo::resizeEvent(QResizeEvent *event)
{
	if (mDisImg->isNull())
		return;

	QPixmap img;
	getFitImg(img, ui.scrollArea->width(), ui.scrollArea->height(), mDisImg->width(), mDisImg->height());
	ui.label->setPixmap(img);
}

void Demo::initStatusBar()
{
	auto sb = ui.statusBar;
	
	sb->setStyleSheet("background-color:rgb(85, 85, 255);color:white;");
	sb->setSizeGripEnabled(false);

	// 由于status bar 的默认会自带一条竖线,所以这里使用先给一个widget设置layout ，然后再将widget添加到 status bar 的方法
	QWidget * widget = new QWidget;

	// 给状态栏添加图标  添加显示信息
	mStatusIconPixmap = new QPixmap(":/Demo/exit.svg");
	mStatusIcon = new QLabel;
	mStatusIcon->setMaximumSize(16, 16);
	mStatusIcon->setPixmap(mStatusIconPixmap->scaled(16,16));

	mStatusInfo = new QLabel(" Ready");

	QHBoxLayout* hLY = new QHBoxLayout;
	hLY->setSpacing(0);
	hLY->setContentsMargins(0, 0, 0, 0);
	hLY->addWidget(mStatusIcon);
	hLY->addWidget(mStatusInfo);
	widget->setLayout(hLY);

	sb->addWidget(widget,1);
}

void Demo::on_actionDockShow_triggered(bool checked)
{
	ui.dockWidget->setVisible(checked);
}

void Demo::on_actionDockFloat_triggered(bool checked)
{
	ui.dockWidget->setFloating(checked);
}

void Demo::on_dockWidget_topLevelChanged(bool topLevel)
{
	// The topLevel parameter is true if the dock widget is now floating; otherwise it is false.
	ui.actionDockFloat->setChecked(topLevel);
}

void Demo::on_dockWidget_visibilityChanged(bool visible)
{
	// The visible parameter is true if the dock widget is now showen; hidden is false.
	ui.actionDockShow->setChecked(visible);
}


//void printDirTreeData(QFileInfo rootPwd)
//{
//	if (!rootPwd.isDir()) // 递归终止条件  
//	{
//		qDebug() << "文件: " << rootPwd.absoluteFilePath();
//		return;
//	}
//
//
//	QDir curDir(rootPwd.absoluteFilePath());
//	qDebug() << "目录: " << curDir.absolutePath();
//
//	for (auto ele : QDir(rootPwd.absoluteFilePath()).entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot))
//	{
//		printDirTreeData(QFileInfo(curDir.absoluteFilePath(ele))); // 递归链条
//	}
//}

void generateDirTreeData(QFileInfo rootPwd, QTreeWidgetItem* rootItem,QList<QTreeWidgetItem*>& items)
{
	if (!rootPwd.isDir()) // 递归终止条件  
		return;

	QDir curDir(rootPwd.absoluteFilePath());
	for (auto ele : QDir(rootPwd.absoluteFilePath()).entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot))
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setText(0, ele);
		rootItem->addChild(item);

		generateDirTreeData(QFileInfo(curDir.absoluteFilePath(ele)),item,items); // 递归链条
		items.append(item);
	}
}

// QFileInfo -> dir + filename -> pwd.absoluteFilePath() + pwd.fileName()
void Demo::on_lineEdit_chooseDirCompleted()
{
	if (ui.lineEdit->text().isEmpty())
		return;

	// 首先清空 tree data 
	ui.treeWidget->clear();
	
	QFileInfo pwd(ui.lineEdit->text());
	
	QString rootStr = QDir(pwd.absoluteFilePath()).absolutePath();
	QString rootName = rootStr.right(rootStr.length() - rootStr.lastIndexOf("/") - 1);
	QString rootPath = rootStr.left(rootStr.length() - rootName.length());
	ui.treeWidget->setHeaderLabel(rootPath);
	ui.treeWidget->header()->hide();

	QTreeWidgetItem* rootItem = new QTreeWidgetItem;
	rootItem->setText(0,rootName);

	QList<QTreeWidgetItem*> items;
	items.append(rootItem);
	generateDirTreeData(pwd,rootItem,items);
	//qDebug() << "size " << items.size();

	ui.treeWidget->insertTopLevelItems(0, items);
}

void Demo::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
	if (!current)
		return;

	QString fullFilePath;
	fullFilePath.insert(0, current->text(0));

	// 向上找出当前所选项的全路径 并设置到状态栏中 
	QTreeWidgetItem* item = current->parent();
	while (item)
	{
		fullFilePath.insert(0, item->text(0)+"/");
		item = item->parent();
	}

	fullFilePath.insert(0, ui.treeWidget->headerItem()->text(0));

	// 如果当前项 是图片 就展示出来
	if (mDisImg->load(fullFilePath))
	{
		// 激活 按钮使能
		ui.actionZoomIn->setEnabled(true);
		ui.actionZoomOut->setEnabled(true);
		ui.actionRealSize->setEnabled(true);

		QPixmap img;
		getFitImg(img, ui.scrollArea->width(), ui.scrollArea->height(), mDisImg->width(), mDisImg->height());
		ui.label->setPixmap(img);

		/*double areaH = ui.scrollArea->height();
		double areaW = ui.scrollArea->width();
		double realImgRatio = mDisImg->width() / mDisImg->height();
		if(areaW/areaH > realImgRatio)
			ui.label->setPixmap(mDisImg->scaledToHeight(areaH - 30));
		else
			ui.label->setPixmap(mDisImg->scaledToWidth(areaW - 30));*/
	}
	else
	{
		// 取消 缩放按钮使能
		ui.actionZoomIn->setEnabled(false);
		ui.actionZoomOut->setEnabled(false);
		ui.actionRealSize->setEnabled(false);


		ui.label->clear();
		ui.label->setText("NO IMAGE");
	}

	mStatusInfo->setText(fullFilePath);

	}


// 放大图片
void Demo::on_actionZoomIn_triggered()
{
	if (ui.label->pixmap()->isNull())
		return;

	// 当前图片的 width 和 height  
	double curWidth = ui.label->pixmap()->width();
	double curHeight = ui.label->pixmap()->height();
	double ratio = 1.2;
	if (curWidth > mDisImg->width() * 8) // 不能再放大了
		return;

	ui.label->setPixmap(mDisImg->scaled(curWidth*ratio, curHeight*ratio));
}

void Demo::on_actionZoomOut_triggered()
{
	if (ui.label->pixmap()->isNull())
		return;

	// 当前图片的 width 和 height  
	double curWidth = ui.label->pixmap()->width();
	double curHeight = ui.label->pixmap()->height();
	double ratio = 0.8;

	ui.label->setPixmap(mDisImg->scaled(curWidth*ratio, curHeight*ratio));
}

void Demo::on_actionRealSize_triggered()
{
	QPixmap img;
	getFitImg(img, ui.scrollArea->width(), ui.scrollArea->height(), mDisImg->width(), mDisImg->height());
	
	ui.label->setPixmap(img);
}
