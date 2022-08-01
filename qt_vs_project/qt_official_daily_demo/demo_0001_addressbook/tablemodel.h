#pragma once

#include <QAbstractTableModel>

#include <QDebug>

struct Contact
{
	QString name;
	QString address;

	bool operator==(const Contact& other) const
	{
		return name == other.name && address == other.address;
	}

};

// 全局重载操作符
inline QDataStream& operator<<(QDataStream& out,const Contact& contact)
{
	out << contact.name << contact.address;
	return out;
}

// 全局重载操作符
inline QDataStream& operator>>(QDataStream& in, Contact& contact)
{
	in >> contact.name >> contact.address;
	return in;
}



class TableModel  : public QAbstractTableModel
{
	Q_OBJECT

public:
	TableModel(QObject *parent = nullptr);
	TableModel(const QVector<Contact> & vContact, QObject *parent = nullptr);
	~TableModel();

	int rowCount(const QModelIndex &parent /* = QModelIndex() */) const override;
	int columnCount(const QModelIndex &parent /* = QModelIndex() */) const override;
	QVariant data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */) override;

	Qt::ItemFlags flags(const QModelIndex &index) const override;


	bool insertRows(int row, int count, const QModelIndex &parent /* = QModelIndex() */) override;
	bool removeRows(int row, int count, const QModelIndex &parent /* = QModelIndex() */) override;


	const QVector<Contact> getAllContact() const;
	void clearAllContact();


private:
	QVector<Contact> mv_contact;
};
