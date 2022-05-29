#include "demo.h"
#include <QtWidgets/QApplication>

#include "learnqtabbar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	LearnQTabBar learn;
	learn.show();

    return a.exec();
}
