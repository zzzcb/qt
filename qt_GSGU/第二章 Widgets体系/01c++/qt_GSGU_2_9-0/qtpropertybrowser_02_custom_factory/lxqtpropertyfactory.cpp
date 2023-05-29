#include "lxqtpropertyfactory.h"

#include <QFileDialog>
#include <QDebug>

/**=============================lxQtEditor===========================================*/
template <class Editor>
Editor * lxQtEditor<Editor>::createEditor(QtProperty *property, QWidget *parent)
{
	Editor *editor = new Editor(parent);
	initializeEditor(property, editor);
	return editor;
}

template <class Editor>
void lxQtEditor<Editor>::initializeEditor(QtProperty *property, Editor *editor)
{
	typename PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
	if (it == m_createdEditors.end())
		it = m_createdEditors.insert(property, EditorList());
	it.value().append(editor);
	m_editorToProperty.insert(editor, property);
}

template <class Editor>
void lxQtEditor<Editor>::slotEditorDestroyed(QObject *object)
{
	const typename EditorToPropertyMap::iterator ecend = m_editorToProperty.end();
	for (typename EditorToPropertyMap::iterator itEditor = m_editorToProperty.begin(); itEditor != ecend; ++itEditor) {
		if (itEditor.key() == object) {
			Editor *editor = itEditor.key();
			QtProperty *property = itEditor.value();
			const typename PropertyToEditorListMap::iterator pit = m_createdEditors.find(property);
			if (pit != m_createdEditors.end()) {
				pit.value().removeAll(editor);
				if (pit.value().empty())
					m_createdEditors.erase(pit);
			}
			m_editorToProperty.erase(itEditor);
			return;
		}
	}
}


/**=============================lxQtFilePathFactory===========================================*/
// lxQtFilePathEdit
lxQtFilePathEdit::lxQtFilePathEdit(QWidget*parent)
	:QLineEdit(parent)
{
	connect(this, &QLineEdit::textChanged, this, &lxQtFilePathEdit::slot_textChanged, Qt::QueuedConnection);
}

QString lxQtFilePathEdit::value() const
{
	return m_strVal;
}

void lxQtFilePathEdit::setValue(const QString &value)
{
	if (value == m_strVal)
		return;

	m_strVal = value;
	setText(m_strVal);
}

void lxQtFilePathEdit::slot_textChanged(const QString &text)
{
	// 在此处统一发出最终的数据
	//qDebug() << text << " " << m_strVal;

	// 验证数据是否合法
	if (!text.isEmpty())
	{
		setStyleSheet("background-color:green;");
		setText(text);
		setValue(text);
		emit valueChanged(text);
	}
	else
	{
		setText(text);
		setStyleSheet("background-color:red;");
	}
}

void lxQtFilePathEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
	QString val = QFileDialog::getOpenFileName();
	if (val != m_strVal)
		slot_textChanged(val);
}

void lxQtFilePathEdit::focusOutEvent(QFocusEvent * event)
{
	QString val = displayText();
	if (val != m_strVal)
		slot_textChanged(val);
}

// lxQtFilePathFactory
lxQtFilePathFactory::lxQtFilePathFactory(QObject *parent)
	:QtAbstractEditorFactory<QtStringPropertyManager>(parent), m_pEditor(new lxQtEditor<lxQtFilePathEdit>())
{
}

lxQtFilePathFactory::~lxQtFilePathFactory()
{
	qDeleteAll(m_pEditor->m_editorToProperty.keys());
}

void lxQtFilePathFactory::connectPropertyManager(QtStringPropertyManager *manager)
{
	connect(manager, &QtStringPropertyManager::valueChanged,this,&lxQtFilePathFactory::slotManagerValueChanged);
}

QWidget * lxQtFilePathFactory::createEditor(QtStringPropertyManager *manager, QtProperty *property, QWidget *parent)
{
	lxQtFilePathEdit *editor = m_pEditor->createEditor(property, parent);
	editor->setValue(manager->value(property));
	
	connect(editor, &lxQtFilePathEdit::valueChanged, this, &lxQtFilePathFactory::slotEditorValueChanged);
	connect(editor, &lxQtFilePathEdit::destroyed, this, &lxQtFilePathFactory::slotEditorDestroyed);

	return editor;
}

void lxQtFilePathFactory::disconnectPropertyManager(QtStringPropertyManager *manager)
{
	disconnect(manager, &QtStringPropertyManager::valueChanged, this, &lxQtFilePathFactory::slotManagerValueChanged);
}

void lxQtFilePathFactory::slotManagerValueChanged(QtProperty * property, const QString &value)
{
	const auto it = m_pEditor->m_createdEditors.constFind(property);
	if (it == m_pEditor->m_createdEditors.cend())
		return;
	for (lxQtFilePathEdit *editor : it.value()) {
		if (editor->value() != value)
		{
			editor->blockSignals(true);
			editor->setValue(value);
			editor->blockSignals(false);
		}
	}
}

