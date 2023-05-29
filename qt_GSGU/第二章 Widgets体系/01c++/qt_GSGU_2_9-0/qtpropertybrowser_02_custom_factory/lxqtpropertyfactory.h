#include "lxqtpropertyvalidator.h"

#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include <QLineEdit>


/**=============================lxQtEditor===========================================*/
template <class Editor>
class lxQtEditor
{
public:
	typedef QList<Editor *> EditorList;
	typedef QMap<QtProperty *, EditorList> PropertyToEditorListMap;
	typedef QMap<Editor *, QtProperty *> EditorToPropertyMap;

	Editor *createEditor(QtProperty *property, QWidget *parent);
	void initializeEditor(QtProperty *property, Editor *editor);
	void slotEditorDestroyed(QObject *object);

	PropertyToEditorListMap  m_createdEditors;
	EditorToPropertyMap m_editorToProperty;
};

/**=============================lxQtFilePathFactory===========================================*/
// lxQtFilePathEdit
class lxQtFilePathEdit : public QLineEdit
{
	Q_OBJECT
public:
	lxQtFilePathEdit(QWidget *parent = 0);

	QString value() const;
	void setValue(const QString &value);

signals:
	void valueChanged(const QString &value);
public Q_SLOTS:
	void slot_textChanged(const QString &text);

protected:
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void focusOutEvent(QFocusEvent * event) override;

private:
	QString m_strVal;
};

// lxQtFilePathFactory
class lxQtFilePathFactory : public QtAbstractEditorFactory<QtStringPropertyManager>
{
	Q_OBJECT
public:
	lxQtFilePathFactory(QObject *parent = nullptr);
	~lxQtFilePathFactory();
protected:
	void connectPropertyManager(QtStringPropertyManager *manager);
	QWidget *createEditor(QtStringPropertyManager *manager, QtProperty *property,QWidget *parent);
	void disconnectPropertyManager(QtStringPropertyManager *manager);
private slots:
	void slotManagerValueChanged(QtProperty * property, const QString &value);
	void slotEditorValueChanged(const QString & value);
	void slotEditorDestroyed(QObject *editor);

private:
	QScopedPointer<lxQtEditor<lxQtFilePathEdit>> m_pEditor;
};


/**=============================lxQtEmailFactory===========================================*/
// lxQtEmailEdit
class lxQtEmailEdit : public QLineEdit
{
	Q_OBJECT
public:
	lxQtEmailEdit(QWidget *parent = 0);
	
	QString value() const;
	void setValue(const QString &value);
	void setValidator(lxQtAbstractValidator* validator);

signals:
	void valueChanged(const QString &value);
private slots:
	void slot_textChanged(const QString& text);

private:
	QString m_strVal;
	lxQtAbstractValidator* m_pValidator = nullptr;
};

// lxQtEmailFactory
class lxQtEmailFactory : public QtAbstractEditorFactory<QtStringPropertyManager>
{
	Q_OBJECT
public:
	lxQtEmailFactory(QObject *parent = nullptr);
	~lxQtEmailFactory();

	void setValidator(QtProperty * property, lxQtAbstractValidator* validator);
protected:
	void connectPropertyManager(QtStringPropertyManager *manager);
	QWidget *createEditor(QtStringPropertyManager *manager, QtProperty *property, QWidget *parent);
	void disconnectPropertyManager(QtStringPropertyManager *manager);
private slots:
	void slotManagerValueChanged(QtProperty * property, const QString &value);
	void slotEditorValueChanged(const QString & value);
	void slotEditorDestroyed(QObject *editor);

private:
	typedef QMap<QtProperty *,  lxQtAbstractValidator*> PropertyToValidatorMap;
	PropertyToValidatorMap m_mapPropertyToValidator;

	QScopedPointer<lxQtEditor<lxQtEmailEdit>> m_pEditor;
};
