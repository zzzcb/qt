#pragma execution_character_set("utf-8")
#include "demo.h"

#include <QTextFrame>
#include <QLayout>
#include <QDebug>

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);

	m_pTextEdit = new QTextEdit(this);
	setCentralWidget(m_pTextEdit);
	
	resize(600, 400);

	initRootFrameFormat();
	m_pTextEdit->append("hello qt!");
	m_pTextEdit->append("hello qt!");

	insertRightFrame("我从哪里来?");
	insertLeftFrame("我要到哪里去?");

	foreachDoc();
}

Demo::~Demo()
{}

void Demo::initRootFrameFormat()
{
	QTextDocument* doc = m_pTextEdit->document();

	QTextFrame* rootFrame = doc->rootFrame();

	auto fmt = rootFrame->frameFormat();
	fmt.setBorder(3);
	fmt.setBorderBrush(Qt::red);
	fmt.setBackground(QColor(Qt::cyan));
	rootFrame->setFrameFormat(fmt);
}

void Demo::insertLeftFrame(QString text)
{
	QTextFrameFormat fmt;
	fmt.setBackground(Qt::green);
	fmt.setMargin(1);
	fmt.setBorder(1);
	fmt.setPadding(2);
	fmt.setWidth(QTextLength(QTextLength::PercentageLength, 55));
	fmt.setPosition(QTextFrameFormat::FloatLeft);

	QTextCursor cursor = m_pTextEdit->document()->rootFrame()->lastCursorPosition();
	cursor.insertFrame(fmt);
	cursor.insertText(text);
}



void Demo::insertRightFrame(QString text)
{
	QTextFrameFormat fmt;
	fmt.setBackground(Qt::yellow);
	fmt.setMargin(1);
	fmt.setBorder(1);
	fmt.setPadding(2);
	fmt.setWidth(QTextLength(QTextLength::PercentageLength, 55));
	fmt.setPosition(QTextFrameFormat::FloatRight);

	QTextCursor cursor = m_pTextEdit->document()->rootFrame()->lastCursorPosition();
	cursor.insertFrame(fmt);
	cursor.insertText(text);
}

void Demo::foreachDoc()
{
	foreachFrame(m_pTextEdit->document()->rootFrame());
	qDebug() << "-------------------";
	foreachBlock();
}

void Demo::foreachFrame(QTextFrame* frame)
{
	for (QTextFrame::iterator it = frame->begin(); !it.atEnd(); it++)
	{
		QTextBlock curBlock = it.currentBlock();
		QTextFrame * curFrame = it.currentFrame();
		if (curBlock.isValid() && !curBlock.text().isEmpty())
			qDebug() << curBlock.text();
		else if (curFrame)
			foreachFrame(curFrame);
	}
}

void Demo::foreachBlock()
{
	QTextBlock block = m_pTextEdit->document()->begin();
	while (block.isValid())
	{
		if (!block.text().isEmpty())
			qDebug() << block.text();
		block = block.next();
	}
}