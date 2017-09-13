#include "CTRL_motordebug.h"
#include "UI_MessageBox.h"

CTRL_MotorDebug::CTRL_MotorDebug(QObject * parent) 
	: CTRL_Base(parent) 
{
	InitVal();
	InitConnect();
}

CTRL_MotorDebug::~CTRL_MotorDebug() 
{
	
}

bool CTRL_MotorDebug::SaveMotolData(QVector<ST_CHANGE_POINT> VeChangePoint)
{
	ST_CHANGE_POINT ChangeTemp;
	ST_VALUECFG*     ValuecfgTemp;
	QMap<QString, QString> QmapString;
	bool result = true;
	for (int i = 0; i < VeChangePoint.size(); i++)
	{
		ChangeTemp = VeChangePoint.at(i);
		ValuecfgTemp = (MACHINECTRL.m_QveMotorDebug.data() + ChangeTemp.nModuleNum)->Value_.data() + ChangeTemp.nChildNum;
		ValuecfgTemp->Vel = ChangeTemp.dlData;  //修改全局容器中的值
												//生产写入PLC所需的参数
		int Accuracy = ValuecfgTemp->Vel_Accuracy;
		int addr = ValuecfgTemp->Addr.toInt();
		EM_Type addType = ValuecfgTemp->Addr_Type;

		HC_PLC_INTERFACE.SetDWORDToPLC(Accuracy*ChangeTemp.dlData, addr, addType);//写入PLC
		QmapString.insert(ValuecfgTemp->Function_name, QString::number(ValuecfgTemp->Vel));
		if (ValuecfgTemp->Function_name.endsWith(QString::fromLocal8Bit("反馈位置")))
		{
			;
		}
	}
	CFGINTERFACE.WriteValue(QmapString, QString::fromLocal8Bit("Vel"),MACHINECTRL.ReturnPageCfgPath(MOTORDEBUG));
	for (int i = 0; i < VeChangePoint.size(); i++)
	{
		ChangeTemp = VeChangePoint.at(i);
		ValuecfgTemp = (MACHINECTRL.m_QveMotorDebug.data() + ChangeTemp.nModuleNum)->Value_.data() + ChangeTemp.nChildNum;

		int addr = ValuecfgTemp->Addr.toInt();
		EM_Type addType = ValuecfgTemp->Addr_Type;
		if (HC_PLC_INTERFACE.GetDWORDFromPLC(addr, addType) != ValuecfgTemp->Vel*ValuecfgTemp->Vel_Accuracy)
			result = false;

	}
	return result;
}

bool CTRL_MotorDebug::AxisleMove(int nAxisNum, double nDist, EM_AXIS_MOVE_SIGNAL MoveModel, bool RunDir /*= true*/, bool bFlag /*= true*/)
{
	if (ChickFeasible(nAxisNum, MoveModel))
	{
		//MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("正在移动，稍等"), 1, 2000, true);
		return MOTORSCTRL[nAxisNum]->SetMotorMove(nDist, MoveModel, RunDir, bFlag);
	}
	return false;

}

bool CTRL_MotorDebug::SetMotorEnable(int nAxis, bool bAutoGetCurrentStatus, bool bEnableStatu)
{
	QString nAxisName;
	int result = 0;
	bool ResultBool = true;
	MOTORSCTRL[nAxis]->GetAxisAttribute(nAxisName, result);
	if (result & AXIS_ATTRIBUTE::ENABLE)
		return MOTORSCTRL[nAxis]->SetMotorEnable(bAutoGetCurrentStatus, bEnableStatu);
	else
		return false;
}

bool CTRL_MotorDebug::SetMotorStop(int nAxis, bool bAutoGetCurrentStatus /*= true*/, bool bRunStatu /*= false*/)
{
	return MOTORSCTRL[nAxis]->SetMotorStop(bAutoGetCurrentStatus, bRunStatu);
}

bool CTRL_MotorDebug::SetMotorCleanAlarm(int nAxis)
{
	return MOTORSCTRL[nAxis]->SetMotorAlarmClean();
}

