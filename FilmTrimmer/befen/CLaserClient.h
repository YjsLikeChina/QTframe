#pragma once
#include "afxmt.h"

#pragma comment(lib, "CLaserClient.lib")

class __declspec(dllexport) CLaserClient
{
public:
	CLaserClient(void);
	~CLaserClient(void);

public:
	BOOL Connect();
	BOOL IsConnect();
	void Disconnect();

public:
	BOOL IsMarking();
	BOOL WaitMarkEnd(int nTimeOut);
	BOOL ChangeTextByName(CString strName,CString strContent);
	BOOL OpticMatrixRotate(CString strName,double dCenterX,double dCenterY,double dAngle);
	BOOL TranslateEntity(CString strName,double dlX,double dlY,BOOL bIsAbsolute);
	BOOL MarkEntityByName(CString strName,int nWaitForEnd = 0);
	BOOL EnableEntityMark(CString strName,BOOL bEnable = FALSE);
	BOOL LoadJob(CString strFileName);

	BOOL Start(BOOL bFirst);
	BOOL Stop(BOOL bEnd);
	BOOL ChangeSpeed(double dlSpeed);
	BOOL UpdateOffset(int nGroup,int nIndex,double dlOffset);
	BOOL NewLineGroup();
	BOOL ResetResult();

	BOOL StopMark();
	BOOL OpenMarkFile(CString strFileName);
	BOOL SetPoleInfo(int nCount,CString strDist);
	int  GetPraStatus();
	BOOL SetMainFShow(bool bShow);
	BOOL SetPower(int nPower);
	BOOL SetWorkModel(int nModel);

	BOOL  SetPoleSize(double dWidht, double dHight);
	BOOL  SetPoleChangeSizes(int nCount, double dChangeValues);
	BOOL  SaveAsFile(CString strFilePath);

	BOOL  SetFreq(int nFreq);

	BOOL  SetPlcFSpeedAddr(int nAddr);
public:
	BOOL InitDll(char* pDllName);
	CString m_strError;
	BOOL m_bDebugPrint;
	CStringA m_strIp;
	int m_nPort;
protected:
	VOID* m_pClientSocket;
};
