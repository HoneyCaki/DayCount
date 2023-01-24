/********************************************************************************
** Form generated from reading UI file 'positionSettingsdBeteO.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef POSITIONSETTINGSDBETEO_H
#define POSITIONSETTINGSDBETEO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_positionSettings
{
public:

    void setupUi(QWidget *positionSettings)
    {
        if (positionSettings->objectName().isEmpty())
            positionSettings->setObjectName(QString::fromUtf8("positionSettings"));
        positionSettings->resize(483, 440);

        retranslateUi(positionSettings);

        QMetaObject::connectSlotsByName(positionSettings);
    } // setupUi

    void retranslateUi(QWidget *positionSettings)
    {
        positionSettings->setWindowTitle(QCoreApplication::translate("positionSettings", "positionSettings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class positionSettings: public Ui_positionSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // POSITIONSETTINGSDBETEO_H
