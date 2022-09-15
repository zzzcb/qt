#include "demo.h"

#include <QtWidgets/QApplication>
#include <QDialog>
#include <QToolButton>
#include <QObject>
#include <QDesktopServices>
#include <QUrl>

void showWelcomeScreen()
{
	QDialog dialog;
	dialog.setWindowTitle("Welcome Screen");
	dialog.setFixedSize(500, 300);
	dialog.setStyleSheet(
		"QToolButton{border: 1px solid transparent;border-radius: 10px;font-size: 13px;icon-size: 75px;}"
		"QToolButton::pressed{background-color: palette(highlight);color: palette(highlighted-text);}"
		"QDialog{background-color: #E9EFF2;}"
	);


	QToolButton* button = new QToolButton(&dialog);
	button->setIcon(QIcon(":/website.svg"));
	button->setIconSize(QSize(100,80));
	button->setText("Get Started");
	button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	button->move(100, 100);

	QToolButton* button2 = new QToolButton(&dialog);
	button2->setIcon(QIcon(":/website.svg"));
	button2->setIconSize(QSize(100, 80));
	button2->setText("Get Started2");
	button2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	button2->move(300, 100);

	QObject::connect(button, &QToolButton::clicked, []() {
		QDesktopServices::openUrl(QUrl("https://space.bilibili.com/441821181"));
	});

	QObject::connect(button2, &QToolButton::clicked, []() {
		QDesktopServices::openUrl(QUrl("https://space.bilibili.com/441821181"));
	});

	dialog.exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Demo w;
    w.show();

	showWelcomeScreen();

    return a.exec();
}
