/********************************************************************************
** Form generated from reading UI file 'UI_filmtrimmer.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_FILMTRIMMER_H
#define UI_UI_FILMTRIMMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FrameWidget
{
public:
    QWidget *centralWidget;
    QStackedWidget *SW_ClientWidget;
    QWidget *page;
    QWidget *page_2;
    QLabel *LB_Show3;
    QLabel *LB_AlarmOrError_Show;
    QLabel *LB_Show2;
    QLabel *LB_Show1;
    QLabel *LB_MachineStatusCtrl;
    QPushButton *PB_MachineStart;
    QPushButton *PB_MachineStop;
    QPushButton *PB_MachineReset;
    QPushButton *PB_MachineEStop;
    QPushButton *PB_UserLogin;
    QLabel *LB_SystemTime;
    QLabel *LB_CtrlShow;
    QLabel *LB_CtrlHide;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *HL_PageButtonLayout;
    QLabel *LB_OperatorHintText;
    QLabel *LB_MachineStatusShow;
    QLabel *LB_MachineOperatorHint;
    QLabel *LB_MachineModelLabel;
    QLabel *LB_MachineModel;
    QLabel *LB_AlarmOrError_Text;

    void setupUi(QMainWindow *FrameWidget)
    {
        if (FrameWidget->objectName().isEmpty())
            FrameWidget->setObjectName(QStringLiteral("FrameWidget"));
        FrameWidget->resize(1024, 768);
        FrameWidget->setMinimumSize(QSize(1024, 768));
        FrameWidget->setMaximumSize(QSize(1024, 768));
        centralWidget = new QWidget(FrameWidget);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SW_ClientWidget = new QStackedWidget(centralWidget);
        SW_ClientWidget->setObjectName(QStringLiteral("SW_ClientWidget"));
        SW_ClientWidget->setGeometry(QRect(0, 60, 951, 651));
        SW_ClientWidget->setFrameShape(QFrame::NoFrame);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        SW_ClientWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        SW_ClientWidget->addWidget(page_2);
        LB_Show3 = new QLabel(centralWidget);
        LB_Show3->setObjectName(QStringLiteral("LB_Show3"));
        LB_Show3->setGeometry(QRect(0, 0, 1031, 51));
        LB_Show3->setFrameShape(QFrame::NoFrame);
        LB_AlarmOrError_Show = new QLabel(centralWidget);
        LB_AlarmOrError_Show->setObjectName(QStringLiteral("LB_AlarmOrError_Show"));
        LB_AlarmOrError_Show->setGeometry(QRect(250, 8, 551, 35));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_AlarmOrError_Show->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        LB_AlarmOrError_Show->setFont(font);
        LB_AlarmOrError_Show->setFrameShape(QFrame::NoFrame);
        LB_AlarmOrError_Show->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LB_Show2 = new QLabel(centralWidget);
        LB_Show2->setObjectName(QStringLiteral("LB_Show2"));
        LB_Show2->setGeometry(QRect(830, 14, 70, 20));
        LB_Show2->setFrameShape(QFrame::NoFrame);
        LB_Show1 = new QLabel(centralWidget);
        LB_Show1->setObjectName(QStringLiteral("LB_Show1"));
        LB_Show1->setGeometry(QRect(150, 14, 70, 20));
        LB_Show1->setFrameShape(QFrame::NoFrame);
        LB_MachineStatusCtrl = new QLabel(centralWidget);
        LB_MachineStatusCtrl->setObjectName(QStringLiteral("LB_MachineStatusCtrl"));
        LB_MachineStatusCtrl->setGeometry(QRect(0, 709, 1024, 61));
        LB_MachineStatusCtrl->setFrameShape(QFrame::NoFrame);
        PB_MachineStart = new QPushButton(centralWidget);
        PB_MachineStart->setObjectName(QStringLiteral("PB_MachineStart"));
        PB_MachineStart->setGeometry(QRect(10, 717, 105, 45));
        QPalette palette1;
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_MachineStart->setPalette(palette1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(11);
        PB_MachineStart->setFont(font1);
        PB_MachineStop = new QPushButton(centralWidget);
        PB_MachineStop->setObjectName(QStringLiteral("PB_MachineStop"));
        PB_MachineStop->setGeometry(QRect(130, 717, 105, 45));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_MachineStop->setPalette(palette2);
        PB_MachineStop->setFont(font1);
        PB_MachineReset = new QPushButton(centralWidget);
        PB_MachineReset->setObjectName(QStringLiteral("PB_MachineReset"));
        PB_MachineReset->setGeometry(QRect(250, 717, 105, 45));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_MachineReset->setPalette(palette3);
        PB_MachineReset->setFont(font1);
        PB_MachineEStop = new QPushButton(centralWidget);
        PB_MachineEStop->setObjectName(QStringLiteral("PB_MachineEStop"));
        PB_MachineEStop->setGeometry(QRect(370, 717, 105, 45));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_MachineEStop->setPalette(palette4);
        PB_MachineEStop->setFont(font1);
        PB_UserLogin = new QPushButton(centralWidget);
        PB_UserLogin->setObjectName(QStringLiteral("PB_UserLogin"));
        PB_UserLogin->setGeometry(QRect(9, 0, 141, 51));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_UserLogin->setPalette(palette5);
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(10);
        PB_UserLogin->setFont(font2);
        LB_SystemTime = new QLabel(centralWidget);
        LB_SystemTime->setObjectName(QStringLiteral("LB_SystemTime"));
        LB_SystemTime->setGeometry(QRect(820, 741, 191, 25));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_SystemTime->setPalette(palette6);
        LB_SystemTime->setFont(font2);
        LB_SystemTime->setLayoutDirection(Qt::RightToLeft);
        LB_SystemTime->setFrameShape(QFrame::NoFrame);
        LB_SystemTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LB_CtrlShow = new QLabel(centralWidget);
        LB_CtrlShow->setObjectName(QStringLiteral("LB_CtrlShow"));
        LB_CtrlShow->setGeometry(QRect(-3, 709, 20, 60));
        LB_CtrlShow->setFrameShape(QFrame::NoFrame);
        LB_CtrlHide = new QLabel(centralWidget);
        LB_CtrlHide->setObjectName(QStringLiteral("LB_CtrlHide"));
        LB_CtrlHide->setGeometry(QRect(480, 709, 20, 60));
        LB_CtrlHide->setFrameShape(QFrame::NoFrame);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(950, 50, 71, 651));
        HL_PageButtonLayout = new QVBoxLayout(verticalLayoutWidget);
        HL_PageButtonLayout->setSpacing(6);
        HL_PageButtonLayout->setContentsMargins(11, 11, 11, 11);
        HL_PageButtonLayout->setObjectName(QStringLiteral("HL_PageButtonLayout"));
        HL_PageButtonLayout->setContentsMargins(0, 0, 0, 0);
        LB_OperatorHintText = new QLabel(centralWidget);
        LB_OperatorHintText->setObjectName(QStringLiteral("LB_OperatorHintText"));
        LB_OperatorHintText->setGeometry(QRect(688, 738, 131, 28));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_OperatorHintText->setPalette(palette7);
        LB_OperatorHintText->setFont(font2);
        LB_OperatorHintText->setFrameShape(QFrame::NoFrame);
        LB_OperatorHintText->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LB_MachineStatusShow = new QLabel(centralWidget);
        LB_MachineStatusShow->setObjectName(QStringLiteral("LB_MachineStatusShow"));
        LB_MachineStatusShow->setGeometry(QRect(913, 9, 111, 31));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_MachineStatusShow->setPalette(palette8);
        LB_MachineStatusShow->setFont(font2);
        LB_MachineStatusShow->setFrameShape(QFrame::NoFrame);
        LB_MachineOperatorHint = new QLabel(centralWidget);
        LB_MachineOperatorHint->setObjectName(QStringLiteral("LB_MachineOperatorHint"));
        LB_MachineOperatorHint->setGeometry(QRect(625, 738, 61, 28));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_MachineOperatorHint->setPalette(palette9);
        LB_MachineOperatorHint->setFont(font2);
        LB_MachineOperatorHint->setFrameShape(QFrame::NoFrame);
        LB_MachineModelLabel = new QLabel(centralWidget);
        LB_MachineModelLabel->setObjectName(QStringLiteral("LB_MachineModelLabel"));
        LB_MachineModelLabel->setGeometry(QRect(624, 711, 61, 28));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_MachineModelLabel->setPalette(palette10);
        LB_MachineModelLabel->setFont(font2);
        LB_MachineModelLabel->setFrameShape(QFrame::NoFrame);
        LB_MachineModel = new QLabel(centralWidget);
        LB_MachineModel->setObjectName(QStringLiteral("LB_MachineModel"));
        LB_MachineModel->setGeometry(QRect(687, 711, 131, 28));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_MachineModel->setPalette(palette11);
        LB_MachineModel->setFont(font2);
        LB_MachineModel->setFrameShape(QFrame::NoFrame);
        LB_AlarmOrError_Text = new QLabel(centralWidget);
        LB_AlarmOrError_Text->setObjectName(QStringLiteral("LB_AlarmOrError_Text"));
        LB_AlarmOrError_Text->setGeometry(QRect(250, 8, 551, 35));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_AlarmOrError_Text->setPalette(palette12);
        LB_AlarmOrError_Text->setFont(font);
        LB_AlarmOrError_Text->setFrameShape(QFrame::NoFrame);
        LB_AlarmOrError_Text->setAlignment(Qt::AlignCenter);
        FrameWidget->setCentralWidget(centralWidget);

        retranslateUi(FrameWidget);

        SW_ClientWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FrameWidget);
    } // setupUi

    void retranslateUi(QMainWindow *FrameWidget)
    {
        FrameWidget->setWindowTitle(QApplication::translate("FrameWidget", "FilmTrimmer", 0));
        LB_Show3->setText(QString());
        LB_AlarmOrError_Show->setText(QApplication::translate("FrameWidget", "textLabel", 0));
        LB_Show2->setText(QApplication::translate("FrameWidget", "TextLabel", 0));
        LB_Show1->setText(QApplication::translate("FrameWidget", "TextLabel", 0));
        LB_MachineStatusCtrl->setText(QString());
        PB_MachineStart->setText(QApplication::translate("FrameWidget", "\345\220\257\345\212\250", 0));
        PB_MachineStop->setText(QApplication::translate("FrameWidget", "\345\201\234\346\255\242", 0));
        PB_MachineReset->setText(QApplication::translate("FrameWidget", "\345\244\215\344\275\215", 0));
        PB_MachineEStop->setText(QApplication::translate("FrameWidget", "\346\200\245\345\201\234", 0));
        PB_UserLogin->setText(QApplication::translate("FrameWidget", "\347\224\250\346\210\267\345\220\215:\346\223\215\344\275\234\345\221\230", 0));
        LB_SystemTime->setText(QApplication::translate("FrameWidget", "TextLabel", 0));
        LB_CtrlShow->setText(QApplication::translate("FrameWidget", "TextLabel", 0));
        LB_CtrlHide->setText(QApplication::translate("FrameWidget", "TextLabel", 0));
        LB_OperatorHintText->setText(QApplication::translate("FrameWidget", "\350\257\267\347\202\271\345\207\273\345\244\215\344\275\215\346\214\211\351\222\256", 0));
        LB_MachineStatusShow->setText(QApplication::translate("FrameWidget", "\345\274\200\345\247\213\347\212\266\346\200\201", 0));
        LB_MachineOperatorHint->setText(QApplication::translate("FrameWidget", "\346\223\215\344\275\234\346\217\220\347\244\272:", 0));
        LB_MachineModelLabel->setText(QApplication::translate("FrameWidget", "\350\256\276\345\244\207\346\250\241\345\274\217:", 0));
        LB_MachineModel->setText(QApplication::translate("FrameWidget", "\346\211\213\345\212\250\346\250\241\345\274\217", 0));
        LB_AlarmOrError_Text->setText(QApplication::translate("FrameWidget", "\346\212\245\350\255\246\346\230\276\347\244\272", 0));
    } // retranslateUi

};

namespace Ui {
    class FrameWidget: public Ui_FrameWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_FILMTRIMMER_H
