#include "addresswidget.h"

#include <QTableView>
#include <QHeaderView>
#include <QSortFilterProxyModel>

#include <QMessageBox>
#include <QFile>

#include <QDebug>

AddressWidget::AddressWidget(QWidget *parent)
	: QTabWidget(parent),
	mp_tableModel(new TableModel(this)),
	mp_newAddressTab(new NewAddressTab(this))
{
	addTab(mp_newAddressTab, "new address by zcb");

	connect(mp_newAddressTab, &NewAddressTab::sendDetails, this, &AddressWidget::addEntry);

	setUpTabs();
}

AddressWidget::~AddressWidget()
{
}

void AddressWidget::readFromFile(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(this, "unable read file", file.errorString());
		return;
	}

	QDataStream dataStream(&file);
	QVector<Contact> vContact;
	dataStream >> vContact;
	
	if (vContact.isEmpty())
		QMessageBox::information(this, "content is empty", "");
	else
		mp_tableModel->clearAllContact();
	for (auto &contact : vContact)
		addEntry(contact.name, contact.address);
}


void AddressWidget::writeToFile(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::information(this,"unable write file",file.errorString());
		return;
	}

	QDataStream dataStream(&file);
	dataStream << mp_tableModel->getAllContact();

}

void AddressWidget::addEntry(const QString& name, const QString& address)
{
	if (!mp_tableModel->getAllContact().contains({name,address}))
	{
		mp_tableModel->insertRows(0, 1, QModelIndex());

		QModelIndex index = mp_tableModel->index(0, 0);
		mp_tableModel->setData(index, name,Qt::EditRole);

		index = mp_tableModel->index(0, 1);
		mp_tableModel->setData(index, address, Qt::EditRole);
	}
	else
	{
		QMessageBox::information(this, tr("Duplicate Name"),
			tr("The name \"%1\" already exists.").arg(name));
	}
}

void AddressWidget::removeEntry()
{
	// 对当前所选定的所有entry 删除即可
	qDebug() <<"cur index " << indexOf(currentWidget());

	auto curTab = qobject_cast<QTableView*>(currentWidget());
	if (curTab)
	{
		auto proxyModel = static_cast<QSortFilterProxyModel*>(curTab->model());
		auto * selectionModel = curTab->selectionModel();

		auto indexs = selectionModel->selectedRows();

		for (auto index : indexs)
		{
			int row = proxyModel->mapToSource(index).row();
			qDebug() << " selection row is " << row;
			mp_tableModel->removeRows(row, 1, QModelIndex());
		}
	}

}

void AddressWidget::editEntry()
{
	
	auto curTab = qobject_cast<QTableView*>(currentWidget());
	if (curTab)
	{
		auto selectModel = curTab->selectionModel();
		auto indexs = selectModel->selectedRows();

		auto proxyModel = static_cast<QSortFilterProxyModel*>(curTab->model());

		for (auto index : indexs)
		{
			int row = proxyModel->mapToSource(index).row();
			auto nameIndex = mp_tableModel->index(row, 0);
			auto addressIndex = mp_tableModel->index(row, 1);
			QString name = nameIndex.data().toString();
			QString address = addressIndex.data().toString();

			AddDialog aDialog;
			aDialog.editAddress(name, address);
			aDialog.setWindowTitle("edit address");
			if (aDialog.exec())
			{
				QString newAddress = aDialog.address();
				if (newAddress != address)
				{
					mp_tableModel->setData(addressIndex,newAddress,Qt::EditRole);
				}
			}

			break;
		}
	}
}

void AddressWidget::showAddEntryDialog()
{
	AddDialog addDialog;
	if (addDialog.exec())
		addEntry(addDialog.name(), addDialog.address());
}

void AddressWidget::setUpTabs()
{
	const auto groups = { "ABC", "DEF", "GHI", "JKL", "MNO", "PQR", "STU", "VW", "XYZ" };

	for (const QString& group : groups)
	{
		const auto regExp = QRegularExpression(QString("^[%1].*").arg(group),QRegularExpression::CaseInsensitiveOption);

		auto proxyModel = new QSortFilterProxyModel(this);
		proxyModel->setSourceModel(mp_tableModel);
		proxyModel->setFilterRegularExpression(regExp);
		proxyModel->setFilterKeyColumn(0);

		QTableView* tableView = new QTableView;
		tableView->setModel(proxyModel);
		tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // 鼠标点击时是行,而不是具体的item
		tableView->horizontalHeader()->setStretchLastSection(true);     // 最后一列扩展到最后
		tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 无法对item进行编辑
		tableView->setSelectionMode(QAbstractItemView::SingleSelection);// 最多选择一行
		tableView->setSortingEnabled(true);// 开启按照列进行排序功能

		
		// 当模型中的数据发生变化的时候 更新按钮的状态
		connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &AddressWidget::selectionChanged);

		// 当切换tab的时候也 更新按钮的状态
		connect(this, &QTabWidget::currentChanged, [this,tableView](int idx) {
			if (widget(idx) == tableView)
			{
				emit selectionChanged(tableView->selectionModel()->selection());
			}
		});



		addTab(tableView, group);
	}



}
