#include "DP_HCPLCInteraction.h"
#include <logwrite.h>
#include "Ping.h"

#define TEMP_STR_LEN                 20

DP_HCPLCInteraction* DP_HCPLCInteraction::m_pInstanceObj = NULL;

DP_HCPLCInteraction* DP_HCPLCInteraction::GetInstanceObj()
{
	if (NULL == m_pInstanceObj)
		m_pInstanceObj = new DP_HCPLCInteraction;

	return m_pInstanceObj;
}

DP_HCPLCInteraction::DP_HCPLCInteraction()
{
	m_pHcModbusTcpClient = new HcModbusTcpClient;
}


DP_HCPLCInteraction::~DP_HCPLCInteraction()
{
	delete m_pHcModbusTcpClient;
}

int DP_HCPLCInteraction::GetDWORDFromPLC(DWORD dwPLCAddr, EM_Type addrType)
{
	int nRes = -1;
	switch (addrType)
	{
	case MD:
		nRes = m_pHcModbusTcpClient->GetDWordData(dwPLCAddr);
		break;
	case MW:
		nRes = m_pHcModbusTcpClient->GetWordData(dwPLCAddr);
		break;
	case QW:
		nRes = m_pHcModbusTcpClient->ReadInChannel(dwPLCAddr);
		break;
	default:
		nRes = -1;
		break;
	}
	return nRes;
}

bool DP_HCPLCInteraction::GetBOOLFromPLC(DWORD dwPLCAddr, EM_Type addrType)
{
	bool bRes = false;
	switch (addrType)
	{
	case MX:
		bRes = m_pHcModbusTcpClient->ReadWBit(dwPLCAddr);
		break;
	case QX:
		bRes = m_pHcModbusTcpClient->ReadBit(dwPLCAddr);
		break;
	}
	return bRes;
}

bool DP_HCPLCInteraction::SetDWORDToPLC(int nData, DWORD dwPLCAddr, EM_Type addrType)
{
	bool bRes = false;
	switch (addrType)
	{
	case MD:
		m_pHcModbusTcpClient->SetDWordData(dwPLCAddr, nData);
		bRes = true;
		break;
	case MW:
	case QW:
		m_pHcModbusTcpClient->SetWordData(dwPLCAddr, nData);
		bRes = true;
		break;
	case INVALID:
		break;
	default:
		PRINTF(_T("参数类型设定错误,调用 SetDWORDToPLC() 写入PLC失败!"));
		bRes = false;
		break;
	}
	return bRes;
}

bool DP_HCPLCInteraction::SetBOOLToPLC(bool bData, DWORD dwPLCAddr, EM_Type addrType)
{
	bool bRes = false;
	switch (addrType)
	{
	case MX:
		m_pHcModbusTcpClient->WriteWBit(dwPLCAddr, bData);
		bRes = true;
		break;
	case QX:
		m_pHcModbusTcpClient->WriteBit(dwPLCAddr, bData);
		bRes = true;
		break;
	case INVALID:
		break;
	default:
		PRINTF(_T("参数类型设定错误,调用 SetBOOLToPLC() 写入PLC失败!"));
		bRes = false;
		break;
	}
	return bRes;
}

bool DP_HCPLCInteraction::Init_HC_DLL()
{
	return m_pHcModbusTcpClient->Init();
}

bool DP_HCPLCInteraction::Connect_HC_PLC()
{
	return m_pHcModbusTcpClient->Connect();
}

////汇川PLC
HcModbusTcpClient::HcModbusTcpClient(void)
{
	m_nPort = 502;
	m_strIpAddress = _T("192.168.1.88");
	CStringA str;
	str = m_strIpAddress;
	DWORD IpAddress = inet_addr("192.168.1.88");
	m_dIpAddress = IpAddress;//inet_addr("192.168.1.2");
	m_bIsConnected = FALSE;
	m_bFirstFailed = TRUE;
	m_bExiting = FALSE;
}

HcModbusTcpClient::~HcModbusTcpClient(void)
{
	if (m_bIsConnected)
	{
		m_bIsConnected = false;
		m_fnClose(1);
	}
	::FreeLibrary(hInst);
}

