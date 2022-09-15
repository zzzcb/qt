#include "demo.h"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	createActions();
	createMenus();

}

Demo::~Demo()
{
}

void Demo::createActions()
{
	m_pNewAct = new QAction("New", this);
	m_pNewAct->setShortcut(QKeySequence::New);						/**标准快捷键*/

	m_pOpenAct = new QAction("Open", this);
	m_pOpenAct->setShortcut(QKeySequence::Open);					/**标准快捷键*/

	m_pOpenAndFreezeAct = new QAction("Open and Freeze", this);
	m_pOpenAndFreezeAct->setShortcut(QKeySequence("Ctrl+Alt+O"));	/**自定义快捷键*/
}

void Demo::createMenus()
{
	/**file menu*/
	QMenu* fileMenu = menuBar()->addMenu("&File");
	fileMenu->addAction(m_pNewAct);
	fileMenu->addAction(m_pOpenAct);
	fileMenu->addSeparator();
	fileMenu->addAction(m_pOpenAndFreezeAct);

}
