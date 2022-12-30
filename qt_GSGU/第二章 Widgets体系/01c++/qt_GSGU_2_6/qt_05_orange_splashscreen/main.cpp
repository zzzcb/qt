#include "splashscreen.h"
#include "demo.h"
#include <QtWidgets/QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	SplashScreen::testThis();  // 测试SplashScreen

	Demo d;
	d.show();

    return a.exec();
}
