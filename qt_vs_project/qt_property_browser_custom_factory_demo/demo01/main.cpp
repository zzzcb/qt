#include "customproperty.h"
#include "qttreepropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#include "qteditorfactory.h"

#include <QApplication>
#include <QPushButton>
#include <QCheckBox>
#include <QObject>
#include <QDebug>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QtGroupPropertyManager *groupManager = new QtGroupPropertyManager();
	QtProperty *item0 = groupManager->addProperty("Group");

	lxQtSpacePointManager *spMng = new lxQtSpacePointManager();
	QtProperty *item = spMng->addProperty("SpacePoint");
	item0->addSubProperty(item);

	QtPointFPropertyManager *pfMng = new QtPointFPropertyManager();
	item = pfMng->addProperty("PointF");
	item0->addSubProperty(item);
	item->subProperties();

	lxQtSpacePointManager *spMng2 = new lxQtSpacePointManager();
	item = spMng2->addProperty("SpacePoint2");
	item0->addSubProperty(item);

	QtColorPropertyManager* colorMng = new QtColorPropertyManager();
	QtProperty* colorPorperty = colorMng->addProperty("Color");

	QtStringPropertyManager* filePathMng = new QtStringPropertyManager();
	QtProperty* filePathPorperty = filePathMng->addProperty("FilePath");

	QtTreePropertyBrowser* browser = new QtTreePropertyBrowser;
	QtGroupBoxPropertyBrowser* browser1 = new QtGroupBoxPropertyBrowser;
	auto factory = new QtDoubleSpinBoxFactory();
	auto colorFactory = new QtColorEditorFactory();
	auto intFac = new QtSpinBoxFactory();
	auto filePathFac = new lxQtFilePathFactory();

	browser->setAlternatingRowColors(false);
	browser->setFactoryForManager(pfMng->subDoublePropertyManager(), factory);
	browser->setFactoryForManager(spMng->subDoublePropertyManager(), factory);
	browser->setFactoryForManager(spMng2->subDoublePropertyManager(), factory);

	browser->setFactoryForManager(colorMng, colorFactory);
	browser->setFactoryForManager(colorMng->subIntPropertyManager(), intFac);

	browser->setFactoryForManager(filePathMng, filePathFac);

	browser->addProperty(item0);
	browser->addProperty(colorPorperty);
	browser->addProperty(filePathPorperty);

	browser->show();

	return app.exec();
}