void lxQtFilePathFactory::slotEditorValueChanged(const QString & value)
{
	QObject *object = sender();

	auto ecend = m_pEditor->m_editorToProperty.constEnd();
	for (auto itEditor = m_pEditor->m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
		if (itEditor.key() == object) {
			QtProperty *property = itEditor.value();
			QtStringPropertyManager *manager = propertyManager(property);
			if (!manager)
				return;
			manager->setValue(property, value);

			return;
		}
}

void lxQtFilePathFactory::slotEditorDestroyed(QObject *editor)
{
	m_pEditor->slotEditorDestroyed(editor);
}

/**=============================lxQtEmailFactory===========================================*/
//lxQtEmailEdit
lxQtEmailEdit::lxQtEmailEdit(QWidget *parent /*= 0*/)
	:QLineEdit(parent)
{
	connect(this, &QLineEdit::textChanged, this, &lxQtEmailEdit::slot_textChanged, Qt::QueuedConnection);
}

QString lxQtEmailEdit::value() const
{
	return m_strVal;
}

void lxQtEmailEdit::setValue(const QString &value)
{
	if (value == m_strVal)
		return;

	m_strVal = value;
	setText(m_strVal);
}

void lxQtEmailEdit::setValidator(lxQtAbstractValidator* validator)
{
	if (validator != m_pValidator)
		m_pValidator = validator;
}

void lxQtEmailEdit::slot_textChanged(const QString& text)
{
	// 在此处统一发出最终的数据
	if (m_pValidator && m_pValidator->validate(text)) // 验证数据是否合法
	{
		setStyleSheet("background-color:green;");
		setText(text);
		setValue(text);
		emit valueChanged(text);
	}
	else
	{
		if (text.isEmpty())
		{
			setValue(text);
			emit valueChanged(text);
		}

		setText(text);
		setStyleSheet("background-color:red;");
	}
}

//lxQtEmailFactory
lxQtEmailFactory::lxQtEmailFactory(QObject *parent /*= nullptr*/)
	:QtAbstractEditorFactory<QtStringPropertyManager>(parent),m_pEditor(new lxQtEditor<lxQtEmailEdit>())
{
}

lxQtEmailFactory::~lxQtEmailFactory()
{
	qDeleteAll(m_pEditor->m_editorToProperty.keys());
}

void lxQtEmailFactory::setValidator(QtProperty * property, lxQtAbstractValidator* validator)
{
	m_mapPropertyToValidator.insert(property, validator);
}

void lxQtEmailFactory::connectPropertyManager(QtStringPropertyManager *manager)
{
	connect(manager, &QtStringPropertyManager::valueChanged, this, &lxQtEmailFactory::slotManagerValueChanged);
}

QWidget * lxQtEmailFactory::createEditor(QtStringPropertyManager *manager, QtProperty *property, QWidget *parent)
{
	lxQtEmailEdit *editor = m_pEditor->createEditor(property, parent);
	editor->setValue(manager->value(property));

	// 给editor 设置验证器
	auto it = m_mapPropertyToValidator.find(property);
	if (it != m_mapPropertyToValidator.end())
		editor->setValidator(m_mapPropertyToValidator.value(property));

	connect(editor, &lxQtEmailEdit::valueChanged, this, &lxQtEmailFactory::slotEditorValueChanged);
	connect(editor, &lxQtEmailEdit::destroyed, this, &lxQtEmailFactory::slotEditorDestroyed);

	return editor;
}

void lxQtEmailFactory::disconnectPropertyManager(QtStringPropertyManager *manager)
{
	disconnect(manager, &QtStringPropertyManager::valueChanged, this, &lxQtEmailFactory::slotManagerValueChanged);
}

void lxQtEmailFactory::slotManagerValueChanged(QtProperty * property, const QString &value)
{
	const auto it = m_pEditor->m_createdEditors.constFind(property);
	if (it == m_pEditor->m_createdEditors.cend())
		return;
	for (lxQtEmailEdit *editor : it.value()) {
		if (editor->value() != value)
		{
			editor->blockSignals(true);
			editor->setValue(value);
			editor->blockSignals(false);
		}
	}
}

void lxQtEmailFactory::slotEditorValueChanged(const QString & value)
{
	QObject *object = sender();

	auto ecend = m_pEditor->m_editorToProperty.constEnd();
	for (auto itEditor = m_pEditor->m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
		if (itEditor.key() == object) {
			QtProperty *property = itEditor.value();
			QtStringPropertyManager *manager = propertyManager(property);
			if (!manager)
				return;
			manager->setValue(property, value);

			return;
		}
}

void lxQtEmailFactory::slotEditorDestroyed(QObject *editor)
{
	m_pEditor->slotEditorDestroyed(editor);
}

