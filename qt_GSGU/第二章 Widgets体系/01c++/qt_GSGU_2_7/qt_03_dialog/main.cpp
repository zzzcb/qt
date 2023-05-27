#include <QtWidgets/QApplication>

#include <QDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	/** QDialog */
	QDialog dlg;
	dlg.show();
	
	/** QColorDialog */
	QColor clr = QColorDialog::getColor();
	qDebug() << clr.name();

	/** QFileDialog */
	QString file = QFileDialog::getOpenFileName(nullptr, "select a file", "D:", "(*.txt)");
	qDebug() << file;

	/** QFontDialog */
	bool ok;
	QFontDialog::getFont(&ok, nullptr);

	/** QInputDialog */
	QInputDialog::getInt(nullptr, "get int", "num");
	QInputDialog::getDouble(nullptr, "get double", "num");
	QInputDialog::getText(nullptr, "get text", "text");
	QInputDialog::getMultiLineText(nullptr, "get multi text", "text");
	QInputDialog::getItem(nullptr, "get item", "item", {"1","2","3"});

	/** QMessageBox */
	QMessageBox::information(nullptr, "information", "information...");
	QMessageBox::warning(nullptr, "warning", "warning...");
	QMessageBox::question(nullptr, "question", "question...");
	QMessageBox::critical(nullptr, "critical", "critical...");

	/** QProgressDialog */
	QProgressDialog* progreessDlg = new QProgressDialog;
	progreessDlg->show();

    return a.exec();
}
