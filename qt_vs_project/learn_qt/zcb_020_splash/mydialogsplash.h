#pragma once

#include <QDialog>
#include "qdebug.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "QPixmap"
#include "qevent.h"

#include "ui_mydialogsplash.h"

class MyDialogSplash : public QDialog
{
	Q_OBJECT

public:
	MyDialogSplash(QWidget *parent = Q_NULLPTR);
	~MyDialogSplash();


private slots:
	void on_pushButton_clicked();

private:
	Ui::MyDialogSplash ui;
	QSqlDatabase mDB;

	QPoint mPointInDialog_BeforeMoveMouse;
	
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

};
