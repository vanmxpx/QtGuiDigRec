/********************************************************************************
** Form generated from reading UI file 'QtGuiDigRec.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIDIGREC_H
#define UI_QTGUIDIGREC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>

QT_BEGIN_NAMESPACE

class Ui_QtGuiDigRecClass
{
public:

    void setupUi(QMainWindow *QtGuiDigRecClass)
    {
        if (QtGuiDigRecClass->objectName().isEmpty())
            QtGuiDigRecClass->setObjectName(QStringLiteral("QtGuiDigRecClass"));
        QtGuiDigRecClass->resize(600, 400);

        retranslateUi(QtGuiDigRecClass);

        QMetaObject::connectSlotsByName(QtGuiDigRecClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiDigRecClass)
    {
        QtGuiDigRecClass->setWindowTitle(QApplication::translate("QtGuiDigRecClass", "QtGuiDigRec", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGuiDigRecClass: public Ui_QtGuiDigRecClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIDIGREC_H
