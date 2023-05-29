#include "lxqtpropertymanager.h"

#include "lxqtpropertyfactory.h"
#include "qteditorfactory.h"

#include "qttreepropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#include "qtbuttonpropertybrowser.h"

#include <QApplication>
#include <QPushButton>
#include <QCheckBox>
#include <QObject>
#include <QDebug>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	// manager 
	QtGroupPropertyManager *groupManager = new QtGroupPropertyManager();
	lxQtSpacePointManager *spMng = new lxQtSpacePointManager();
	QtPointFPropertyManager *pfMng = new QtPointFPropertyManager();
	lxQtSpacePointManager *spMng2 = new lxQtSpacePointManager();
	QtColorPropertyManager* colorMng = new QtColorPropertyManager();
	QtStringPropertyManager* strMng = new QtStringPropertyManager();
	QtStringPropertyManager* strMng2 = new QtStringPropertyManager(); 
	QtIntPropertyManager* intMng = new QtIntPropertyManager();

	// property
	QtProperty *rootItem = groupManager->addProperty("Group");
	QtProperty *spItem = spMng->addProperty("SpacePoint");
	rootItem->addSubProperty(spItem);

	spItem = pfMng->addProperty("PointF");
	rootItem->addSubProperty(spItem);

	spItem = spMng2->addProperty("SpacePoint2");
	rootItem->addSubProperty(spItem);

	QtProperty* colorPorperty = colorMng->addProperty("Color");
	QtProperty* filePathPorperty = strMng->addProperty("FilePath");
	QtProperty* emailPorperty = strMng2->addProperty("Email");
	QtProperty* joint1Property = intMng->addProperty("Joint1");
	intMng->setMinimum(joint1Property, -180);
	intMng->setMaximum(joint1Property, 180);

	// browser
	QtTreePropertyBrowser* browser = new QtTreePropertyBrowser;
	QtGroupBoxPropertyBrowser* gpBrowser = new QtGroupBoxPropertyBrowser;
	QtButtonPropertyBrowser* btnBrowser = new QtButtonPropertyBrowser;
	
	// factory
	auto factory = new QtDoubleSpinBoxFactory();
	auto colorFactory = new QtColorEditorFactory();
	auto intFac = new QtSpinBoxFactory();
	auto filePathFac = new lxQtFilePathFactory();
	auto emailPathFac = new lxQtEmailFactory();
	auto sliderFac = new QtSliderFactory();


	// validator 
	auto emailValidator = new lxQtRegexValidator("^[1-9][0-9]{4,9}@qq.com$", (QObject*)&browser);
	emailPathFac->setValidator(emailPorperty, emailValidator);

	// tree browser
	browser->setAlternatingRowColors(false);
	browser->setFactoryForManager(pfMng->subDoublePropertyManager(), factory); // a factory has many manager
	browser->setFactoryForManager(spMng->subDoublePropertyManager(), factory);
	browser->setFactoryForManager(spMng2->subDoublePropertyManager(), factory);
	browser->setFactoryForManager(colorMng, colorFactory);
	browser->setFactoryForManager(colorMng->subIntPropertyManager(), intFac);
	browser->setFactoryForManager(strMng, filePathFac);
	browser->setFactoryForManager(strMng2, emailPathFac);
	browser->setFactoryForManager(intMng, intFac);

	browser->addProperty(rootItem);
	browser->addProperty(colorPorperty);
	browser->addProperty(filePathPorperty);
	browser->addProperty(emailPorperty);
	browser->addProperty(joint1Property);

	browser->show();

	// group box browser 
	gpBrowser->setFactoryForManager(pfMng->subDoublePropertyManager(), factory); // a factory has many manager
	gpBrowser->setFactoryForManager(spMng->subDoublePropertyManager(), factory);
	gpBrowser->setFactoryForManager(spMng2->subDoublePropertyManager(), factory);
	gpBrowser->setFactoryForManager(colorMng, colorFactory);
	gpBrowser->setFactoryForManager(colorMng->subIntPropertyManager(), intFac);
	gpBrowser->setFactoryForManager(strMng, filePathFac);
	gpBrowser->setFactoryForManager(strMng2, emailPathFac);
	gpBrowser->setFactoryForManager(intMng, sliderFac);

	gpBrowser->addProperty(rootItem);
	gpBrowser->addProperty(colorPorperty);
	gpBrowser->addProperty(filePathPorperty);
	gpBrowser->addProperty(emailPorperty);
	gpBrowser->addProperty(joint1Property);

	gpBrowser->show();

	// btn browser 
	btnBrowser->setFactoryForManager(pfMng->subDoublePropertyManager(), factory); // a factory has many manager
	btnBrowser->setFactoryForManager(spMng->subDoublePropertyManager(), factory);
	btnBrowser->setFactoryForManager(spMng2->subDoublePropertyManager(), factory);
	btnBrowser->setFactoryForManager(colorMng, colorFactory);
	btnBrowser->setFactoryForManager(colorMng->subIntPropertyManager(), intFac);
	btnBrowser->setFactoryForManager(strMng, filePathFac);
	btnBrowser->setFactoryForManager(strMng2, emailPathFac);
	btnBrowser->setFactoryForManager(intMng, sliderFac);

	btnBrowser->addProperty(rootItem);
	btnBrowser->addProperty(colorPorperty);
	btnBrowser->addProperty(filePathPorperty);
	btnBrowser->addProperty(emailPorperty);
	btnBrowser->addProperty(joint1Property);

	btnBrowser->show();

	return app.exec();
}
