/********************************************************************************
** Form generated from reading UI file 'changeperson.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEPERSON_H
#define UI_CHANGEPERSON_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_changePerson
{
public:

    void setupUi(QWidget *changePerson)
    {
        if (changePerson->objectName().isEmpty())
            changePerson->setObjectName(QStringLiteral("changePerson"));
        changePerson->resize(400, 300);

        retranslateUi(changePerson);

        QMetaObject::connectSlotsByName(changePerson);
    } // setupUi

    void retranslateUi(QWidget *changePerson)
    {
        changePerson->setWindowTitle(QApplication::translate("changePerson", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class changePerson: public Ui_changePerson {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEPERSON_H
