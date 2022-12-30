#include "configdialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	ConfigDialog configDialog;
	configDialog.show();

    return a.exec();
}