BOOL HcModbusTcpClient::Init()
{
	hInst = LoadLibraryA("HCTcp.dll");
	if (NULL == hInst)
	{
		//AfxMessageBox(_T("加载动态库HCTcp.dll 失败."));
		return FALSE;
	}
	m_fnConnect = (MBTCPCONNECT)GetProcAddress(hInst, "mbtcpConnect");
	if (!m_fnConnect)
	{
		//AfxMessageBox(_T("获取函数mbtcpConnect 失败."));
		return FALSE;
	}
	m_fnClose = (MBTCPCLOSE)GetProcAddress(hInst, "mbtcpClose");
	if (!m_fnClose)
	{
		//AfxMessageBox(_T("获取函数mbtcpClose 失败."));
		return FALSE;
	}
	m_fnSetTimeOut = (MBTCPSETTIMEOUT)GetProcAddress(hInst, "mbtcpSetTimeout");
	if (!m_fnSetTimeOut)
	{
		//AfxMessageBox(_T("获取函数mbtcpSetTimeout 失败."));
		return FALSE;
	}
	m_fnSetDelay = (MBTCPSETDELAY)GetProcAddress(hInst, "mbtcpSetDelay");
	if (!m_fnSetDelay)
	{
		//AfxMessageBox(_T("获取函数mbtcpSetDelay 失败."));
		return FALSE;
	}
	m_fnMbt01 = (MBTCPFCN01)GetProcAddress(hInst, "mbtcpfcn01");
	if (!m_fnMbt01)
	{
		//AfxMessageBox(_T("获取函数mbtcpfcn01 失败."));
		return FALSE;
	}
	m_fnMbt02 = (MBTCPFCN01)GetProcAddress(hInst, "mbtcpfcn02");
	if (!m_fnMbt02)
	{
		//AfxMessageBox(_T("获取函数mbtcpfcn02 失败."));
		return FALSE;
	}
	m_fnMbt03 = (MBTCPFCN03)GetProcAddress(hInst, "mbtcpfcn03");
	if (!m_fnMbt03)
	{
		//AfxMessageBox(_T("获取函数mbtcpfcn03 失败."));
		return FALSE;
	}
	m_fnMbt04 = (MBTCPFCN04)GetProcAddress(hInst, "mbtcpfcn04");
	if (!m_fnMbt04)
	{
		//AfxMessageBox(_T("获取函数mbtcpfcn04 失败."));
		return FALSE;
	}
	m_fnMbt05 = (MBTCPFCN05)GetProcAddress(hInst, "mbtcpfcn05");
	if (!m_fnMbt05)
	{
		//AfxMessageBox(_T("获取函数mbtcpfcn05 失败."));
		return FALSE;
	}
	m_fnMbt06 = (MBTCPFCN06)GetProcAddress(hInst, "mbtcpfcn06");
	if (!m_fnMbt06)
	{
		//AfxMessageBox(_T("获取函数mbtcpfcn06 失败."));
		return FALSE;
	}
	m_fnMbt15 = (MBTCPFCN15)GetProcAddress(hInst, "mbtcpfcn15");
	if (!m_fnMbt15)
	{
		//AfxMessageBox(_T("获取函数mbtcpfcn15 失败."));
		return FALSE;
	}
	m_fnMbt16 = (MBTCPFCN16)GetProcAddress(hInst, "mbtcpfcn16");
	if (!m_fnMbt06)
	{
		//AfxMessageBox(_T("获取函数mbtcpfcn16 失败."));
		return FALSE;
	}
	return TRUE;
}

