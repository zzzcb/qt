#include "mydoublespinboxfactory.h"


MyDoubleSpinBoxFactory::MyDoubleSpinBoxFactory(QObject *parent)
    :QtAbstractEditorFactory<MyDoublePropertyManager>(parent)
{
    mInnerFactory = new QtDoubleSpinBoxFactory;
}

MyDoubleSpinBoxFactory::~MyDoubleSpinBoxFactory()
{

}

void MyDoubleSpinBoxFactory::connectPropertyManager(MyDoublePropertyManager *manager)
{
    mInnerFactory->addPropertyManager(manager);   // old
    connect(manager,&MyDoublePropertyManager::prefixChanged,this,&MyDoubleSpinBoxFactory::on_manager_prefixChanged);
    connect(manager,&MyDoublePropertyManager::suffixChanged,this,&MyDoubleSpinBoxFactory::on_manager_suffixChanged);

}

QWidget *MyDoubleSpinBoxFactory::createEditor(MyDoublePropertyManager *manager, QtProperty *property, QWidget *parent)
{
    QtAbstractEditorFactoryBase *base = mInnerFactory;
    QWidget *w = base->createEditor(property, parent);
    if (!w)
        return nullptr;

    QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox *>(w);
    if (!spinBox)
        return nullptr;

    spinBox->setPrefix(manager->getPrefix(property));
    spinBox->setSuffix(manager->getSuffix(property));

    mCreatedEditors[property].append(spinBox);
    mEditorToProperty[spinBox] = property;


    return spinBox;
}

void MyDoubleSpinBoxFactory::disconnectPropertyManager(MyDoublePropertyManager *manager)
{
    mInnerFactory->removePropertyManager(manager);
    connect(manager,&MyDoublePropertyManager::prefixChanged,this,&MyDoubleSpinBoxFactory::on_manager_prefixChanged);
    connect(manager,&MyDoublePropertyManager::suffixChanged,this,&MyDoubleSpinBoxFactory::on_manager_suffixChanged);
}

void MyDoubleSpinBoxFactory::on_manager_prefixChanged(QtProperty *property, QString prefix)
{
    // property hasn't manager
    if(!propertyManager(property))
        return;

    for(auto editor: mCreatedEditors[property])
    {
        editor->setPrefix(prefix);
    }

}

void MyDoubleSpinBoxFactory::on_manager_suffixChanged(QtProperty *property, QString suffix)
{
    // property hasn't manager
    if(!propertyManager(property))
        return;

    for(auto editor: mCreatedEditors[property])
    {
        editor->setPrefix(suffix);
    }
}

void MyDoubleSpinBoxFactory::slot_editor_destroyed(QObject* object)
{

        QMap<QDoubleSpinBox *, QtProperty *>::ConstIterator itEditor =
                    mEditorToProperty.constBegin();
        while (itEditor != mEditorToProperty.constEnd()) {
            if (itEditor.key() == object) {
                QDoubleSpinBox *editor = itEditor.key();
                QtProperty *property = itEditor.value();
                mEditorToProperty.remove(editor);
                mCreatedEditors[property].removeAll(editor);
                if (mCreatedEditors[property].isEmpty())
                    mCreatedEditors.remove(property);
                return;
            }
            itEditor++;
        }

}
