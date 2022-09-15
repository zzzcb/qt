#pragma execution_character_set("utf-8")
#include "demo.h"
#include "qdebug.h"
#include "QDir"
#include "QFileDialog"
#include "QMessageBox"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	setCentralWidget(ui.tabWidget);

	// 为 tableView 设置模型
	theModel = new QStandardItemModel(5, FixedColumnCount, this); //创建数据模型
	QStringList headerList = { "Depth" ,"Measured Depth" , "Direction" , "Offset" , "Quality" , "Sampled" };
	theModel->setHorizontalHeaderLabels(headerList); //设置表头文字

	theSelection = new QItemSelectionModel(theModel);
	// 连接 select model 到 我们自己的槽函数
	connect(theSelection, &QItemSelectionModel::currentChanged, this, &Demo::on_currentChanged);

	ui.tableView->setModel(theModel);
	ui.tableView->setSelectionModel(theSelection);

	// 为tableView的列添加代理 
	ui.tableView->setItemDelegateForColumn(0, &intSpinDelegate);  //测深，整数
	ui.tableView->setItemDelegateForColumn(1, &floatSpinDelegate);  //浮点数
	ui.tableView->setItemDelegateForColumn(2, &floatSpinDelegate); //浮点数
	ui.tableView->setItemDelegateForColumn(3, &floatSpinDelegate); //浮点数
	ui.tableView->setItemDelegateForColumn(4, &comboBoxDelegate); //Combbox选择型

	resetTable(5);  // 表格复位

	// 状态栏组件 
	labCellPos = new QLabel("当前单元格：", this);
	labCellPos->setMinimumWidth(180);
	labCellPos->setAlignment(Qt::AlignHCenter);

	labCellText = new QLabel("单元格内容：", this);
	labCellText->setMinimumWidth(200);

	ui.statusBar->addWidget(labCellPos);
	ui.statusBar->addWidget(labCellText);
}

void Demo::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
	if (current.isValid())
	{
		labCellPos->setText(QString::asprintf("当前单元格：%d行，%d列",
			current.row(), current.column()));
		QStandardItem   *aItem;
		aItem = theModel->itemFromIndex(current); //从模型索引获得Item
		labCellText->setText("单元格内容：" + aItem->text());
	}
}


bool Demo::openDataAsStream(QString &aFileName)
{ //从Qt预定义流文件读入数据
	QFile aFile(aFileName);  //以文件方式读出
	if (!(aFile.open(QIODevice::ReadOnly)))
		return false;

	QDataStream aStream(&aFile); //用文本流读取文件
	aStream.setVersion(QDataStream::Qt_5_13); //设置流文件版本号

	qint16  rowCount, colCount;
	aStream >> rowCount; //读取行数
	aStream >> colCount; //列数

	resetTable(rowCount); //表格复位

	//获取表头文字
	QString str;
	for (int i = 0; i < colCount; i++)
		aStream >> str;  //读取表头字符串

	//获取数据区文字，
	qint16  ceShen;
	qreal  chuiShen;
	qreal  fangWei;
	qreal  weiYi;
	QString  zhiLiang;
	bool    quYang;
	QStandardItem   *aItem;
	QModelIndex index;

	for (int i = 0; i < rowCount; i++)
	{
		aStream >> ceShen;//读取测深, qint16
		index = theModel->index(i, 0);
		aItem = theModel->itemFromIndex(index);
		aItem->setData(ceShen, Qt::DisplayRole);

		aStream >> chuiShen;//垂深,qreal
		index = theModel->index(i, 1);
		aItem = theModel->itemFromIndex(index);
		aItem->setData(chuiShen, Qt::DisplayRole);


		aStream >> fangWei;//方位,qreal
		index = theModel->index(i, 2);
		aItem = theModel->itemFromIndex(index);
		aItem->setData(fangWei, Qt::DisplayRole);


		aStream >> weiYi;//位移,qreal
		index = theModel->index(i, 3);
		aItem = theModel->itemFromIndex(index);
		aItem->setData(weiYi, Qt::DisplayRole);


		aStream >> zhiLiang;//固井质量,QString
		index = theModel->index(i, 4);
		aItem = theModel->itemFromIndex(index);
		aItem->setData(zhiLiang, Qt::DisplayRole);

		aStream >> quYang;//bool
		index = theModel->index(i, 5);
		aItem = theModel->itemFromIndex(index);
		if (quYang)
			aItem->setCheckState(Qt::Checked);
		else
			aItem->setCheckState(Qt::Unchecked);
	}

	aFile.close();
	return true;
}
bool Demo::saveDataAsStream(QString &aFileName)
{//将模型数据保存为Qt预定义编码的数据文件
	QFile aFile(aFileName);  
	if (!(aFile.open(QIODevice::WriteOnly | QIODevice::Truncate)))
		return false;

	QDataStream aStream(&aFile);
	aStream.setVersion(QDataStream::Qt_5_13); //设置版本号，写入和读取的版本号要兼容

	qint16  rowCount = theModel->rowCount(); //数据模型行数
	qint16  colCount = theModel->columnCount(); //数据模型列数

	aStream << rowCount; //写入文件流，行数
	aStream << colCount;//写入文件流，列数

	//获取表头文字
	for (int i = 0; i < theModel->columnCount(); i++)
	{
		QString str = theModel->horizontalHeaderItem(i)->text();//获取表头文字
		aStream << str; //字符串写入文件流，Qt预定义编码方式
	}


	//保存数据区的数据
	QStandardItem* aItem;
	qint16 ceshen;
	qreal chuishen;
	qreal fangwei;
	qreal weiyi;
	QString zhiliang;
	bool quyang;
	for (int i = 0; i < theModel->rowCount(); i++)
	{
		ceshen = 0;
		chuishen = 0;
		fangwei = 0;
		weiyi = 0;
		zhiliang = " ";
		quyang = false;

		for (int j = 0; j < theModel->columnCount(); j++)
		{
			aItem = theModel->item(i, j);
			if (aItem)
			{
				switch (j)
				{
				case 0:
					ceshen = aItem->data(Qt::DisplayRole).toInt(); 
					break;
				case 1:
					chuishen = aItem->data(Qt::DisplayRole).toFloat();
					break;
				case 2:
					fangwei = aItem->data(Qt::DisplayRole).toFloat();
					break;
				case 3:
					weiyi = aItem->data(Qt::DisplayRole).toFloat();
					break;
				case 4:
					zhiliang = aItem->data(Qt::DisplayRole).toString();
					break;
				case 5:
					quyang = (aItem->checkState() == Qt::Checked);
					break;
				default:
					break;
				}
			}
		}

		aStream << ceshen << chuishen << fangwei << weiyi << zhiliang << quyang;
	}
	aFile.close();
	return true;
}