BOOL HcModbusTcpClient::Connect()
{
	PRINTF(_T("HcModbusTcpClient::Connect() start..."));
	if (m_bExiting)
		return FALSE;
	BOOL bIsEnable = FALSE;
	CPing ping;
	CStringA strIp;
	strIp = m_strIpAddress;
	for (int i = 0; i < 3; i++)
	{
		if (ServerConnectIsEnable(m_strIpAddress, m_nPort))//if(ping.Ping(strIp.GetBuffer()))
		{
			bIsEnable = TRUE;
			break;
		}
		if (m_bExiting)
			return FALSE;
		strIp.ReleaseBuffer();
		Sleep(1);
	}
	strIp.ReleaseBuffer();
	if (!bIsEnable)
	{
		CString strMsg;
		strMsg.Format(_T("连接控制器失败:%s"), m_strIpAddress);
		PRINTF(strMsg);
		if (m_bFirstFailed)
		{
			//AfxMessageBox(strMsg);
			m_bFirstFailed = FALSE;
		}
		m_bIsConnected = FALSE;
		m_dwLastConnectTime = GetTickCount();
		return FALSE;
	}
	Sleep(1);
	m_fnSetTimeOut(1, 500);
	if (m_bExiting)
		return FALSE;
	int nRes = m_fnConnect(1, m_nPort, m_dIpAddress);
	m_bIsConnected = nRes;
	if (!m_bIsConnected)
	{
		CString strMsg;
		strMsg.Format(_T("连接%s,nPort:%d,IpPort:%d 失败."), m_strIpAddress, 1, m_nPort);
		PRINTF(strMsg);
		if (m_bFirstFailed)
		{
			//AfxMessageBox(strMsg);
			//BLMessageBox(strMsg);
			m_bFirstFailed = FALSE;
		}
		m_bIsConnected = FALSE;
	}
	else
	{
		m_bFirstFailed = TRUE;
	}
	PRINTF(_T("HcModbusTcpClient::Connect() finished."));
	m_bIsConnected = TRUE;
	m_dwLastConnectTime = GetTickCount();
	return nRes;
}

bool HcModbusTcpClient::ServerConnectIsEnable(CString strIp, int nPort, int nTimeOut)
{
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to WSAStartup\r\n");
		return FALSE;
	}
	SOCKET fd;
	if ((fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		int nCode = ::WSAGetLastError();
		printf("Failed to create socket\r\n");
		PRINTF(_T("Client Failed to create socket."));
		return FALSE;
	}
	char tmpstr[TEMP_STR_LEN];
	memset(tmpstr, 0, TEMP_STR_LEN);
	::WideCharToMultiByte(CP_ACP, 0, strIp.GetBuffer(), -1, tmpstr, TEMP_STR_LEN, NULL, NULL);
	strIp.ReleaseBuffer();
	struct sockaddr_in video_server;
	memset(&video_server, 0, sizeof(video_server));
	video_server.sin_family = AF_INET;
	video_server.sin_addr.s_addr = inet_addr(tmpstr);
	video_server.sin_port = htons(nPort);

	int error = -1, len;
	len = sizeof(int);
	timeval tm;
	fd_set set;
	unsigned long ul = 1;
	::ioctlsocket(fd, FIONBIO, &ul); //设置为非阻塞模式

	bool ret = false;
	if (::connect(fd, (struct sockaddr *)&video_server, sizeof(video_server)) == -1)
	{
		tm.tv_sec = nTimeOut;
		tm.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(fd, &set);
		if (::select(fd + 1, NULL, &set, NULL, &tm) > 0)
		{
			::getsockopt(fd, SOL_SOCKET, SO_ERROR, (char *)&error, /*(socklen_t *)*/&len);
			if (error == 0)
				ret = TRUE;
			else
				ret = false;
		}
		else
			ret = false;
	}
	else
		ret = TRUE;
	ul = 0;
	::ioctlsocket(fd, FIONBIO, &ul); //设置为阻塞模式
	if (!ret)
	{
		::closesocket(fd);
		fprintf(stderr, "Cannot Connect the server!/n");
		CString strMsg;
		strMsg.Format(_T("Client Cannot Connect the server %s:%d."), strIp, nPort);
		PRINTF(strMsg);

		return FALSE;
	}
	::closesocket(fd);
	fprintf(stderr, "Connected!/n");
	return TRUE;
	return false;
}

