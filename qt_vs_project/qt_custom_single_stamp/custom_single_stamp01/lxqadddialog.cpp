#include "lxqadddialog.h"

#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QDebug>



lxQAddDialog::lxQAddDialog(QWidget *parent)
	: QDialog(parent)
{
	/** 设置自定义窗口flag*/
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	auto okButton = new QPushButton(tr("OK"));
	auto cancelButton = new QPushButton(tr("Cancel"));
	connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
	connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

	auto buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);


	mp_mainLayout = new QFormLayout(this);
	//mainLayout->addRow(tr("Name:"), new QLineEdit(this));
	//mainLayout->addRow("", new QCheckBox(this));
	//mainLayout->addRow(tr("Name:"), new QComboBox(this));
	//mainLayout->addRow(tr("Name:"), new QLineEdit(this));
	//mainLayout->addRow(tr("Name:"), new QLineEdit(this));
	mp_mainLayout->addRow("",buttonLayout);
}

lxQAddDialog::~lxQAddDialog()
{
}

QString lxQAddDialog::name()
{
	return "";
}

QString lxQAddDialog::address()
{
	return "";
}

bool lxQAddDialog::initEditor(QString strTitle, QVector<QVector<QString>> vLabelAndWidget)
{
	setWindowTitle(strTitle);

	for (const auto& itemPair : vLabelAndWidget)
	{
		if (itemPair.size() < 2)
			return false;

		if (itemPair[1] == "QLineEdit")
		{
			auto lineEdit = new QLineEdit(this);
			mv_editor.push_back(lineEdit);
			if (itemPair.size() >= 3)
				lineEdit->setText(itemPair[2]);
			mp_mainLayout->insertRow(mp_mainLayout->rowCount()-1, itemPair[0], lineEdit);
		}
		else if (itemPair[1] == "QCheckBox")
		{
			auto checkBox = new QCheckBox(this);
			mv_editor.push_back(checkBox);
			if (itemPair.size() >= 3)
				checkBox->setText(itemPair[2]);

			mp_mainLayout->insertRow(mp_mainLayout->rowCount()-1, itemPair[0], checkBox);
		}
		else if (itemPair[1] == "QComboBox")
		{
			auto comboBox = new QComboBox(this);
			mv_editor.push_back(comboBox);
			for (int i = 2; i < itemPair.size(); i++)
				comboBox->addItem(itemPair[i]);
			mp_mainLayout->insertRow(mp_mainLayout->rowCount()-1, itemPair[0], comboBox);
		}
	}
	return true;
}


QVector<QString> lxQAddDialog::getEditorResult()
{
	QVector<QString> vResult;
	QString val;
	mv_editor;

	for (auto widget : mv_editor)
	{
		if (qobject_cast<QLineEdit*>(widget))
		{
			vResult.push_back(((QLineEdit*)widget)->text());
		}
		else if (qobject_cast<QCheckBox*>(widget))
		{
			val = ((QCheckBox*)widget)->isChecked()?"1":"0";
			vResult.push_back(val);
		}
		else if (qobject_cast<QComboBox*>(widget))
		{
			auto curWidget = (QComboBox*)(widget);

			val = QString("%1+%2").arg(QString::number(curWidget->currentIndex()), curWidget->currentText());
			vResult.push_back(val);
		}
	}

	return vResult;
}
