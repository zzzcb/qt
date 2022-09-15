#pragma execution_character_set("utf-8")
#include "demo.h"
#include "qdebug.h"

Demo::Demo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	// 设置 table  header 的样式  不然第一行和表头之间的线看不到 
	ui.tableWidget->setStyleSheet("QHeaderView::section{background:rgb(190, 190, 190);}");
	MyItemWrapDelegate* itemDelegate =  new MyItemWrapDelegate;
	ui.tableWidget->setItemDelegate(itemDelegate);


	connect(itemDelegate, &MyItemWrapDelegate::editItemCompleted, this, &Demo::on_itemDelegate_editItemCompleted);
}

void Demo::on_pushButton_clicked()
{
	// 初始化 表格 
	ui.tableWidget->clear(); // 清理所有行头和列头 以及内容 

	QStringList headers = { "姓名","性别","出生日期","民族","分数","是否是党员" };
	ui.tableWidget->setColumnCount(headers.size());
	ui.tableWidget->setRowCount(5);
	ui.tableWidget->setHorizontalHeaderLabels(headers);  
}

void Demo::on_pushButton2_clicked()
{
	int row = ui.tableWidget->rowCount();
	int col = ui.tableWidget->columnCount();
	QTableWidgetItem* item;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j == 0)
			{
				item = new QTableWidgetItem(QIcon(":/Demo/exit.svg"),"hello");
			}
			else if (j == 1)
			{
				item = new QTableWidgetItem("hello");
				item->setCheckState(Qt::Unchecked);
			}
			else
			{
				item = new QTableWidgetItem("hello");
			}
			
			ui.tableWidget->setItem(i, j,item);  
		}

	}
}

void Demo::on_pushButton3_clicked()
{  
	ui.tableWidget->resizeRowsToContents();
	ui.tableWidget->resizeColumnsToContents();
}

void Demo::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
	QMenu menu;
	menu.addAction(ui.actionCenter);
	menu.exec(QCursor::pos());
}

void Demo::on_actionCenter_toggled(bool checked /*= false*/)
{
	if (checked)
	{
		// 将 表格中的所有选中部分 居中  
		for (auto item : ui.tableWidget->selectedItems())
		{
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
	}
	else
	{
		// 将 表格中的所有选中部分 居中  
		for (auto item : ui.tableWidget->selectedItems())
		{
			item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		}
	}



}

void Demo::on_itemDelegate_editItemCompleted(int row, int column)
{
	ui.tableWidget->resizeRowToContents(row);
	ui.tableWidget->resizeColumnToContents(column);
}