BOOL HcModbusTcpClient::GetMutiWordData(int nAddress, int* ReadData, int nCount /*= 1*/)
{
	if (!m_bIsConnected)
		return 0;
	m_readLock.Lock();

	BYTE RxdBuffer[200];
	int len = 0;
	int nReadCount = nCount;
	m_fnMbt03(1, 255, nAddress, nReadCount, (int*)RxdBuffer, &len);
	WORD* pWord = new WORD[nReadCount];
	int nDataLen = 2 * nReadCount;
	if (len > nDataLen)
	{
		for (int i = len - nDataLen; i < len; i += 2)
		{
			pWord[(i - (len - nDataLen)) / 2] = MAKEWORD(RxdBuffer[i + 1], RxdBuffer[i]);
			ReadData[(i - (len - nDataLen)) / 2] = pWord[(i - (len - nDataLen)) / 2];
		}
	}
	else
	{
		delete[]pWord;
		m_fnClose(1);
		PRINTF(_T("GetMutiWordData m_fnMbt03 error,nAddress%d,nCount%d,len%d."), nAddress, nCount, len);
		m_bIsConnected = FALSE;
		m_readLock.Unlock();
		return FALSE;
	}
	delete[]pWord;
	m_readLock.Unlock();
	return TRUE;
}

DWORD HcModbusTcpClient::GetDWordData(int nAddress)
{
	///////////////获取汇川PLC数据////////////
	//BYTE* RxdBuffer = new BYTE[20+nCount*2];
	if (!m_bIsConnected)
		return 0;
	m_readLock.Lock();

	BYTE RxdBuffer[20];
	int len = 0;
	int nReadCount = 2;
	m_fnMbt03(1, 255, nAddress * 2, nReadCount, (int*)RxdBuffer, &len);
	WORD* pWord = new WORD[nReadCount];
	int nDataLen = 2 * nReadCount;
	if (len > nDataLen)
	{
		for (int i = len - nDataLen; i < len; i += 2)
		{
			pWord[(i - (len - nDataLen)) / 2] = MAKEWORD(RxdBuffer[i + 1], RxdBuffer[i]);
		}
	}
	else
	{
		delete[]pWord;
		m_fnClose(1);
		PRINTF(_T("GetDWordData m_fnMbt03 error,nAddress%d,len%d."), nAddress, len);
		m_bIsConnected = FALSE;
		m_readLock.Unlock();
		return FALSE;
	}
	DWORD data = *(DWORD*)pWord;
	delete[]pWord;
	m_readLock.Unlock();
	///////////////获取汇川PLC数据结束////////////
	return data;
}

WORD HcModbusTcpClient::GetWordData(int nAddress)
{
	if (!m_bIsConnected)
		return 0;
	m_readLock.Lock();
	///////////////获取汇川PLC数据////////////
	BYTE RxdBuffer[20];
	int len = 0;
	int nReadCount = 1;
	m_fnMbt03(1, 255, nAddress, nReadCount, (int*)RxdBuffer, &len);
	WORD* pWord = new WORD[nReadCount];
	int nDataLen = 2 * nReadCount;
	if (len > nDataLen)
	{
		for (int i = len - nDataLen; i < len; i += 2)
		{
			pWord[(i - (len - nDataLen)) / 2] = MAKEWORD(RxdBuffer[i + 1], RxdBuffer[i]);
		}
	}
	else
	{
		delete[]pWord;
		m_fnClose(1);
		m_bIsConnected = FALSE;
		PRINTF(_T("GetWordData m_fnMbt03 error,nAddress%d,len%d."), nAddress, len);
		m_readLock.Unlock();
		return FALSE;
	}
	DWORD data = *(DWORD*)pWord;
	delete[]pWord;
	m_readLock.Unlock();
	///////////////获取汇川PLC数据结束////////////
	return data;
}

BOOL HcModbusTcpClient::SetDWordData(int nAddress, int nValue)
{
	if (!m_bIsConnected)
		return 0;
	m_readLock.Lock();
	BYTE RxdBuffer[20];
	WORD TxdBuffer[20];
	TxdBuffer[0] = LOWORD(nValue);
	TxdBuffer[1] = HIWORD(nValue);
	int len = 0;
	int nReadCount = 1;
	int nRes = m_fnMbt16(1, 255, nAddress * 2, 2, TxdBuffer, (int*)RxdBuffer, &len);
	if (nRes < 1)
	{
		m_fnClose(1);
		m_bIsConnected = FALSE;
		PRINTF(_T("SetDWordData m_fnMbt16 error,nAddress%d,nValue%d,len%d."), nAddress, nValue, len);
		m_readLock.Unlock();
		return FALSE;
	}
	m_readLock.Unlock();
	return nRes;
}

