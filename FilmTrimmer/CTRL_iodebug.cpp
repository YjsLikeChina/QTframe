#include "CTRL_iodebug.h"

CTRL_IODebug::CTRL_IODebug(QObject * parent) : CTRL_Base(parent) {
	Initconnect();
}

CTRL_IODebug::~CTRL_IODebug() 
{
	//
}

void CTRL_IODebug::Initconnect()
{
	connect(MACHINECTRL.m_pAutoUpdateData, SIGNAL(SigIODebug(QList<ST_UPDATEDATA>)), this, SLOT(SlotAutoUpdateData(QList<ST_UPDATEDATA>)));
}

bool CTRL_IODebug::ButtonClickedChanged(int nModuleNum, int nChildeNum)
{
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: 控制层]_[函数名 : %1]_操作:下发PCL输出点输出信号,输出点:%2").arg(__func__).arg(MACHINECTRL.m_QveIODebug.at(nModuleNum).Value_.at(nChildeNum).Function_name));
	bool bRes = HC_PLC_INTERFACE.GetBOOLFromPLC(MACHINECTRL.m_QveIODebug.at(nModuleNum).Value_.at(nChildeNum).Addr.toInt(),
		MACHINECTRL.m_QveIODebug.at(nModuleNum).Value_.at(nChildeNum).Addr_Type);
	HC_PLC_INTERFACE.SetBOOLToPLC(!bRes, MACHINECTRL.m_QveIODebug.at(nModuleNum).Value_.at(nChildeNum).Addr.toInt(),
		MACHINECTRL.m_QveIODebug.at(nModuleNum).Value_.at(nChildeNum).Addr_Type);

	Sleep(50);
	return HC_PLC_INTERFACE.GetBOOLFromPLC(MACHINECTRL.m_QveIODebug.at(nModuleNum).Value_.at(nChildeNum).Addr.toInt(),
		MACHINECTRL.m_QveIODebug.at(nModuleNum).Value_.at(nChildeNum).Addr_Type);
}
QString CTRL_IODebug::ChangeMoudle(int Moudle)
{
	QString result("");
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: 控制层]_[函数名 : %1]_操作:返回切换模组数据").arg(__func__));
	ST_MODULE*     ValueStMoudle = MACHINECTRL.m_QveIODebug.data() + Moudle;
	ST_VALUECFG    ValuecfgTemp;
	for (int i = 0; i < ValueStMoudle->m_nModuleLength(); i++)
	{
		ValuecfgTemp = ValueStMoudle->Value_.at(i);
		if (ValuecfgTemp.OtherAttribute == OUTPUT)	//
		{
			result += QString::number(HC_PLC_INTERFACE.GetBOOLFromPLC(ValuecfgTemp.Addr.toInt(), ValuecfgTemp.Addr_Type));
		}
	}
	MACHINECTRL.m_pAutoUpdateData->SwitchWorkTask(IODEBUG, Moudle); //自动更新任务切换到当前模组
	return result;
}


