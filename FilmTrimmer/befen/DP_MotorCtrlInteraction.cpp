#include "DP_MotorCtrlInteraction.h"
#include "UI_MessageBox.h"
#include "OP_MachineSoftWareMain.h"

DP_MotorCtrlInteraction::DP_MotorCtrlInteraction()
{
	m_bIsMoveing = false;
	m_pMotorMoveThread = new MotorCtrlThread(this);
}

DP_MotorCtrlInteraction::~DP_MotorCtrlInteraction()
{
	delete m_pMotorMoveThread;
}

void DP_MotorCtrlInteraction::MotorMove(double dlDist, EM_AXIS_MOVE_SIGNAL emMoveModel /*= ABSOLUTE_MOVE*/)
{
	//if (!GetMotorEanble()) //判断是否有使能
	//{
	//	QString strMsg = QString::fromLocal8Bit("%1轴未使能").arg(m_qstrAxisName);
	//	//m_pMessageBox->NoDomodel(strMsg);
	//	emit MESSAGEBOX.SigNalMessAgeBoxData(strMsg, NODOMODEL);
	//	return;
	//}
	//DWORD dwAxisRunEnable = GetMotorStatus();
	//if (dwAxisRunEnable & AXIS_STATU_ALARM)//电机是否报警
	//{
	//	QString strMsg = QString::fromLocal8Bit("%1轴报警").arg(m_qstrAxisName);
	//	//m_pMessageBox->NoDomodel(strMsg);
	//	emit MESSAGEBOX.SigNalMessAgeBoxData(strMsg, NODOMODEL);
	//	return;
	//}
	//if (!(dwAxisRunEnable & AXIS_STATU_ORIGIN)) //是否拥有原地位
	//{
	//	QString strMsg = QString::fromLocal8Bit("%1轴无原点位").arg(m_qstrAxisName);
	//	//m_pMessageBox->NoDomodel(strMsg);
	//	emit MESSAGEBOX.SigNalMessAgeBoxData(strMsg, NODOMODEL);
	//	return;
	//}

	m_bIsMoveing = true;

	//移动电机
	double dlTargetPos = dlDist * m_qVecMotorsInfo.at(ORDER_SET_TARGET_POS).Vel_Accuracy; //距离*精度
	DWORD dwStartaddr = m_qVecMotorsInfo.at(ORDER_SET_TARGET_POS).Addr.toInt();
	bool bRes = HC_PLC_INTERFACE.SetDWORDToPLC(dlTargetPos,
		m_qVecMotorsInfo.at(ORDER_SET_TARGET_POS).Addr.toInt(),
		m_qVecMotorsInfo.at(ORDER_SET_TARGET_POS).Addr_Type);

	bRes = HC_PLC_INTERFACE.SetBOOLToPLC(1,
		m_qVecMotorsInfo.at(ORDER_ABS_TRIGGER).Addr.toInt(),
		m_qVecMotorsInfo.at(ORDER_ABS_TRIGGER).Addr_Type);

	if (!bRes)
	{
		m_bIsMoveing = false;
		return;
	}
	bRes = false;
	DWORD dwStartTime = GetTickCount();
	while (true)
	{
		DWORD dwAxisStatus = GetMotorStatus();
		if (dwAxisStatus & AXIS_STATU_INPLACE)
		{
			bRes = true;
			break;
		}
		if ((dwAxisStatus & AXIS_STATU_ALARM) || (dwAxisStatus & AXIS_STATU_LIMIT_MINUS) || (dwAxisStatus & AXIS_STATU_LIMIT_PLUS))
		{
			SetMotorEnable(false, false);	//断掉使能
			Sleep(200);
			SetMotorEnable(false, true);
			QString strMsg = QString::fromLocal8Bit("%1轴报警或到达限位").arg(m_qstrAxisName);
			//m_pMessageBox->NoDomodel(strMsg);
			emit MESSAGEBOX.SigNalMessAgeBoxData(strMsg, NODOMODEL);
			bRes = false;
			break;
		}
		if (GetTickCount() - dwStartTime > 15000)
		{
			SetMotorEnable(false, false);	//断掉使能
			Sleep(200);
			SetMotorEnable(false, true);
			QString strMsg = QString::fromLocal8Bit("%1轴移动超时").arg(m_qstrAxisName);
			//m_pMessageBox->NoDomodel(strMsg);
			emit MESSAGEBOX.SigNalMessAgeBoxData(strMsg, NODOMODEL);
			bRes = false;
			break;
		}
	}
	m_bIsMoveing = false;
	return;
}

