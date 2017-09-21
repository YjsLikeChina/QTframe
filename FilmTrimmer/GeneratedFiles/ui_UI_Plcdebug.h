/********************************************************************************
** Form generated from reading UI file 'UI_Plcdebug.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_PLCDEBUG_H
#define UI_UI_PLCDEBUG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlcDebug
{
public:
    QLineEdit *lineEdit_RAddr;
    QLineEdit *lineEdit_RVal;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox_R;
    QLabel *label_3;
    QComboBox *comboBox_W;
    QLineEdit *lineEdit_WVal;
    QLineEdit *lineEdit_WAddr;
    QLabel *label_4;
    QPushButton *pushButton_R;
    QPushButton *pushButton_W;
    QLineEdit *lineEdit_RPos;
    QLineEdit *lineEdit_WPos;

    void setupUi(QWidget *PlcDebug)
    {
        if (PlcDebug->objectName().isEmpty())
            PlcDebug->setObjectName(QStringLiteral("PlcDebug"));
        PlcDebug->resize(619, 255);
        lineEdit_RAddr = new QLineEdit(PlcDebug);
        lineEdit_RAddr->setObjectName(QStringLiteral("lineEdit_RAddr"));
        lineEdit_RAddr->setGeometry(QRect(110, 40, 61, 20));
        lineEdit_RVal = new QLineEdit(PlcDebug);
        lineEdit_RVal->setObjectName(QStringLiteral("lineEdit_RVal"));
        lineEdit_RVal->setGeometry(QRect(430, 40, 113, 20));
        label = new QLabel(PlcDebug);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 40, 54, 12));
        label_2 = new QLabel(PlcDebug);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(350, 40, 54, 16));
        comboBox_R = new QComboBox(PlcDebug);
        comboBox_R->setObjectName(QStringLiteral("comboBox_R"));
        comboBox_R->setGeometry(QRect(240, 40, 69, 22));
        label_3 = new QLabel(PlcDebug);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 150, 54, 12));
        comboBox_W = new QComboBox(PlcDebug);
        comboBox_W->setObjectName(QStringLiteral("comboBox_W"));
        comboBox_W->setGeometry(QRect(240, 150, 69, 22));
        lineEdit_WVal = new QLineEdit(PlcDebug);
        lineEdit_WVal->setObjectName(QStringLiteral("lineEdit_WVal"));
        lineEdit_WVal->setGeometry(QRect(430, 150, 113, 20));
        lineEdit_WAddr = new QLineEdit(PlcDebug);
        lineEdit_WAddr->setObjectName(QStringLiteral("lineEdit_WAddr"));
        lineEdit_WAddr->setGeometry(QRect(110, 150, 61, 20));
        label_4 = new QLabel(PlcDebug);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(350, 150, 54, 16));
        pushButton_R = new QPushButton(PlcDebug);
        pushButton_R->setObjectName(QStringLiteral("pushButton_R"));
        pushButton_R->setGeometry(QRect(270, 90, 91, 31));
        pushButton_W = new QPushButton(PlcDebug);
        pushButton_W->setObjectName(QStringLiteral("pushButton_W"));
        pushButton_W->setGeometry(QRect(270, 200, 91, 31));
        lineEdit_RPos = new QLineEdit(PlcDebug);
        lineEdit_RPos->setObjectName(QStringLiteral("lineEdit_RPos"));
        lineEdit_RPos->setGeometry(QRect(190, 40, 31, 20));
        lineEdit_WPos = new QLineEdit(PlcDebug);
        lineEdit_WPos->setObjectName(QStringLiteral("lineEdit_WPos"));
        lineEdit_WPos->setGeometry(QRect(190, 150, 31, 20));

        retranslateUi(PlcDebug);

        QMetaObject::connectSlotsByName(PlcDebug);
    } // setupUi

    void retranslateUi(QWidget *PlcDebug)
    {
        PlcDebug->setWindowTitle(QApplication::translate("PlcDebug", "PlcDebug", 0));
        label->setText(QApplication::translate("PlcDebug", "PLC\345\234\260\345\235\200", 0));
        label_2->setText(QApplication::translate("PlcDebug", "\350\257\273\345\217\226\346\225\260\345\200\274", 0));
        comboBox_R->clear();
        comboBox_R->insertItems(0, QStringList()
         << QApplication::translate("PlcDebug", "MD", 0)
         << QApplication::translate("PlcDebug", "MW", 0)
         << QApplication::translate("PlcDebug", "QW", 0)
         << QApplication::translate("PlcDebug", "MX", 0)
         << QApplication::translate("PlcDebug", "QX", 0)
         << QApplication::translate("PlcDebug", "IX", 0)
        );
        label_3->setText(QApplication::translate("PlcDebug", "PLC\345\234\260\345\235\200", 0));
        comboBox_W->clear();
        comboBox_W->insertItems(0, QStringList()
         << QApplication::translate("PlcDebug", "MD", 0)
         << QApplication::translate("PlcDebug", "MW", 0)
         << QApplication::translate("PlcDebug", "QW", 0)
         << QApplication::translate("PlcDebug", "MX", 0)
         << QApplication::translate("PlcDebug", "QX", 0)
         << QApplication::translate("PlcDebug", "IX", 0)
        );
        label_4->setText(QApplication::translate("PlcDebug", "\345\206\231\345\205\245\346\225\260\345\200\274", 0));
        pushButton_R->setText(QApplication::translate("PlcDebug", "\350\257\273\345\217\226", 0));
        pushButton_W->setText(QApplication::translate("PlcDebug", "\345\206\231\345\205\245 ", 0));
    } // retranslateUi

};

namespace Ui {
    class PlcDebug: public Ui_PlcDebug {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_PLCDEBUG_H
