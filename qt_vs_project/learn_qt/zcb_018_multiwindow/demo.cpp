#pragma execution_character_set("utf-8")
#include "demo.h"
#include "qdebug.h"
#include <QPainter>
#include "innerwidget.h"
#include "innermainwindow.h"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	ui.tabWidget->setVisible(false); // 默认不显示 tab widget 
	//setWindowState(Qt::WindowMaximized);
	setCentralWidget(ui.tabWidget);
}

void Demo::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawPixmap(0, ui.mainToolBar->height(), width(), height() - ui.mainToolBar->height() - ui.statusBar->height(),
		QPixmap(":/Demo/1.jpg"));
}

void Demo::on_action_widget_triggered()
{
	ui.tabWidget->setVisible(true);
	InnerWidget * widget = new InnerWidget(this);
	widget->setAttribute(Qt::WA_DeleteOnClose);    
	int tabIdx = ui.tabWidget->addTab(widget, "new widget"); 
	ui.tabWidget->setCurrentIndex(tabIdx);
}

void Demo::on_action_widget_2_triggered()
{
	ui.tabWidget->setVisible(true);
	InnerMainWindow * window = new InnerMainWindow(this);
	window->setAttribute(Qt::WA_DeleteOnClose);
	int tabIdx = ui.tabWidget->addTab(window, "new window");
	ui.tabWidget->setCurrentIndex(tabIdx);
}

void Demo::on_action_widget_3_triggered()
{
	InnerWidget * widget = new InnerWidget;
	widget->setAttribute(Qt::WA_DeleteOnClose);
	widget->setWindowTitle("widget 独立显示");
	widget->setWindowOpacity(0.8);
	widget->show();
}

void Demo::on_action_widget_4_triggered()
{
	InnerMainWindow * window = new InnerMainWindow;
	window->setAttribute(Qt::WA_DeleteOnClose);
	window->setWindowTitle("window 独立显示");
	window->setWindowOpacity(0.8);
	window->show();
}

void Demo::on_tabWidget_tabCloseRequested(int index)
{
	if (index < 0) return;
	if (ui.tabWidget->count() == 1) ui.tabWidget->setVisible(false);

	ui.tabWidget->widget(index)->close();
}
