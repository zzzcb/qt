#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QtWidgets/QLineEdit>
#include <QtUiPlugin/QDesignerExportWidget>


class QDESIGNER_WIDGET_EXPORT MyLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    MyLineEdit(QWidget *parent = nullptr);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
signals:
    void doubleClicked();
};

#endif // MYLINEEDIT_H
