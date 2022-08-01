#include "adddialog.h"

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>


AddDialog::AddDialog(QWidget *parent)
	: QDialog(parent),
	mp_nameText(new QLineEdit),
	mp_addressText(new QTextEdit)
{
	auto nameLabel = new QLabel(tr("Name"));
	auto addressLabel = new QLabel(tr("Address"));
	auto okButton = new QPushButton(tr("OK"));
	auto cancelButton = new QPushButton(tr("Cancel"));

	auto gLayout = new QGridLayout;
	gLayout->setColumnStretch(1, 2);
	gLayout->addWidget(nameLabel, 0, 0);
	gLayout->addWidget(mp_nameText, 0, 1);
	gLayout->addWidget(addressLabel, 1, 0, Qt::AlignLeft | Qt::AlignTop);
	gLayout->addWidget(mp_addressText, 1, 1, Qt::AlignLeft);

	auto buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);

	gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);
	setLayout(gLayout);

	connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
	connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

	setWindowTitle(tr("Add a Contact"));
}

AddDialog::~AddDialog()
{
}

QString AddDialog::name()
{
	return mp_nameText->text();
}

QString AddDialog::address()
{
	return mp_addressText->toPlainText();
}

void AddDialog::editAddress(const QString &name, const QString &address)
{
	mp_nameText->setText(name);
	mp_addressText->setText(address);
	mp_nameText->setReadOnly(true);
}
