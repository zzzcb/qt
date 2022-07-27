#include "addresswidget.h"

#include <QDebug>

AddressWidget::AddressWidget(QWidget *parent)
	: QTabWidget(parent),
	mp_newAddressTab(new NewAddressTab(this))
{
	addTab(mp_newAddressTab, "new address by zcb");

	//connect(mp_newAddressTab, &NewAddressTab::sendDetails, [](const QString&name,const QString& addr) {
	//	qDebug() << "name 0--------------->> " << name;
	//	qDebug() << "addr 0--------------->> " << addr;
	//});



}

AddressWidget::~AddressWidget()
{
}
