#pragma once

#include "newaddresstab.h"
#include "tablemodel.h"

#include <QTabWidget>
#include <QItemSelection>

class AddressWidget : public QTabWidget
{
	Q_OBJECT

public:
	AddressWidget(QWidget *parent=nullptr);
	~AddressWidget();

	void readFromFile(const QString& fileName);
	void writeToFile(const QString& fileName);


public slots:
	void showAddEntryDialog();
	void removeEntry();
	void editEntry();


private slots:
	void addEntry(const QString& name, const QString& address);


signals:
	void selectionChanged(const QItemSelection &selected);

private:

	void setUpTabs();


	TableModel * mp_tableModel;
	NewAddressTab* mp_newAddressTab;

};
