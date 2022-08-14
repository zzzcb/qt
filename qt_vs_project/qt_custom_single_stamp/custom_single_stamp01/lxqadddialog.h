#pragma once

#include <QDialog>
#include <QFormLayout>

class QLineEdit;
class QTextEdit;


class lxQAddDialog : public QDialog
{
	Q_OBJECT

public:
	lxQAddDialog(QWidget *parent = nullptr);
	~lxQAddDialog();

	QString name();
	QString address();

	/** 
	*******************************************************************
	* @brief      初始化添加对话框的数据内容 
	* @param[in] strTitle  ————   对话框的标题
	* @param[in] vLabelAndWidget  ———— 
						其中，内部的vector前两个QString,第一个为Label,第二个为Widget类型 {{"size","QLineEdit"},{"","QCheckbox"}}
						后续所需数据,排在第三位往后。
						例如:{"size","QLineEdit","10.3"}  默认值为10.3
						例如:{"font","QComboBoxEdit","item1","item2","item3"}  默认下拉框包含item1 item2 item3 三个元素
	* @return     void
	******************************************************************* 
	*/
	bool initEditor(QString strTitle,QVector<QVector<QString>> vLabelAndWidget);

	/** 
	*******************************************************************
	* @brief      获取用户输入的数据        
	* @return     QVector<QString> ————
					返回均返回字符串,
					例如: lineedit 返回 "0.001"
					例如: checkbox 返回 "0"  或者 "1"
					例如: commobox 返回当前位置+内容文本 "0+item"
	******************************************************************* 
	*/
	QVector<QString> getEditorResult();



private:
	QFormLayout* mp_mainLayout;
	QVector<QWidget*> mv_editor;
};
