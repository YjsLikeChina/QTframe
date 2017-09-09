#pragma once

#include "BaseDataType.h"
#include <afxmt.h>

class DP_HCPLCInteraction;

typedef int(*MBTCPCONNECT)(int nport, int IpPort, DWORD IpAddress);
typedef int(*MBTCPCLOSE)(int nport);
typedef int(*MBTCPSETTIMEOUT)(int nport, int nTime);
typedef int(*MBTCPSETDELAY)(int nport, int nTime);
typedef int(*MBTCPFCN01)(int nport, int node, int address, int Count, int* RxdBuffer, int* RxdLength);
typedef int(*MBTCPFCN02)(int nport, int node, int address, int Count, int* RxdBuffer, int* RxdLength);
typedef int(*MBTCPFCN03)(int nport, int node, int address, int Count, int* RxdBuffer, int* RxdLength);
typedef int(*MBTCPFCN04)(int nport, int node, int address, int Count, int* RxdBuffer, int* RxdLength);
typedef int(*MBTCPFCN05)(int nport, int node, int address, int Count, int value, int* RxdBuffer, int* RxdLength);
typedef int(*MBTCPFCN06)(int nport, int node, int address, int Count, int value, int* RxdBuffer, int* RxdLength);

typedef int(*MBTCPFCN15)(int nport, int node, int address, int Count, WORD* TxdBuffer, int* RxdBuffer, int* RxdLength);
typedef int(*MBTCPFCN16)(int nport, int node, int address, int Count, WORD* TxdBuffer, int* RxdBuffer, int* RxdLength);

class HcModbusTcpClient
{
private:
	HcModbusTcpClient(void);
	~HcModbusTcpClient(void);

	BOOL Init();

	MBTCPCONNECT m_fnConnect;
	MBTCPCLOSE m_fnClose;
	MBTCPSETTIMEOUT m_fnSetTimeOut;
	MBTCPSETDELAY m_fnSetDelay;
	MBTCPFCN01 m_fnMbt01;
	MBTCPFCN02 m_fnMbt02;
	MBTCPFCN03 m_fnMbt03;
	MBTCPFCN04 m_fnMbt04;
	MBTCPFCN05 m_fnMbt05;
	MBTCPFCN06 m_fnMbt06;

	MBTCPFCN15 m_fnMbt15;
	MBTCPFCN16 m_fnMbt16;
	HINSTANCE hInst;
	BOOL Connect();
	bool ServerConnectIsEnable(CString strIp, int nPort, int nTimeOut = 1);
	BOOL GetMutiWordData(int nAddress, int* ReadData, int nCount = 1);
	DWORD GetDWordData(int nAddress);
	WORD GetWordData(int nAddress);
	BOOL SetDWordData(int nAddress, int nValue);
	BOOL SetWordData(int nAddress, int nValue);
	BOOL ReadBit(int nAddress);
	BOOL ReadWBit(int nAddress);
	int ReadInChannel(int nAddressStart, int nCount = 8);
	BOOL WriteBit(int nAddress, BOOL bOn = TRUE);
	BOOL WriteWBit(int nAddress, BOOL bOn = TRUE);
private:
	int m_nPort;
	BOOL m_bIsConnected;								//PLC是否已经连接
	BOOL m_bFirstFailed;
	CString m_strIpAddress;
	DWORD m_dIpAddress;
	DWORD m_dwLastConnectTime;
	CCriticalSection m_readLock;
	BOOL m_bExiting;
	friend DP_HCPLCInteraction;
};
class DP_HCPLCInteraction
{

public:
	~DP_HCPLCInteraction();
	static DP_HCPLCInteraction* GetInstanceObj();
	static DP_HCPLCInteraction* m_pInstanceObj;
public:
	int		GetDWORDFromPLC(DWORD dwPLCAddr, EM_Type addrType); //
	bool	GetBOOLFromPLC(DWORD dwPLCAddr, EM_Type addrType);
	bool	SetDWORDToPLC(int nData, DWORD dwPLCAddr, EM_Type addrType);
	bool	SetBOOLToPLC(bool nData, DWORD dwPLCAddr, EM_Type addrType);

	bool	Init_HC_DLL();
	bool	Connect_HC_PLC();

private:
	DP_HCPLCInteraction();
	HcModbusTcpClient* m_pHcModbusTcpClient;
};

#define HC_PLC_INTERFACE (*DP_HCPLCInteraction::GetInstanceObj()) //PLC接口类
