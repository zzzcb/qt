#include "mydoublepropertymanager.h"




MyDoublePropertyManager::MyDoublePropertyManager(QObject *parent)
    :QtDoublePropertyManager(parent)
{

}

MyDoublePropertyManager::~MyDoublePropertyManager()
{

}

void MyDoublePropertyManager::setPrefix(QtProperty *property,QString prefix)
{
    if(!mMapPropertyAndElseData.contains(property))
        return;

    QString oldPrefix = mMapPropertyAndElseData[property].prefix;

    if(prefix == oldPrefix)
        return;

    mMapPropertyAndElseData[property].prefix = prefix;
}

void MyDoublePropertyManager::setSuffix(QtProperty *property,QString suffix)
{
    if(!mMapPropertyAndElseData.contains(property))
        return;

    QString oldSuffix = mMapPropertyAndElseData[property].suffix;

    if(suffix == oldSuffix)
        return;

    mMapPropertyAndElseData[property].suffix = suffix;
}

QString MyDoublePropertyManager::getPrefix(QtProperty *property)
{
    return mMapPropertyAndElseData[property].prefix;
}

QString MyDoublePropertyManager::getSuffix(QtProperty *property)
{
    return mMapPropertyAndElseData[property].suffix;
}

void MyDoublePropertyManager::initializeProperty(QtProperty *property)
{
    mMapPropertyAndElseData[property] = ElseData();
    QtDoublePropertyManager::initializeProperty(property);
}

void MyDoublePropertyManager::uninitializeProperty(QtProperty *property)
{
    mMapPropertyAndElseData.remove(property);
    QtDoublePropertyManager::uninitializeProperty(property);
}

QString MyDoublePropertyManager::valueText(const QtProperty *property) const
{
    QString text = QtDoublePropertyManager::valueText(property);
    if(!mMapPropertyAndElseData.contains(property))
    {
        return text;
    }

    ElseData data= mMapPropertyAndElseData[property];
    text = data.prefix + text + data.suffix;
    return text;
}
