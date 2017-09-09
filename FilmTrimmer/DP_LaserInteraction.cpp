#include "DP_LaserInteraction.h"
#include "Ping.h"
#include <logwrite.h>
#include "UI_MessageBox.h"
#define TEMP_STR_LEN 20

DP_LaserInteraction* DP_LaserInteraction::m_pInstanceObj = NULL;

DP_LaserInteraction* DP_LaserInteraction::GetInstanceObj()
{
	if (NULL == m_pInstanceObj)
		m_pInstanceObj = new DP_LaserInteraction;

	return m_pInstanceObj;
}

CLaserCtrl::CLaserCtrl(void)
{
	m_HmsDLL = NULL;
	m_bLoadSucess = FALSE;
	InisHMSLaserDll = NULL;
	CloseHMSLaserDll = NULL;
	HMSShowEditWindow = NULL;
	HMSOpenFile = NULL;
	HMSChangeSpeed = NULL;
	HMSSetPoleInfo = NULL;
	HMSGetPraStatus = NULL;
	HMSSetPower = NULL;
	HMSSetFreq = NULL;
	HMSSetWorkModel = NULL;
	HMSSetPoleSize = NULL;
	HMSCreatePole = NULL;
	UploadMarkDate = NULL;
}


CLaserCtrl::~CLaserCtrl(void)
{
	if (!m_bComputerCard)
		return;
	if (CloseHMSLaserDll())
	{
		CloseHMSLaserDll();
	}
}

BOOL CLaserCtrl::InitDll()
{
	m_HmsDLL = LoadLibraryA("HMSLaser.dll");
	if (NULL == m_HmsDLL)
	{
		//AfxMessageBox(_T("HMSLaser.dll 加载失败"));
		m_bLoadSucess = FALSE;
	}
	else
	{
		char* pchFun = "InisHMSLaserDll";
		CStringA strMessage;
		FARPROC pFunProc = GetProcAddress(m_HmsDLL, pchFun);
		for (;;)
		{
			if (!pFunProc)
				break;
			InisHMSLaserDll = (bool(__stdcall *)())pFunProc;

			pchFun = "CloseHMSLaserDll";
			pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			if (!pFunProc)
				break;
			CloseHMSLaserDll = (bool(__stdcall *)())pFunProc;

			pchFun = "HMSShowEditWindow";
			pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			if (!pFunProc)
				break;
			HMSShowEditWindow = (bool(__stdcall *)())pFunProc;

			pchFun = "HMSCreatePole";
			pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			if (!pFunProc)
				break;
			HMSCreatePole = (bool(__stdcall *)(SPloeSizeInfo *pSizeInfo))pFunProc;

			pchFun = "HMSOpenFile";
			pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			if (!pFunProc)
				break;
			HMSOpenFile = (bool(__stdcall *)(char* cFilePath))pFunProc;

			pchFun = "HMSChangeSpeed";
			pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			if (!pFunProc)
				break;
			HMSChangeSpeed = (bool(__stdcall *)(double dlSpeed))pFunProc;

			pchFun = "HMSSetPoleInfo";
			pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			if (!pFunProc)
				break;
			HMSSetPoleInfo = (bool(__stdcall *)(int nCount, char* cIntervals))pFunProc;

			pchFun = "HMSGetPraStatus";
			pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			if (!pFunProc)
				break;
			HMSGetPraStatus = (int(__stdcall *)(int No))pFunProc;

			pchFun = "HMSSetPower";
			pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			if (!pFunProc)
				break;
			HMSSetPower = (bool(__stdcall *)(int nPower))pFunProc;

			pchFun = "HMSSetFreq";
			pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			if (!pFunProc)
				break;
			HMSSetFreq = (bool(__stdcall *)(int nFreq))pFunProc;

			pchFun = "HMSSetPoleSize";
			pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			if (!pFunProc)
				break;
			HMSSetPoleSize = (bool(__stdcall *)(double dWidth, double dHight))pFunProc;

			pchFun = "UploadMarkDate";
			pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			if (!pFunProc)
				break;
			UploadMarkDate = (bool(__stdcall *)(int nNo, int nModel))pFunProc;

			//0713 tqc Laser dll Updata Test
			//pchFun = "HMSGetVersion";
			//pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			//if (!pFunProc)
			//	break;
			//HMSGetVersion = (bool(__stdcall *)(char* cVersion))pFunProc;

			//pchFun = "HMSGetPoleSizeByCard";
			//pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			//if (!pFunProc)
			//	break;
			//HMSGetPoleSizeByCard = (bool(__stdcall *)(int nNo, double& dWidth, double& dHeight, int& nNum))pFunProc;

			//pchFun = "HMSSetPowerByCard";
			//pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			//if (!pFunProc)
			//	break;
			//HMSSetPowerByCard = (bool(__stdcall *)(int nNo, int nPower))pFunProc;

			//pchFun = "HMSSetFreqByCard";
			//pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			//if (!pFunProc)
			//	break;
			//HMSSetFreqByCard = (bool(__stdcall *)(int nNo, int nFreq))pFunProc;

			//pchFun = "HMSSetPoleSizeByCard";
			//pFunProc = GetProcAddress(m_HmsDLL, pchFun);
			//if (!pFunProc)
			//	break;
			//HMSSetPoleSizeByCard = (bool(__stdcall *)(int nNo, double dWidth, double dHight))pFunProc;
			//end 

			if (InisHMSLaserDll())
			{
				m_bLoadSucess = TRUE;
			}
			else
			{
				AfxMessageBox(_T("调用函数InisHMSLaserDll失败"));
			}
			break;
		}
		if (!m_bLoadSucess)
		{
			strMessage.Format("获取函数%s失败", pchFun);
			AfxMessageBox(CString(strMessage));
		}
	}
	return m_bLoadSucess;
}


