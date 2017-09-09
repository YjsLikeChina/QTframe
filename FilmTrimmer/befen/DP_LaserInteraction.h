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
	//��ʼ��������
	bool(__stdcall *InisHMSLaserDll)();
	//�رմ�����
	bool(__stdcall *CloseHMSLaserDll)();
	//��ʾ�����ش������༭���壬����TRUE��ʾ��ǰΪ��ʾ״̬��falseΪ����״̬
	bool(__stdcall *HMSShowEditWindow)();

	/////////////////����ר��///////////////////////
	//���ļ�
	bool(__stdcall *HMSOpenFile)(char* cFilePath);
	//���ù����ٶ�
	bool(__stdcall *HMSChangeSpeed)(double dlSpeed);
	//���ü�����Ϣ
	bool(__stdcall *HMSSetPoleInfo)(int nCount, char* cIntervals);
	//��ȡ����״̬
	int(__stdcall *HMSGetPraStatus)(int No);
	//���ü��⹦��
	bool(__stdcall *HMSSetPower)(int nPower);
	//����Ƶ��
	bool(__stdcall *HMSSetFreq)(int nFreq);
	//���ù���ģʽ
	bool(__stdcall *HMSSetWorkModel)(int nModel);
	//���ü����ߴ�
	bool(__stdcall *HMSSetPoleSize)(double dWidth, double dHight);
	//��������ͼ��
	bool(__stdcall *HMSCreatePole)(SPloeSizeInfo *pSizeInfo);
	//�ϴ������������
	bool(__stdcall *UploadMarkDate)(int nNo, int nModel);

	//0713 tqc Laser dll Updata
	//��ȡ����汾
	bool(__stdcall *HMSGetVersion)(char* cVersion);
	//��ȡ��������
	bool(__stdcall *HMSGetPoleSizeByCard)(int nNo, double& dWidth, double& dHeight, int& nNum);
	//���ù���
	bool(__stdcall *HMSSetPowerByCard)(int nNo, int nPower);
	//����Ƶ��
	bool(__stdcall *HMSSetFreqByCard)(int nNo, int nFreq);
	//���ü����ߴ�
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

#define LASERINTERFACE (*DP_LaserInteraction::GetInstanceObj()) //����ӿ���