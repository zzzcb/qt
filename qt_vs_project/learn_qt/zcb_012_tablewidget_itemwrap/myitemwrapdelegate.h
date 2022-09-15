#pragma once
#include <QWidget>
#include <QStyledItemDelegate>
#include <QTextEdit>

class MyItemWrapDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	MyItemWrapDelegate(QObject *parent = nullptr);

	QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	
Q_SIGNALS:
	void editItemCompleted(int row, int column);
};
