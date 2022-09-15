#pragma execution_character_set("utf-8")

#include "mydialogsplash.h"


/** 
*******************************************************************
* @brief      判断数据库是否存在表        
* @param[in] db  ———— 数据库对象
* @param[in] tableName  ———— 表名
* @return     bool
******************************************************************* 
*/
bool isExistTable(QSqlDatabase db,QString tableName)
{
	if (!db.isOpen())
	{
		return false;
	}
	bool bRet = false;

	QSqlQuery query(db);
	query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(tableName));

	if (query.next())
	{
		if (query.value(0).toInt() > 0)
		{
			bRet = true;
		}
	}
	return bRet;
}

bool createTable(QSqlDatabase db, QString tableName)
{
	if (!db.isOpen())
	{
		return false;
	}

	QSqlQuery query(db);
	bool bSuccess = query.exec(
		QString("CREATE TABLE %1 ("
			"id INTEGER PRIMARY KEY AUTOINCREMENT, "
			"username VARCHAR(40) NOT NULL, "
			"password VARCHAR(40) NOT NULL)"
		).arg(tableName)
	);
	if (bSuccess)
	{
		return true;
	}
	else
	{
		qDebug() <<"=============== "<< query.lastError().driverText();
		return false;
	}
}

MyDialogSplash::MyDialogSplash(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose); // 窗口关闭时 自动回收内存
	setWindowFlag(Qt::SplashScreen);

	// 创建数据库,有的话就打开,没的话就创建
	mDB = QSqlDatabase::addDatabase("QSQLITE");
	mDB.setDatabaseName("data.db");
	bool ok = mDB.open();
	if (ok)
	{
		// 创建表 
		if (!isExistTable(mDB, "username_pwd_tb"))
		{
			createTable(mDB, "username_pwd_tb");
		}
	}
	else {
		qDebug() << "----------> 打开数据库失败";
	}

}

MyDialogSplash::~MyDialogSplash()
{
	qDebug() << "db close ......................."; 
	mDB.close();
}

#include "QMessageBox"
void MyDialogSplash::on_pushButton_clicked()
{
	// get name and pwd
	QString userName = ui.lineEdit->text().trimmed();
	QString userPwd = ui.lineEdit_2->text().trimmed();
	
	if (userName.startsWith("register_zcb_")) // 用户名以 register_zcb_ 开头则是要注册用户,保存到数据库中
	{
		bool bSuccess = false;
		QSqlQuery query(mDB);
		bSuccess = query.exec(
			QString(
				"INSERT INTO username_pwd_tb(username, password)"
				"VALUES('%1','%2');").arg(userName.mid(13),userPwd)
		);
		if (!bSuccess)
		{
			qDebug() << "=============== " << query.lastError().driverText();
		}

		this->accept();
		return;
	}

	// 查找数据库 看是否用户名和密码正确
	QSqlQuery query(mDB);
	bool bSuccess = false;
	bSuccess = query.exec(
		QString(
			"SELECT count(*) FROM username_pwd_tb "
			"WHERE username = '%1' and password = '%2';").arg(userName,userPwd)
	);
	if (!bSuccess)
	{
		qDebug() << "=============== " << query.lastError().driverText();
	}
	else {
		if (query.next())
		{
			if (query.value(0).toInt() == 1)
			{
				QMessageBox::information(this, "登录成功", "恭喜你哦");
				this->accept();
			}
			else {
				QMessageBox::critical(this, "失败", "用户名或密码错误");
				this->reject();
			}
		}
	}

}

void MyDialogSplash::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		mPointInDialog_BeforeMoveMouse = event->globalPos() - this->pos();
	}
}

void MyDialogSplash::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		move(event->globalPos() - mPointInDialog_BeforeMoveMouse);
	}
}
