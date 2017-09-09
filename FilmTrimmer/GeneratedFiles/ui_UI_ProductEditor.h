/********************************************************************************
** Form generated from reading UI file 'UI_ProductEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_PRODUCTEDITOR_H
#define UI_UI_PRODUCTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProductEditorWidget
{
public:
    QLabel *LB_Background1;
    QListWidget *LW_PackageList;
    QLabel *label_2;
    QPushButton *PB_Package_SetCurrent;
    QPushButton *PB_Package_Copy;
    QPushButton *PB_Package_Delete;
    QPushButton *PB_Package_New;
    QLabel *LB_Background2;
    QTreeWidget *TRW_PkgParticularInfo;
    QLabel *label_3;
    QPushButton *PB_Package_Save;

    void setupUi(QWidget *ProductEditorWidget)
    {
        if (ProductEditorWidget->objectName().isEmpty())
            ProductEditorWidget->setObjectName(QStringLiteral("ProductEditorWidget"));
        ProductEditorWidget->resize(950, 649);
        ProductEditorWidget->setMinimumSize(QSize(950, 649));
        ProductEditorWidget->setMaximumSize(QSize(950, 649));
        LB_Background1 = new QLabel(ProductEditorWidget);
        LB_Background1->setObjectName(QStringLiteral("LB_Background1"));
        LB_Background1->setGeometry(QRect(0, 20, 351, 621));
        LB_Background1->setFrameShape(QFrame::NoFrame);
        LW_PackageList = new QListWidget(ProductEditorWidget);
        LW_PackageList->setObjectName(QStringLiteral("LW_PackageList"));
        LW_PackageList->setGeometry(QRect(17, 56, 300, 441));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        LW_PackageList->setPalette(palette);
        QFont font;
        font.setPointSize(11);
        LW_PackageList->setFont(font);
        label_2 = new QLabel(ProductEditorWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(155, 27, 81, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_2->setPalette(palette1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(11);
        label_2->setFont(font1);
        PB_Package_SetCurrent = new QPushButton(ProductEditorWidget);
        PB_Package_SetCurrent->setObjectName(QStringLiteral("PB_Package_SetCurrent"));
        PB_Package_SetCurrent->setGeometry(QRect(50, 515, 111, 41));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_Package_SetCurrent->setPalette(palette2);
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(10);
        PB_Package_SetCurrent->setFont(font2);
        PB_Package_Copy = new QPushButton(ProductEditorWidget);
        PB_Package_Copy->setObjectName(QStringLiteral("PB_Package_Copy"));
        PB_Package_Copy->setGeometry(QRect(200, 515, 111, 41));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_Package_Copy->setPalette(palette3);
        PB_Package_Copy->setFont(font2);
        PB_Package_Delete = new QPushButton(ProductEditorWidget);
        PB_Package_Delete->setObjectName(QStringLiteral("PB_Package_Delete"));
        PB_Package_Delete->setGeometry(QRect(50, 580, 111, 41));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_Package_Delete->setPalette(palette4);
        PB_Package_Delete->setFont(font2);
        PB_Package_New = new QPushButton(ProductEditorWidget);
        PB_Package_New->setObjectName(QStringLiteral("PB_Package_New"));
        PB_Package_New->setGeometry(QRect(200, 580, 111, 41));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_Package_New->setPalette(palette5);
        PB_Package_New->setFont(font2);
        LB_Background2 = new QLabel(ProductEditorWidget);
        LB_Background2->setObjectName(QStringLiteral("LB_Background2"));
        LB_Background2->setGeometry(QRect(390, 20, 560, 621));
        LB_Background2->setFrameShape(QFrame::NoFrame);
        TRW_PkgParticularInfo = new QTreeWidget(ProductEditorWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("\346\250\241\347\273\204"));
        TRW_PkgParticularInfo->setHeaderItem(__qtreewidgetitem);
        TRW_PkgParticularInfo->setObjectName(QStringLiteral("TRW_PkgParticularInfo"));
        TRW_PkgParticularInfo->setGeometry(QRect(417, 60, 510, 501));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Text, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        TRW_PkgParticularInfo->setPalette(palette6);
        TRW_PkgParticularInfo->setFont(font);
        TRW_PkgParticularInfo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label_3 = new QLabel(ProductEditorWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(670, 30, 71, 21));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_3->setPalette(palette7);
        label_3->setFont(font1);
        PB_Package_Save = new QPushButton(ProductEditorWidget);
        PB_Package_Save->setObjectName(QStringLiteral("PB_Package_Save"));
        PB_Package_Save->setGeometry(QRect(620, 580, 111, 41));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        PB_Package_Save->setPalette(palette8);
        PB_Package_Save->setFont(font2);

        retranslateUi(ProductEditorWidget);

        QMetaObject::connectSlotsByName(ProductEditorWidget);
    } // setupUi

    void retranslateUi(QWidget *ProductEditorWidget)
    {
        ProductEditorWidget->setWindowTitle(QApplication::translate("ProductEditorWidget", "Form", 0));
        LB_Background1->setText(QString());
        label_2->setText(QApplication::translate("ProductEditorWidget", "\344\272\247\345\223\201\345\220\215\345\210\227\350\241\250", 0));
        PB_Package_SetCurrent->setText(QApplication::translate("ProductEditorWidget", "\350\256\276\347\275\256\345\275\223\345\211\215\344\272\247\345\223\201", 0));
        PB_Package_Copy->setText(QApplication::translate("ProductEditorWidget", "\345\244\215\345\210\266", 0));
        PB_Package_Delete->setText(QApplication::translate("ProductEditorWidget", "\345\210\240\351\231\244            ", 0));
        PB_Package_New->setText(QApplication::translate("ProductEditorWidget", "\346\226\260\345\273\272", 0));
        LB_Background2->setText(QString());
        QTreeWidgetItem *___qtreewidgetitem = TRW_PkgParticularInfo->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("ProductEditorWidget", "\346\223\215\344\275\234", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("ProductEditorWidget", "\345\200\274", 0));
        label_3->setText(QApplication::translate("ProductEditorWidget", "\344\272\247\345\223\201\344\277\241\346\201\257", 0));
        PB_Package_Save->setText(QApplication::translate("ProductEditorWidget", "\344\277\235\345\255\230", 0));
    } // retranslateUi

};

namespace Ui {
    class ProductEditorWidget: public Ui_ProductEditorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_PRODUCTEDITOR_H
