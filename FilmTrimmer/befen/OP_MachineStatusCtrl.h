#pragma once
#include <QThread>
#include "UI_MessageBox.h"
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
	QString m_qstrMachineCfgPath;		//Machine.cfg路径
	CString m_cstrMachineCfgPath;		//Machine.cfg路径
	QString m_qstrPackageFilePath;
	UI_MessageBox* m_pMessageBox;
	bool m_bSetCurPkgLock;				//设置当前产品锁
	bool m_bSoftwareIsFirstStart;		//是否第一次启动设备
	bool m_bComputerCard;				//是否为脱机卡
	bool m_bIsAutoMoveToPos;			//电机是否自动到位
	QVector<ST_MODULE> m_qVecPackageInfo;//当前产品文件容器
	bool m_bMachineCurModel;			//设备当前模式(1自动模式,0为手动模式)
	int m_nMachineCurWork;				//设备当前工作任务
private:
	void InitVal();
	void run();
	bool MachineCtrlStart();			//设备启动
	bool MachineCtrlStop();				//设备停止
	bool MachineCtrlReset();			//设备复位
	bool MachineCtrlEStop();			//设备急停
	bool MachineCtrlMaintain();			//设备维护
	bool SetCurrentPackage();			//设置当前产品

	bool RunProcess();					//自动运行线程
	bool SetOtherData();				//设置其他与具体产品无关的数据(参数设置页面)
	bool SetMotorSpeed();				//设置电机速度等参数
	bool GetMotorIsInplace();			//判断电机是否到达工作位
	bool GetIsAutoMovePos();			//判断是否勾选电机自动定位

public:
	bool InitMachineCtrl();
	bool SetMachineStatus(int nModel,bool bFlag);	//设置设备状态,设备状态、手自动模式(1自动模式,0为手动模式)
	bool SetCrurentPackage(QString qstrCurPkgName);

Q_SIGNALS:
	void SigMachineStatusResult(bool);		//设备启动结果
	void SigMachineResetResult(bool);		//设备复位结果
	void SigSetCurrentPackage(bool);		//设置当前产品
};

