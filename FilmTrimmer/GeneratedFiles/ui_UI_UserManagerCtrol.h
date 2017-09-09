/********************************************************************************
** Form generated from reading UI file 'UI_UserManagerCtrol.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_USERMANAGERCTROL_H
#define UI_UI_USERMANAGERCTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_UI_UserManagerCtrol
{
public:
    QPushButton *Save;
    QPushButton *Cancel;
    QLabel *label;
    QLabel *Authority;
    QLineEdit *UserName;
    QLabel *label_3;
    QLineEdit *PasswordOne;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *PasswordTwo;
    QTableWidget *NoAdminUserList;
    QPushButton *UserContrlButton;
    QPushButton *Add;
    QPushButton *Dec;

    void setupUi(QDialog *UI_UserManagerCtrol)
    {
        if (UI_UserManagerCtrol->objectName().isEmpty())
            UI_UserManagerCtrol->setObjectName(QStringLiteral("UI_UserManagerCtrol"));
        UI_UserManagerCtrol->resize(437, 343);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        UI_UserManagerCtrol->setFont(font);
        Save = new QPushButton(UI_UserManagerCtrol);
        Save->setObjectName(QStringLiteral("Save"));
        Save->setGeometry(QRect(70, 290, 100, 40));
        Cancel = new QPushButton(UI_UserManagerCtrol);
        Cancel->setObjectName(QStringLiteral("Cancel"));
        Cancel->setGeometry(QRect(250, 290, 100, 40));
        label = new QLabel(UI_UserManagerCtrol);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(270, 15, 81, 16));
        Authority = new QLabel(UI_UserManagerCtrol);
        Authority->setObjectName(QStringLiteral("Authority"));
        Authority->setGeometry(QRect(350, 15, 71, 16));
        UserName = new QLineEdit(UI_UserManagerCtrol);
        UserName->setObjectName(QStringLiteral("UserName"));
        UserName->setGeometry(QRect(120, 10, 131, 25));
        label_3 = new QLabel(UI_UserManagerCtrol);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 15, 80, 16));
        PasswordOne = new QLineEdit(UI_UserManagerCtrol);
        PasswordOne->setObjectName(QStringLiteral("PasswordOne"));
        PasswordOne->setGeometry(QRect(120, 50, 131, 25));
        label_4 = new QLabel(UI_UserManagerCtrol);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 55, 71, 16));
        label_5 = new QLabel(UI_UserManagerCtrol);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 95, 71, 16));
        PasswordTwo = new QLineEdit(UI_UserManagerCtrol);
        PasswordTwo->setObjectName(QStringLiteral("PasswordTwo"));
        PasswordTwo->setGeometry(QRect(120, 90, 131, 25));
        NoAdminUserList = new QTableWidget(UI_UserManagerCtrol);
        if (NoAdminUserList->columnCount() < 2)
            NoAdminUserList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        NoAdminUserList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        NoAdminUserList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        NoAdminUserList->setObjectName(QStringLiteral("NoAdminUserList"));
        NoAdminUserList->setGeometry(QRect(15, 130, 381, 141));
        NoAdminUserList->horizontalHeader()->setStretchLastSection(true);
        NoAdminUserList->verticalHeader()->setCascadingSectionResizes(false);
        UserContrlButton = new QPushButton(UI_UserManagerCtrol);
        UserContrlButton->setObjectName(QStringLiteral("UserContrlButton"));
        UserContrlButton->setGeometry(QRect(300, 90, 91, 31));
        Add = new QPushButton(UI_UserManagerCtrol);
        Add->setObjectName(QStringLiteral("Add"));
        Add->setGeometry(QRect(405, 155, 21, 31));
        Dec = new QPushButton(UI_UserManagerCtrol);
        Dec->setObjectName(QStringLiteral("Dec"));
        Dec->setGeometry(QRect(405, 200, 21, 31));

        retranslateUi(UI_UserManagerCtrol);

        QMetaObject::connectSlotsByName(UI_UserManagerCtrol);
    } // setupUi

    void retranslateUi(QDialog *UI_UserManagerCtrol)
    {
        UI_UserManagerCtrol->setWindowTitle(QApplication::translate("UI_UserManagerCtrol", "Dialog", 0));
        Save->setText(QApplication::translate("UI_UserManagerCtrol", "\344\277\235\345\255\230", 0));
        Cancel->setText(QApplication::translate("UI_UserManagerCtrol", "\345\217\226\346\266\210", 0));
        label->setText(QApplication::translate("UI_UserManagerCtrol", "\345\275\223\345\211\215\346\235\203\351\231\220\357\274\232", 0));
        Authority->setText(QApplication::translate("UI_UserManagerCtrol", "TextLabel", 0));
        label_3->setText(QApplication::translate("UI_UserManagerCtrol", "\345\275\223\345\211\215\347\224\250\346\210\267\345\220\215:", 0));
        label_4->setText(QApplication::translate("UI_UserManagerCtrol", "\346\226\260\345\257\206\347\240\201\357\274\232", 0));
        label_5->setText(QApplication::translate("UI_UserManagerCtrol", "\345\206\215\346\254\241\350\276\223\345\205\245\357\274\232", 0));
        QTableWidgetItem *___qtablewidgetitem = NoAdminUserList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("UI_UserManagerCtrol", "\347\224\250\346\210\267\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem1 = NoAdminUserList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("UI_UserManagerCtrol", "\346\223\215\344\275\234\346\235\203\351\231\220", 0));
        UserContrlButton->setText(QApplication::translate("UI_UserManagerCtrol", "\347\224\250\346\210\267\347\256\241\347\220\206", 0));
        Add->setText(QApplication::translate("UI_UserManagerCtrol", "+", 0));
        Dec->setText(QApplication::translate("UI_UserManagerCtrol", "-", 0));
    } // retranslateUi

};

namespace Ui {
    class UI_UserManagerCtrol: public Ui_UI_UserManagerCtrol {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_USERMANAGERCTROL_H