bool Demo::openBinaryFile(QString aFileName)
{
	QFile aFile(aFileName);
	if (!(aFile.open(QIODevice::ReadOnly)))
		return false;

	QDataStream aStream(&aFile);
	aStream.setByteOrder(QDataStream::LittleEndian);

	qint16  rowCount, colCount;
	aStream.readRawData((char *)&rowCount, sizeof(qint16));
	aStream.readRawData((char *)&colCount, sizeof(qint16));
	resetTable(rowCount);


	char *buf;
	uint strLen;  
	for (int i = 0; i < colCount; i++)
	{
		aStream.readBytes(buf, strLen);
		QString str = QString::fromUtf8(buf, strLen); 
	}

	//获取数据区数据
	QStandardItem   *aItem;
	qint16  ceShen;
	qreal  chuiShen;
	qreal  fangWei;
	qreal  weiYi;
	QString  zhiLiang;
	qint8   quYang; 
	QModelIndex index;

	for (int i = 0; i < rowCount; i++)
	{
		aStream.readRawData((char *)&ceShen, sizeof(qint16)); //测深
		index = theModel->index(i, 0);
		aItem = theModel->itemFromIndex(index);
		aItem->setData(ceShen, Qt::DisplayRole);

		aStream.readRawData((char *)&chuiShen, sizeof(qreal)); //垂深
		index = theModel->index(i, 1);
		aItem = theModel->itemFromIndex(index);
		aItem->setData(chuiShen, Qt::DisplayRole);

		aStream.readRawData((char *)&fangWei, sizeof(qreal)); //方位
		index = theModel->index(i, 2);
		aItem = theModel->itemFromIndex(index);
		aItem->setData(fangWei, Qt::DisplayRole);

		aStream.readRawData((char *)&weiYi, sizeof(qreal)); //位移
		index = theModel->index(i, 3);
		aItem = theModel->itemFromIndex(index);
		aItem->setData(weiYi, Qt::DisplayRole);

		aStream.readBytes(buf, strLen);//固井质量
		zhiLiang = QString::fromUtf8(buf, strLen);
		index = theModel->index(i, 4);
		aItem = theModel->itemFromIndex(index);
		aItem->setData(zhiLiang, Qt::DisplayRole);

		aStream.readRawData((char *)&quYang, sizeof(qint8)); //测井取样
		index = theModel->index(i, 5);
		aItem = theModel->itemFromIndex(index);
		if (quYang == 1)
			aItem->setCheckState(Qt::Checked);
		else
			aItem->setCheckState(Qt::Unchecked);
	}

	aFile.close();
	return true;
}

