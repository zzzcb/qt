#include "qttreepropertybrowser.h"
#include "qteditorfactory.h"
#include "lxqtpropertymanager.h"

#include <QApplication>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	// browser 
	QtTreePropertyBrowser* browser = new QtTreePropertyBrowser;
	browser->setAlternatingRowColors(false);

	// manager 
	QtGroupPropertyManager *groupMng = new QtGroupPropertyManager(browser);
	lxQtSpacePointManager *spacePointMng = new lxQtSpacePointManager(browser);

	// property 
	QtProperty *groupProp = groupMng->addProperty("Group");
	QtProperty *sp1 = spacePointMng->addProperty("SP1");
	QtProperty *sp2 = spacePointMng->addProperty("SP2");
	
	groupProp->addSubProperty(sp1);
	groupProp->addSubProperty(sp2);

	// factory
	auto doubleFactory = new QtDoubleSpinBoxFactory(browser);
	browser->setFactoryForManager(spacePointMng->subDoublePropertyManager(), doubleFactory);

	// browser 
	browser->addProperty(groupProp);
	browser->show();

	return app.exec();
}
