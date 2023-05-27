#include <QtWidgets/QApplication>

#include <QDateTimeEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


	QWidget * mw = new QWidget;

	/** QDateTimeEdit */
	QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), mw);
	dateTimeEdit->setMinimumDate(QDate::currentDate().addDays(-365));
	dateTimeEdit->setMaximumDate(QDate::currentDate().addDays(365));
	dateTimeEdit->setDisplayFormat("yyyy.MM.dd");

	/** QDateEdit */
	QDateEdit* dateEdit = new QDateEdit(QDate::currentDate(), mw);
	dateEdit->move(100, 100);

	/** QTimeEdit */
	QTimeEdit* timeEdit = new QTimeEdit(QTime::currentTime(), mw);
	timeEdit->move(200, 100);

	/** QDoubleSpinBox */
	QDoubleSpinBox* dsb = new QDoubleSpinBox(mw);
	dsb->move(100, 200);

	/** QSpinBox */
	QSpinBox* sb = new QSpinBox(mw);
	sb->move(200, 200);

	mw->show();

    return a.exec();
}