void DP_MotorCtrlInteraction::MotorGotoHome()
{
	if (!GetMotorEanble()) //判断是否有使能
	{
		SetMotorEnable(false, true);	//上使能
		bool bflag = false;
		DWORD dwStartTime = GetTickCount();
		while (1)	//等待使能
		{
			if (GetMotorEanble())
			{
				bflag = true;
				break;
			}
			else
			{
				if (GetTickCount() - dwStartTime > 1000)
				{
					QString strMsg = QString::fromLocal8Bit("%1轴使能失败").arg(m_qstrAxisName);
					//m_pMessageBox->NoDomodel(strMsg);
					emit MESSAGEBOX.SigNalMessAgeBoxData(strMsg, NODOMODEL);
					break;
				}
			}
			Sleep(10);
		}
		if (!bflag)	//使能失败
		{
			return;
		}
	}
	if (GetMotorStatus() & AXIS_STATU_ALARM)//电机是否报警
	{
		SetMotorAlarmClean(); //清除报警
		Sleep(200);
		if (GetMotorStatus() & AXIS_STATU_ALARM)
		{
			QString strMsg = QString::fromLocal8Bit("%1轴报警").arg(m_qstrAxisName);
			//m_pMessageBox->NoDomodel(strMsg);
			emit MESSAGEBOX.SigNalMessAgeBoxData(strMsg, NODOMODEL);
			return;
		}
	}

	//移动电机
	m_bIsMoveing = true;
	DWORD dwPLCAddr = m_qVecMotorsInfo.at(ORDER_GOTO_HOME).Addr.toInt();
	HC_PLC_INTERFACE.GetBOOLFromPLC(dwPLCAddr, m_qVecMotorsInfo.at(ORDER_GOTO_HOME).Addr_Type);
	DWORD dwStartTime = GetTickCount();
	bool bflag = false;
	while (true)
	{
		if (GetMotorStatus() & AXIS_STATU_INPLACE)	//到位
		{
			bflag = true;
			break;
		}
		if (GetTickCount() - dwStartTime > 15000)	//超时
		{
			SetMotorEnable(false, false);	//断掉使能
			Sleep(200);
			SetMotorEnable(false, true);
			QString strMsg = QString::fromLocal8Bit("%1轴移动超时").arg(m_qstrAxisName);
			//m_pMessageBox->NoDomodel(strMsg);
			emit MESSAGEBOX.SigNalMessAgeBoxData(strMsg, NODOMODEL);
			break;
		}
		Sleep(10);
	}
	m_bIsMoveing = false;
	return;
}

bool DP_MotorCtrlInteraction::InitMotorsInfo(int nAxis, QVector<ST_VALUECFG> MotorsInfo)
{
	m_nMotorNum = nAxis;
	m_qVecMotorsInfo = MotorsInfo;
	m_qstrAxisName = MACHINECTRL.m_QveMotorDebug.at(nAxis-1).ModuleName;
	m_nAxisAttribute = (int)MotorsInfo.at(ORDER_OTHER_ATTRIBUTE).Addr.toInt();
	return true;
}

bool DP_MotorCtrlInteraction::SetMotorGotoHome()
{
	m_pMotorMoveThread->SetMotorRunModel(0,MOVE_GOTOHOME);
	return true;
}

bool DP_MotorCtrlInteraction::SetMotorMove(double dlDist, EM_AXIS_MOVE_SIGNAL emMoveModel /*= ABSOLUTE_MOVE*/,bool bRunDir,bool flag)
{
	if (INCHING_MOVE == emMoveModel) //Jog
	{
		return true;
	}
	else
	{
		m_pMotorMoveThread->SetMotorRunModel(dlDist,MOVE_TOPOS);
		return true;
	}
}

bool DP_MotorCtrlInteraction::SetMotorEnable(bool bAutoGetCurrentStatus /*= true*/, bool bEnableStatu /*= false*/)
{
	bool res = false;
	if (bAutoGetCurrentStatus)
	{
		HC_PLC_INTERFACE.SetBOOLToPLC(
			!GetMotorEanble(),
			m_qVecMotorsInfo.at(ORDER_ENABLE).Addr.toInt(),
			m_qVecMotorsInfo.at(ORDER_ENABLE).Addr_Type);
	}
	else
	{
		res = HC_PLC_INTERFACE.SetBOOLToPLC(
			bEnableStatu,
			m_qVecMotorsInfo.at(ORDER_ENABLE).Addr.toInt(),
			m_qVecMotorsInfo.at(ORDER_ENABLE).Addr_Type);
	}
	return res;
}

