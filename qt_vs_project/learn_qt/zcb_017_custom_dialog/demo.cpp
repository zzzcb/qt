#include "demo.h"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	mpStdItemModel = new QStandardItemModel(10, 6, this);
	mpItemSelModel = new QItemSelectionModel(mpStdItemModel);


	ui.tableView->setModel(mpStdItemModel);
	ui.tableView->setSelectionModel(mpItemSelModel);

}

void Demo::on_action_triggered()
{
	myDialog1 dlg1;
	dlg1.setSpinDefaultVal(mpStdItemModel->rowCount(), mpStdItemModel->columnCount());
	if (dlg1.exec() == QDialog::Accepted)
	{
		mpStdItemModel->setRowCount(dlg1.rowCnt());
		mpStdItemModel->setColumnCount(dlg1.columnCnt());
	}
}

void Demo::on_action_2_triggered()
{

}

void Demo::on_action_3_triggered()
{

}
