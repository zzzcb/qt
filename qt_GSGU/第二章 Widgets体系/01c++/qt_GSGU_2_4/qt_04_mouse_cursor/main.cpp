#include <QtWidgets/QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  
	QWidget w;
	//w.setCursor(Qt::ClosedHandCursor);  
	w.setCursor(QCursor(QPixmap(":/images/my_cursor.png").scaledToWidth(50),0,0));
	w.show();

    return a.exec();
}


