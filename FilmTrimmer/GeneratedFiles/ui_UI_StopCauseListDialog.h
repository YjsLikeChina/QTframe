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
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StopCauseListDialog
{
public:
    QTextEdit *TE_Alarm_Info;
    QLabel *LB_Background1;
    QLabel *LB_Background2;
    QLabel *LB_Background3;
    QLabel *LB_Background4;
    QLabel *LB_Background5;
    QScrollArea *LW_StopCauseList1;
    QWidget *scrollAreaWidgetContents;
    QScrollArea *LW_StopCauseList2;
    QWidget *scrollAreaWidgetContents_2;
    QScrollArea *LW_StopCauseList3;
    QWidget *scrollAreaWidgetContents_3;
    QScrollArea *LW_StopCauseList4;
    QWidget *scrollAreaWidgetContents_4;
    QScrollArea *LW_StopCauseList5;
    QWidget *scrollAreaWidgetContents_5;

    void setupUi(QDialog *StopCauseListDialog)
    {
        if (StopCauseListDialog->objectName().isEmpty())
            StopCauseListDialog->setObjectName(QStringLiteral("StopCauseListDialog"));
        StopCauseListDialog->resize(829, 405);
        TE_Alarm_Info = new QTextEdit(StopCauseListDialog);
        TE_Alarm_Info->setObjectName(QStringLiteral("TE_Alarm_Info"));
        TE_Alarm_Info->setGeometry(QRect(20, 330, 791, 71));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(0, 85, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        QBrush brush3(QColor(240, 240, 240, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        TE_Alarm_Info->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        TE_Alarm_Info->setFont(font);
        LB_Background1 = new QLabel(StopCauseListDialog);
        LB_Background1->setObjectName(QStringLiteral("LB_Background1"));
        LB_Background1->setGeometry(QRect(20, 10, 131, 311));
        LB_Background1->setStyleSheet(QStringLiteral("background:rgb(170, 255, 127)"));
        LB_Background1->setFrameShape(QFrame::NoFrame);
        LB_Background2 = new QLabel(StopCauseListDialog);
        LB_Background2->setObjectName(QStringLiteral("LB_Background2"));
        LB_Background2->setGeometry(QRect(185, 10, 131, 311));
        LB_Background2->setStyleSheet(QStringLiteral("background:rgb(0, 85, 255)"));
        LB_Background2->setFrameShape(QFrame::NoFrame);
        LB_Background3 = new QLabel(StopCauseListDialog);
        LB_Background3->setObjectName(QStringLiteral("LB_Background3"));
        LB_Background3->setGeometry(QRect(350, 10, 131, 311));
        LB_Background3->setStyleSheet(QStringLiteral("background:rgb(83, 201, 255)"));
        LB_Background3->setFrameShape(QFrame::NoFrame);
        LB_Background4 = new QLabel(StopCauseListDialog);
        LB_Background4->setObjectName(QStringLiteral("LB_Background4"));
        LB_Background4->setGeometry(QRect(515, 10, 131, 311));
        LB_Background4->setStyleSheet(QStringLiteral("background:rgb(255, 85, 0)"));
        LB_Background4->setFrameShape(QFrame::NoFrame);
        LB_Background5 = new QLabel(StopCauseListDialog);
        LB_Background5->setObjectName(QStringLiteral("LB_Background5"));
        LB_Background5->setGeometry(QRect(680, 10, 131, 311));
        LB_Background5->setStyleSheet(QStringLiteral("background:rgb(170, 255, 255)"));
        LB_Background5->setFrameShape(QFrame::NoFrame);
        LW_StopCauseList1 = new QScrollArea(StopCauseListDialog);
        LW_StopCauseList1->setObjectName(QStringLiteral("LW_StopCauseList1"));
        LW_StopCauseList1->setGeometry(QRect(20, 10, 131, 311));
        LW_StopCauseList1->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 129, 309));
        LW_StopCauseList1->setWidget(scrollAreaWidgetContents);
        LW_StopCauseList2 = new QScrollArea(StopCauseListDialog);
        LW_StopCauseList2->setObjectName(QStringLiteral("LW_StopCauseList2"));
        LW_StopCauseList2->setGeometry(QRect(185, 10, 131, 311));
        LW_StopCauseList2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 129, 309));
        LW_StopCauseList2->setWidget(scrollAreaWidgetContents_2);
        LW_StopCauseList3 = new QScrollArea(StopCauseListDialog);
        LW_StopCauseList3->setObjectName(QStringLiteral("LW_StopCauseList3"));
        LW_StopCauseList3->setGeometry(QRect(350, 10, 131, 311));
        LW_StopCauseList3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 129, 309));
        LW_StopCauseList3->setWidget(scrollAreaWidgetContents_3);
        LW_StopCauseList4 = new QScrollArea(StopCauseListDialog);
        LW_StopCauseList4->setObjectName(QStringLiteral("LW_StopCauseList4"));
        LW_StopCauseList4->setGeometry(QRect(515, 10, 131, 311));
        LW_StopCauseList4->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QStringLiteral("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 129, 309));
        LW_StopCauseList4->setWidget(scrollAreaWidgetContents_4);
        LW_StopCauseList5 = new QScrollArea(StopCauseListDialog);
        LW_StopCauseList5->setObjectName(QStringLiteral("LW_StopCauseList5"));
        LW_StopCauseList5->setGeometry(QRect(680, 10, 131, 311));
        LW_StopCauseList5->setWidgetResizable(true);
        scrollAreaWidgetContents_5 = new QWidget();
        scrollAreaWidgetContents_5->setObjectName(QStringLiteral("scrollAreaWidgetContents_5"));
        scrollAreaWidgetContents_5->setGeometry(QRect(0, 0, 129, 309));
        LW_StopCauseList5->setWidget(scrollAreaWidgetContents_5);
        LB_Background5->raise();
        LB_Background4->raise();
        LB_Background3->raise();
        TE_Alarm_Info->raise();
        LB_Background1->raise();
        LB_Background2->raise();
        LW_StopCauseList1->raise();
        LW_StopCauseList2->raise();
        LW_StopCauseList3->raise();
        LW_StopCauseList4->raise();
        LW_StopCauseList5->raise();

        retranslateUi(StopCauseListDialog);

        QMetaObject::connectSlotsByName(StopCauseListDialog);
    } // setupUi

    void retranslateUi(QDialog *StopCauseListDialog)
    {
        StopCauseListDialog->setWindowTitle(QApplication::translate("StopCauseListDialog", "\351\200\211\346\213\251\345\201\234\346\234\272\345\216\237\345\233\240", 0));
        TE_Alarm_Info->setHtml(QApplication::translate("StopCauseListDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        LB_Background1->setText(QString());
        LB_Background2->setText(QString());
        LB_Background3->setText(QString());
        LB_Background4->setText(QString());
        LB_Background5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StopCauseListDialog: public Ui_StopCauseListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_STOPCAUSELISTDIALOG_H
