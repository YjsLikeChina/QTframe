#pragma once
#include "qdialog.h"
#include "ui_UI_Maintenance.h"
#include "UI_InterfaceBase.h"

class UI_Maintenance :
	public QDialog,virtual public UI_InterfaceBase
{
	Q_OBJECT

public:
	UI_Maintenance(QWidget* parent = Q_NULLPTR);
	~UI_Maintenance();

private:
	Ui::MaintenanceDlg ui;

private:
	void InitUI();
	void InitConnect();
	bool ExitMaintenance();

protected:
	bool eventFilter(QObject *obj, QEvent *ev);
	
public:
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal);//获取有修改的数据
	virtual void SkipCurrentPage();										//跳转到当前页面

Q_SIGNALS:
	void SigExit();
};

