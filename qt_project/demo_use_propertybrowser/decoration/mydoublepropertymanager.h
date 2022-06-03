#ifndef MYDOUBLEPROPERTYMANAGER_H
#define MYDOUBLEPROPERTYMANAGER_H

#include <QtDoublePropertyManager>

class MyDoublePropertyManager:public QtDoublePropertyManager
{
    Q_OBJECT
public:
    MyDoublePropertyManager(QObject* parent=nullptr);
    ~MyDoublePropertyManager();

    void setPrefix(QtProperty *property,QString prefix);
    void setSuffix(QtProperty *property,QString suffix);

    QString getPrefix(QtProperty *property);
    QString getSuffix(QtProperty *property);

signals:
    void prefixChanged(QtProperty* property,QString prefix);
    void suffixChanged(QtProperty* property,QString suffix);


protected:
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
    QString valueText(const QtProperty *property) const override;

private:
    struct ElseData
    {
        QString prefix;
        QString suffix;
    };
    QMap<const QtProperty*,ElseData> mMapPropertyAndElseData;
};


#endif // MYDOUBLEPROPERTYMANAGER_H