DP_LaserInteraction::DP_LaserInteraction()
{
	m_pLaserCardCtrl = new CLaserCtrl;
	m_bEnableLaser[0] = false;
	m_bEnableLaser[1] = false;
	m_bLock = false;
	m_pLaserThread = new LaserThread(this);
}


DP_LaserInteraction::~DP_LaserInteraction()
{
	delete m_pLaserCardCtrl;
}

bool DP_LaserInteraction::ConnectLaser()
{
	bool bRes = false;
	if (m_bIsComputerCard)
	{
		m_pLaserCardCtrl->m_bComputerCard = true;
		if(!m_pLaserCardCtrl->m_bLoadSucess)
			bRes = m_pLaserCardCtrl->InitDll();
	}
	else 
	{
		for (int i = 0; i < 2; i++)
		{
			m_laser[i].Disconnect();
			Sleep(1);
			CStringA strIp;
			strIp = m_laser[i].m_strIp;
			if (m_bEnableLaser[i])
			{
				CPing ping;
				if (ServerConnectIsEnable(CString(m_laser[i].m_strIp), m_laser[i].m_nPort))
				{
					if (m_laser[i].Connect())
					{
						bRes = true;
					}
					else
					{
						CString strMsg;
						strMsg.Format(_T("%s Connect Failed."), CString(m_laser[i].m_strIp));

						PRINTF(strMsg);
						bRes = false;
						m_bTcpConnect = bRes;
					}
				}
				else
				{
					CString strMsg;
					strMsg.Format(_T("%s Connect Failed."), CString(m_laser[i].m_strIp));

					PRINTF(strMsg);
					bRes = false;
				}
			}
		}
	}
	m_bTcpConnect = bRes;
	return bRes;
}

