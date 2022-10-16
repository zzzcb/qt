#include <QtCore/QCoreApplication>

#include "webserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	WebServer server;

    return a.exec();
}
