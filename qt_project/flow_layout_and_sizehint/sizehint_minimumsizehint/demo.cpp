#include "demo.h"

#include <QHBoxLayout>

Demo::Demo(QWidget *parent)
    : QWidget(parent)
{
	QHBoxLayout* hLayout = new QHBoxLayout(this);
	hLayout->addWidget(new MyWidget);
	hLayout->addWidget(new MyWidget);

	setLayout(hLayout);
}

Demo::~Demo()
{}
