#pragma once
#include <vector>
#include <QObject>
#include "BaseDataType.h"

using namespace std;
//设备状态
/*
目前只是做了初步的状态，还没有加入小的状态（标志位）需要确定
*/

class OP_FSM;

typedef bool (OP_FSM::*pFSMFun)();

//状态机Item
typedef struct TAG_FSM_ITEM
{
	MACHINE_STATUS    CurStatus;	    //当前状态
	MACHINE_EVENT     CurEvent;	        //当前事件
	pFSMFun           pTaskProc;	    //事件任务函数指针
}FSM_ITEM;

class OP_FSM : public QObject
{
	Q_OBJECT
public:
	~OP_FSM(void);
	OP_FSM(void);

private:
	std::vector<FSM_ITEM> m_FSMList;    //状态机列表
	MACHINE_EVENT m_emPCEvent;		//设备启停控制
	MACHINE_EVENT m_emPLCLasetEvnet;	//PLC最后设备启动事件
	VALUECFG m_stMachineStatus;			//设备当前状态
	VALUECFG m_stMachineStatusAlarm;	//设备当前状态(报警状态)
	VALUECFG m_stMachineFlag;			//设备状态标志
	VALUECFG m_stMachineHardwareStatus;	//设备硬件按钮状态(启停复位停止急停)

private:
	void InitVal();
	//事件任务函数
	bool BeginToInitProc();	//进行初始化任务
	bool InitToReadyProc();	//进行复位任务 
	bool ReadyToRunProc();	//进行启动任务
	bool RunToStopProc();	//进行停止任务
	bool RunToEStopProc();	//进行急停任务
	bool AlarmCleanProc();	//进行报警清除任务

public:
	void InitFSM();                  //初始化状态机
	MACHINE_STATUS GetCurStatus();   //获取当前状态
	bool GetCurAlarmStatus();		 //获取设备报警状态
	MACHINE_EVENT  GetCurEvent();    //获取当前事件
	MACHINE_FLAG   GetCurFlag();	 //获取当前标志
	void TransferFSM(MACHINE_STATUS MachineStatus,MACHINE_EVENT MachineEvent); //牵引状态机
    void InsertTask(MACHINE_STATUS CurMachineStatus,MACHINE_EVENT MachineEvent,pFSMFun pTaskProc); //插入任务

	void GetMachineTask();

protected Q_SLOTS:
	void SlotMachineCtrl(EM_MACHINE_SIGNAL emEvent);

Q_SIGNALS:
	void SigSetStatusFlagTest(QString strStatusHint,QString strOperHint, MACHINE_STATUSTOOL_COLOR AlarmStatus);
};

