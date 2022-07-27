#include "mainwindow.h"

#include <QDebug>
#include <QMenuBar>

MainWindow::MainWindow()
	: mp_addressWidget(new AddressWidget)
{

	setCentralWidget(mp_addressWidget);
	createMenus();
	setWindowTitle(tr("address book"));

}

MainWindow::~MainWindow()
{




}

void MainWindow::on_openAct_triggered()
{

}

void MainWindow::on_saveAct_triggered()
{

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
	QAction* editAct = new QAction(tr("&Edit"), this);
	toolMenu->addAction(editAct);
	toolMenu->addSeparator();
	QAction* removeAct = new QAction(tr("&Remove"), this);
	toolMenu->addAction(removeAct);


}
