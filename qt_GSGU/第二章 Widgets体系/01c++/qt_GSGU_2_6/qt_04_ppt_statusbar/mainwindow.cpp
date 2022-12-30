#pragma execution_character_set("utf-8")
#include "mainwindow.h"

#include <QStatusBar>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QSlider>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle("模仿PowerPoint的状态栏");
	resize(1000, 600);

	initQss();
	initStatusBar();

	QFont font;
	font.setBold(true);
	font.setPixelSize(60);
	font.setFamily("Microsoft Yahei");
	QLabel* lb = new QLabel("我在模仿PPT的状态栏^v^", this);
	lb->setAlignment(Qt::AlignCenter);
	lb->setFont(font);
	setCentralWidget(lb);
}

MainWindow::~MainWindow()
{}

void MainWindow::initStatusBar()
{
	// create status bar
	QStatusBar* pStatubBar = statusBar();

	// hide size grip
	pStatubBar->setSizeGripEnabled(false);

	// left 
	QLabel* pageLb = new QLabel("幻灯片 第 1 张，共 1 张",this);
	QLabel* languageLb = new QLabel("中文(中国)", this);
	QPushButton* infoBtn = new QPushButton("辅助功能:一切就绪", this);
	infoBtn->setIcon(QIcon(":images/dance.png"));
	pStatubBar->addWidget(pageLb);
	pStatubBar->addWidget(languageLb);
	pStatubBar->addWidget(infoBtn);

	// right 
	QToolButton* gridBtn = new QToolButton(this);
	gridBtn->setIcon(QIcon(":images/grid.png"));
	QToolButton* bookBtn = new QToolButton(this);
	bookBtn->setIcon(QIcon(":images/book.png"));
	QToolButton* drinkBtn = new QToolButton(this);
	drinkBtn->setIcon(QIcon(":images/drink.png"));

	QSlider* percentSlider = new QSlider(Qt::Horizontal,this);
	percentSlider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	percentSlider->setValue(53);
	QLabel* percentLb = new QLabel(" 53%", this);

	pStatubBar->addPermanentWidget(gridBtn);
	pStatubBar->addPermanentWidget(bookBtn);
	pStatubBar->addPermanentWidget(drinkBtn);
	pStatubBar->addPermanentWidget(percentSlider);
	pStatubBar->addPermanentWidget(percentLb);


}

void MainWindow::initQss()
{
	QString qss = R"(
		*{
			font-family:Microsoft YaHei;
		}
		QMainWindow{
			background: #e6e6e6;
		}
		QStatusBar{
			background: #f3f2f1;
		}

		QStatusBar::item{
			border: 0px
		}
		QLabel{
			margin-right: 20px;
		}
		QToolButton{
			margin-right: 10px;
		}

		QPushButton,QToolButton{
			border:none;
			background:transparent;
		}
		QPushButton:hover,QToolButton:hover{
			background:#E1DfDD;
		}
		QPushButton:pressed,QToolButton:pressed{
			background:#c8c6c4;
		}


		QSlider::groove:horizontal {
			height: 1px; 
			background: #3b3a39;
		}
		QSlider::handle:horizontal {
			background: #3b3a39;
			border: 1px solid #5c5c5c;
			width: 5px;
			margin: -2px 0; 
			border-radius: 3px;
		}

	)";
	setStyleSheet(qss);
}
