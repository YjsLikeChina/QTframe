/********************************************************************************
** Form generated from reading UI file 'UI_MessageBox.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_MESSAGEBOX_H
#define UI_UI_MESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_QMessageBox
{
public:
    QLabel *LB_Background1;
    QPushButton *PB_OK;
    QLabel *LB_MessageInfo;
    QPushButton *PB_Cancel;
    QPushButton *NeverJump;

    void setupUi(QDialog *QMessageBox)
    {
        if (QMessageBox->objectName().isEmpty())
            QMessageBox->setObjectName(QStringLiteral("QMessageBox"));
        QMessageBox->resize(400, 256);
        LB_Background1 = new QLabel(QMessageBox);
        LB_Background1->setObjectName(QStringLiteral("LB_Background1"));
        LB_Background1->setGeometry(QRect(0, 0, 401, 261));
        PB_OK = new QPushButton(QMessageBox);
        PB_OK->setObjectName(QStringLiteral("PB_OK"));
        PB_OK->setGeometry(QRect(20, 195, 110, 45));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_OK->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        PB_OK->setFont(font);
        LB_MessageInfo = new QLabel(QMessageBox);
        LB_MessageInfo->setObjectName(QStringLiteral("LB_MessageInfo"));
        LB_MessageInfo->setGeometry(QRect(20, 20, 361, 161));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_MessageInfo->setPalette(palette1);
        LB_MessageInfo->setFont(font);
        LB_MessageInfo->setFrameShape(QFrame::NoFrame);
        PB_Cancel = new QPushButton(QMessageBox);
        PB_Cancel->setObjectName(QStringLiteral("PB_Cancel"));
        PB_Cancel->setGeometry(QRect(270, 195, 110, 45));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_Cancel->setPalette(palette2);
        PB_Cancel->setFont(font);
        NeverJump = new QPushButton(QMessageBox);
        NeverJump->setObjectName(QStringLiteral("NeverJump"));
        NeverJump->setGeometry(QRect(145, 195, 110, 45));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        NeverJump->setPalette(palette3);
        NeverJump->setFont(font);

        retranslateUi(QMessageBox);

        QMetaObject::connectSlotsByName(QMessageBox);
    } // setupUi

    void retranslateUi(QDialog *QMessageBox)
    {
        QMessageBox->setWindowTitle(QApplication::translate("QMessageBox", "Dialog", 0));
        LB_Background1->setText(QString());
        PB_OK->setText(QApplication::translate("QMessageBox", "\347\241\256\345\256\232", 0));
        LB_MessageInfo->setText(QApplication::translate("QMessageBox", "TextLabel", 0));
        PB_Cancel->setText(QApplication::translate("QMessageBox", "\345\217\226\346\266\210", 0));
        NeverJump->setText(QApplication::translate("QMessageBox", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class QMessageBox: public Ui_QMessageBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_MESSAGEBOX_H
