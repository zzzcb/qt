#include "qtpropertymanager.h"

#include <QMap>
#include <QIcon>

struct SpacePoint
{
	double x;
	double y;
	double z;
	double rx;
	double ry;
	double rz;

	bool operator==(const SpacePoint& sp)
	{
		return
			x == sp.x &&
			y == sp.y &&
			z == sp.z &&
			rx == sp.rx &&
			ry == sp.ry &&
			rz == sp.rz;
	}
};

class lxQtSpacePointManager : public QtAbstractPropertyManager
{
	Q_OBJECT
public:
	lxQtSpacePointManager(QObject *parent = 0);

	QtDoublePropertyManager *subDoublePropertyManager() const;

protected:
	void initializeProperty(QtProperty *property) override;
	void uninitializeProperty(QtProperty *property) override;

public slots:
	void setValue(QtProperty *property, const SpacePoint &val);
signals:
	void valueChanged(QtProperty *property, const SpacePoint &val);

private:
	typedef QMap<const QtProperty *, SpacePoint> PropertyValueMap;
	PropertyValueMap m_mapPropertyValue;

	QtDoublePropertyManager *m_pDoublePropertyManager;

	QMap<const QtProperty *, QtProperty *> m_mapPropertyToX;
	QMap<const QtProperty *, QtProperty *> m_mapPropertyToY;
	QMap<const QtProperty *, QtProperty *> m_mapPropertyToZ;
	QMap<const QtProperty *, QtProperty *> m_mapPropertyToRx;
	QMap<const QtProperty *, QtProperty *> m_mapPropertyToRy;
	QMap<const QtProperty *, QtProperty *> m_mapPropertyToRz;

	QMap<const QtProperty *, QtProperty *> m_mapXToProperty;
	QMap<const QtProperty *, QtProperty *> m_mapYToProperty;
	QMap<const QtProperty *, QtProperty *> m_mapZToProperty;
	QMap<const QtProperty *, QtProperty *> m_mapRxToProperty;
	QMap<const QtProperty *, QtProperty *> m_mapRyToProperty;
	QMap<const QtProperty *, QtProperty *> m_mapRzToProperty;

};
