#pragma once
#include <QObject>
#include <afxmt.h>
#include "BaseDataType.h"
#include "CLaserClient.h"

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
	//显示或隐藏打标软件编辑窗体，返回TRUE表示当前为显示状态，false为隐藏状态
	bool(__stdcall *HMSShowEditWindow)();

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

	//0713 tqc Laser dll Updata
	//获取软件版本
	bool(__stdcall *HMSGetVersion)(char* cVersion);
	//获取极耳个数
	bool(__stdcall *HMSGetPoleSizeByCard)(int nNo, double& dWidth, double& dHeight, int& nNum);
	//设置功率
	bool(__stdcall *HMSSetPowerByCard)(int nNo, int nPower);
	//设置频率
	bool(__stdcall *HMSSetFreqByCard)(int nNo, int nFreq);
	//设置极耳尺寸
	bool(__stdcall *HMSSetPoleSizeByCard)(int nNo, double dWidth, double dHight);
	friend DP_LaserInteraction;
public:
	BOOL m_bLoadSucess;
	bool m_bComputerCard;
};

class DP_LaserInteraction : public QObject
{
	Q_OBJECT
public:
	~DP_LaserInteraction();
	CLaserCtrl* m_pLaserCtrl;
	CLaserClient m_laser[2];
	BOOL m_bEnableLaser[2];
	_LASER_DATA m_stLaserData;

	bool ConnectLaser(bool bComputerCard = true);
	bool UploadLaserData(ST_LASER_DATA stLaser,bool bComputerCard = true);

	static DP_LaserInteraction* GetInstanceObj();
	static DP_LaserInteraction* m_pInstanceObj;


private:
	bool m_bLock;

private:
	DP_LaserInteraction();
	bool ServerConnectIsEnable(CString strIp, int nPort, int nTimeOut = 1);
	bool LaserCardSeparate(ST_LASER_DATA stLaser);
	bool LaserCardInPC(ST_LASER_DATA stLaser,BOOL bStart = true);
	
Q_SIGNALS:
	void SigLaserResultMsg(QString);
};

#define LASERINTERFACE (*DP_LaserInteraction::GetInstanceObj()) //激光接口类