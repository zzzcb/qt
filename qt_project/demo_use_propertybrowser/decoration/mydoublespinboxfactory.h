#ifndef MYDOUBLESPINBOXFACTORY_H
#define MYDOUBLESPINBOXFACTORY_H

#include "mydoublepropertymanager.h"
#include <QtDoubleSpinBoxFactory>
#include <QDoubleSpinBox>

class MyDoubleSpinBoxFactory : public QtAbstractEditorFactory<MyDoublePropertyManager>
{
public:
    MyDoubleSpinBoxFactory(QObject* parent=nullptr);
    ~MyDoubleSpinBoxFactory();

protected:
    void connectPropertyManager(MyDoublePropertyManager *manager) override;
    QWidget * createEditor(MyDoublePropertyManager *manager, QtProperty *property, QWidget *parent) override;
    void disconnectPropertyManager(MyDoublePropertyManager *manager) override;

private:
    void on_manager_prefixChanged(QtProperty* property,QString prefix);
    void on_manager_suffixChanged(QtProperty* property,QString suffix);
    void slot_editor_destroyed(QObject* object);


private:
    QtDoubleSpinBoxFactory* mInnerFactory;

    QMap<QtProperty *, QList<QDoubleSpinBox *> > mCreatedEditors;
    QMap<QDoubleSpinBox *, QtProperty *> mEditorToProperty;

};

#endif // MYDOUBLESPINBOXFACTORY_H
