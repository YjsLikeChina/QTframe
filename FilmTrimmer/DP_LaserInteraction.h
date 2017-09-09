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
	//��ʼ��������
	bool(__stdcall *InisHMSLaserDll)();
	//�رմ�����
	bool(__stdcall *CloseHMSLaserDll)();

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
public:
	//��ʾ�����ش������༭���壬����TRUE��ʾ��ǰΪ��ʾ״̬��falseΪ����״̬
	bool(__stdcall *HMSShowEditWindow)();

private:
	////0713 tqc Laser dll Updata
	////��ȡ����汾
	//bool(__stdcall *HMSGetVersion)(char* cVersion);
	////��ȡ��������
	//bool(__stdcall *HMSGetPoleSizeByCard)(int nNo, double& dWidth, double& dHeight, int& nNum);
	////���ù���
	//bool(__stdcall *HMSSetPowerByCard)(int nNo, int nPower);
	////����Ƶ��
	//bool(__stdcall *HMSSetFreqByCard)(int nNo, int nFreq);
	////���ü����ߴ�
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
	bool m_bTcpConnect = false;	//�����жϷ��ѻ������Ƿ����ӳɹ�
	bool m_bIsComputerCard;
	CLaserClient m_laser[2];	//���ѻ���
	QMutex m_QMutex;
private:
	DP_LaserInteraction();
	bool ServerConnectIsEnable(CString strIp, int nPort, int nTimeOut = 1);
	bool LaserCardSeparate(ST_LASER_DATA stLaser);
	bool LaserCardInPC(ST_LASER_DATA stLaser,BOOL bStart = true);

public:
	BOOL m_bEnableLaser[2];
	CLaserCtrl* m_pLaserCardCtrl; //�ѻ���
	LaserThread* m_pLaserThread;

public:
	bool ConnectLaser();
	bool UploadLaserData(ST_LASER_DATA stLaser);
	bool GetLaserIsConnect();	//�жϼ����Ƿ��Ѿ�����
	void SetLaserType(bool bFlag);	//�����Ƿ�Ϊ�ѻ���(trueΪ�ѻ���)
	bool GetLaserType();			//�����Ƿ�Ϊ�ѻ���(trueΪ�ѻ���)
	int GetLaserStatus(int nCard);

	static DP_LaserInteraction* GetInstanceObj();
	static DP_LaserInteraction* m_pInstanceObj;
	friend LaserThread;
	
Q_SIGNALS:
	void SigLaserResultMsg(QString);
};

#define LASERINTERFACE (*DP_LaserInteraction::GetInstanceObj()) //����ӿ���