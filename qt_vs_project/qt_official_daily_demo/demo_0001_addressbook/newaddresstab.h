#pragma once

#include "adddialog.h"

#include <QWidget>

class NewAddressTab  : public QWidget
{
	Q_OBJECT

public:
	NewAddressTab(QWidget *parent=nullptr);
	~NewAddressTab();

private slots:
	void addEntry();
signals:
	void sendDetails(const QString& name,const QString& address);


};
