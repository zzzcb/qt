#include "vs2017_solution.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	VS2017SolutionMng mngDialog;
	mngDialog.show();

    return a.exec();
}
