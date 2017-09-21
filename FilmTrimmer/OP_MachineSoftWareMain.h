#pragma once
#include <QObject>
#include "BaseDataType.h"
#include "OP_AutoUpdateData.h"
#include "OP_MachineStatusCtrl.h"
#include <vector>
#include "DP_MotorCtrlInteraction.h"
#include "LogManager.h"
#include "OP_FSM.h"

class OP_MachineSoftWareMain
	: public QObject
{
	Q_OBJECT
public:
	~OP_MachineSoftWareMain();

private:
	int m_nCurentPage;											//当前页面
	QString m_qstrCfgPath;										//配置文件路径
	QMap<int, QList<ST_UPDATEDATA>> m_qMapAutoUpdateData;		//自动更新数据							//Filmtrimmer.cfg路径
public:
	//Work
	OP_AutoUpdateData* m_pAutoUpdateData;
	OP_MachineStatusCtrl* m_pMachineStatusCtrl;					//设备启停、激光、产品等功能
	OP_FSM* m_pFSM;
	std::vector<DP_MotorCtrlInteraction*> m_MotorList;			//电机列表
private:
	OP_MachineSoftWareMain(QObject* parent = NULL);
	void initVal();
	void initConnect();
	void LoadModuleInfo();										//加载模块信息
	void LoadMotorInfo();                                       //加载电机信息

																//获取自动更新数据,nPage用来区分IO界面\历史页面\其他页面
	bool GetAutoUpdateData(const QVector<ST_MODULE>& QVecSource,QList<ST_UPDATEDATA>& AutoUpdateData,int nPage = -1);
	bool m_bOnloadConfigFinish;									//配置文件加载完毕(UI_FilmTrimmer、OP_MachineCtrlOrAlarmStatus中使用)
	
public:
	//自动生产页面
	QVector<ST_MODULE> m_QveAutoProduction;						//自动生产页面模组信息
	QList<ST_UPDATEDATA> m_QliAutoProduction_AutoUpdateData;	//自动更新的数据信息
																//设备调试页面
	QVector<ST_MODULE> m_QveIODebug;							//IO调试页面模组信息
	QVector<QList<ST_UPDATEDATA>> m_QliIODebug_AutoUpdateData;	//自动更新一个模组的Input //QList<ST_UPDATEDATA>一个模组,QVector中包含多个模组
	ST_MODULE m_UpdateDataModule;								//切换页面时更新单个模组,包含输入输出点
																//电机调试页面
	QVector<ST_MODULE> m_QveMotorDebug;							//电机调试模组信息
	QList<ST_UPDATEDATA> m_QliMotorDebug_AutoUpdateData;		//自动更新的数据信息
																//参数设置页面
	QVector<ST_MODULE> m_QveParameterSetting;					//参数设置模组信息
	QList<ST_UPDATEDATA> m_QliParameterSetting_AutoUpdateData;	//自动更新的数据信息
																//产品编辑
	QVector<ST_MODULE> m_QveProductEditor;						//参数设置模组信息
	QList<ST_UPDATEDATA> m_QliProductEditor_AutoUpdateData;		//自动更新的数据信息
																//历史信息
	QVector<ST_MODULE> m_QveHistoricalInfo;						//参数设置模组信息
	QList<ST_UPDATEDATA> m_QliHistoricalInfo_AutoUpdateData;	//自动更新的数据信息

	QVector<QVector<ST_MODULE>> m_qVecAllPageData;				//所有页面参数

	QVector<ST_MODULE> m_QveFilmParam;						//部分默认参数(FilmTrimmer),第一项为默认参数，顺序按照EM_FILM_DEFAULT_ORDER

	static OP_MachineSoftWareMain* m_pInstanceObj;
	QString ReturnPageCfgPath(EM_CHILDPAGEITEM emPageItem);		//返回配置文件名称
	CLog *m_Clog;												//日志编写类

public:
	void initTask();											//初始化工作任务
	bool GetOnloadConfigStatus();								//获取配置文件加载状态
	static OP_MachineSoftWareMain* GetInstanceObj();
	bool AllMotorGotoHome();									//所有电机归零
	bool AllMotorMoveToPos(QVector<ST_MODULE> qVecMotorInfo);	//所有电机移动到位
	bool GetAllMotorIsOrigin();									//判断需要自动定位的轴是否拥有原地位
	bool GetAllMotorInplace(ST_MODULE stModuleInfo);			//判断电机是否全部到位

//Q_SIGNALS:
//	void SigOnloadConfigFinish();
};

#define MACHINECTRL (*OP_MachineSoftWareMain::GetInstanceObj())
#define MOTORSCTRL  (OP_MachineSoftWareMain::GetInstanceObj()->m_MotorList)
#define MACHINELOG	(OP_MachineSoftWareMain::GetInstanceObj()->m_Clog);