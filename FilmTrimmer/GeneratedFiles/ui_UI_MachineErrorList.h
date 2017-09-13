/********************************************************************************
** Form generated from reading UI file 'UI_MachineErrorList.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_MACHINEERRORLIST_H
#define UI_UI_MACHINEERRORLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MachineErrorInfoList
{
public:
    QLabel *LB_Background;
    QListWidget *LW_ErrorInfo;
    QPushButton *PB_CloseButton;

    void setupUi(QWidget *MachineErrorInfoList)
    {
        if (MachineErrorInfoList->objectName().isEmpty())
            MachineErrorInfoList->setObjectName(QStringLiteral("MachineErrorInfoList"));
        MachineErrorInfoList->resize(493, 82);
        MachineErrorInfoList->setMinimumSize(QSize(0, 0));
        MachineErrorInfoList->setMaximumSize(QSize(493, 535));
        LB_Background = new QLabel(MachineErrorInfoList);
        LB_Background->setObjectName(QStringLiteral("LB_Background"));
        LB_Background->setGeometry(QRect(0, 0, 493, 81));
        QPalette palette;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_Background->setPalette(palette);
        LB_Background->setFrameShape(QFrame::Box);
        LW_ErrorInfo = new QListWidget(MachineErrorInfoList);
        LW_ErrorInfo->setObjectName(QStringLiteral("LW_ErrorInfo"));
        LW_ErrorInfo->setGeometry(QRect(1, 1, 491, 31));
        QPalette palette1;
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        LW_ErrorInfo->setPalette(palette1);
        QFont font;
        font.setPointSize(12);
        LW_ErrorInfo->setFont(font);
        LW_ErrorInfo->setFrameShape(QFrame::NoFrame);
        PB_CloseButton = new QPushButton(MachineErrorInfoList);
        PB_CloseButton->setObjectName(QStringLiteral("PB_CloseButton"));
        PB_CloseButton->setGeometry(QRect(196, 40, 101, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        PB_CloseButton->setFont(font1);

        retranslateUi(MachineErrorInfoList);

        QMetaObject::connectSlotsByName(MachineErrorInfoList);
    } // setupUi

    void retranslateUi(QWidget *MachineErrorInfoList)
    {
        MachineErrorInfoList->setWindowTitle(QApplication::translate("MachineErrorInfoList", "Form", 0));
        LB_Background->setText(QString());
        PB_CloseButton->setText(QApplication::translate("MachineErrorInfoList", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class MachineErrorInfoList: public Ui_MachineErrorInfoList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_MACHINEERRORLIST_H
