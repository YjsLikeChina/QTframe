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
	void SlodAdd();
	void SlotCancel();
	void SlotPasswordClicked();
private:
	Ui::UI_UserManagerCtrol ui;
	void initVal();
	void initUi();
	void initConnect();
	QMap<QString, USER_TYPE> m_UserList;
};

#endif // UI_USERMANAGERCTROL_H
