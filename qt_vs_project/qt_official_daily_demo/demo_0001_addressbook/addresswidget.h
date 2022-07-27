#pragma once

#include "newaddresstab.h"

#include <QTabWidget>

class AddressWidget : public QTabWidget
{
	Q_OBJECT

public:
	AddressWidget(QWidget *parent=nullptr);
	~AddressWidget();


private:
	//TableModel * mp_tableModel;
	NewAddressTab* mp_newAddressTab;

};
