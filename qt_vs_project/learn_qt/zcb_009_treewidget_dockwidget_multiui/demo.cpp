#include "demo.h"
#include "qdebug.h"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void Demo::on_actionDockShow_triggered(bool checked)
{
	ui.dockWidget->setVisible(checked);
}

void Demo::on_actionDockFloat_triggered(bool checked)
{
	ui.dockWidget->setFloating(checked);
}

void Demo::on_dockWidget_topLevelChanged(bool topLevel)
{
	// The topLevel parameter is true if the dock widget is now floating; otherwise it is false.
	ui.actionDockFloat->setChecked(topLevel);
}

void Demo::on_dockWidget_visibilityChanged(bool visible)
{
	// The visible parameter is true if the dock widget is now showen; hidden is false.
	ui.actionDockShow->setChecked(visible);
}

void Demo::on_actionNewDir_triggered(bool checked)
{
	qDebug() << ui.treeWidget->currentItem();
	QTreeWidgetItem item;
}

