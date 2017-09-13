/********************************************************************************
** Form generated from reading UI file 'UI_StopCauseListDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_STOPCAUSELISTDIALOG_H
#define UI_UI_STOPCAUSELISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_StopCauseListDialog
{
public:
    QTextEdit *TE_Alarm_Info;
    QListWidget *LW_StopCause1;

    void setupUi(QDialog *StopCauseListDialog)
    {
        if (StopCauseListDialog->objectName().isEmpty())
            StopCauseListDialog->setObjectName(QStringLiteral("StopCauseListDialog"));
        StopCauseListDialog->resize(829, 405);
        TE_Alarm_Info = new QTextEdit(StopCauseListDialog);
        TE_Alarm_Info->setObjectName(QStringLiteral("TE_Alarm_Info"));
        TE_Alarm_Info->setGeometry(QRect(20, 330, 791, 71));
        LW_StopCause1 = new QListWidget(StopCauseListDialog);
        LW_StopCause1->setObjectName(QStringLiteral("LW_StopCause1"));
        LW_StopCause1->setGeometry(QRect(20, 10, 171, 311));

        retranslateUi(StopCauseListDialog);

        QMetaObject::connectSlotsByName(StopCauseListDialog);
    } // setupUi

    void retranslateUi(QDialog *StopCauseListDialog)
    {
        StopCauseListDialog->setWindowTitle(QApplication::translate("StopCauseListDialog", "\351\200\211\346\213\251\345\201\234\346\234\272\345\216\237\345\233\240", 0));
    } // retranslateUi

};

namespace Ui {
    class StopCauseListDialog: public Ui_StopCauseListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_STOPCAUSELISTDIALOG_H
