#pragma execution_character_set("utf-8")
#include "demo.h"

Demo::Demo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	this->setWindowTitle("QT学习");
	
	class PopupItemDelegate : public QStyledItemDelegate
	{
	public:
		using QStyledItemDelegate::QStyledItemDelegate;
		QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
		{
			QSize s = QStyledItemDelegate::sizeHint(option, index);
			s.setHeight(20);
			return s;
		}
		
	};

	//QListView *fontSizeView = new QListView(ui.comboBox);
	//ui.comboBox->setView(fontSizeView);
	ui.comboBox->view()->setItemDelegate(new PopupItemDelegate(ui.comboBox));
	ui.comboBox->addItems({ "一号","二号","三号","四号","五号","六号","七号" });

}

