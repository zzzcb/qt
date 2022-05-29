#pragma once

#include <QTabWidget>

class AddressWidget : public QTabWidget
{
	Q_OBJECT

public:
	AddressWidget(QWidget *parent=nullptr);
	~AddressWidget();
};
