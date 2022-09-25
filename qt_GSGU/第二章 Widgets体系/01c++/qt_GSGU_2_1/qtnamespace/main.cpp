#include <QDate>
#include <QDebug>

void printCurDate(Qt::DateFormat format)
{
	qDebug() << "--------------> " << QDate::currentDate().toString(format);
}


int main(int argc, char *argv[])
{
	printCurDate(Qt::ISODate);
	printCurDate(Qt::LocalDate);
	printCurDate(Qt::TextDate);
}
