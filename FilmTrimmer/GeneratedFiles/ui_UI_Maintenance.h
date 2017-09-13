/********************************************************************************
** Form generated from reading UI file 'UI_Maintenance.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_MAINTENANCE_H
#define UI_UI_MAINTENANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_MaintenanceDlg
{
public:
    QLabel *LB_Background;
    QLabel *LB_Exit;

    void setupUi(QDialog *MaintenanceDlg)
    {
        if (MaintenanceDlg->objectName().isEmpty())
            MaintenanceDlg->setObjectName(QStringLiteral("MaintenanceDlg"));
        MaintenanceDlg->setWindowModality(Qt::NonModal);
        MaintenanceDlg->resize(1024, 768);
        MaintenanceDlg->setAutoFillBackground(true);
        MaintenanceDlg->setStyleSheet(QLatin1String("color rgb(255, 255, 0)\n"
"background-color rgb(255, 0, 0)"));
        LB_Background = new QLabel(MaintenanceDlg);
        LB_Background->setObjectName(QStringLiteral("LB_Background"));
        LB_Background->setGeometry(QRect(0, 0, 1024, 768));
        LB_Exit = new QLabel(MaintenanceDlg);
        LB_Exit->setObjectName(QStringLiteral("LB_Exit"));
        LB_Exit->setGeometry(QRect(450, 519, 151, 61));

        retranslateUi(MaintenanceDlg);

        QMetaObject::connectSlotsByName(MaintenanceDlg);
    } // setupUi

    void retranslateUi(QDialog *MaintenanceDlg)
    {
        MaintenanceDlg->setWindowTitle(QString());
        LB_Background->setText(QString());
        LB_Exit->setText(QApplication::translate("MaintenanceDlg", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class MaintenanceDlg: public Ui_MaintenanceDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_MAINTENANCE_H
