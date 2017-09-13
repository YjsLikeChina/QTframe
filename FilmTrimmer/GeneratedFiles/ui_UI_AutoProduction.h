/********************************************************************************
** Form generated from reading UI file 'UI_AutoProduction.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_AUTOPRODUCTION_H
#define UI_UI_AUTOPRODUCTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoProduWidget
{
public:
    QLabel *LB_Info;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_Laser1;
    QLabel *label_Laser2;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_MainAxis;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_2;
    QLabel *label_13;
    QLabel *LB_WorkSpeedSet;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *LB_DataListShow;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QWidget *widget;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *LB_Laser1CurYield;
    QLabel *label_28;
    QLabel *LB_Laser2CurYield;
    QLabel *LB_LaserCurSumYield;
    QLabel *LB_Laser1SumYield;
    QLabel *LB_Laser2SumYield;
    QLabel *label_33;
    QLabel *LB_LaserSumYield;
    QPushButton *PB_CleanYield;
    QPushButton *PB_MainAxisFW;
    QPushButton *PB_MainAxisRE;
    QLabel *label_35;
    QLabel *label_20;
    QLabel *label_22;
    QPushButton *PB_SendloadFW;
    QPushButton *PB_SendloadRE;
    QPushButton *PB_RecvloadFW;
    QPushButton *PB_RecvloadRE;
    QLabel *LB_Laser1Step;
    QLabel *label_38;
    QLabel *label_27;
    QLabel *LB_Laser2Step;
    QPushButton *Btn_Put;
    QPushButton *Btn_Get;
    QLabel *label_40;
    QLabel *LB_Background1;
    QTreeWidget *TRW_ModuleTree;
    QPushButton *PB_RunDirection;
    QPushButton *PB_OnloadDirection;
    QLabel *LCD_OnloadDiameter;
    QLabel *LCD_OnloadTension;
    QLabel *LCD_WorkSpeedShow;
    QLabel *LCD_RecvTension;
    QLabel *LCD_RecvDiameter;

    void setupUi(QWidget *AutoProduWidget)
    {
        if (AutoProduWidget->objectName().isEmpty())
            AutoProduWidget->setObjectName(QStringLiteral("AutoProduWidget"));
        AutoProduWidget->resize(950, 649);
        AutoProduWidget->setMinimumSize(QSize(950, 649));
        AutoProduWidget->setMaximumSize(QSize(950, 649));
        LB_Info = new QLabel(AutoProduWidget);
        LB_Info->setObjectName(QStringLiteral("LB_Info"));
        LB_Info->setGeometry(QRect(770, 19, 111, 21));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_Info->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        LB_Info->setFont(font);
        label = new QLabel(AutoProduWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 430, 130, 130));
        label->setFrameShape(QFrame::NoFrame);
        label->setPixmap(QPixmap(QString::fromUtf8(":/FilmTrimmer/Image/1.png")));
        label->setScaledContents(true);
        label_3 = new QLabel(AutoProduWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(810, 435, 130, 130));
        label_3->setFrameShape(QFrame::NoFrame);
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/FilmTrimmer/Image/1.png")));
        label_3->setScaledContents(true);
        label_Laser1 = new QLabel(AutoProduWidget);
        label_Laser1->setObjectName(QStringLiteral("label_Laser1"));
        label_Laser1->setGeometry(QRect(310, 190, 120, 120));
        label_Laser1->setFrameShape(QFrame::NoFrame);
        label_Laser1->setPixmap(QPixmap(QString::fromUtf8(":/FilmTrimmer/Image/2.png")));
        label_Laser1->setScaledContents(true);
        label_Laser2 = new QLabel(AutoProduWidget);
        label_Laser2->setObjectName(QStringLiteral("label_Laser2"));
        label_Laser2->setGeometry(QRect(350, 300, 120, 120));
        label_Laser2->setFrameShape(QFrame::NoFrame);
        label_Laser2->setPixmap(QPixmap(QString::fromUtf8(":/FilmTrimmer/Image/2.png")));
        label_Laser2->setScaledContents(true);
        label_7 = new QLabel(AutoProduWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(420, 210, 70, 70));
        label_7->setStyleSheet(QStringLiteral("border:none"));
        label_7->setFrameShape(QFrame::NoFrame);
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/FilmTrimmer/Image/1.png")));
        label_7->setScaledContents(true);
        label_8 = new QLabel(AutoProduWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(470, 320, 70, 70));
        label_8->setFrameShape(QFrame::NoFrame);
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/FilmTrimmer/Image/1.png")));
        label_8->setScaledContents(true);
        label_MainAxis = new QLabel(AutoProduWidget);
        label_MainAxis->setObjectName(QStringLiteral("label_MainAxis"));
        label_MainAxis->setGeometry(QRect(660, 320, 70, 70));
        label_MainAxis->setFrameShape(QFrame::NoFrame);
        label_MainAxis->setPixmap(QPixmap(QString::fromUtf8(":/FilmTrimmer/Image/1.png")));
        label_MainAxis->setScaledContents(true);
        label_9 = new QLabel(AutoProduWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(130, 160, 30, 30));
        label_9->setFrameShape(QFrame::NoFrame);
        label_9->setPixmap(QPixmap(QString::fromUtf8(":/FilmTrimmer/Image/1.png")));
        label_9->setScaledContents(true);
        label_10 = new QLabel(AutoProduWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(780, 160, 30, 30));
        label_10->setFrameShape(QFrame::NoFrame);
        label_10->setPixmap(QPixmap(QString::fromUtf8(":/FilmTrimmer/Image/1.png")));
        label_10->setScaledContents(true);
        label_11 = new QLabel(AutoProduWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(520, 270, 30, 30));
        label_11->setFrameShape(QFrame::NoFrame);
        label_11->setPixmap(QPixmap(QString::fromUtf8(":/FilmTrimmer/Image/1.png")));
        label_11->setScaledContents(true);
        label_12 = new QLabel(AutoProduWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(340, 160, 101, 31));
        label_12->setStyleSheet(QLatin1String("border:3px groove gray;border-radius:8px;\n"
"background-color: rgb(250, 205, 137);\n"
"border-color: red;"));
        label_12->setFrameShape(QFrame::NoFrame);
        label_12->setScaledContents(true);
        label_2 = new QLabel(AutoProduWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 595, 71, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_2->setPalette(palette1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        label_2->setFont(font1);
        label_2->setFrameShape(QFrame::Box);
        label_13 = new QLabel(AutoProduWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(765, 598, 71, 21));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_13->setPalette(palette2);
        label_13->setFont(font1);
        LB_WorkSpeedSet = new QLabel(AutoProduWidget);
        LB_WorkSpeedSet->setObjectName(QStringLiteral("LB_WorkSpeedSet"));
        LB_WorkSpeedSet->setGeometry(QRect(660, 250, 71, 21));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_WorkSpeedSet->setPalette(palette3);
        LB_WorkSpeedSet->setFont(font1);
        label_15 = new QLabel(AutoProduWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(220, 80, 91, 21));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_15->setPalette(palette4);
        label_15->setFont(font1);
        label_16 = new QLabel(AutoProduWidget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(850, 80, 91, 21));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_16->setPalette(palette5);
        label_16->setFont(font1);
        LB_DataListShow = new QLabel(AutoProduWidget);
        LB_DataListShow->setObjectName(QStringLiteral("LB_DataListShow"));
        LB_DataListShow->setGeometry(QRect(935, 320, 18, 51));
        label_17 = new QLabel(AutoProduWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(180, 430, 130, 130));
        label_17->setFrameShape(QFrame::NoFrame);
        label_17->setPixmap(QPixmap(QString::fromUtf8(":/FilmTrimmer/Image/1.png")));
        label_17->setScaledContents(true);
        label_18 = new QLabel(AutoProduWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(640, 435, 130, 130));
        label_18->setFrameShape(QFrame::NoFrame);
        label_18->setPixmap(QPixmap(QString::fromUtf8(":/FilmTrimmer/Image/1.png")));
        label_18->setScaledContents(true);
        label_19 = new QLabel(AutoProduWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(60, 530, 41, 20));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_19->setPalette(palette6);
        label_19->setFont(font);
        widget = new QWidget(AutoProduWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(340, -1, 301, 120));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 127);"));
        label_23 = new QLabel(widget);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(0, 0, 60, 30));
        label_23->setFont(font);
        label_23->setStyleSheet(QLatin1String("QLabel{\n"
"     border-width: 1px;\n"
"     border-style: solid;\n"
"     border-color: rgb(255, 0, 0);\n"
"}"));
        label_23->setAlignment(Qt::AlignCenter);
        label_24 = new QLabel(widget);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(0, 30, 60, 30));
        label_24->setFont(font);
        label_24->setStyleSheet(QLatin1String("QLabel{\n"
"     border-width: 1px;\n"
"     border-style: solid;\n"
"     border-color: rgb(255, 0, 0);\n"
"}"));
        label_24->setAlignment(Qt::AlignCenter);
        label_25 = new QLabel(widget);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(0, 60, 60, 30));
        label_25->setFont(font);
        label_25->setStyleSheet(QLatin1String("QLabel{\n"
"     border-width: 1px;\n"
"     border-style: solid;\n"
"     border-color: rgb(255, 0, 0);\n"
"}"));
        label_25->setAlignment(Qt::AlignCenter);
        label_26 = new QLabel(widget);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(0, 90, 60, 30));
        label_26->setFont(font);
        label_26->setStyleSheet(QLatin1String("QLabel{\n"
"     border-width: 1px;\n"
"     border-style: solid;\n"
"     border-color: rgb(255, 0, 0);\n"
"}"));
        label_26->setAlignment(Qt::AlignCenter);
        LB_Laser1CurYield = new QLabel(widget);
        LB_Laser1CurYield->setObjectName(QStringLiteral("LB_Laser1CurYield"));
        LB_Laser1CurYield->setGeometry(QRect(60, 30, 120, 30));
        LB_Laser1CurYield->setFont(font);
        LB_Laser1CurYield->setStyleSheet(QLatin1String("QLabel{\n"
"     border-width: 1px;\n"
"     border-style: solid;\n"
"     border-color: rgb(255, 0, 0);\n"
"}"));
        LB_Laser1CurYield->setAlignment(Qt::AlignCenter);
        label_28 = new QLabel(widget);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(60, 0, 120, 30));
        label_28->setFont(font);
        label_28->setStyleSheet(QLatin1String("QLabel{\n"
"     border-width: 1px;\n"
"     border-style: solid;\n"
"     border-color: rgb(255, 0, 0);\n"
"}"));
        label_28->setAlignment(Qt::AlignCenter);
        LB_Laser2CurYield = new QLabel(widget);
        LB_Laser2CurYield->setObjectName(QStringLiteral("LB_Laser2CurYield"));
        LB_Laser2CurYield->setGeometry(QRect(60, 60, 120, 30));
        LB_Laser2CurYield->setFont(font);
        LB_Laser2CurYield->setStyleSheet(QLatin1String("QLabel{\n"
"     border-width: 1px;\n"
"     border-style: solid;\n"
"     border-color: rgb(255, 0, 0);\n"
"}"));
        LB_Laser2CurYield->setAlignment(Qt::AlignCenter);
        LB_LaserCurSumYield = new QLabel(widget);
        LB_LaserCurSumYield->setObjectName(QStringLiteral("LB_LaserCurSumYield"));
        LB_LaserCurSumYield->setGeometry(QRect(60, 90, 120, 30));
        LB_LaserCurSumYield->setFont(font);
        LB_LaserCurSumYield->setStyleSheet(QLatin1String("QLabel{\n"
"     border-width: 1px;\n"
"     border-style: solid;\n"
"     border-color: rgb(255, 0, 0);\n"
"}"));
        LB_LaserCurSumYield->setAlignment(Qt::AlignCenter);
        LB_Laser1SumYield = new QLabel(widget);
        LB_Laser1SumYield->setObjectName(QStringLiteral("LB_Laser1SumYield"));
        LB_Laser1SumYield->setGeometry(QRect(180, 30, 120, 30));
        LB_Laser1SumYield->setFont(font);
        LB_Laser1SumYield->setStyleSheet(QLatin1String("QLabel{\n"
"     border-width: 1px;\n"
"     border-style: solid;\n"
"     border-color: rgb(255, 0, 0);\n"
"}"));
        LB_Laser1SumYield->setAlignment(Qt::AlignCenter);
        LB_Laser2SumYield = new QLabel(widget);
        LB_Laser2SumYield->setObjectName(QStringLiteral("LB_Laser2SumYield"));
        LB_Laser2SumYield->setGeometry(QRect(180, 60, 120, 30));
        LB_Laser2SumYield->setFont(font);
        LB_Laser2SumYield->setStyleSheet(QLatin1String("QLabel{\n"
"     border-width: 1px;\n"
"     border-style: solid;\n"
"     border-color: rgb(255, 0, 0);\n"
"}"));
        LB_Laser2SumYield->setAlignment(Qt::AlignCenter);
        label_33 = new QLabel(widget);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(180, 0, 120, 30));
        label_33->setFont(font);
        label_33->setStyleSheet(QLatin1String("QLabel{\n"
"     border-width: 1px;\n"
"     border-style: solid;\n"
"     border-color: rgb(255, 0, 0);\n"
"}"));
        label_33->setAlignment(Qt::AlignCenter);
        LB_LaserSumYield = new QLabel(widget);
        LB_LaserSumYield->setObjectName(QStringLiteral("LB_LaserSumYield"));
        LB_LaserSumYield->setGeometry(QRect(180, 90, 120, 30));
        LB_LaserSumYield->setFont(font);
        LB_LaserSumYield->setStyleSheet(QLatin1String("QLabel{\n"
"     border-width: 1px;\n"
"     border-style: solid;\n"
"     border-color: rgb(255, 0, 0);\n"
"}"));
        LB_LaserSumYield->setAlignment(Qt::AlignCenter);
        label_28->raise();
        label_33->raise();
        LB_Laser1CurYield->raise();
        LB_Laser1SumYield->raise();
        LB_Laser2SumYield->raise();
        label_25->raise();
        LB_Laser2CurYield->raise();
        LB_LaserCurSumYield->raise();
        label_24->raise();
        LB_LaserSumYield->raise();
        label_26->raise();
        label_23->raise();
        PB_CleanYield = new QPushButton(AutoProduWidget);
        PB_CleanYield->setObjectName(QStringLiteral("PB_CleanYield"));
        PB_CleanYield->setGeometry(QRect(639, 0, 51, 120));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_CleanYield->setPalette(palette7);
        PB_CleanYield->setFont(font);
        PB_CleanYield->setStyleSheet(QStringLiteral(""));
        PB_MainAxisFW = new QPushButton(AutoProduWidget);
        PB_MainAxisFW->setObjectName(QStringLiteral("PB_MainAxisFW"));
        PB_MainAxisFW->setGeometry(QRect(595, 392, 91, 30));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_MainAxisFW->setPalette(palette8);
        PB_MainAxisFW->setFont(font);
        PB_MainAxisRE = new QPushButton(AutoProduWidget);
        PB_MainAxisRE->setObjectName(QStringLiteral("PB_MainAxisRE"));
        PB_MainAxisRE->setGeometry(QRect(700, 392, 91, 30));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_MainAxisRE->setPalette(palette9);
        PB_MainAxisRE->setFont(font);
        label_35 = new QLabel(AutoProduWidget);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(679, 362, 31, 20));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_35->setPalette(palette10);
        label_35->setFont(font);
        label_20 = new QLabel(AutoProduWidget);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(230, 530, 41, 20));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_20->setPalette(palette11);
        label_20->setFont(font);
        label_22 = new QLabel(AutoProduWidget);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(686, 533, 41, 20));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_22->setPalette(palette12);
        label_22->setFont(font);
        PB_SendloadFW = new QPushButton(AutoProduWidget);
        PB_SendloadFW->setObjectName(QStringLiteral("PB_SendloadFW"));
        PB_SendloadFW->setGeometry(QRect(30, 562, 91, 30));
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_SendloadFW->setPalette(palette13);
        PB_SendloadFW->setFont(font);
        PB_SendloadRE = new QPushButton(AutoProduWidget);
        PB_SendloadRE->setObjectName(QStringLiteral("PB_SendloadRE"));
        PB_SendloadRE->setGeometry(QRect(200, 562, 91, 30));
        QPalette palette14;
        palette14.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_SendloadRE->setPalette(palette14);
        PB_SendloadRE->setFont(font);
        PB_RecvloadFW = new QPushButton(AutoProduWidget);
        PB_RecvloadFW->setObjectName(QStringLiteral("PB_RecvloadFW"));
        PB_RecvloadFW->setGeometry(QRect(660, 567, 91, 30));
        QPalette palette15;
        palette15.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_RecvloadFW->setPalette(palette15);
        PB_RecvloadFW->setFont(font);
        PB_RecvloadRE = new QPushButton(AutoProduWidget);
        PB_RecvloadRE->setObjectName(QStringLiteral("PB_RecvloadRE"));
        PB_RecvloadRE->setGeometry(QRect(830, 567, 91, 30));
        QPalette palette16;
        palette16.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_RecvloadRE->setPalette(palette16);
        PB_RecvloadRE->setFont(font);
        LB_Laser1Step = new QLabel(AutoProduWidget);
        LB_Laser1Step->setObjectName(QStringLiteral("LB_Laser1Step"));
        LB_Laser1Step->setGeometry(QRect(360, 280, 61, 30));
        QPalette palette17;
        palette17.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette17.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_Laser1Step->setPalette(palette17);
        LB_Laser1Step->setFont(font);
        label_38 = new QLabel(AutoProduWidget);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setGeometry(QRect(281, 280, 81, 30));
        QPalette palette18;
        palette18.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette18.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_38->setPalette(palette18);
        label_38->setFont(font);
        label_27 = new QLabel(AutoProduWidget);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(321, 390, 81, 30));
        QPalette palette19;
        palette19.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette19.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette19.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_27->setPalette(palette19);
        label_27->setFont(font);
        LB_Laser2Step = new QLabel(AutoProduWidget);
        LB_Laser2Step->setObjectName(QStringLiteral("LB_Laser2Step"));
        LB_Laser2Step->setGeometry(QRect(400, 390, 81, 30));
        QPalette palette20;
        palette20.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette20.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette20.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_Laser2Step->setPalette(palette20);
        LB_Laser2Step->setFont(font);
        Btn_Put = new QPushButton(AutoProduWidget);
        Btn_Put->setObjectName(QStringLiteral("Btn_Put"));
        Btn_Put->setGeometry(QRect(30, 160, 91, 31));
        Btn_Get = new QPushButton(AutoProduWidget);
        Btn_Get->setObjectName(QStringLiteral("Btn_Get"));
        Btn_Get->setGeometry(QRect(820, 160, 81, 31));
        label_40 = new QLabel(AutoProduWidget);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setGeometry(QRect(859, 534, 41, 20));
        QPalette palette21;
        palette21.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette21.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette21.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_40->setPalette(palette21);
        label_40->setFont(font);
        LB_Background1 = new QLabel(AutoProduWidget);
        LB_Background1->setObjectName(QStringLiteral("LB_Background1"));
        LB_Background1->setGeometry(QRect(690, 40, 261, 581));
        LB_Background1->setFrameShape(QFrame::NoFrame);
        TRW_ModuleTree = new QTreeWidget(AutoProduWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        TRW_ModuleTree->setHeaderItem(__qtreewidgetitem);
        TRW_ModuleTree->setObjectName(QStringLiteral("TRW_ModuleTree"));
        TRW_ModuleTree->setEnabled(true);
        TRW_ModuleTree->setGeometry(QRect(690, 40, 261, 581));
        QPalette palette22;
        palette22.setBrush(QPalette::Active, QPalette::Text, brush);
        palette22.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette22.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette22.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette22.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette22.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        TRW_ModuleTree->setPalette(palette22);
        TRW_ModuleTree->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        PB_RunDirection = new QPushButton(AutoProduWidget);
        PB_RunDirection->setObjectName(QStringLiteral("PB_RunDirection"));
        PB_RunDirection->setGeometry(QRect(390, 600, 121, 41));
        QPalette palette23;
        palette23.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette23.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette23.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_RunDirection->setPalette(palette23);
        PB_RunDirection->setFont(font);
        PB_OnloadDirection = new QPushButton(AutoProduWidget);
        PB_OnloadDirection->setObjectName(QStringLiteral("PB_OnloadDirection"));
        PB_OnloadDirection->setGeometry(QRect(530, 600, 121, 41));
        QPalette palette24;
        palette24.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette24.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette24.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_OnloadDirection->setPalette(palette24);
        PB_OnloadDirection->setFont(font);
        LCD_OnloadDiameter = new QLabel(AutoProduWidget);
        LCD_OnloadDiameter->setObjectName(QStringLiteral("LCD_OnloadDiameter"));
        LCD_OnloadDiameter->setGeometry(QRect(120, 620, 91, 20));
        QPalette palette25;
        palette25.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette25.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette25.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LCD_OnloadDiameter->setPalette(palette25);
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(11);
        LCD_OnloadDiameter->setFont(font2);
        LCD_OnloadDiameter->setAlignment(Qt::AlignCenter);
        LCD_OnloadTension = new QLabel(AutoProduWidget);
        LCD_OnloadTension->setObjectName(QStringLiteral("LCD_OnloadTension"));
        LCD_OnloadTension->setGeometry(QRect(215, 102, 91, 20));
        QPalette palette26;
        palette26.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette26.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette26.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LCD_OnloadTension->setPalette(palette26);
        LCD_OnloadTension->setFont(font2);
        LCD_OnloadTension->setAlignment(Qt::AlignCenter);
        LCD_WorkSpeedShow = new QLabel(AutoProduWidget);
        LCD_WorkSpeedShow->setObjectName(QStringLiteral("LCD_WorkSpeedShow"));
        LCD_WorkSpeedShow->setGeometry(QRect(647, 270, 91, 20));
        QPalette palette27;
        palette27.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette27.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette27.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LCD_WorkSpeedShow->setPalette(palette27);
        LCD_WorkSpeedShow->setFont(font2);
        LCD_WorkSpeedShow->setAlignment(Qt::AlignCenter);
        LCD_RecvTension = new QLabel(AutoProduWidget);
        LCD_RecvTension->setObjectName(QStringLiteral("LCD_RecvTension"));
        LCD_RecvTension->setGeometry(QRect(844, 101, 91, 20));
        QPalette palette28;
        palette28.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette28.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette28.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LCD_RecvTension->setPalette(palette28);
        LCD_RecvTension->setFont(font2);
        LCD_RecvTension->setAlignment(Qt::AlignCenter);
        LCD_RecvDiameter = new QLabel(AutoProduWidget);
        LCD_RecvDiameter->setObjectName(QStringLiteral("LCD_RecvDiameter"));
        LCD_RecvDiameter->setGeometry(QRect(754, 620, 91, 20));
        QPalette palette29;
        palette29.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette29.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette29.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LCD_RecvDiameter->setPalette(palette29);
        LCD_RecvDiameter->setFont(font2);
        LCD_RecvDiameter->setAlignment(Qt::AlignCenter);
        LCD_WorkSpeedShow->raise();
        LCD_RecvTension->raise();
        LB_Info->raise();
        label->raise();
        label_3->raise();
        label_Laser1->raise();
        label_Laser2->raise();
        label_7->raise();
        label_8->raise();
        label_MainAxis->raise();
        label_9->raise();
        label_10->raise();
        label_11->raise();
        label_12->raise();
        label_2->raise();
        label_13->raise();
        LB_WorkSpeedSet->raise();
        label_15->raise();
        label_16->raise();
        LB_DataListShow->raise();
        label_17->raise();
        label_18->raise();
        label_19->raise();
        widget->raise();
        PB_MainAxisFW->raise();
        PB_MainAxisRE->raise();
        label_35->raise();
        label_20->raise();
        label_22->raise();
        PB_SendloadFW->raise();
        PB_SendloadRE->raise();
        PB_RecvloadFW->raise();
        PB_RecvloadRE->raise();
        LB_Laser1Step->raise();
        label_38->raise();
        label_27->raise();
        LB_Laser2Step->raise();
        Btn_Put->raise();
        Btn_Get->raise();
        label_40->raise();
        PB_CleanYield->raise();
        LB_Background1->raise();
        TRW_ModuleTree->raise();
        PB_RunDirection->raise();
        PB_OnloadDirection->raise();
        LCD_OnloadDiameter->raise();
        LCD_OnloadTension->raise();
        LCD_RecvDiameter->raise();

        retranslateUi(AutoProduWidget);

        QMetaObject::connectSlotsByName(AutoProduWidget);
    } // setupUi

    void retranslateUi(QWidget *AutoProduWidget)
    {
        AutoProduWidget->setWindowTitle(QApplication::translate("AutoProduWidget", "Form", 0));
        LB_Info->setText(QApplication::translate("AutoProduWidget", "\350\207\252\345\212\250\347\224\237\344\272\247\347\233\270\345\205\263\346\225\260\346\215\256", 0));
        label->setText(QString());
        label_3->setText(QString());
        label_Laser1->setText(QString());
        label_Laser2->setText(QString());
        label_7->setText(QString());
        label_8->setText(QString());
        label_MainAxis->setText(QString());
        label_9->setText(QString());
        label_10->setText(QString());
        label_11->setText(QString());
        label_12->setText(QString());
        label_2->setText(QApplication::translate("AutoProduWidget", "\346\224\276\345\215\267\345\215\267\345\276\204", 0));
        label_13->setText(QApplication::translate("AutoProduWidget", "\346\224\266\345\215\267\345\215\267\345\276\204", 0));
        LB_WorkSpeedSet->setText(QApplication::translate("AutoProduWidget", "\345\267\245\344\275\234\351\200\237\345\272\246", 0));
        label_15->setText(QApplication::translate("AutoProduWidget", "\346\224\276\345\215\267\345\212\233\350\207\202\344\275\215", 0));
        label_16->setText(QApplication::translate("AutoProduWidget", "\346\224\266\345\215\267\345\212\233\350\207\202\344\275\215", 0));
        LB_DataListShow->setText(QString());
        label_17->setText(QString());
        label_18->setText(QString());
        label_19->setText(QApplication::translate("AutoProduWidget", "\346\224\276\345\215\267A", 0));
        label_23->setText(QApplication::translate("AutoProduWidget", "\345\267\245\344\275\215", 0));
        label_24->setText(QApplication::translate("AutoProduWidget", "\346\277\200\345\205\2111", 0));
        label_25->setText(QApplication::translate("AutoProduWidget", "\346\277\200\345\205\2112", 0));
        label_26->setText(QApplication::translate("AutoProduWidget", "\346\200\273\346\225\260", 0));
        LB_Laser1CurYield->setText(QApplication::translate("AutoProduWidget", "30", 0));
        label_28->setText(QApplication::translate("AutoProduWidget", "\345\275\223\347\217\255\344\272\247\351\207\217", 0));
        LB_Laser2CurYield->setText(QApplication::translate("AutoProduWidget", "30", 0));
        LB_LaserCurSumYield->setText(QApplication::translate("AutoProduWidget", "60", 0));
        LB_Laser1SumYield->setText(QApplication::translate("AutoProduWidget", "1000", 0));
        LB_Laser2SumYield->setText(QApplication::translate("AutoProduWidget", "1000", 0));
        label_33->setText(QApplication::translate("AutoProduWidget", "\346\200\273\344\272\247\351\207\217", 0));
        LB_LaserSumYield->setText(QApplication::translate("AutoProduWidget", " 60", 0));
        PB_CleanYield->setText(QApplication::translate("AutoProduWidget", "\346\270\205\n"
"\351\231\244\n"
"\344\272\247\n"
"\351\207\217", 0));
        PB_MainAxisFW->setText(QApplication::translate("AutoProduWidget", "\344\270\273\350\275\264\346\255\243\350\275\254", 0));
        PB_MainAxisRE->setText(QApplication::translate("AutoProduWidget", "\344\270\273\350\275\264\345\217\215\350\275\254", 0));
        label_35->setText(QApplication::translate("AutoProduWidget", " \344\270\273\350\275\264", 0));
        label_20->setText(QApplication::translate("AutoProduWidget", "\346\224\276\345\215\267B", 0));
        label_22->setText(QApplication::translate("AutoProduWidget", "\346\224\266\345\215\267A", 0));
        PB_SendloadFW->setText(QApplication::translate("AutoProduWidget", "\346\224\276\345\215\267\346\255\243\350\275\254", 0));
        PB_SendloadRE->setText(QApplication::translate("AutoProduWidget", "\346\224\276\345\215\267\345\217\215\350\275\254", 0));
        PB_RecvloadFW->setText(QApplication::translate("AutoProduWidget", "\346\224\266\345\215\267\346\255\243\350\275\254", 0));
        PB_RecvloadRE->setText(QApplication::translate("AutoProduWidget", "\346\224\266\345\215\267\345\217\215\350\275\254", 0));
        LB_Laser1Step->setText(QApplication::translate("AutoProduWidget", "60", 0));
        label_38->setText(QApplication::translate("AutoProduWidget", " \346\277\200\345\205\2111\346\255\245\346\225\260\357\274\232", 0));
        label_27->setText(QApplication::translate("AutoProduWidget", " \346\277\200\345\205\2112\346\255\245\346\225\260\357\274\232", 0));
        LB_Laser2Step->setText(QApplication::translate("AutoProduWidget", "60", 0));
        Btn_Put->setText(QApplication::translate("AutoProduWidget", "\346\224\276\345\215\267PID", 0));
        Btn_Get->setText(QApplication::translate("AutoProduWidget", "\346\224\266\345\215\267PID", 0));
        label_40->setText(QApplication::translate("AutoProduWidget", "\346\224\266\345\215\267B", 0));
        LB_Background1->setText(QString());
        PB_RunDirection->setText(QApplication::translate("AutoProduWidget", "\346\255\243\345\220\221\350\277\220\350\241\214", 0));
        PB_OnloadDirection->setText(QApplication::translate("AutoProduWidget", "\351\241\272\346\227\266\351\222\210\346\224\276\345\215\267", 0));
        LCD_OnloadDiameter->setText(QApplication::translate("AutoProduWidget", "TextLabel", 0));
        LCD_OnloadTension->setText(QApplication::translate("AutoProduWidget", "TextLabel", 0));
        LCD_WorkSpeedShow->setText(QApplication::translate("AutoProduWidget", "TextLabel", 0));
        LCD_RecvTension->setText(QApplication::translate("AutoProduWidget", "TextLabel", 0));
        LCD_RecvDiameter->setText(QApplication::translate("AutoProduWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class AutoProduWidget: public Ui_AutoProduWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_AUTOPRODUCTION_H
