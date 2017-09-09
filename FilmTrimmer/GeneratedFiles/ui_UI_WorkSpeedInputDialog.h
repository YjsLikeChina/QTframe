/********************************************************************************
** Form generated from reading UI file 'UI_WorkSpeedInputDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_WORKSPEEDINPUTDIALOG_H
#define UI_UI_WORKSPEEDINPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WorkSpeedInputDialog
{
public:
    QLabel *LB_Background;
    QPushButton *PB_Cancel;
    QPushButton *PB_OK;
    QLineEdit *LE_WorkSpeedInput;

    void setupUi(QDialog *WorkSpeedInputDialog)
    {
        if (WorkSpeedInputDialog->objectName().isEmpty())
            WorkSpeedInputDialog->setObjectName(QStringLiteral("WorkSpeedInputDialog"));
        WorkSpeedInputDialog->resize(339, 111);
        WorkSpeedInputDialog->setMinimumSize(QSize(339, 111));
        WorkSpeedInputDialog->setMaximumSize(QSize(339, 111));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        WorkSpeedInputDialog->setFont(font);
        LB_Background = new QLabel(WorkSpeedInputDialog);
        LB_Background->setObjectName(QStringLiteral("LB_Background"));
        LB_Background->setGeometry(QRect(0, 0, 341, 111));
        PB_Cancel = new QPushButton(WorkSpeedInputDialog);
        PB_Cancel->setObjectName(QStringLiteral("PB_Cancel"));
        PB_Cancel->setGeometry(QRect(200, 63, 101, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        PB_Cancel->setFont(font1);
        PB_OK = new QPushButton(WorkSpeedInputDialog);
        PB_OK->setObjectName(QStringLiteral("PB_OK"));
        PB_OK->setGeometry(QRect(40, 63, 101, 41));
        PB_OK->setFont(font1);
        LE_WorkSpeedInput = new QLineEdit(WorkSpeedInputDialog);
        LE_WorkSpeedInput->setObjectName(QStringLiteral("LE_WorkSpeedInput"));
        LE_WorkSpeedInput->setGeometry(QRect(40, 10, 261, 41));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        LE_WorkSpeedInput->setPalette(palette);
        LE_WorkSpeedInput->setFont(font);
        LE_WorkSpeedInput->setContextMenuPolicy(Qt::NoContextMenu);
        QWidget::setTabOrder(PB_OK, LE_WorkSpeedInput);
        QWidget::setTabOrder(LE_WorkSpeedInput, PB_Cancel);

        retranslateUi(WorkSpeedInputDialog);

        QMetaObject::connectSlotsByName(WorkSpeedInputDialog);
    } // setupUi

    void retranslateUi(QDialog *WorkSpeedInputDialog)
    {
        WorkSpeedInputDialog->setWindowTitle(QApplication::translate("WorkSpeedInputDialog", "\345\267\245\344\275\234\351\200\237\345\272\246\350\256\276\345\256\232", 0));
        LB_Background->setText(QString());
        PB_Cancel->setText(QApplication::translate("WorkSpeedInputDialog", "\345\217\226\346\266\210 ", 0));
        PB_OK->setText(QApplication::translate("WorkSpeedInputDialog", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class WorkSpeedInputDialog: public Ui_WorkSpeedInputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_WORKSPEEDINPUTDIALOG_H
