#include "demo.h"
#include "qdebug.h"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	setCentralWidget(ui.splitter);

	ui.toolButton_5->setDefaultAction(ui.actionInit);
	ui.toolButton_6->setDefaultAction(ui.actionClear);
	ui.toolButton_7->setDefaultAction(ui.actionInsert);
	ui.toolButton_8->setDefaultAction(ui.actionAdd);
	ui.toolButton_17->setDefaultAction(ui.actionDelete);

	QMenu* menu = new QMenu(this);
	menu->addAction(ui.actionAll);
	menu->addAction(ui.actionNone);
	menu->addAction(ui.actionInverse);
	ui.actionItem->setMenu(menu);
	ui.toolButton->setDefaultAction(ui.actionItem);
	
	ui.mainToolBar->addAction(ui.actionItem);
	ui.mainToolBar->addSeparator();
	ui.mainToolBar->addAction(ui.actionQuit);

	ui.toolButton_4->setDefaultAction(ui.actionAll);
	ui.toolButton_3->setDefaultAction(ui.actionNone);
	ui.toolButton_2->setDefaultAction(ui.actionInverse);

}

void Demo::on_toolBox_currentChanged(int index)
{
	ui.tabWidget->setCurrentIndex(index);
}

void Demo::on_actionInit_triggered()
{
	ui.listWidget->clear();

	QListWidgetItem * item;
	for (int i = 0; i < 20; i++)
	{
		QString s = QString::asprintf("item %d", i); 
		item = new QListWidgetItem(s);
		item->setIcon(QIcon(":/Demo/exit.svg"));
		item->setCheckState(Qt::Unchecked);
		ui.listWidget->addItem(item);
	}



}

void Demo::on_actionClear_triggered()
{
	ui.listWidget->clear();
}

void Demo::on_actionInsert_triggered()
{
	ui.listWidget->insertItem(ui.listWidget->currentRow()+1, "nb");
}

void Demo::on_actionAdd_triggered()
{
	ui.listWidget->addItem("nb2");
}

void Demo::on_actionDelete_triggered()
{
	delete ui.listWidget->currentItem();
}

void Demo::on_actionItem_triggered()
{

}

void Demo::on_actionAll_triggered()
{
	for (int i = 0; i < ui.listWidget->count(); i++)
	{
		ui.listWidget->item(i)->setCheckState(Qt::Checked);
	}
}

void Demo::on_actionNone_triggered()
{
	for (int i = 0; i < ui.listWidget->count(); i++)
	{
		ui.listWidget->item(i)->setCheckState(Qt::Unchecked);
	}
}

void Demo::on_actionInverse_triggered()
{
	for (int i = 0; i < ui.listWidget->count(); i++)
	{
		auto item = ui.listWidget->item(i);
		if(item->checkState() == Qt::Checked)
			item->setCheckState(Qt::Unchecked);
		else 
			item->setCheckState(Qt::Checked);
	}
}

void Demo::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
	if(current)
		ui.lineEdit->setText(current->text());
}

void Demo::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
	qDebug() << "pos " << pos.x() << " " << pos.y();
	QMenu menu; 
	menu.addAction(ui.actionInit);
	menu.addAction(ui.actionClear);
	menu.addAction(ui.actionInsert);
	menu.addAction(ui.actionAdd);
	menu.addAction(ui.actionDelete);
	menu.addSeparator();
	menu.addAction(ui.actionAll);
	menu.addAction(ui.actionNone);
	menu.addAction(ui.actionInverse);
	
	menu.exec(QCursor::pos());  // 鼠标右键 位置处 显示menu 
}

