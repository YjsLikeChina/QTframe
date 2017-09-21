#pragma once
#include <QThread>
#include "BaseDataType.h"
#include <QMutex>

class OP_AutoUpdateData :
	public QThread
{
	Q_OBJECT

public:
	OP_AutoUpdateData();
	~OP_AutoUpdateData();

private:
	int m_nCurPage;											//当前页面
	QMap<int, QList<ST_UPDATEDATA>>* m_qMapAutoUpdateData;	//自动更新数据列表
	bool m_bRunFlag;										//运行标志
	int m_nCurModule;										//当前模组
	QStringList m_qslHistoryInfoFilePath;					//历史信息文件路径
	bool m_bReadHistoryInfoLock;							//读取历史文件保护
	QList<ST_UPDATEDATA> m_qLisAutoUpdata;					//自动更新过后的数据
	QString m_qstrAlarmList;								//设备报警列表
	QString m_qstrErrorList;								//设备错误列表
	DWORD m_dwMachineModelAddr;								//设备手自动模式读取
	EM_Type m_emMachineModelType;							//设备手自动模式地址类型
	bool m_bMachineModel = false;							//设备当前模式

private:
	void initVal();
	void run();
	void AutoUpdateCommon(QList<ST_UPDATEDATA>&);
	void AutoUpdateIOStatus(QList<ST_UPDATEDATA>&);
	void AutoUpdataHistoryInfo(QList<ST_UPDATEDATA>&);
	bool MachineAlarmUpdata(QString& qslAlarm, QString& qslError);				//更新报警
	void MachineModelUpdata(bool& bMachineModel);								//设备手自动模式

public:
	QVector<ST_VALUECFG> m_qVecAlarmList;										//警告地址列表
	QVector<ST_VALUECFG> m_qVecErrorList;										//错误地址列表
public:
	bool StartAutoUpdateDataThread(bool bFlag = true);							//bflag为真时启动自动刷新线程,flag为假时线程结束
	void SwitchWorkTask(int nCurPage, int nCurModule);							//切换工作任务,
	void insertWorkTask(QMap<int, QList<ST_UPDATEDATA>>& qMapAutoUpdateData);	//添加自动更新列表
	QString GetMachineError();

Q_SIGNALS:
	void SigAutoProduction(QList<ST_UPDATEDATA>);								//自动生产页面
	void SigIODebug(QList<ST_UPDATEDATA>);										//IO调试
	void SigMotorDebug(QList<ST_UPDATEDATA>);									//电机控制
	void SigParameterSetting(QList<ST_UPDATEDATA>);								//参数设置
	void SigProductEditor(QList<ST_UPDATEDATA>);								//产品编辑
	void SigHistoricalInformation(QList<ST_UPDATEDATA>);						//历史信息
	void SigMachineAlarm(QString qslAlarm, QString qslError);					//设备报警列表
	void SigMachineModel(bool bFlag);
};

