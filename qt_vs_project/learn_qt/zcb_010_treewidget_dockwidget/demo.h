#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>

#include <QtWidgets/QPushButton>
#include <QtGui/QPixmap>

#include "ui_demo.h"

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

private:
	void resizeEvent(QResizeEvent *event);

private:
	void initStatusBar();
	void getFitImg(QPixmap& fittedImg, double areaW, double areaH, double realW, double realH);

	Ui::DemoClass ui;

	// display image 
	QPixmap* mDisImg;

	// status bar 
	QLabel* mStatusIcon;
	QPixmap* mStatusIconPixmap;
	QLabel* mStatusInfo;

private slots:
	void on_actionDockShow_triggered(bool checked);
	void on_actionDockFloat_triggered(bool checked);
	void on_dockWidget_topLevelChanged(bool topLevel);
	void on_dockWidget_visibilityChanged(bool visible);

	void on_lineEdit_chooseDirCompleted();

	void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

	void on_actionZoomIn_triggered();
	void on_actionZoomOut_triggered();
	void on_actionRealSize_triggered();

};
