#include <QtGui/QGuiApplication> // 注意不是QApplication

#include "rasterwindow.h"

int main(int argc, char *argv[])
{
	QGuiApplication a(argc,argv);

	RasterWindow w;
	w.show();

    return a.exec();
}
