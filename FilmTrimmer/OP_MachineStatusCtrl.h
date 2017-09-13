#pragma once
#include <QThread>
#include "BaseDataType.h"

class OP_MachineStatusCtrl
	: QThread
{
	Q_OBJECT

public:
	OP_MachineStatusCtrl();
	~OP_MachineStatusCtrl();

private:
	QString m_qstrCurPkgName;			//产品文件名
	int m_nCurMachineStatus;			//当前设备状态
	QString m_qstrFilmCfgPath;			//FilmTrimmer.cfg路径
	CString m_cstrFilmCfgPath;			//FilmTrimmer.cfg路径
	QString m_qstrPackageFilePath;
	bool m_bSetCurPkgLock;				//设置当前产品锁
	bool m_bSoftwareIsFirstStart;		//是否第一次启动设备
	bool m_bComputerCard;				//是否为脱机卡
	bool m_bIsAutoMoveToPos;			//电机是否自动到位
	QVector<ST_MODULE> m_qVecPackageInfo;//当前产品文件容器
	MACHINE_STATUS m_emMachineStatusCtrl;//设备状态机
	ST_LASER_DATA m_stCurLaserData;		//当前激光数据
	bool m_bMachineLasetStatus;			//设备最后一次状态
	bool m_bMachineRunDir;				//设备运行方向
	QString m_qstrHistoryFilePath;		//历史文件路径
	ST_VALUECFG m_stCurSpeed;				//当前(反馈)速度地址

	//设备状态机控制变量
	MACHINE_TASK m_emMachineTask;		//设备需要执行的任务

	//启停复位急停地址
	ST_VALUECFG m_stStart;
	ST_VALUECFG m_stReset;
	ST_VALUECFG m_stStop;
	ST_VALUECFG m_stEStop;
	ST_VALUECFG m_stMaintain;

private:
	void InitVal();
	void run();
	bool MachineCtrlStart();			//设备启动
	bool MachineCtrlStop();				//设备停止
	bool MachineCtrlReset();			//设备复位
	bool MachineCtrlEStop();			//设备急停
	bool MachineCtrlMaintain();			//设备维护
	bool MachineCtrlInit();				//设备初始化
	bool MachineCtrlCleanAlarm();		//清除报警
	bool SetCurrentPackage();			//设置当前产品

	bool SetOtherData();				//设置其他与具体产品无关的数据(参数设置页面)
	bool SetMotorSpeed();				//设置电机速度等参数
	bool GetMotorIsInplace();			//判断电机是否到达工作位
	bool GetIsAutoMovePos();			//判断是否勾选电机自动定位

	bool CheckMachineStop();
	void WriteWorkHistoryLog();
	void WriteAlarmHistoryLog();

public:
	bool InitMachineWork();
	bool SetCrurentPackage(QString qstrCurPkgName);
	bool SetMachineTask(MACHINE_TASK emMachineTask);
	ST_LASER_DATA GetCurLaserData();	//获取当前激光数据
	void SetLaserData(ST_LASER_DATA stLaserData);
	void SetMachineRunDir(bool bFlag);

Q_SIGNALS:
	void SigMachineStatusResult(bool);		//设备启动结果
	void SigMachineResetResult(bool);		//设备复位结果
	void SigSetCurrentPackage(bool);		//设置当前产品
};