bool CTRL_MotorDebug::ChickFeasible(int nAxisNum, EM_AXIS_MOVE_SIGNAL MoveModel)
{
	QString nAxisName;
	int result = 0;
	bool ResultBool = true;
	MOTORSCTRL[nAxisNum]->GetAxisAttribute(nAxisName, result);
	if (result & 7 == 0)
	{
		MESSAGEBOX.SlotNewMessAgeBoxData(nAxisName + QString::fromLocal8Bit("禁止移动"), 1, 2000, true);
		return false;
	}
	QString MessageStr;
	switch (MoveModel)
	{
	case ABSOLUTE_MOVE : {
		if (result & AXIS_ATTRIBUTE::TRIGGERMOVE == 0)
		{
			MessageStr = nAxisName + QString::fromLocal8Bit("禁止相对/绝对/点动/移动");
			ResultBool = false;
		}
	}
		break;
	case RELATIVE_MOVE: {
		if (result & AXIS_ATTRIBUTE::MOVETOPOS == 0)
		{
			MessageStr = nAxisName + QString::fromLocal8Bit("禁止相对/绝对/点动/移动");
			ResultBool = false;
		}
	}
		break;
	case DISTANCE_MOVE: {
		if (result & AXIS_ATTRIBUTE::MOVETOPOS == 0)
		{
			MessageStr = nAxisName + QString::fromLocal8Bit("禁止定距移动");
			ResultBool= false;
		}
	}
		break;
	case INCHING_MOVE: {
		if (result & AXIS_ATTRIBUTE::TRIGGERMOVE == 0)
		{
			MessageStr = nAxisName + QString::fromLocal8Bit("禁止相对/绝对/点动/移动");
			ResultBool = false;
		}
	}
		break;
	case GOTOHOME_MOVE: {
		if (result & AXIS_ATTRIBUTE::GOTOHOME == 0)
		{
			MessageStr = nAxisName + QString::fromLocal8Bit("禁止归零");
			ResultBool = false;
		}
	}
		break;
	default:
		break;
	}
	if (ResultBool)
	{
		ResultBool = !MOTORSCTRL[nAxisNum]->GetMoveStatus();
		if (ResultBool == false)
		{
			MessageStr = nAxisName + QString::fromLocal8Bit("正在移动!");
			return ResultBool;
		}
	}
	else
		MESSAGEBOX.SlotNewMessAgeBoxData(MessageStr, 1, 2000, true);
	return ResultBool;
}

bool CTRL_MotorDebug::SwitchMotor(int nAxis, QVector<ST_CHANGE_POINT> &NewMotorData)
{
	bool result = true;
	ST_CHANGE_POINT Potemp;
	if (MACHINECTRL.m_QveMotorDebug.length() <= nAxis)
	{
		MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("轴号错误！"), 1, 2000, true);
		result = false;
		return result;
	}
	for (int i = 0; i < MACHINECTRL.m_QveMotorDebug.at(nAxis).m_nModuleLength(); i++)
	{
		if (i < 6)
		{
			Potemp.dlData = MACHINECTRL.m_QveMotorDebug.at(nAxis).Value_.at(i).Vel;
			Potemp.nChildNum = i;
			Potemp.nModuleNum = nAxis;
			NewMotorData.push_back(Potemp);
		}
		if (i == 13)
		{
			Potemp.dlData = MACHINECTRL.m_QveMotorDebug.at(nAxis).Value_.at(i).Vel;
			Potemp.nChildNum = i;
			Potemp.nModuleNum = nAxis;
			NewMotorData.push_back(Potemp);
		}
	}
	//切换Motor自动更新
	MACHINECTRL.m_pAutoUpdateData->SwitchWorkTask(MOTORDEBUG, nAxis);
	return result;
}


void CTRL_MotorDebug::InitVal()
{
}

void CTRL_MotorDebug::InitConnect()
{
	connect(MACHINECTRL.m_pAutoUpdateData, SIGNAL(SigMotorDebug(QList<ST_UPDATEDATA>)), this, SLOT(SlotAutoUpdateData(QList<ST_UPDATEDATA>)));
}