bool DP_MotorCtrlInteraction::SetMotorStop(bool bAutoGetCurrentStatus /*= true*/, bool bRunStatu /*= false*/)
{
	bool bRes = false;
	if (bAutoGetCurrentStatus)
	{
		bRes = HC_PLC_INTERFACE.SetBOOLToPLC(
			!(GetMotorStatus() & AXIS_STATU_STOP),
			m_qVecMotorsInfo.at(ORDER_STOP).Addr.toInt(),
			m_qVecMotorsInfo.at(ORDER_STOP).Addr_Type);
	}
	else
	{
		bRes = HC_PLC_INTERFACE.SetBOOLToPLC(
			bRunStatu,
			m_qVecMotorsInfo.at(ORDER_STOP).Addr.toInt(),
			m_qVecMotorsInfo.at(ORDER_STOP).Addr_Type);
	}
	return bRes;
}

bool DP_MotorCtrlInteraction::SetMotorAlarmClean()
{
	bool res = HC_PLC_INTERFACE.SetBOOLToPLC(true,
		m_qVecMotorsInfo.at(ORDER_ALARM_CLEAN).Addr.toInt(),
		m_qVecMotorsInfo.at(ORDER_ALARM_CLEAN).Addr_Type);

	return res;
}

int DP_MotorCtrlInteraction::GetMotorStatus()
{
	DWORD dwStatus = HC_PLC_INTERFACE.GetDWORDFromPLC(
		m_qVecMotorsInfo.at(ORDER_GET_STATUS).Addr.toInt(),
		m_qVecMotorsInfo.at(ORDER_GET_STATUS).Addr_Type);

	return dwStatus;
}

bool DP_MotorCtrlInteraction::GetMotorEanble()
{
	DWORD dwStatus = HC_PLC_INTERFACE.GetDWORDFromPLC(
		m_qVecMotorsInfo.at(ORDER_GET_STATUS).Addr.toInt(),
		m_qVecMotorsInfo.at(ORDER_GET_STATUS).Addr_Type);

	bool bres = dwStatus & AXIS_STATU_ENABLE;
	return bres;
}

double DP_MotorCtrlInteraction::GetMotorCurrentPos()
{
	DWORD dwCurPos = HC_PLC_INTERFACE.GetDWORDFromPLC(
		m_qVecMotorsInfo.at(ORDER_GET_POS).Addr.toInt(),
		m_qVecMotorsInfo.at(ORDER_GET_POS).Addr_Type);

	return (dwCurPos / m_qVecMotorsInfo.at(ORDER_GET_POS).Vel_Accuracy);
}

double DP_MotorCtrlInteraction::GetMotorCurrnetSpeed()
{
	DWORD dwCurPos = HC_PLC_INTERFACE.GetDWORDFromPLC(
		m_qVecMotorsInfo.at(ORDER_GET_SPEED).Addr.toInt(),
		m_qVecMotorsInfo.at(ORDER_GET_SPEED).Addr_Type);

	return (dwCurPos / m_qVecMotorsInfo.at(ORDER_GET_SPEED).Vel_Accuracy);
}

bool DP_MotorCtrlInteraction::GetMoveStatus()
{
	return m_bIsMoveing;
}

bool DP_MotorCtrlInteraction::GetAxisAttribute(QString& qstrAxisName, int& nAxisAttribute)
{
	qstrAxisName = m_qstrAxisName;
	nAxisAttribute = m_nAxisAttribute;
	return true;
}

MotorCtrlThread::~MotorCtrlThread()
{

}

MotorCtrlThread::MotorCtrlThread(DP_MotorCtrlInteraction* CallObject)
{
	m_pMotorCtrlInteraction = CallObject;
}

void MotorCtrlThread::run()
{
	switch (m_emMoveCtrl)
	{
	case MOVE_GOTOHOME:
		m_pMotorCtrlInteraction->MotorMove(m_dlMoveDist, GOTOHOME_MOVE);
		break;
	case MOVE_TOPOS:
		m_pMotorCtrlInteraction->MotorMove(m_dlMoveDist, ABSOLUTE_MOVE);
		break;
	default:
		break;
	}
}

void MotorCtrlThread::SetMotorRunModel(double dlMoveDist, MOTOR_MOVE_CTRL MoveType)
{
	m_emMoveCtrl = MoveType;
	m_dlMoveDist = dlMoveDist;
	start();
}
