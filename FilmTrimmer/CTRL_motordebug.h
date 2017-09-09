#pragma once
#include <QObject>
#include "OP_MachineSoftWareMain.h"
#include "CTRL_Base.h"
class CTRL_MotorDebug : public CTRL_Base {


public:
	CTRL_MotorDebug(QObject * parent = Q_NULLPTR);
	~CTRL_MotorDebug();

	bool SaveMotolData(QVector<ST_CHANGE_POINT> VeChangePoint);	//保存数据
	//轴号、移动距离、移动类型、移动方向(Jog)、是否移动(Jog,1为移动，0为停止)
	bool AxisleMove(int nAxisNum, double nDist, EM_AXIS_MOVE_SIGNAL MoveModel, bool RunDir = true,bool bFlag = true);

	bool SetMotorEnable(int nAxis, bool bAutoGetCurrentStatus = true, bool bEnableStatu = false);//设置电机使能
	bool SetMotorStop(int nAxis, bool bAutoGetCurrentStatus = true, bool bRunStatu = false);	//设置电机运行状态
	bool SetMotorCleanAlarm(int nAxis);

	bool ChickFeasible(int nAxisNum, EM_AXIS_MOVE_SIGNAL MoveModel);
	bool SwitchMotor(int nAxis, QVector<ST_CHANGE_POINT> &NewMotorData);							//切换电机刷新数据
private:
	void InitVal();
	void InitConnect();
};
