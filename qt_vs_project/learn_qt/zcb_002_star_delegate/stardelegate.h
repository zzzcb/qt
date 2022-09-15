#ifndef STARDELEGATE_H
#define STARDELEGATE_H

#include <QStyledItemDelegate>

// delegate time order: create editor -> set editor data -> commit and close editor -> set model data ->(if new data)set editor data

class StarDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	using QStyledItemDelegate::QStyledItemDelegate;

	void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const override;
	QSize sizeHint(const QStyleOptionViewItem &option,
		const QModelIndex &index) const override;
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const override;

private slots:
	void commitAndCloseEditor();
};

#endif