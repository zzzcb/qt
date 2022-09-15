#include "demo.h"
#include "qdebug.h"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	mStrListModel = new QStringListModel(this);
	mStrListModel->setStringList({ "item1","item2","item3" });
	ui.listView->setModel(mStrListModel);

}

void Demo::on_pushButton_2_clicked()
{
	int count = mStrListModel->rowCount();
	mStrListModel->insertRow(count);
	mStrListModel->setData(mStrListModel->index(count), "new item",Qt::DisplayRole);
}

void Demo::on_pushButton_3_clicked()
{
	mStrListModel->removeRows(0, mStrListModel->rowCount());   
}
