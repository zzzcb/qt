#include <QtWidgets>

#include "stardelegate.h"
#include "stareditor.h"
#include "starrating.h"

#include "qdebug.h"

void StarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	qDebug() << "delegate paint ... ";
	if (index.data().canConvert<StarRating>()) {
		StarRating starRating = qvariant_cast<StarRating>(index.data());

		if (option.state & QStyle::State_Selected)
			painter->fillRect(option.rect, option.palette.highlight());

		starRating.paint(painter, option.rect, option.palette,
			StarRating::EditMode::ReadOnly);
	}
	else {
		QStyledItemDelegate::paint(painter, option, index); // 父类的方法 
	}
}

QSize StarDelegate::sizeHint(const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	qDebug() << "delegate sizeHint ... ";
	if (index.data().canConvert<StarRating>()) {
		StarRating starRating = qvariant_cast<StarRating>(index.data());
		return starRating.sizeHint();
	}
	return QStyledItemDelegate::sizeHint(option, index);  // 父类的方法 
}

QWidget *StarDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &option,
	const QModelIndex &index) const

{
	qDebug() << "delegate createEditor ... ";

	if (index.data().canConvert<StarRating>()) {
		StarEditor *editor = new StarEditor(parent);
		connect(editor, &StarEditor::editingFinished,
			this, &StarDelegate::commitAndCloseEditor);
		return editor;
	}
	return QStyledItemDelegate::createEditor(parent, option, index);// 父类的方法 
}

void StarDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	qDebug() << "delegate setEditorData ... ";

	if (index.data().canConvert<StarRating>()) {
		StarRating starRating = qvariant_cast<StarRating>(index.data());
		StarEditor *starEditor = qobject_cast<StarEditor *>(editor);
		starEditor->setStarRating(starRating);
	}
	else {
		QStyledItemDelegate::setEditorData(editor, index); // 父类的方法 
	}
}

void StarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	qDebug() << "delegate setModelData ... ";

	if (index.data().canConvert<StarRating>()) {
		StarEditor *starEditor = qobject_cast<StarEditor *>(editor);
		model->setData(index, QVariant::fromValue(starEditor->starRating()));
	}
	else {
		QStyledItemDelegate::setModelData(editor, model, index); // 父类的方法 
	}
}

void StarDelegate::commitAndCloseEditor()
{
	qDebug() << "delegate commitAndCloseEditor ... ";

	StarEditor *editor = qobject_cast<StarEditor *>(sender());
	emit commitData(editor);
	emit closeEditor(editor);
}
