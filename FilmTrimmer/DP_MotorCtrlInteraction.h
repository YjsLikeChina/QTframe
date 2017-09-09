#pragma once
#include <QObject>
#include "BaseDataType.h"
#include "DP_HCPLCInteraction.h"
#include <QThread>

enum MOTOR_MOVE_CTRL
{
	MOVE_GOTOHOME = 0,	//归零
	MOVE_TOPOS,		//定位
};

class DP_MotorCtrlInteraction;

class MotorCtrlThread
	:public QThread
{
	Q_OBJECT
public:
	~MotorCtrlThread();
private:
	MotorCtrlThread(DP_MotorCtrlInteraction*);
	void run();
	void SetMotorRunModel(double dlDist,MOTOR_MOVE_CTRL MoveType);
	MOTOR_MOVE_CTRL m_emMoveCtrl;
	double m_dlMoveDist;
	DP_MotorCtrlInteraction* m_pMotorCtrlInteraction;
	friend DP_MotorCtrlInteraction;
};


class DP_MotorCtrlInteraction
	:public QObject
{
	Q_OBJECT
public:
	DP_MotorCtrlInteraction();
	~DP_MotorCtrlInteraction();

private:
	QVector<ST_VALUECFG> m_qVecMotorsInfo;

private:
	bool m_bIsMoveing;													//是否有电机在移动
	int m_nMotorNum;													//电机轴号
	QString m_qstrAxisName;												//轴名称
	int m_nAxisAttribute;												//轴属性
	MotorCtrlThread* m_pMotorMoveThread;								//电机移动线程
	double m_dlMoveDist;
	friend MotorCtrlThread;

private:
	void MotorMove(double dlDist, EM_AXIS_MOVE_SIGNAL emMoveModel = ABSOLUTE_MOVE);	//
	void MotorGotoHome();

public:
	bool	InitMotorsInfo(int nAxis,QVector<ST_VALUECFG> MotorsInfo);
	bool	SetMotorGotoHome();
	bool	SetMotorMove(double dlDist, EM_AXIS_MOVE_SIGNAL emMoveModel = ABSOLUTE_MOVE, bool bRunDir = false, bool flag = false); //定距移动
	bool	SetMotorEnable(bool bAutoGetCurrentStatus = true, bool bEnableStatu = false);//设置电机使能
	bool	SetMotorStop(bool bAutoGetCurrentStatus = true, bool bRunStatu = false);	//设置电机运行状态
	bool	SetMotorAlarmClean();										//清除报警
	int		GetMotorStatus();											//获取电机状态
	bool	GetMotorEanble();											//或者电机使能状态
	double	GetMotorCurrentPos();										//获取电机当前位置
	double	GetMotorCurrnetSpeed();										//获取当前电机速度
	bool	GetMoveStatus();											//判断是否正在移动中
	bool	GetAxisAttribute(QString& qstrAxisName,int& nAxisAttribute);//获取轴名称、属性
};


