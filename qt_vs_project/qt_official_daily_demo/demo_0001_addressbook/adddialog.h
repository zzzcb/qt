#pragma once

#include <QDialog>


class QLineEdit;
class QTextEdit;


class AddDialog : public QDialog
{
	Q_OBJECT

public:
	AddDialog(QWidget *parent = nullptr);
	~AddDialog();

	QString name();
	QString address();

	void editAddress(const QString &name,const QString &address);

private:
	QLineEdit *mp_nameText;
	QTextEdit *mp_addressText;

};
