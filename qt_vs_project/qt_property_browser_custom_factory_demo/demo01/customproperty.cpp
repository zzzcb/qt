#include "customproperty.h"

lxQtSpacePointManager::lxQtSpacePointManager(QObject *parent /*= 0*/)
	:QtAbstractPropertyManager(parent)
{
	m_pDoublePropertyManager = new QtDoublePropertyManager(this);
}

QtDoublePropertyManager * lxQtSpacePointManager::subDoublePropertyManager() const
{
	return m_pDoublePropertyManager;
}

void lxQtSpacePointManager::initializeProperty(QtProperty *property)
{
	SpacePoint sp = { 0,0,0,0,0,0};
	m_mapPropertyValue[property] = sp;

	QtProperty * xProp = m_pDoublePropertyManager->addProperty();
	xProp->setPropertyName("X");
	xProp->setToolTip("0-100");
	m_pDoublePropertyManager->setValue(xProp, sp.x);
	m_pDoublePropertyManager->setSingleStep(xProp, 10);
	m_mapPropertyToX[property] = xProp;
	m_mapXToProperty[xProp] = property;
	property->addSubProperty(xProp);

	QtProperty * yProp = m_pDoublePropertyManager->addProperty();
	yProp->setPropertyName("Y");
	m_pDoublePropertyManager->setValue(yProp, sp.y);
	m_mapPropertyToY[property] = yProp;
	m_mapYToProperty[yProp] = property;
	property->addSubProperty(yProp);

	QtProperty * zProp = m_pDoublePropertyManager->addProperty();
	zProp->setPropertyName("Z");
	m_pDoublePropertyManager->setValue(zProp, sp.z);
	m_mapPropertyToZ[property] = zProp;
	m_mapZToProperty[zProp] = property;
	property->addSubProperty(zProp);

	QtProperty * rxProp = m_pDoublePropertyManager->addProperty();
	rxProp->setPropertyName("Rx");
	m_pDoublePropertyManager->setValue(rxProp, sp.rx);
	m_mapPropertyToRx[property] = rxProp;
	m_mapRxToProperty[rxProp] = property;
	property->addSubProperty(rxProp);

	QtProperty * ryProp = m_pDoublePropertyManager->addProperty();
	ryProp->setPropertyName("Ry");
	m_pDoublePropertyManager->setValue(ryProp, sp.ry);
	m_mapPropertyToRy[property] = ryProp;
	m_mapRyToProperty[ryProp] = property;
	property->addSubProperty(ryProp);

	QtProperty * rzProp = m_pDoublePropertyManager->addProperty();
	rzProp->setPropertyName("Rz");
	m_pDoublePropertyManager->setValue(rzProp, sp.rz);
	m_mapPropertyToRz[property] = rzProp;
	m_mapRzToProperty[rzProp] = property;
	property->addSubProperty(rzProp);
}

void lxQtSpacePointManager::uninitializeProperty(QtProperty *property)
{
	QtProperty *Prop = m_mapPropertyToX[property];
	if (Prop) {
		m_mapXToProperty.remove(Prop);
		delete Prop;
	}
	m_mapXToProperty.remove(property);

	Prop = m_mapPropertyToY[property];
	if (Prop) {
		m_mapYToProperty.remove(Prop);
		delete Prop;
	}
	m_mapYToProperty.remove(property);

	Prop = m_mapPropertyToZ[property];
	if (Prop) {
		m_mapZToProperty.remove(Prop);
		delete Prop;
	}
	m_mapZToProperty.remove(property);

	Prop = m_mapPropertyToRx[property];
	if (Prop) {
		m_mapRxToProperty.remove(Prop);
		delete Prop;
	}
	m_mapRxToProperty.remove(property);

	Prop = m_mapPropertyToRy[property];
	if (Prop) {
		m_mapRyToProperty.remove(Prop);
		delete Prop;
	}
	m_mapRyToProperty.remove(property);

	Prop = m_mapPropertyToRz[property];
	if (Prop) {
		m_mapRzToProperty.remove(Prop);
		delete Prop;
	}
	m_mapRzToProperty.remove(property);

	m_mapPropertyValue.remove(property);
}

void lxQtSpacePointManager::setValue(QtProperty *property, const SpacePoint &val)
{
	const PropertyValueMap::iterator it = m_mapPropertyValue.find(property);
	if (it == m_mapPropertyValue.end())
		return;

	SpacePoint oldVal = it.value();
	if (oldVal == val)
		return;

	it.value() = val;

	m_pDoublePropertyManager->setValue(m_mapPropertyToX[property], val.x);
	m_pDoublePropertyManager->setValue(m_mapPropertyToY[property], val.y);
	m_pDoublePropertyManager->setValue(m_mapPropertyToZ[property], val.z);
	m_pDoublePropertyManager->setValue(m_mapPropertyToRx[property], val.rx);
	m_pDoublePropertyManager->setValue(m_mapPropertyToRy[property], val.ry);
	m_pDoublePropertyManager->setValue(m_mapPropertyToRz[property], val.rz);

	emit propertyChanged(property);
	emit valueChanged(property, val);
}

/// -------------------------