bool DP_LaserInteraction::UploadLaserData(ST_LASER_DATA stLaser)
{
	bool bRes = false;
	m_pLaserThread->SetLaserData(stLaser);
	m_pLaserThread->start();

	QEventLoop loop;
	connect(m_pLaserThread, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();//QEventLoop::ExcludeUserInputEvents);

	return m_pLaserThread->m_bResult;
}

bool DP_LaserInteraction::GetLaserIsConnect()
{
	if (m_bIsComputerCard)
		return m_pLaserCardCtrl->m_bLoadSucess;
	else
		return m_bTcpConnect;
}

void DP_LaserInteraction::SetLaserType(bool bFlag)
{
	m_bIsComputerCard = bFlag;
}

bool DP_LaserInteraction::GetLaserType()
{
	return m_bIsComputerCard;
}

int DP_LaserInteraction::GetLaserStatus(int nCard)
{
	int nLaserState = -1;
	if (m_bIsComputerCard != TRUE) //非脱机卡
	{
		//for (int i = 0; i < 2; i++)
		{
			if (m_bEnableLaser[nCard])
			{
				nLaserState = m_laser[nCard].GetPraStatus();
				nLaserState += m_laser[nCard].IsConnect();
			}
			else
			{
				nLaserState = -1;
			}
		}
	}
	else //脱机卡
	{
		//for (int i = 0; i < 2; i++)
		{
			if (m_bEnableLaser[nCard] && m_pLaserCardCtrl->m_bLoadSucess)
			{
				nLaserState = m_pLaserCardCtrl->HMSGetPraStatus(nCard);
				nLaserState += m_pLaserCardCtrl->m_bLoadSucess;
			}
			else
			{
				nLaserState = -1;
			}
		}
	}
	return nLaserState;
}

bool DP_LaserInteraction::ServerConnectIsEnable(CString strIp, int nPort, int nTimeOut /*= 1*/)
{
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to WSAStartup\r\n");
		return FALSE;
	}
	SOCKET fd;
	if ((fd = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
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

bool DP_LaserInteraction::LaserCardSeparate(ST_LASER_DATA stLaser)
{
	m_QMutex.lock();
	if (m_bLock)
	{
		PRINTF(_T("激光数据上传已经启动!"));
		emit MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("激光数据上传已经启动!"), NODOMODEL,2000,1);//SigLaserResultMsg();
		return false;
	}
	m_bLock = true;
	BOOL bResult = true;
	emit MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("激光数据上传中..."), NODOMODEL, 60000, 1);
	for (int i = 0; i < 2; i++)
	{
		int nReadLaserStrat = GetTickCount(); //1026 tqc add
		if (m_bEnableLaser[i] && m_pLaserCardCtrl->m_bLoadSucess)
		{
			if (m_pLaserCardCtrl->HMSGetPraStatus(i) <= 0)
			{
				emit MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("激光状态未连接"),NODOMODEL);//SigLaserResultMsg();
				bResult = FALSE;
				break;
			}
			if (stLaser.strLaserFilePath.IsEmpty())
			{
				CString strFile;
				strFile = stLaser.strLaserFilePath + stLaser.strLaserFileName +  _T("*.hms");
				CFileFind find;
				BOOL bFindFile = find.FindFile(strFile);
				if (bFindFile)
				{
					CStringA strFileA;
					strFileA = strFile;
					PRINTF(_T("Call laser function:HMSOpenFile(%s),to laser%d start..."), CString(strFileA), i + 1);
					bResult = m_pLaserCardCtrl->HMSOpenFile(strFileA.GetBuffer());
					strFileA.ReleaseBuffer();
					PRINTF(_T("Call laser function:HMSOpenFile to laser%d end,result%d."), i + 1, bResult);
					if (!bResult)
						break;
				}
			}
			CStringA strListDist;
			strListDist = stLaser.strLaserStepInfo;
			PRINTF(_T("Call laser function:HMSSetPoleInfo(%d,%s),to laser start..."), stLaser.nLaserStep, stLaser.strLaserStepInfo);
			bResult = m_pLaserCardCtrl->HMSSetPoleInfo(stLaser.nLaserStep, strListDist.GetBuffer());
			strListDist.ReleaseBuffer();
			PRINTF(_T("Call laser function:HMSSetPoleInfo,to laser end,result%d."), bResult);
			if (!bResult)
				break;

			PRINTF(_T("Call laser function:HMSSetPoleSizeByCard(%.3f,%.3f),to laser%d start..."), stLaser.dlEarWidth, stLaser.dlEarHeight, i + 1);
			//bResult = m_pLaserCardCtrl->HMSSetPoleSizeByCard(i, stLaser.dlEarWidth, stLaser.dlEarHeight);
			bResult = m_pLaserCardCtrl->HMSSetPoleSize(stLaser.dlEarWidth, stLaser.dlEarHeight);
			PRINTF(_T("Call laser function:HMSSetPoleSizeByCard,to laser%d end,result%d."), i + 1, bResult);
			if (!bResult)
				break;

			if (i == 0)
			{
				////
				//PRINTF(_T("Call laser function:HMSSetPoleSizeByCard(%.3f,%.3f),to laser%d start..."), stLaser.dlEarWidth, stLaser.dlEarHeight, i + 1);
				////bResult = m_pLaserCardCtrl->HMSSetPoleSizeByCard(i, stLaser.dlEarWidth, stLaser.dlEarHeight);
				//bResult = m_pLaserCardCtrl->HMSSetPoleSize(stLaser.dlEarWidth, stLaser.dlEarHeight);
				//PRINTF(_T("Call laser function:HMSSetPoleSizeByCard,to laser%d end,result%d."), i + 1, bResult);
				//if (!bResult)
				//	break;
				////
				PRINTF(_T("Call laser function:HMSSetPowerByCard(%d),to laser1 start..."), int(stLaser.dlLaser1Power + 0.00001));
				bResult = m_pLaserCardCtrl->HMSSetPower(int(stLaser.dlLaser1Power + 0.00001));
				//bResult = m_pLaserCardCtrl->HMSSetPowerByCard(i, int(stLaser.dlLaser1Power + 0.00001));
				PRINTF(_T("Call laser function:HMSSetPowerByCard,to laser1 end,result%d."), bResult);
				if (!bResult)
					break;

				PRINTF(_T("Call laser function:HMSSetFreqByCard(%d),to laser1 start..."), int((stLaser.dlLaser1Freq + 0.00001)*KKHZ));
				bResult = m_pLaserCardCtrl->HMSSetFreq(int((stLaser.dlLaser1Freq + 0.00001)*KKHZ));
				//bResult = m_pLaserCardCtrl->HMSSetFreqByCard(i, int((stLaser.dlLaser1Freq + 0.00001)*KKHZ));
				PRINTF(_T("Call laser function:HMSSetFreqByCard,to laser1 end,result%d."), bResult);
				if (!bResult)
					break;
			}
			else
			{
				
				//PRINTF(_T("Call laser function:HMSSetPoleSizeByCard(%.3f,%.3f),to laser%d start..."), stLaser.dlEarWidth, stLaser.dlEarHeight, i + 1);
				////bResult = m_pLaserCardCtrl->HMSSetPoleSizeByCard(i, stLaser.dlEarWidth, stLaser.dlEarHeight);
				//bResult = m_pLaserCardCtrl->HMSSetPoleSize(stLaser.dlEarWidth, stLaser.dlEarHeight);
				//PRINTF(_T("Call laser function:HMSSetPoleSizeByCard,to laser%d end,result%d."), i + 1, bResult);
				//if (!bResult)
				//	break;
				
				PRINTF(_T("Call laser function:HMSSetPowerByCard(%d),to laser2 start..."), int(stLaser.dlLaser2Power + 0.00001));
				bResult = m_pLaserCardCtrl->HMSSetPower(int(stLaser.dlLaser2Power + 0.00001));
				//bResult = m_pLaserCardCtrl->HMSSetPowerByCard(i, int(stLaser.dlLaser2Power + 0.00001));
				PRINTF(_T("Current Laser Number %d"), i);
				PRINTF(_T("Call laser function:HMSSetPowerByCard,to laser2 end,result%d."), bResult);
				if (!bResult)
					break;

				PRINTF(_T("Call laser function:HMSSetFreqByCard(%d),to laser2 start..."), int((stLaser.dlLaser2Freq + 0.00001)*KKHZ));
				bResult = m_pLaserCardCtrl->HMSSetFreq(int((stLaser.dlLaser2Freq + 0.00001)*KKHZ));
				//bResult = m_pLaserCardCtrl->HMSSetFreqByCard(i, int((stLaser.dlLaser2Freq + 0.00001)*KKHZ));
				PRINTF(_T("Current Laser Number %d"), i);
				PRINTF(_T("Call laser function:HMSSetFreqByCard,to laser2 end,result%d."), bResult);
				if (!bResult)
					break;
			}
			PRINTF(_T("Call laser function:UploadMarkDate(%d,0),to laser%d start..."), i, i + 1);
			bResult = m_pLaserCardCtrl->UploadMarkDate(i, 0);
			PRINTF(_T("Call laser function:UploadMarkDate to laser%d end,result%d."), i + 1, bResult);
			if (!bResult)
				break;
		}
	}
	Sleep(4000);
	emit MESSAGEBOX.SigNalCloseMessageBox();
	if (!bResult)
	{
		emit SigLaserResultMsg(QString::fromLocal8Bit("激光上传失败"));
	}
	m_bLock = false;
	m_QMutex.unlock();
	return bResult;
}

