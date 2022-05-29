#pragma once

#include <QtWidgets/QDialog>

#include <QGridLayout>
#include <QTabBar>
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>

class LearnQTabBar : public QDialog
{
	Q_OBJECT

public:
	LearnQTabBar(QWidget *parent=nullptr);
	~LearnQTabBar();

	void test();

	void testDrawBase();
	void testCount();
	void testCurrentIndex();
	void testDocumentMode();  // 好像只有在mac上,tabbar的documentMode才有用

private:
	QGridLayout* mpGridLayout;
	QFrame* mpFrame1;
	QFrame* mpFrame2;
	QVBoxLayout* mpVInnerLayout1;
	QVBoxLayout* mpVInnerLayout2;
	QTabBar* mpTabBar1;
	QTabBar* mpTabBar2;

	QLabel* mpLabel1;
	QLabel* mpLabel2;

private slots:
	void on_tab1_currentChanged(int index);
	
	
};



