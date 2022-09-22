#include <QMainWindow>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow* mw = new QMainWindow;
    mw->setWindowTitle("我不是Qt");
    mw->show();

    return a.exec();
}
