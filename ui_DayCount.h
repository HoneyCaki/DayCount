/********************************************************************************
** Form generated from reading UI file 'DayCountaGhIuS.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DAYCOUNTAGHIUS_H
#define DAYCOUNTAGHIUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DayCountClass
{
public:
    QWidget *centralWidget;
    QLabel *targetDate;
    QLabel *currentDate;
    QLabel *dayText;
    QLabel *days;
    QLabel *tipText;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DayCountClass)
    {
        if (DayCountClass->objectName().isEmpty())
            DayCountClass->setObjectName(QString::fromUtf8("DayCountClass"));
        DayCountClass->resize(483, 445);
        DayCountClass->setLayoutDirection(Qt::LeftToRight);
        centralWidget = new QWidget(DayCountClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        targetDate = new QLabel(centralWidget);
        targetDate->setObjectName(QString::fromUtf8("targetDate"));
        targetDate->setEnabled(true);
        targetDate->setGeometry(QRect(280, 370, 96, 20));
        currentDate = new QLabel(centralWidget);
        currentDate->setObjectName(QString::fromUtf8("currentDate"));
        currentDate->setGeometry(QRect(90, 370, 346, 20));
        dayText = new QLabel(centralWidget);
        dayText->setObjectName(QString::fromUtf8("dayText"));
        dayText->setGeometry(QRect(320, 280, 127, 111));
        days = new QLabel(centralWidget);
        days->setObjectName(QString::fromUtf8("days"));
        days->setGeometry(QRect(120, 260, 277, 111));
        tipText = new QLabel(centralWidget);
        tipText->setObjectName(QString::fromUtf8("tipText"));
        tipText->setGeometry(QRect(120, 230, 229, 24));
        DayCountClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DayCountClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 483, 23));
        DayCountClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(DayCountClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DayCountClass->setStatusBar(statusBar);

        retranslateUi(DayCountClass);

        QMetaObject::connectSlotsByName(DayCountClass);
    } // setupUi

    void retranslateUi(QMainWindow *DayCountClass)
    {
        DayCountClass->setWindowTitle(QCoreApplication::translate("DayCountClass", "DayCount", nullptr));
        targetDate->setText(QCoreApplication::translate("DayCountClass", "<html><head/><body><p><span style=\" font-size:12pt;\">2023\345\271\2646\346\234\2107\346\227\245</span></p></body></html>", nullptr));
        currentDate->setText(QCoreApplication::translate("DayCountClass", "<html><head/><body><p><span style=\" font-size:12pt;\">2022\345\271\26410\346\234\21020\346\227\245 \342\200\224\342\200\224</span></p></body></html>", nullptr));
        dayText->setText(QCoreApplication::translate("DayCountClass", "<html><head/><body><p><span style=\" font-size:26pt;\">\345\244\251</span></p></body></html>", nullptr));
        days->setText(QCoreApplication::translate("DayCountClass", "<html><head/><body><p><span style=\" font-size:72pt;\">232</span></p></body></html>", nullptr));
        tipText->setText(QCoreApplication::translate("DayCountClass", "<html><head/><body><p><span style=\" font-size:16pt;\">\350\267\235\347\246\273\351\253\230\350\200\203\350\277\230\346\234\211:</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DayCountClass: public Ui_DayCountClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DAYCOUNTAGHIUS_H
