#pragma once
#include <QObject>
#include "CTRL_Base.h"
class CTRL_AutoProduction : public CTRL_Base {
	Q_OBJECT

private:
	int m_nSetMaxSpeed;
public:
	CTRL_AutoProduction(QObject * parent = Q_NULLPTR);
	~CTRL_AutoProduction();
	void Initconnect(); 
	bool ItemChanged(QVector<ST_CHANGE_POINT> VeChangePoint); //参数修改

	bool SetMachineRunDir();								  //设置设备运行方向，当前方向从PLC中获取
	bool SetMachineOnloadDir();								  //设置设备放卷方向，当前方向从PLC中获取
	bool SetWorkSpeed(int nSetSpeed);						  //设置工作速度

	//true为转动, false停止
	void SetOnloadClockwise(bool bFlag);					  //放卷正转
	void SetOnloadAnticlockwise(bool bFlag);				  //放卷反转
	void SetMainAxisClockwise(bool bFlag);					  //主牵引正转
	void SetMainAxisAnticlockwise(bool bFlag);				  //主牵引反转
	void SetRecvClockwise(bool bFlag);						  //收卷正转
	void SetRecvAnticlockwise(bool bFlag);					  //收卷反转
};
