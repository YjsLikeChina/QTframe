/********************************************************************************
** Form generated from reading UI file 'UI_ParameterSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_PARAMETERSETTING_H
#define UI_UI_PARAMETERSETTING_H

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

class Ui_ParameterSettingWidget
{
public:
    QLabel *LB_Background1;
    QTreeWidget *TRW_DataModule;
    QLabel *LB_Background2;
    QTreeWidget *TRW_BoolModule;
    QLabel *LB_Background3;
    QPushButton *PB_ParamerSave;
    QPushButton *PB_LaserDataSet;
    QPushButton *PB_UserManage;
    QPushButton *PB_MESUploadSet;

    void setupUi(QWidget *ParameterSettingWidget)
    {
        if (ParameterSettingWidget->objectName().isEmpty())
            ParameterSettingWidget->setObjectName(QStringLiteral("ParameterSettingWidget"));
        ParameterSettingWidget->resize(950, 649);
        ParameterSettingWidget->setMinimumSize(QSize(950, 649));
        ParameterSettingWidget->setMaximumSize(QSize(950, 649));
        LB_Background1 = new QLabel(ParameterSettingWidget);
        LB_Background1->setObjectName(QStringLiteral("LB_Background1"));
        LB_Background1->setGeometry(QRect(0, 13, 461, 561));
        LB_Background1->setFrameShape(QFrame::NoFrame);
        TRW_DataModule = new QTreeWidget(ParameterSettingWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("\346\250\241\347\273\204\345\220\215"));
        TRW_DataModule->setHeaderItem(__qtreewidgetitem);
        TRW_DataModule->setObjectName(QStringLiteral("TRW_DataModule"));
        TRW_DataModule->setGeometry(QRect(20, 13, 421, 561));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        TRW_DataModule->setPalette(palette);
        QFont font;
        font.setPointSize(11);
        TRW_DataModule->setFont(font);
        TRW_DataModule->setFocusPolicy(Qt::NoFocus);
        TRW_DataModule->setContextMenuPolicy(Qt::NoContextMenu);
        TRW_DataModule->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        LB_Background2 = new QLabel(ParameterSettingWidget);
        LB_Background2->setObjectName(QStringLiteral("LB_Background2"));
        LB_Background2->setGeometry(QRect(488, 13, 491, 561));
        LB_Background2->setFrameShape(QFrame::NoFrame);
        TRW_BoolModule = new QTreeWidget(ParameterSettingWidget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("\346\250\241\347\273\204\345\220\215"));
        TRW_BoolModule->setHeaderItem(__qtreewidgetitem1);
        TRW_BoolModule->setObjectName(QStringLiteral("TRW_BoolModule"));
        TRW_BoolModule->setGeometry(QRect(510, 13, 421, 561));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        TRW_BoolModule->setPalette(palette1);
        TRW_BoolModule->setFont(font);
        TRW_BoolModule->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        LB_Background3 = new QLabel(ParameterSettingWidget);
        LB_Background3->setObjectName(QStringLiteral("LB_Background3"));
        LB_Background3->setGeometry(QRect(0, 592, 1021, 51));
        LB_Background3->setFrameShape(QFrame::NoFrame);
        PB_ParamerSave = new QPushButton(ParameterSettingWidget);
        PB_ParamerSave->setObjectName(QStringLiteral("PB_ParamerSave"));
        PB_ParamerSave->setGeometry(QRect(750, 597, 111, 41));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_ParamerSave->setPalette(palette2);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        PB_ParamerSave->setFont(font1);
        PB_LaserDataSet = new QPushButton(ParameterSettingWidget);
        PB_LaserDataSet->setObjectName(QStringLiteral("PB_LaserDataSet"));
        PB_LaserDataSet->setGeometry(QRect(110, 597, 121, 41));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_LaserDataSet->setPalette(palette3);
        PB_LaserDataSet->setFont(font1);
        PB_UserManage = new QPushButton(ParameterSettingWidget);
        PB_UserManage->setObjectName(QStringLiteral("PB_UserManage"));
        PB_UserManage->setGeometry(QRect(530, 600, 121, 41));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_UserManage->setPalette(palette4);
        PB_UserManage->setFont(font1);
        PB_MESUploadSet = new QPushButton(ParameterSettingWidget);
        PB_MESUploadSet->setObjectName(QStringLiteral("PB_MESUploadSet"));
        PB_MESUploadSet->setGeometry(QRect(300, 597, 121, 41));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_MESUploadSet->setPalette(palette5);
        PB_MESUploadSet->setFont(font1);

        retranslateUi(ParameterSettingWidget);

        QMetaObject::connectSlotsByName(ParameterSettingWidget);
    } // setupUi

    void retranslateUi(QWidget *ParameterSettingWidget)
    {
        ParameterSettingWidget->setWindowTitle(QApplication::translate("ParameterSettingWidget", "Form", 0));
        LB_Background1->setText(QString());
        QTreeWidgetItem *___qtreewidgetitem = TRW_DataModule->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("ParameterSettingWidget", "\345\200\274", 0));
        LB_Background2->setText(QString());
        QTreeWidgetItem *___qtreewidgetitem1 = TRW_BoolModule->headerItem();
        ___qtreewidgetitem1->setText(1, QApplication::translate("ParameterSettingWidget", "\345\200\274", 0));
        LB_Background3->setText(QString());
        PB_ParamerSave->setText(QApplication::translate("ParameterSettingWidget", "\344\277\235\345\255\230", 0));
        PB_LaserDataSet->setText(QApplication::translate("ParameterSettingWidget", "\346\277\200\345\205\211\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        PB_UserManage->setText(QApplication::translate("ParameterSettingWidget", "\347\224\250\346\210\267\347\256\241\347\220\206", 0));
        PB_MESUploadSet->setText(QApplication::translate("ParameterSettingWidget", "MES\345\217\202\346\225\260\350\256\276\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class ParameterSettingWidget: public Ui_ParameterSettingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_PARAMETERSETTING_H
