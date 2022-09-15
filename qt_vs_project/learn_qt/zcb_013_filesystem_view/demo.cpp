#include "demo.h"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	mFileSysModel = new QFileSystemModel(this);
	mFileSysModel->setRootPath(QDir::currentPath());

	ui.treeView->setModel(mFileSysModel);  
	ui.listView->setModel(mFileSysModel);
	ui.tableView->setModel(mFileSysModel);
	ui.tableView->verticalHeader()->setVisible(false);

	connect(ui.treeView, &QTreeView::clicked, ui.listView, &QListView::setRootIndex);
	connect(ui.treeView, &QTreeView::clicked, ui.tableView, &QTableView::setRootIndex);

}

void Demo::on_treeView_clicked(const QModelIndex &index)
{
	ui.label->setText(mFileSysModel->fileName(index));
	ui.label_2->setText(QString::asprintf("%d", mFileSysModel->size(index)));
	ui.label_3->setText(mFileSysModel->type(index));
	ui.checkBox->setChecked(mFileSysModel->isDir(index));

	ui.label_4->setText(mFileSysModel->filePath(index));
}
