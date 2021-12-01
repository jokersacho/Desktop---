/********************************************************************************
** Form generated from reading UI file 'autohidewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOHIDEWIDGET_H
#define UI_AUTOHIDEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_autoHideWidget
{
public:
    QPushButton *btnClose;

    void setupUi(QWidget *autoHideWidget)
    {
        if (autoHideWidget->objectName().isEmpty())
            autoHideWidget->setObjectName(QStringLiteral("autoHideWidget"));
        autoHideWidget->resize(388, 737);
        btnClose = new QPushButton(autoHideWidget);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(290, 0, 93, 51));

        retranslateUi(autoHideWidget);

        QMetaObject::connectSlotsByName(autoHideWidget);
    } // setupUi

    void retranslateUi(QWidget *autoHideWidget)
    {
        autoHideWidget->setWindowTitle(QApplication::translate("autoHideWidget", "Form", Q_NULLPTR));
        btnClose->setText(QApplication::translate("autoHideWidget", "clsoe", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class autoHideWidget: public Ui_autoHideWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOHIDEWIDGET_H
