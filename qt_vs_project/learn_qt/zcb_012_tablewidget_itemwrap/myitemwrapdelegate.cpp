#include "myitemwrapdelegate.h"
#include "qdebug.h"
#include <QTableWidgetItem>

MyItemWrapDelegate::MyItemWrapDelegate(QObject *parent /*= nullptr*/)
{

}

QWidget* MyItemWrapDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QTextEdit* editor= new QTextEdit(parent);
	editor->move(QPoint(option.rect.x(),option.rect.y()));

	return editor;
}

// 每次进入 editor 都会调它 或者  内容改变也会调
void MyItemWrapDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (index.data().canConvert<QString>()) {
		QString value = qvariant_cast<QString>(index.data());
		QTextEdit *newTextEdit = qobject_cast<QTextEdit *>(editor);
		newTextEdit->setPlainText(value);
		
		((MyItemWrapDelegate*)this)->emit editItemCompleted(index.row(), index.column());
	}
	else {
		QStyledItemDelegate::setEditorData(editor, index); // 父类的方法 
	}

}

void MyItemWrapDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QTextEdit *newTextEdit = static_cast<QTextEdit*>(editor);

	QString value = newTextEdit->toPlainText();

	model->setData(index, value, Qt::EditRole);
}

void MyItemWrapDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	//editor->setGeometry(option.rect);
}
