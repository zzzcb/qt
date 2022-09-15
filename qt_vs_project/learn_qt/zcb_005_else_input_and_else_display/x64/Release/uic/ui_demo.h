/********************************************************************************
** Form generated from reading UI file 'demo.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMO_H
#define UI_DEMO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DemoClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QSlider *redSlider;
    QLabel *label_3;
    QSlider *greenSlider;
    QLabel *label_4;
    QSlider *blueSlider;
    QLabel *label_5;
    QSlider *alphaSlider;
    QSpacerItem *horizontalSpacer;
    QTextEdit *colorDisplay;
    QPushButton *btnClose;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout;
    QSlider *verticalSlider_3;
    QScrollBar *verticalScrollBar_2;
    QProgressBar *progressBar_2;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_2;
    QDial *dial;
    QLCDNumber *lcdNumber;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QProgressBar *progressBar;
    QScrollBar *verticalScrollBar;
    QSlider *verticalSlider_2;

    void setupUi(QMainWindow *DemoClass)
    {
        if (DemoClass->objectName().isEmpty())
            DemoClass->setObjectName(QString::fromUtf8("DemoClass"));
        DemoClass->resize(903, 586);
        DemoClass->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(DemoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 331, 211));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(331, 211));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 50, 298, 110));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        redSlider = new QSlider(widget);
        redSlider->setObjectName(QString::fromUtf8("redSlider"));
        redSlider->setMinimumSize(QSize(100, 0));
        redSlider->setMaximum(255);
        redSlider->setValue(255);
        redSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(redSlider, 0, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        greenSlider = new QSlider(widget);
        greenSlider->setObjectName(QString::fromUtf8("greenSlider"));
        greenSlider->setMinimumSize(QSize(100, 0));
        greenSlider->setMaximum(255);
        greenSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(greenSlider, 1, 1, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        blueSlider = new QSlider(widget);
        blueSlider->setObjectName(QString::fromUtf8("blueSlider"));
        blueSlider->setMinimumSize(QSize(100, 0));
        blueSlider->setMaximum(255);
        blueSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(blueSlider, 2, 1, 1, 1);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        alphaSlider = new QSlider(widget);
        alphaSlider->setObjectName(QString::fromUtf8("alphaSlider"));
        alphaSlider->setMinimumSize(QSize(100, 0));
        alphaSlider->setMaximum(255);
        alphaSlider->setValue(255);
        alphaSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(alphaSlider, 3, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        colorDisplay = new QTextEdit(widget);
        colorDisplay->setObjectName(QString::fromUtf8("colorDisplay"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(colorDisplay->sizePolicy().hasHeightForWidth());
        colorDisplay->setSizePolicy(sizePolicy1);
        colorDisplay->setMinimumSize(QSize(100, 100));
        colorDisplay->setMaximumSize(QSize(100, 100));
        colorDisplay->setSizeIncrement(QSize(0, 0));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        colorDisplay->setPalette(palette);
        colorDisplay->setLayoutDirection(Qt::LeftToRight);
        colorDisplay->setFrameShape(QFrame::Box);
        colorDisplay->setFrameShadow(QFrame::Sunken);
        colorDisplay->setLineWidth(3);
        colorDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        colorDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        horizontalLayout->addWidget(colorDisplay);

        btnClose = new QPushButton(centralWidget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(809, 546, 75, 24));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/images/exit.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 240, 291, 261));
        groupBox_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox_3->setFlat(false);
        groupBox_3->setCheckable(false);
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(20, -1, 20, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSlider_3 = new QSlider(groupBox_3);
        verticalSlider_3->setObjectName(QString::fromUtf8("verticalSlider_3"));
        verticalSlider_3->setTracking(true);
        verticalSlider_3->setOrientation(Qt::Horizontal);
        verticalSlider_3->setTickPosition(QSlider::TicksAbove);

        verticalLayout->addWidget(verticalSlider_3);

        verticalScrollBar_2 = new QScrollBar(groupBox_3);
        verticalScrollBar_2->setObjectName(QString::fromUtf8("verticalScrollBar_2"));
        verticalScrollBar_2->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(verticalScrollBar_2);

        progressBar_2 = new QProgressBar(groupBox_3);
        progressBar_2->setObjectName(QString::fromUtf8("progressBar_2"));
        progressBar_2->setValue(24);
        progressBar_2->setAlignment(Qt::AlignBottom|Qt::AlignRight|Qt::AlignTrailing);
        progressBar_2->setTextVisible(true);
        progressBar_2->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(progressBar_2);


        gridLayout_4->addLayout(verticalLayout, 0, 0, 1, 1);

        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(340, 260, 481, 231));
        groupBox_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox_4->setFlat(false);
        groupBox_4->setCheckable(false);
        horizontalLayout_2 = new QHBoxLayout(groupBox_4);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        dial = new QDial(groupBox_4);
        dial->setObjectName(QString::fromUtf8("dial"));
        dial->setValue(0);
        dial->setWrapping(false);
        dial->setNotchesVisible(true);

        horizontalLayout_2->addWidget(dial);

        lcdNumber = new QLCDNumber(groupBox_4);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setDigitCount(5);
        lcdNumber->setProperty("value", QVariant(15.000000000000000));

        horizontalLayout_2->addWidget(lcdNumber);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(15, 15, -1, -1);
        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(label);

        radioButton = new QRadioButton(groupBox_4);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setChecked(true);

        verticalLayout_2->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox_4);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout_2->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(groupBox_4);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout_2->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(groupBox_4);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        verticalLayout_2->addWidget(radioButton_4);


        horizontalLayout_2->addLayout(verticalLayout_2);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(530, 40, 271, 162));
        groupBox_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(22, 20, 22, 20);
        progressBar = new QProgressBar(groupBox_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);
        progressBar->setAlignment(Qt::AlignBottom|Qt::AlignRight|Qt::AlignTrailing);
        progressBar->setTextVisible(true);
        progressBar->setOrientation(Qt::Vertical);

        gridLayout_3->addWidget(progressBar, 1, 2, 1, 1);

        verticalScrollBar = new QScrollBar(groupBox_2);
        verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
        verticalScrollBar->setOrientation(Qt::Vertical);

        gridLayout_3->addWidget(verticalScrollBar, 1, 1, 1, 1);

        verticalSlider_2 = new QSlider(groupBox_2);
        verticalSlider_2->setObjectName(QString::fromUtf8("verticalSlider_2"));
        verticalSlider_2->setTracking(true);
        verticalSlider_2->setOrientation(Qt::Vertical);
        verticalSlider_2->setTickPosition(QSlider::TicksAbove);

        gridLayout_3->addWidget(verticalSlider_2, 1, 0, 1, 1);

        DemoClass->setCentralWidget(centralWidget);

        retranslateUi(DemoClass);
        QObject::connect(btnClose, SIGNAL(clicked()), DemoClass, SLOT(close()));

        QMetaObject::connectSlotsByName(DemoClass);
    } // setupUi

    void retranslateUi(QMainWindow *DemoClass)
    {
        DemoClass->setWindowTitle(QCoreApplication::translate("DemoClass", "Demo", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DemoClass", "Slider\345\222\214QColor", nullptr));
        label_2->setText(QCoreApplication::translate("DemoClass", "Red", nullptr));
        label_3->setText(QCoreApplication::translate("DemoClass", "Green", nullptr));
        label_4->setText(QCoreApplication::translate("DemoClass", "Blue", nullptr));
        label_5->setText(QCoreApplication::translate("DemoClass", "Alapha", nullptr));
        colorDisplay->setHtml(QCoreApplication::translate("DemoClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p></body></html>", nullptr));
        btnClose->setText(QCoreApplication::translate("DemoClass", "\345\205\263\351\227\255", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("DemoClass", "scroll bar\345\222\214 progress bar", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("DemoClass", "LCD Number\345\222\214 Dial", nullptr));
        label->setText(QCoreApplication::translate("DemoClass", "LCD \346\230\276\347\244\272\346\216\247\345\210\266", nullptr));
        radioButton->setText(QCoreApplication::translate("DemoClass", "\345\215\201\350\277\233\345\210\266", nullptr));
        radioButton_2->setText(QCoreApplication::translate("DemoClass", "\344\272\214\350\277\233\345\210\266", nullptr));
        radioButton_3->setText(QCoreApplication::translate("DemoClass", "\345\205\253\350\277\233\345\210\266", nullptr));
        radioButton_4->setText(QCoreApplication::translate("DemoClass", "\345\215\201\345\205\255\350\277\233\345\210\266", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("DemoClass", "scroll bar\345\222\214 progress bar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DemoClass: public Ui_DemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMO_H
