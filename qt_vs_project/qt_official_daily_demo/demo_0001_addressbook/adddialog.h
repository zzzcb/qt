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

private:
	QLineEdit *mp_nameText;
	QTextEdit *mp_addressText;

};
