#include "demo.h"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	/**add file menu*/
	QMenu* fileMenu = menuBar()->addMenu("&File");
	QAction* openAct = new QAction("&open", this);
	QAction* closeAct = new QAction("&close", this);
	fileMenu->addAction(openAct);
	fileMenu->addAction(closeAct);

}

Demo::~Demo()
{
}

QMenu* Demo::createPopupMenu()
{
	QMenu* menu = new QMenu(this);
	QAction* openAct = new QAction("&open", this);
	QAction* closeAct = new QAction("&close", this);
	menu->addAction(openAct);
	menu->addAction(closeAct);

	return menu;
}