bool Demo::saveBinaryFile(QString aFileName)
{
	QFile aFile(aFileName);
	if (!(aFile.open(QIODevice::WriteOnly)))
		return false;

	QDataStream aStream(&aFile);
	aStream.setByteOrder(QDataStream::LittleEndian);//windows平台

	qint16  rowCount = theModel->rowCount();
	qint16  colCount = theModel->columnCount();

	aStream.writeRawData((char *)&rowCount, sizeof(qint16)); //写入文件流
	aStream.writeRawData((char *)&colCount, sizeof(qint16));//写入文件流

	//保存表头文字
	QByteArray  btArray;
	QStandardItem   *aItem;
	for (int i = 0; i < theModel->columnCount(); i++)
	{
		aItem = theModel->horizontalHeaderItem(i);
		QString str = aItem->text();
		btArray = str.toUtf8();
		aStream.writeBytes(btArray, btArray.length());
	}

	//保存数据区
	qint16 ceshen;
	qreal chuishen;
	qreal fangwei;
	qreal weiyi;
	QString zhiliang;
	bool quyang;
	for (int i = 0; i < theModel->rowCount(); i++)
	{
		ceshen = 0;
		chuishen = 0;
		fangwei = 0;
		weiyi = 0;
		zhiliang = " ";
		quyang = false;

		for (int j = 0; j < theModel->columnCount(); j++)
		{
			aItem = theModel->item(i, j);
			if (aItem)
			{
				switch (j)
				{
				case 0:
					ceshen = aItem->data(Qt::DisplayRole).toInt();
					break;
				case 1:
					chuishen = aItem->data(Qt::DisplayRole).toFloat();
					break;
				case 2:
					fangwei = aItem->data(Qt::DisplayRole).toFloat();
					break;
				case 3:
					weiyi = aItem->data(Qt::DisplayRole).toFloat();
					break;
				case 4:
					zhiliang = aItem->data(Qt::DisplayRole).toString();
					break;
				case 5:
					quyang = (aItem->checkState() == Qt::Checked);
					break;
				default:
					break;
				}
			}
		}
	
		aStream.writeRawData((char *)&ceshen, sizeof(qint16));
		aStream.writeRawData((char *)&chuishen, sizeof(qreal));
		aStream.writeRawData((char *)&fangwei, sizeof(qreal));
		aStream.writeRawData((char *)&weiyi, sizeof(qreal));
		
		aStream.writeBytes(zhiliang.toUtf8(), zhiliang.toUtf8().length());
		aStream.writeRawData((char *)&quyang, sizeof(qint8));
	}

	aFile.close();
	return true;
}


void Demo::on_actTabReset_triggered()
{
	resetTable(5);
}

// 打开 stm 
void Demo::on_actOpen_triggered()
{
	QString curPath = QDir::currentPath();
	//调用打开文件对话框打开一个文件
	QString aFileName = QFileDialog::getOpenFileName(this, tr("打开一个文件"), curPath,
		"流数据文件(*.stm)");

	if (aFileName.isEmpty())
		return; //

	if (openDataAsStream(aFileName)) //保存为流数据文件
		QMessageBox::information(this, "提示消息", "文件已经打开!");
}

// 保存 stm 
void Demo::on_actSave_triggered()
{ //以Qt预定义编码保存数据文件
	QString curPath = QDir::currentPath();
	QString aFileName = QFileDialog::getSaveFileName(this, tr("选择保存文件"), curPath,
		"Qt预定义编码数据文件(*.stm)");

	if (aFileName.isEmpty())
		return; //

	if (saveDataAsStream(aFileName)) //保存为流数据文件
		QMessageBox::information(this, "提示消息", "文件已经成功保存!");
}

// 打开 dat 
void Demo::on_actOpenBin_triggered()
{
	QString curPath = QDir::currentPath();//系统当前目录
	QString aFileName = QFileDialog::getOpenFileName(this, tr("打开一个文件"), curPath,
		"二进制数据文件(*.dat)");
	if (aFileName.isEmpty())
		return; //

	if (openBinaryFile(aFileName)) //保存为流数据文件
		QMessageBox::information(this, "提示消息", "文件已经打开!");
}

// 保存 dat 
void Demo::on_actSaveBin_triggered()
{
	QString curPath = QDir::currentPath();
	//调用打开文件对话框选择一个文件
	QString aFileName = QFileDialog::getSaveFileName(this, tr("选择保存文件"), curPath,
		"二进制数据文件(*.dat)");
	if (aFileName.isEmpty())
		return; //

	if (saveBinaryFile(aFileName)) //保存为流数据文件
		QMessageBox::information(this, "提示消息", "文件已经成功保存!");
}



void Demo::resetTable(int aRowCount)
{ 
	//表格复位，先删除所有行，再设置新的行数，表头不变

	theModel->removeRows(0, theModel->rowCount()); //删除所有行
	theModel->setRowCount(aRowCount);//设置新的行数

	QString str = theModel->headerData(FixedColumnCount - 1,
		Qt::Horizontal, Qt::DisplayRole).toString();

	for (int i = 0; i < theModel->rowCount(); i++)
	{ //设置最后一列
		QModelIndex index = theModel->index(i, FixedColumnCount - 1); //获取模型索引
		QStandardItem* aItem = theModel->itemFromIndex(index); //获取item
		aItem->setCheckable(true);
		aItem->setData(str, Qt::DisplayRole);
		aItem->setEditable(false); //不可编辑
	}
}

