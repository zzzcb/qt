#include "qttreepropertybrowser.h"
#include "qteditorfactory.h"		//for most manager 
#include "qtvariantproperty.h"		//for QtVariantPropertyManager

#include <QApplication>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	// browser 
	QtTreePropertyBrowser* browser = new QtTreePropertyBrowser;
	browser->setAlternatingRowColors(false);

	// manager 
	QtGroupPropertyManager *groupMng = new QtGroupPropertyManager(browser);
	QtDoublePropertyManager *doubleMng = new QtDoublePropertyManager(browser);
	QtPointFPropertyManager *ptfMng = new QtPointFPropertyManager(browser);
	QtColorPropertyManager *colorMng = new QtColorPropertyManager(browser);
	QtVariantPropertyManager *variantMng = new QtVariantPropertyManager(browser);

	// property 
	QtProperty *groupProp = groupMng->addProperty("Group");
	QtProperty *j1Prop = doubleMng->addProperty("J1");
	QtProperty *j2Prop = doubleMng->addProperty("J2");
	QtProperty *startProp = ptfMng->addProperty("Start");
	QtProperty *endProp = ptfMng->addProperty("End");
	QtProperty *backColorProp = colorMng->addProperty("Background");
	QtProperty *foreColorProp = colorMng->addProperty("Foreground");
	QtProperty *fontColorProp = colorMng->addProperty("FontColor");
	
	QtVariantProperty* j3Prop = variantMng->addProperty(QVariant::Double,"J3");
	QtVariantProperty* j4Prop = variantMng->addProperty(QVariant::Double,"J4");
	QtVariantProperty* midProp = variantMng->addProperty(QVariant::PointF,"Mid");

	groupProp->addSubProperty(j1Prop);
	groupProp->addSubProperty(j2Prop);
	groupProp->addSubProperty(startProp);
	groupProp->addSubProperty(endProp);
	groupProp->addSubProperty(backColorProp);
	groupProp->addSubProperty(fontColorProp);
	groupProp->addSubProperty(j3Prop);
	groupProp->addSubProperty(j4Prop);
	groupProp->addSubProperty(midProp);

	// factory
	auto doubleFactory = new QtDoubleSpinBoxFactory(browser);
	auto intFactory = new QtSpinBoxFactory(browser);
	auto colorFactory = new QtColorEditorFactory(browser);
	auto variantFactory = new QtVariantEditorFactory(browser);

	browser->setFactoryForManager(doubleMng, doubleFactory);
	browser->setFactoryForManager(ptfMng->subDoublePropertyManager(), doubleFactory);
	browser->setFactoryForManager(colorMng, colorFactory);
	browser->setFactoryForManager(colorMng->subIntPropertyManager(), intFactory);
	browser->setFactoryForManager(variantMng, variantFactory);

	// browser 
	browser->addProperty(groupProp);
	browser->show();

	return app.exec();
}
