#pragma once

#include "addresswidget.h"

#include <QMainWindow>


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

private slots:
	void on_openAct_triggered();
	void on_saveAct_triggered();

	void updateActions(const QItemSelection &selected);


private:
	AddressWidget* mp_addressWidget;

	QAction* mp_editAct;
	QAction* mp_removeAct;

	void createMenus();

};
