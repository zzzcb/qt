#include "customproperty.h"
#include "qttreepropertybrowser.h"
#include "qteditorfactory.h"

#include <QApplication>
#include <QPushButton>
#include <QCheckBox>
#include <QObject>
#include <QDebug>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QWidget *w = new QWidget();
	QPushButton * btn = new QPushButton("btn", w);
	QCheckBox * box = new QCheckBox("选中",w);

	QtGroupPropertyManager *groupManager = new QtGroupPropertyManager();
	QtProperty *item0 = groupManager->addProperty("Group");

	lxQtSpacePointManager *spMng = new lxQtSpacePointManager();
	QtProperty *item = spMng->addProperty("SpacePoint");
	item0->addSubProperty(item);

	QtPointFPropertyManager *pfMng = new QtPointFPropertyManager();
	item = pfMng->addProperty("PointF");
	item0->addSubProperty(item);
	item->subProperties();

	QtTreePropertyBrowser* browser = new QtTreePropertyBrowser;
	browser->setAlternatingRowColors(false);
	browser->setFactoryForManager(spMng->subDoublePropertyManager(), new QtDoubleSpinBoxFactory());
	browser->addProperty(item0);
	browser->setStyleSheet("QTreeView{background-color:red;color:white;}"
		"QTreeView{selection-background-color:blue;}"
	);
	browser->show();

	w->setStyleSheet(

		"QCheckBox{background-color:green;}"
	);
	w->show();


	return app.exec();
}
