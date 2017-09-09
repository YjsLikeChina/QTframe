#pragma once
#include <QObject>
#include <afxmt.h>
#include "BaseDataType.h"
#include "CLaserClient.h"
#include "QThread"
#include "QMutex"
class DP_LaserInteraction;
struct SPloeSizeInfo
{
	int nType;
	double dTWidth;
	double dBWidth;
	double dHight;
	double dCoatHeight;
	double dA1;
	double dR1;
	double dA2;
	double dR2;
	double dA3;
	double dR3;
	double dA4;
	double dR4;
	double dTagW;
	double dTagH;
	double dLineSpeed;
	int nShutRate;
	int nPoleShape;
	int nNo;
};

class CLaserCtrl
{
private:
	CLaserCtrl(void);
	~CLaserCtrl(void);
private:

	BOOL InitDll();
	HINSTANCE m_HmsDLL;
	//初始化打标软件
	bool(__stdcall *InisHMSLaserDll)();
	//关闭打标软件
	bool(__stdcall *CloseHMSLaserDll)();

	/////////////////极耳专用///////////////////////
	//打开文件
	bool(__stdcall *HMSOpenFile)(char* cFilePath);
	//设置工作速度
	bool(__stdcall *HMSChangeSpeed)(double dlSpeed);
	//设置极耳信息
	bool(__stdcall *HMSSetPoleInfo)(int nCount, char* cIntervals);
	//获取激光状态
	int(__stdcall *HMSGetPraStatus)(int No);
	//设置激光功率
	bool(__stdcall *HMSSetPower)(int nPower);
	//设置频率
	bool(__stdcall *HMSSetFreq)(int nFreq);
	//设置工作模式
	bool(__stdcall *HMSSetWorkModel)(int nModel);
	//设置极耳尺寸
	bool(__stdcall *HMSSetPoleSize)(double dWidth, double dHight);
	//创建极耳图形
	bool(__stdcall *HMSCreatePole)(SPloeSizeInfo *pSizeInfo);
	//上传极耳打标数据
	bool(__stdcall *UploadMarkDate)(int nNo, int nModel);
public:
	//显示或隐藏打标软件编辑窗体，返回TRUE表示当前为显示状态，false为隐藏状态
	bool(__stdcall *HMSShowEditWindow)();

private:
	////0713 tqc Laser dll Updata
	////获取软件版本
	//bool(__stdcall *HMSGetVersion)(char* cVersion);
	////获取极耳个数
	//bool(__stdcall *HMSGetPoleSizeByCard)(int nNo, double& dWidth, double& dHeight, int& nNum);
	////设置功率
	//bool(__stdcall *HMSSetPowerByCard)(int nNo, int nPower);
	////设置频率
	//bool(__stdcall *HMSSetFreqByCard)(int nNo, int nFreq);
	////设置极耳尺寸
	//bool(__stdcall *HMSSetPoleSizeByCard)(int nNo, double dWidth, double dHight);
	////end
	friend DP_LaserInteraction;
public:
	BOOL m_bLoadSucess = FALSE;
	bool m_bComputerCard;
};

class DP_LaserInteraction;
class LaserThread : public QThread
{
	Q_OBJECT
public:
	LaserThread(DP_LaserInteraction* LaserInteraciton);
	~LaserThread();

private:
	DP_LaserInteraction* m_pLaserInteraction;
	ST_LASER_DATA m_stLaserData;
	bool m_bFlag;

private:
	void run();

public:
	bool m_bResult;
	void SetLaserData(ST_LASER_DATA stLaserData,bool bFlag = true);
};

class DP_LaserInteraction : public QObject
{
	Q_OBJECT
public:
	~DP_LaserInteraction();

private:
	bool m_bLock;
	bool m_bTcpConnect = false;	//用于判断非脱机卡卡是否连接成功
	bool m_bIsComputerCard;
	CLaserClient m_laser[2];	//非脱机卡
	QMutex m_QMutex;
private:
	DP_LaserInteraction();
	bool ServerConnectIsEnable(CString strIp, int nPort, int nTimeOut = 1);
	bool LaserCardSeparate(ST_LASER_DATA stLaser);
	bool LaserCardInPC(ST_LASER_DATA stLaser,BOOL bStart = true);

public:
	BOOL m_bEnableLaser[2];
	CLaserCtrl* m_pLaserCardCtrl; //脱机卡
	LaserThread* m_pLaserThread;

public:
	bool ConnectLaser();
	bool UploadLaserData(ST_LASER_DATA stLaser);
	bool GetLaserIsConnect();	//判断激光是否已经连接
	void SetLaserType(bool bFlag);	//设置是否为脱机卡(true为脱机卡)
	bool GetLaserType();			//返回是否为脱机卡(true为脱机卡)
	int GetLaserStatus(int nCard);

	static DP_LaserInteraction* GetInstanceObj();
	static DP_LaserInteraction* m_pInstanceObj;
	friend LaserThread;
	
Q_SIGNALS:
	void SigLaserResultMsg(QString);
};

#define LASERINTERFACE (*DP_LaserInteraction::GetInstanceObj()) //激光接口类