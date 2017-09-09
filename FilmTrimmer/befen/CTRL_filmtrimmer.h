#pragma once
#include <QObject>
#include "CTRL_Base.h"
#include "OP_MachineSoftWareMain.h"
#include "CTRL_autoproduction.h"
class CTRL_FilmTrimmer : public CTRL_Base 
{
	Q_OBJECT

public:
	CTRL_FilmTrimmer(QObject * parent = Q_NULLPTR);
	~CTRL_FilmTrimmer();

	//槽函数
public:
	 bool SwitchPage(int nCurPage,int newPage, bool bFlag, QVector<ST_CHANGE_POINT>& ModifyVal);//切换页面信号,点击退出时下一个页面为-1
	 bool MachineCtrl(EM_MACHINE_SIGNAL emCtrl);									 //设备控制
public:
	//函数
	void InitConnect();
	void InitValue();
	QString UserLogin();
	bool ResultUserName();	
};
