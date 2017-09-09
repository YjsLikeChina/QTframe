/********************************************************************************
** Form generated from reading UI file 'UI_HistoricalInformation.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_HISTORICALINFORMATION_H
#define UI_UI_HISTORICALINFORMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistoricalInformationWidget
{
public:
    QLabel *LB_Background2;
    QLabel *LB_Background1;
    QComboBox *CB_HistoryInfoSel;
    QPushButton *PB_CleanHistoryFile;
    QPushButton *PB_AlarmScreen;
    QTableWidget *TW_HistoryInfo;

    void setupUi(QWidget *HistoricalInformationWidget)
    {
        if (HistoricalInformationWidget->objectName().isEmpty())
            HistoricalInformationWidget->setObjectName(QStringLiteral("HistoricalInformationWidget"));
        HistoricalInformationWidget->resize(950, 649);
        LB_Background2 = new QLabel(HistoricalInformationWidget);
        LB_Background2->setObjectName(QStringLiteral("LB_Background2"));
        LB_Background2->setGeometry(QRect(0, 100, 1031, 551));
        LB_Background2->setFrameShape(QFrame::Box);
        LB_Background1 = new QLabel(HistoricalInformationWidget);
        LB_Background1->setObjectName(QStringLiteral("LB_Background1"));
        LB_Background1->setGeometry(QRect(0, 14, 1031, 61));
        LB_Background1->setFrameShape(QFrame::NoFrame);
        CB_HistoryInfoSel = new QComboBox(HistoricalInformationWidget);
        CB_HistoryInfoSel->setObjectName(QStringLiteral("CB_HistoryInfoSel"));
        CB_HistoryInfoSel->setGeometry(QRect(10, 24, 181, 41));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        CB_HistoryInfoSel->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        CB_HistoryInfoSel->setFont(font);
        PB_CleanHistoryFile = new QPushButton(HistoricalInformationWidget);
        PB_CleanHistoryFile->setObjectName(QStringLiteral("PB_CleanHistoryFile"));
        PB_CleanHistoryFile->setGeometry(QRect(820, 24, 101, 41));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_CleanHistoryFile->setPalette(palette1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        PB_CleanHistoryFile->setFont(font1);
        PB_AlarmScreen = new QPushButton(HistoricalInformationWidget);
        PB_AlarmScreen->setObjectName(QStringLiteral("PB_AlarmScreen"));
        PB_AlarmScreen->setGeometry(QRect(700, 24, 101, 41));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_AlarmScreen->setPalette(palette2);
        PB_AlarmScreen->setFont(font1);
        TW_HistoryInfo = new QTableWidget(HistoricalInformationWidget);
        TW_HistoryInfo->setObjectName(QStringLiteral("TW_HistoryInfo"));
        TW_HistoryInfo->setGeometry(QRect(0, 100, 951, 551));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        TW_HistoryInfo->setPalette(palette3);

        retranslateUi(HistoricalInformationWidget);

        QMetaObject::connectSlotsByName(HistoricalInformationWidget);
    } // setupUi

    void retranslateUi(QWidget *HistoricalInformationWidget)
    {
        HistoricalInformationWidget->setWindowTitle(QApplication::translate("HistoricalInformationWidget", "Form", 0));
        LB_Background2->setText(QApplication::translate("HistoricalInformationWidget", "TextLabel", 0));
        LB_Background1->setText(QString());
        PB_CleanHistoryFile->setText(QApplication::translate("HistoricalInformationWidget", "\346\270\205\351\231\244\345\216\206\345\217\262", 0));
        PB_AlarmScreen->setText(QApplication::translate("HistoricalInformationWidget", "\346\212\245\350\255\246\347\255\233\351\200\211", 0));
    } // retranslateUi

};

namespace Ui {
    class HistoricalInformationWidget: public Ui_HistoricalInformationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_HISTORICALINFORMATION_H
