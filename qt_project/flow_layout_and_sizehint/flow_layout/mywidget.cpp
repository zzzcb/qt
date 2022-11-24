#include "mywidget.h"

#include <QPushButton>
#include <QScrollArea>

#include "flowlayout.h"
#include <QVBoxLayout>

MyWidget::MyWidget(QWidget*parent)
	:QWidget(parent)
{
	QVBoxLayout *mainLayout = new QVBoxLayout(this);

	QScrollArea *scrollArea = new QScrollArea;
	scrollArea->setWidgetResizable(true); // very important

	QWidget* childW = new QWidget;
	m_pFlowLayout = new FlowLayout(childW);
	m_pFlowLayout->addWidget(new QPushButton);
	m_pFlowLayout->addWidget(new QPushButton);
	m_pFlowLayout->addWidget(new QPushButton);
	childW->setLayout(m_pFlowLayout);

	scrollArea->setWidget(childW);

	auto btn = new QPushButton("add new green");
	mainLayout->addWidget(btn);
	mainLayout->addWidget(scrollArea);

	connect(btn, &QPushButton::clicked, this, &MyWidget::slot_addBtn);
}

void MyWidget::slot_addBtn()
{
	m_pFlowLayout->addWidget(new GreenWidget);
}
