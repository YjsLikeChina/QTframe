#pragma once
#include <QObject>
#include "CTRL_Base.h"
class CTRL_IODebug : public CTRL_Base {


public:
	CTRL_IODebug(QObject * parent = Q_NULLPTR);
	~CTRL_IODebug();

	
	void Initconnect();
	bool ButtonClickedChanged(int nModuleNum,int nChildeNum);	//参数修改
	QString ChangeMoudle(int nModule);									//模组切换
//槽函数
protected Q_SLOTS:
	//void SlotItemCliked(int nModuleNum, int nChildNum, double dlData); //参数修改;
private:
	
};
