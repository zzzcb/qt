#pragma execution_character_set("utf-8")

#include "learnqtabbar.h"

LearnQTabBar::LearnQTabBar(QWidget *parent)
	: QDialog(parent)
{
	mpGridLayout = new QGridLayout(this);

	mpFrame1 = new QFrame(this);
	mpFrame2 = new QFrame(this);
	mpVInnerLayout1 = new QVBoxLayout(mpFrame1);
	mpVInnerLayout2 = new QVBoxLayout(mpFrame2);
	mpTabBar1 = new QTabBar(this);
	mpTabBar2 = new QTabBar(this);
	mpLabel1 = new QLabel("你好,我是左侧",this);
	mpLabel2 = new QLabel("你好,我是右侧",this);
	
	mpFrame1->setFrameStyle(QFrame::Panel|QFrame::Plain);
	mpFrame2->setFrameStyle(QFrame::Panel|QFrame::Plain);

	mpTabBar1->addTab("&tab1");
	mpTabBar1->addTab("t&ab2");

	mpTabBar2->addTab("ta&b3");
	mpTabBar2->addTab("tab4");

	mpVInnerLayout1->addWidget(mpLabel1,1,Qt::AlignLeft);
	mpVInnerLayout1->addWidget(mpTabBar1,0,Qt::AlignRight|Qt::AlignVCenter);
	mpVInnerLayout2->addWidget(mpLabel2, 1, Qt::AlignCenter);
	mpVInnerLayout2->addWidget(mpTabBar2, 0, Qt::AlignCenter);
	
	mpGridLayout->addWidget(mpFrame1, 0, 0);
	mpGridLayout->addWidget(mpFrame2, 0, 1);

	test();
}



LearnQTabBar::~LearnQTabBar()
{
}

void LearnQTabBar::test()
{
	//testDrawBase();
	//testCount();
	//testCurrentIndex();
	testDocumentMode();

	//connect signal and slots
	//connect(mpTabBar1,&QTabBar::currentChanged,this,&LearnQTabBar::on_tab1_currentChanged);


}

void LearnQTabBar::testDrawBase()
{
	// 默认是true 的
	mpTabBar1->setDrawBase(false);
}

void LearnQTabBar::testCount()
{
	mpLabel1->setText(QString::number(mpTabBar1->count()));
}

void LearnQTabBar::testCurrentIndex()
{
	mpTabBar1->setCurrentIndex(1);
	mpLabel2->setText(QString::number(mpTabBar2->currentIndex()));
}

void LearnQTabBar::testDocumentMode()
{
	// 默认是false的
	mpTabBar1->setDocumentMode(true);
}

void LearnQTabBar::on_tab1_currentChanged(int index)
{
	mpLabel1->setText(QString::number(index));
}
