/********************************************************************************
** Form generated from reading UI file 'UI_FloatingWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_FLOATINGWINDOW_H
#define UI_UI_FLOATINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FloatingWindow
{
public:
    QLabel *LB_Show3;
    QLabel *LB_Exit;
    QLabel *LB_Show2;
    QPushButton *PB_RunSchema;
    QLabel *LB_Show4_4;
    QPushButton *PB_RunDirection;
    QPushButton *PB_OnloadDirection;
    QPushButton *PB_MachineEStop;
    QPushButton *PB_MachineStart;
    QLabel *LB_Show5;
    QPushButton *PB_MachineReset;
    QPushButton *PB_MachineStop;

    void setupUi(QWidget *FloatingWindow)
    {
        if (FloatingWindow->objectName().isEmpty())
            FloatingWindow->setObjectName(QStringLiteral("FloatingWindow"));
        FloatingWindow->resize(1024, 305);
        FloatingWindow->setMinimumSize(QSize(1024, 305));
        FloatingWindow->setMaximumSize(QSize(1024, 305));
        LB_Show3 = new QLabel(FloatingWindow);
        LB_Show3->setObjectName(QStringLiteral("LB_Show3"));
        LB_Show3->setGeometry(QRect(559, 20, 331, 261));
        LB_Show3->setFrameShape(QFrame::Box);
        LB_Exit = new QLabel(FloatingWindow);
        LB_Exit->setObjectName(QStringLiteral("LB_Exit"));
        LB_Exit->setGeometry(QRect(977, 12, 35, 35));
        LB_Show2 = new QLabel(FloatingWindow);
        LB_Show2->setObjectName(QStringLiteral("LB_Show2"));
        LB_Show2->setGeometry(QRect(130, 20, 281, 261));
        LB_Show2->setFrameShape(QFrame::Box);
        PB_RunSchema = new QPushButton(FloatingWindow);
        PB_RunSchema->setObjectName(QStringLiteral("PB_RunSchema"));
        PB_RunSchema->setGeometry(QRect(200, 68, 130, 50));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_RunSchema->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        PB_RunSchema->setFont(font);
        LB_Show4_4 = new QLabel(FloatingWindow);
        LB_Show4_4->setObjectName(QStringLiteral("LB_Show4_4"));
        LB_Show4_4->setGeometry(QRect(230, 30, 71, 25));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_Show4_4->setPalette(palette1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        LB_Show4_4->setFont(font1);
        LB_Show4_4->setFrameShape(QFrame::NoFrame);
        PB_RunDirection = new QPushButton(FloatingWindow);
        PB_RunDirection->setObjectName(QStringLiteral("PB_RunDirection"));
        PB_RunDirection->setGeometry(QRect(200, 144, 130, 50));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_RunDirection->setPalette(palette2);
        PB_RunDirection->setFont(font);
        PB_OnloadDirection = new QPushButton(FloatingWindow);
        PB_OnloadDirection->setObjectName(QStringLiteral("PB_OnloadDirection"));
        PB_OnloadDirection->setGeometry(QRect(200, 220, 130, 50));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_OnloadDirection->setPalette(palette3);
        PB_OnloadDirection->setFont(font);
        PB_MachineEStop = new QPushButton(FloatingWindow);
        PB_MachineEStop->setObjectName(QStringLiteral("PB_MachineEStop"));
        PB_MachineEStop->setGeometry(QRect(750, 190, 130, 55));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_MachineEStop->setPalette(palette4);
        PB_MachineEStop->setFont(font);
        PB_MachineStart = new QPushButton(FloatingWindow);
        PB_MachineStart->setObjectName(QStringLiteral("PB_MachineStart"));
        PB_MachineStart->setGeometry(QRect(586, 81, 130, 55));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_MachineStart->setPalette(palette5);
        PB_MachineStart->setFont(font);
        LB_Show5 = new QLabel(FloatingWindow);
        LB_Show5->setObjectName(QStringLiteral("LB_Show5"));
        LB_Show5->setGeometry(QRect(699, 30, 71, 25));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_Show5->setPalette(palette6);
        LB_Show5->setFont(font1);
        LB_Show5->setFrameShape(QFrame::NoFrame);
        PB_MachineReset = new QPushButton(FloatingWindow);
        PB_MachineReset->setObjectName(QStringLiteral("PB_MachineReset"));
        PB_MachineReset->setGeometry(QRect(586, 190, 130, 55));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_MachineReset->setPalette(palette7);
        PB_MachineReset->setFont(font);
        PB_MachineStop = new QPushButton(FloatingWindow);
        PB_MachineStop->setObjectName(QStringLiteral("PB_MachineStop"));
        PB_MachineStop->setGeometry(QRect(750, 81, 130, 55));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_MachineStop->setPalette(palette8);
        PB_MachineStop->setFont(font);

        retranslateUi(FloatingWindow);

        QMetaObject::connectSlotsByName(FloatingWindow);
    } // setupUi

    void retranslateUi(QWidget *FloatingWindow)
    {
        FloatingWindow->setWindowTitle(QApplication::translate("FloatingWindow", "Form", 0));
        LB_Show3->setText(QString());
        LB_Exit->setText(QApplication::translate("FloatingWindow", "TextLabel", 0));
        LB_Show2->setText(QString());
        PB_RunSchema->setText(QApplication::translate("FloatingWindow", " \346\211\213\345\212\250\350\277\220\350\241\214    ", 0));
        LB_Show4_4->setText(QApplication::translate("FloatingWindow", "\350\277\220\350\241\214\346\226\271\345\274\217", 0));
        PB_RunDirection->setText(QApplication::translate("FloatingWindow", " \346\255\243\345\220\221\350\277\220\350\241\214    ", 0));
        PB_OnloadDirection->setText(QApplication::translate("FloatingWindow", " \351\200\206\346\227\266\351\222\210\346\224\276\345\215\267", 0));
        PB_MachineEStop->setText(QApplication::translate("FloatingWindow", " \346\200\245\345\201\234", 0));
        PB_MachineStart->setText(QApplication::translate("FloatingWindow", " \345\220\257\345\212\250", 0));
        LB_Show5->setText(QApplication::translate("FloatingWindow", "\346\216\247\345\210\266\346\214\211\351\222\256", 0));
        PB_MachineReset->setText(QApplication::translate("FloatingWindow", " \345\244\215\344\275\215", 0));
        PB_MachineStop->setText(QApplication::translate("FloatingWindow", " \345\201\234\346\255\242", 0));
    } // retranslateUi

};

namespace Ui {
    class FloatingWindow: public Ui_FloatingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_FLOATINGWINDOW_H
