#include "demo.h"

Demo::Demo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);


	mpStdItemModel = new QStandardItemModel(10, 6, this);
	mpItemSelModel = new QItemSelectionModel(mpStdItemModel);

	// 初始化 mpStdItemModel 
	QStandardItem * item;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			QString s = QString::asprintf("item %d %d", i, j);
			item = new QStandardItem(s);
			mpStdItemModel->setItem(i, j, item);
		}
	}


	ui.tableView->setModel(mpStdItemModel);
	ui.tableView->setSelectionModel(mpItemSelModel);
}
