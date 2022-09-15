#include "demo.h"

#include <QDesktopServices>
#include <QUrl>

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	/**help menu*/
	QMenu* helpMenu = menuBar()->addMenu("help");

	/**help action*/
	QAction* helpAct = new QAction("help", this);
	helpAct->setShortcut(QKeySequence("Ctrl+h"));
	
	helpMenu->addAction(helpAct);

	/**open url*/
	connect(helpAct, &QAction::triggered, []() {
		QDesktopServices::openUrl(QUrl("https://space.bilibili.com/441821181"));
	});
}

Demo::~Demo()
{

}
