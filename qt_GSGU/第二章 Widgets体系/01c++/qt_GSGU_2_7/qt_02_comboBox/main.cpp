#include <QtWidgets/QApplication>

#include <QComboBox>
#include <QFontComboBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
	QWidget mw;
	QComboBox* cb = new QComboBox(&mw);
	cb->addItems({ "China","USA","Russia" });

	QFontComboBox* fcb = new QFontComboBox(&mw);
	fcb->move(100, 100);

	mw.show();
	
	return a.exec();
}
