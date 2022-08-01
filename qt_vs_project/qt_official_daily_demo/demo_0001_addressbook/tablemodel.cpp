#include "tablemodel.h"

#include <QDebug>

TableModel::TableModel(QObject *parent)
	: QAbstractTableModel(parent)
{}

TableModel::TableModel(const QVector<Contact> & vContact, QObject *parent /*= nullptr*/)
	: QAbstractTableModel(parent),
	mv_contact(vContact)

{
}

TableModel::~TableModel()
{}

int TableModel::rowCount(const QModelIndex &parent /* = QModelIndex() */) const
{
	return parent.isValid() ? 0 : mv_contact.size();
}

int TableModel::columnCount(const QModelIndex &parent /* = QModelIndex() */) const
{
	return parent.isValid() ? 0 : 2;
}

QVariant TableModel::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= mv_contact.size() || index.row() < 0)
		return QVariant();

	if (role == Qt::DisplayRole) 
	{
		const auto &contact = mv_contact.at(index.row());

		switch (index.column()) 
		{
		case 0:
			return contact.name;
		case 1:
			return contact.address;
		default:
			break;
		}
	}
	return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal) 
	{
		switch (section) 
		{
		case 0:
			return tr("Name");
		case 1:
			return tr("Address");
		default:
			break;
		}
	}

	return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */)
{
	if (!index.isValid())
		return false;

	int row = index.row();
	Contact& contact = mv_contact[row];

	if (role == Qt::EditRole)
	{
		switch (index.column())
		{
		case 0:
			contact.name = value.toString();
			break;
		case 1:
			contact.address = value.toString();
			break;
		default:
			break;
		}
	}
	emit dataChanged(index, index, { Qt::EditRole | Qt::DisplayRole });
	return true;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent /* = QModelIndex() */)
{
	beginInsertRows(QModelIndex(), row, row + count - 1);

	for (int i = 0; i < count; i++)
	{
		mv_contact.insert(row, {QString(),QString()});
	}

	endInsertRows();
	return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent /* = QModelIndex() */)
{
	beginRemoveRows(QModelIndex(), row, row + count - 1);

	for (int i = 0; i < count; i++)
	{
		mv_contact.removeAt(row);
	}

	endRemoveRows();
	return true;
}


const QVector<Contact> TableModel::getAllContact() const
{
	return mv_contact;
}

void TableModel::clearAllContact()
{
	removeRows(0, mv_contact.size(), QModelIndex());
}