bool DP_LaserInteraction::LaserCardInPC(ST_LASER_DATA stLaser,BOOL bStart /*= true*/)
{
	if (m_bLock)
		return false;
	m_bLock = true;

	double dlCmdSpeed = 10;//(double)MACHINE.m_hcModbus.GetDWordData(HC_PLC_MAINAXIS_SPEED); //工作速度,暂时屏蔽，定义完成后需要修改
	BOOL bResult = TRUE;
	for (int i = 0; i < 2; i++)
	{
		int nReadLaserStrat = GetTickCount(); //1026 tqc add
		if (m_bEnableLaser[i] && m_laser[i].IsConnect())
		{
			PRINTF(_T("%s:%.3f Laser%d."), _T("ChangeSpeed"), dlCmdSpeed, i + 1);
			if (!m_laser[i].SetPoleInfo(stLaser.nLaserStep, stLaser.strLaserStepInfo))
			{
				bResult = FALSE;
				break;
			}

			if (bStart && !m_laser[i].ChangeSpeed(dlCmdSpeed))
			{
				bResult = FALSE;
				break;
			}

			if (!m_laser[i].SetPoleSize(stLaser.dlEarWidth, stLaser.dlEarHeight))
			{
				bResult = FALSE;
				break;
			}
			if (i == 0)
			{
				if (!m_laser[i].SetPlcFSpeedAddr(610))
				{
					bResult = FALSE;
					break;
				}
				if (!m_laser[i].SetPower(int(stLaser.dlLaser1Power + 0.00001)))
				{
					bResult = FALSE;
					break;
				}
				if (!m_laser[i].SetFreq(int((stLaser.dlLaser1Freq + 0.00001)*KKHZ)))
				{
					bResult = FALSE;
					break;
				}
				PRINTF(_T("Laser%d:Power%d,Freq%d."), i + 1, int(stLaser.dlLaser1Power + 0.00001), int(stLaser.dlLaser1Freq + 0.00001)*KKHZ);
			}
			else
			{
				if (!m_laser[i].SetPlcFSpeedAddr(620))
				{
					bResult = FALSE;
					break;
				}
				if (!m_laser[i].SetPower(int(stLaser.dlLaser2Power + 0.00001)))
				{
					bResult = FALSE;
					break;
				}
				if (!m_laser[i].SetFreq(int((stLaser.dlLaser2Freq + 0.00001)*KKHZ)))
				{
					bResult = FALSE;
					break;
				}
				PRINTF(_T("Laser%d:Power%d,Freq%d."), i + 1, int(stLaser.dlLaser2Power + 0.00001), int(stLaser.dlLaser2Freq + 0.00001)*KKHZ);

			}
			if (!stLaser.strLaserFilePath.IsEmpty())
			{
				CString strFile;
				strFile = stLaser.strLaserFilePath + stLaser.strLaserFileName;
				strFile += _T("*.hms");
				CFileFind find;
				BOOL bFindFile = find.FindFile(strFile);//_T("*.bmp|*.jpg")
				if (bFindFile)
				{
					if (!m_laser[i].OpenMarkFile(strFile))
					{
						bResult = FALSE;
						break;
					}
				}
			}
		}
	}
	if (!bResult)
	{
		emit SigLaserResultMsg(QString::fromLocal8Bit("激光上传失败!"));
	}

	m_bLock = false;
	return bResult;
}

LaserThread::LaserThread(DP_LaserInteraction* LaserInteraciton)
{
	m_pLaserInteraction = LaserInteraciton;
}

LaserThread::~LaserThread()
{

}

void LaserThread::run()
{
	m_bResult = false;
	if (m_pLaserInteraction->m_bIsComputerCard)
	{
		m_bResult = m_pLaserInteraction->LaserCardSeparate(m_stLaserData);
	}
	else
	{
		m_bResult = m_pLaserInteraction->LaserCardInPC(m_stLaserData, m_bFlag);
	}
}

void LaserThread::SetLaserData(ST_LASER_DATA stLaserData, bool bFlag /*= true*/)
{
	m_stLaserData = stLaserData;
	m_bFlag = bFlag;
}
