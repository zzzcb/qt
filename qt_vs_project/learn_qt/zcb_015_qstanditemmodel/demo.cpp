#include "demo.h"
#include "qdebug.h"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	
	mpStdItemModel = new QStandardItemModel(10,6,this);
	mpItemSelModel = new QItemSelectionModel(mpStdItemModel);
	
	// 初始化 mpStdItemModel 
	QStandardItem * item;
	for (int i = 0; i < 10; i++)
	{
		QString rowS;
		for (int j = 0; j < 6; j++)
		{
			QString s = QString::asprintf("item %d %d", i, j);
			item = new QStandardItem(s);
			mpStdItemModel->setItem(i,j,item);
			rowS = rowS + s+"   ";
		}
		ui.plainTextEdit->appendPlainText(rowS);
	}


	ui.tableView->setModel(mpStdItemModel);
	ui.tableView->setSelectionModel(mpItemSelModel);
}

void Demo::on_pushButton_clicked()
{
	for (auto index : mpItemSelModel->selectedIndexes())
	{
		if (index.data().canConvert<QString>())
		{
			QString s = qvariant_cast<QString>(index.data());
			qDebug() <<"select data "<< s;
		}
	}

}
