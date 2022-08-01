#include "mainwindow.h"

#include <QDebug>
#include <QMenuBar>
#include <QFileDialog>

MainWindow::MainWindow()
	: mp_addressWidget(new AddressWidget)
{

	setCentralWidget(mp_addressWidget);
	createMenus();
	setWindowTitle(tr("address book"));

	connect(mp_addressWidget, &AddressWidget::selectionChanged, this, &MainWindow::updateActions);

}

MainWindow::~MainWindow()
{




}

void MainWindow::on_openAct_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this);
	if(!fileName.isEmpty())
		mp_addressWidget->readFromFile(fileName);
}

void MainWindow::on_saveAct_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this);
	if(!fileName.isEmpty())
		mp_addressWidget->writeToFile(fileName);
}




void MainWindow::updateActions(const QItemSelection &selected)
{
	qDebug() << "update actions ";
	
	QModelIndexList indexes = selected.indexes();

	if (!indexes.isEmpty())
	{
		mp_removeAct->setEnabled(true);
		mp_editAct->setEnabled(true);
	}
	else 
	{
		mp_removeAct->setEnabled(false);
		mp_editAct->setEnabled(false);
	}
}

void MainWindow::createMenus()
{

	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
	QAction* openAct = new QAction(tr("&Open..."),this);
	fileMenu->addAction(openAct);
	connect(openAct, &QAction::triggered, this, &MainWindow::on_openAct_triggered);
	QAction* saveAct = new QAction(tr("&Save As..."), this);
	fileMenu->addAction(saveAct);
	connect(saveAct, &QAction::triggered, this, &MainWindow::on_saveAct_triggered);
	fileMenu->addSeparator();
	QAction* exitAct = new QAction(tr("E&xit"), this);
	fileMenu->addAction(exitAct);
	connect(exitAct, &QAction::triggered, this, &MainWindow::close);


	QMenu* toolMenu = menuBar()->addMenu(tr("&Tools"));
	QAction* addAct = new QAction(tr("&Add"), this);
	toolMenu->addAction(addAct);
	connect(addAct, &QAction::triggered, mp_addressWidget, &AddressWidget::showAddEntryDialog);
	mp_editAct = new QAction(tr("&Edit"), this);
	mp_editAct->setEnabled(false);  // 初始状态要为false
	toolMenu->addAction(mp_editAct);
	connect(mp_editAct, &QAction::triggered, mp_addressWidget, &AddressWidget::editEntry);
	toolMenu->addSeparator();
	mp_removeAct = new QAction(tr("&Remove"), this);
	mp_removeAct->setEnabled(false);  // 初始状态要为false
	toolMenu->addAction(mp_removeAct);
	connect(mp_removeAct, &QAction::triggered, mp_addressWidget, &AddressWidget::removeEntry);



}
