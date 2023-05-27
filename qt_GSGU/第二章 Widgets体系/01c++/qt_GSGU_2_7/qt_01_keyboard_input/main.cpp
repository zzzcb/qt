#pragma execution_character_set("utf-8")

#include <QApplication>
#include <QWidget>

#include <QLineEdit>
#include <QFileDialog>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QKeySequenceEdit>

#include <QDebug>

class MyWidget :public QWidget 
{
	Q_OBJECT
public:
	MyWidget(QWidget* parent = nullptr)
	{
		initUi();
	}
	void initUi()
	{
		//QLineEdit
		m_pLe = new QLineEdit(this);
		m_pLe->setPlaceholderText("请输入解释器的路径(双击选择路径)");
		m_pLe->installEventFilter(this);

		//QTextEdit
		m_pTe = new QTextEdit("text edit", this);
		m_pTe->move(50, 50);

		//QPlainTextEdit 
		m_pPTE = new QPlainTextEdit("plain text edit", this);
		m_pPTE->move(400, 50);

		//QKeySequenceEdit
		m_pShortEdit = new QKeySequenceEdit(this);
		m_pShortEdit->setKeySequence(QKeySequence("Ctrl+A"));
		m_pShortEdit->move(50, 400);
	}
	bool eventFilter(QObject *watched, QEvent *event) override
	{
		if (watched == m_pLe)
		{
			if (event->type() == QEvent::MouseButtonDblClick)
			{
				QString exePath = QFileDialog::getOpenFileName(nullptr, "请选择exe文件路径", "D:", "(*.exe)");
				m_pLe->setText(exePath);

				return true;
			}
		}
		return QWidget::eventFilter(watched, event);
	}

private:
	QLineEdit* m_pLe;
	QTextEdit* m_pTe;
	QPlainTextEdit* m_pPTE;
	QKeySequenceEdit* m_pShortEdit;
};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MyWidget mw;
	mw.show();

	return a.exec();
}

#include "main.moc"