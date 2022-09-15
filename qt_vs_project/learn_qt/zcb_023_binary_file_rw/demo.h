#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo.h"
#include "QStandardItemModel"
#include "QItemSelectionModel"

#include    "qwintspindelegate.h"
#include    "qwfloatspindelegate.h"
#include    "qwcomboboxdelegate.h"
#include "QLabel"

#define FixedColumnCount 6

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

	void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
	bool openDataAsStream(QString &aFileName);
	bool saveDataAsStream(QString &aFileName);

	void resetTable(int aRowCount);

private slots:
	void on_actTabReset_triggered();

	void on_actOpen_triggered();
	void on_actSave_triggered();

	void on_actOpenBin_triggered();
	void on_actSaveBin_triggered();
private:
    Ui::DemoClass ui;
	QStandardItemModel  *theModel;    //数据模型
	QItemSelectionModel *theSelection;//Item选择模型

	// 三个代理 
	QWIntSpinDelegate    intSpinDelegate; //整型数
	QWFloatSpinDelegate  floatSpinDelegate; //浮点数
	QWComboBoxDelegate   comboBoxDelegate; //列表选择

	// 两个状态栏组件
	QLabel  *labCellPos;    //当前单元格行列号
	QLabel  *labCellText;   //当前单元格内容

	bool openBinaryFile(QString aFileName);
	bool saveBinaryFile(QString aFileName);
};
