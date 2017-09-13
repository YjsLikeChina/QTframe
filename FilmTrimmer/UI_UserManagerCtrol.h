#ifndef UI_USERMANAGERCTROL_H
#define UI_USERMANAGERCTROL_H

#include <QDialog>
#include "ui_UI_UserManagerCtrol.h"
class UI_UserManagerCtrol : public QDialog
{
	Q_OBJECT

public:
	UI_UserManagerCtrol(QWidget *parent = 0);
	~UI_UserManagerCtrol();
public slots:
	void SlotSave();
	void SlotDec();
	void SlotAdd();
	void SlotCancel();
	void SlotPasswordClicked();
	void SlotShowUserContrl();
	void Dialog_show();
private:
	Ui::UI_UserManagerCtrol ui;
	void initVal();
	void initUi();
	void initConnect();
	bool ContrlUser = false;
	bool eventFilter(QObject *, QEvent *);
	void *m_UserList = NULL; //用于存储用户链表指针
};

#endif // UI_USERMANAGERCTROL_H