BOOL HcModbusTcpClient::SetWordData(int nAddress, int nValue)
{
	if (!m_bIsConnected)
		return 0;
	m_readLock.Lock();
	BYTE RxdBuffer[20];
	WORD TxdBuffer[20];
	TxdBuffer[0] = nValue;
	TxdBuffer[1] = 0;
	int len = 0;
	int nReadCount = 1;
	int nRes = m_fnMbt16(1, 255, nAddress, 1, TxdBuffer, (int*)RxdBuffer, &len);
	if (nRes < 1)
	{
		m_fnClose(1);
		m_bIsConnected = FALSE;
		PRINTF(_T("SetWordData m_fnMbt16 error,nAddress%d,nValue%d,len%d."), nAddress, nValue, len);
		m_readLock.Unlock();
		return FALSE;
	}
	m_readLock.Unlock();
	return nRes;
}

BOOL HcModbusTcpClient::ReadBit(int nAddress)
{
	if (!m_bIsConnected)
		return 0;
	m_readLock.Lock();
	BYTE RxdBuffer[20];
	int len = 0;
	m_fnMbt02(1, 255, nAddress, 1, (int*)RxdBuffer, &len);
	if (len > 0)
	{
		m_readLock.Unlock();
		return RxdBuffer[len - 1];
	}
	m_fnClose(1);
	m_bIsConnected = FALSE;
	PRINTF(_T("ReadBit m_fnMbt02 error,nAddress%d,len%d."), nAddress, len);
	m_readLock.Unlock();
	return FALSE;
}

BOOL HcModbusTcpClient::ReadWBit(int nAddress)
{
	WORD nRes = GetWordData(nAddress / 16);
	int nPoint = nAddress % 16;

	return nRes & 0x01 << nPoint;
}

int HcModbusTcpClient::ReadInChannel(int nAddressStart, int nCount /*= 8*/)
{
	if (!m_bIsConnected)
		return 0;
	m_readLock.Lock();
	if (nCount > 32)
		nCount = 32;
	BYTE RxdBuffer[20];
	int len = 0;
	m_fnMbt02(1, 255, nAddressStart, nCount, (int*)RxdBuffer, &len);
	if (len > 0 && len < 19)
	{
		m_readLock.Unlock();
		int res = RxdBuffer[len - 1];
		if (nCount < 9)
			res = RxdBuffer[len - 1];
		else
		{
			res = RxdBuffer[len - 2];
			res |= RxdBuffer[len - 1] << 8;
		}
		return res;
	}
	m_fnClose(1);
	m_bIsConnected = FALSE;
	PRINTF(_T("ReadInChannel m_fnMbt02 error,AddressStart%d,count%d,len%d."), nAddressStart, nCount, len);
	m_readLock.Unlock();
	return 0;
}

BOOL HcModbusTcpClient::WriteBit(int nAddress, BOOL bOn /*= TRUE*/)
{
	if (!m_bIsConnected)
		return 0;
	m_readLock.Lock();
	BYTE RxdBuffer[20];
	int len = 0;
	m_fnMbt05(1, 255, nAddress, 1, bOn, (int*)RxdBuffer, &len);
	if (len > 0)
	{
		m_readLock.Unlock();
		return TRUE;
	}
	m_fnClose(1);
	//Connect();
	m_bIsConnected = FALSE;
	PRINTF(_T("WriteBit m_fnMbt05 error,nAddress%d,bOn%d,len%d."), nAddress, bOn, len);
	m_readLock.Unlock();
	return FALSE;
}

BOOL HcModbusTcpClient::WriteWBit(int nAddress, BOOL bOn /*= TRUE*/)
{
	WORD nRes = GetWordData(nAddress / 16);//
	int nPoint = nAddress % 16;
	if (bOn)
	{
		nRes |= 0x0001 << nPoint;
	}
	else
	{
		nRes &= ~(0x0001 << nPoint);
	}

	return SetWordData(nAddress / 16, nRes);
}
