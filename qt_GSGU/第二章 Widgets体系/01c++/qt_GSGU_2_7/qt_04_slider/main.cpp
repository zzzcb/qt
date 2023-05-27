#include <QtWidgets/QApplication>

#include <QDial>
#include <QScrollBar>
#include <QSlider>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	/** QDial */
	QDial* dial = new QDial;
	dial->show();
	
	/** QScrollBar */
	QScrollBar* sb = new QScrollBar;
	sb->show();
	
	QScrollBar* hsb = new QScrollBar(Qt::Horizontal);
	hsb->show();

	/** QSlider */
	QSlider* slider = new QSlider(Qt::Horizontal);
	slider->show();

    
    return a.exec();
}
