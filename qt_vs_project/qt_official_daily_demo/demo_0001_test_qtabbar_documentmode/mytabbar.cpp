#include "mytabbar.h"

MyTabbar::MyTabbar(QWidget *parent)
	: QWidget(parent)
{
	mpTabBar1 = new QTabBar(this);

	mpTabBar1->addTab("&tab1");
	mpTabBar1->addTab("t&ab2");
	mpTabBar1->addTab("t&ab3");
	mpTabBar1->addTab("t&ab4");
	mpTabBar1->addTab("t&ab5");
	//mpTabBar1->setDocumentMode(true);

	//this->resize(500, 500);



}

MyTabbar::~MyTabbar()
{
}
