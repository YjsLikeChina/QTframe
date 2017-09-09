/********************************************************************************
** Form generated from reading UI file 'UI_IODebug.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_IODEBUG_H
#define UI_UI_IODEBUG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IODebugWidget
{
public:
    QLabel *LB_ModuleName;
    QLabel *LB_InputName;
    QLabel *LB_OutputName;
    QListWidget *LW_InputList;
    QListWidget *LW_OutputList;
    QLabel *LB_Background1;
    QListWidget *LW_ModuleList;

    void setupUi(QWidget *IODebugWidget)
    {
        if (IODebugWidget->objectName().isEmpty())
            IODebugWidget->setObjectName(QStringLiteral("IODebugWidget"));
        IODebugWidget->resize(950, 649);
        IODebugWidget->setMinimumSize(QSize(950, 649));
        IODebugWidget->setMaximumSize(QSize(950, 649));
        LB_ModuleName = new QLabel(IODebugWidget);
        LB_ModuleName->setObjectName(QStringLiteral("LB_ModuleName"));
        LB_ModuleName->setGeometry(QRect(100, 7, 61, 21));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_ModuleName->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        LB_ModuleName->setFont(font);
        LB_InputName = new QLabel(IODebugWidget);
        LB_InputName->setObjectName(QStringLiteral("LB_InputName"));
        LB_InputName->setGeometry(QRect(440, 7, 51, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_InputName->setPalette(palette1);
        LB_InputName->setFont(font);
        LB_OutputName = new QLabel(IODebugWidget);
        LB_OutputName->setObjectName(QStringLiteral("LB_OutputName"));
        LB_OutputName->setGeometry(QRect(770, 10, 51, 21));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        LB_OutputName->setPalette(palette2);
        LB_OutputName->setFont(font);
        LW_InputList = new QListWidget(IODebugWidget);
        LW_InputList->setObjectName(QStringLiteral("LW_InputList"));
        LW_InputList->setGeometry(QRect(320, 35, 291, 601));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        LW_InputList->setPalette(palette3);
        QFont font1;
        font1.setPointSize(11);
        LW_InputList->setFont(font1);
        LW_InputList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        LW_OutputList = new QListWidget(IODebugWidget);
        LW_OutputList->setObjectName(QStringLiteral("LW_OutputList"));
        LW_OutputList->setGeometry(QRect(640, 35, 291, 601));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        LW_OutputList->setPalette(palette4);
        LW_OutputList->setFont(font1);
        LW_OutputList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        LB_Background1 = new QLabel(IODebugWidget);
        LB_Background1->setObjectName(QStringLiteral("LB_Background1"));
        LB_Background1->setGeometry(QRect(0, 35, 291, 601));
        LB_Background1->setFrameShape(QFrame::NoFrame);
        LW_ModuleList = new QListWidget(IODebugWidget);
        LW_ModuleList->setObjectName(QStringLiteral("LW_ModuleList"));
        LW_ModuleList->setGeometry(QRect(0, 35, 291, 601));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Text, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        LW_ModuleList->setPalette(palette5);
        LW_ModuleList->setFont(font1);
        LW_ModuleList->setFocusPolicy(Qt::ClickFocus);
        LW_ModuleList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        LW_ModuleList->setEditTriggers(QAbstractItemView::NoEditTriggers);

        retranslateUi(IODebugWidget);

        QMetaObject::connectSlotsByName(IODebugWidget);
    } // setupUi

    void retranslateUi(QWidget *IODebugWidget)
    {
        IODebugWidget->setWindowTitle(QApplication::translate("IODebugWidget", "Form", 0));
        LB_ModuleName->setText(QApplication::translate("IODebugWidget", "\346\250\241\347\273\204\345\220\215\347\247\260", 0));
        LB_InputName->setText(QApplication::translate("IODebugWidget", "\350\276\223\345\205\245\347\202\271", 0));
        LB_OutputName->setText(QApplication::translate("IODebugWidget", "\350\276\223\345\207\272\347\202\271", 0));
        LB_Background1->setText(QApplication::translate("IODebugWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class IODebugWidget: public Ui_IODebugWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_IODEBUG_H
