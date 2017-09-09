/********************************************************************************
** Form generated from reading UI file 'UI_Simpledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_SIMPLEDIALOG_H
#define UI_UI_SIMPLEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimPleDialog
{
public:
    QPushButton *PB_OK;
    QPushButton *PB_Cancel;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;

    void setupUi(QDialog *SimPleDialog)
    {
        if (SimPleDialog->objectName().isEmpty())
            SimPleDialog->setObjectName(QStringLiteral("SimPleDialog"));
        SimPleDialog->resize(400, 304);
        SimPleDialog->setStyleSheet(QLatin1String("QDialog\n"
"{\n"
"background-image: url(:/FilmTrimmer/Image/Background.png);\n"
"}\n"
"QPushButton::pressed\n"
"{\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;border-color: blue;\n"
"};"));
        PB_OK = new QPushButton(SimPleDialog);
        PB_OK->setObjectName(QStringLiteral("PB_OK"));
        PB_OK->setGeometry(QRect(45, 253, 100, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        PB_OK->setFont(font);
        PB_OK->setStyleSheet(QLatin1String("background:transparent;\n"
"color: rgb(255, 255, 255);"));
        PB_Cancel = new QPushButton(SimPleDialog);
        PB_Cancel->setObjectName(QStringLiteral("PB_Cancel"));
        PB_Cancel->setGeometry(QRect(255, 253, 100, 40));
        PB_Cancel->setFont(font);
        PB_Cancel->setStyleSheet(QLatin1String("background:transparent;\n"
"color: rgb(255, 255, 255);"));
        gridLayoutWidget = new QWidget(SimPleDialog);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(40, 9, 321, 231));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(SimPleDialog);

        QMetaObject::connectSlotsByName(SimPleDialog);
    } // setupUi

    void retranslateUi(QDialog *SimPleDialog)
    {
        SimPleDialog->setWindowTitle(QApplication::translate("SimPleDialog", "SimPleDialog", 0));
        PB_OK->setText(QApplication::translate("SimPleDialog", "\347\241\256\345\256\232", 0));
        PB_Cancel->setText(QApplication::translate("SimPleDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class SimPleDialog: public Ui_SimPleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_SIMPLEDIALOG_H
