#include <QtWidgets/QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
	QWidget w;

	w.setMinimumSize(300, 300);
	w.setMaximumSize(500, 500);
	//w.resize(600, 600);   ///< not work

	w.show();
	
	return a.exec();
}
