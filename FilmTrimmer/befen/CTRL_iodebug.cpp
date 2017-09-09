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

//bool CTRL_IODebug::ButtonClickedChanged(QVector<ST_CHANGE_POINT> VeChangePoint)
//{
//	ST_CHANGE_POINT ChangeTemp;
//	ST_VALUECFG*     ValuecfgTemp;
//	QMap<QString, QString> QmapString;
//	bool result = true;
//	for (int i = 0; i < VeChangePoint.size(); i++)
//	{
//		ChangeTemp = VeChangePoint.at(i);
//		ValuecfgTemp = (MACHINECTRL.m_QveAutoProduction.data() + ChangeTemp.nModuleNum)->Value_.data() + ChangeTemp.nChildNum;
//		
//		//生产写入PLC所需的参数										
//		int addr = ValuecfgTemp->Addr.toInt();
//		EM_Type addType = ValuecfgTemp->Addr_Type;
//		ValuecfgTemp->Vel = !GetDpHCPLCInteraction()->GetBOOLFromPLC(addr, addType);  //修改全局容器中的值
//
//		GetDpHCPLCInteraction()->SetBOOLToPLC(ValuecfgTemp->Vel, addr, addType);//写入PLC
//		QmapString.insert(ValuecfgTemp->Function_name, QString::number(ValuecfgTemp->Vel));
//	}
//	GetDpCfgInterface()->WriteValue(QmapString, MACHINECTRL.ReturnPageCfgPath(AUTOMATICPRODUCT));
//	for (int i = 0; i < VeChangePoint.size(); i++)
//	{
//		ChangeTemp = VeChangePoint.at(i);
//		ValuecfgTemp = (MACHINECTRL.m_QveAutoProduction.data() + ChangeTemp.nModuleNum)->Value_.data() + ChangeTemp.nChildNum;
//
//		int addr = ValuecfgTemp->Addr.toInt();
//		EM_Type addType = ValuecfgTemp->Addr_Type;
//		bool s = GetDpHCPLCInteraction()->GetBOOLFromPLC(addr, addType);
//		if ((bool)ValuecfgTemp->Vel && GetDpHCPLCInteraction()->GetBOOLFromPLC(addr, addType))
//			result = false;
//	}
//	return result;
//}

bool CTRL_IODebug::ButtonClickedChanged(int nModuleNum, int nChildeNum)
{
	//设备调试页面
	QVector<ST_MODULE> temp = MACHINECTRL.m_QveIODebug;
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
	ST_MODULE*     ValueStMoudle = MACHINECTRL.m_QveIODebug.data() + Moudle;
	ST_VALUECFG    ValuecfgTemp;
	for (int i = 0; i < ValueStMoudle->m_nModuleLength(); i++)
	{
		ValuecfgTemp = ValueStMoudle->Value_.at(i);
		if (ValuecfgTemp.OtherAttribute == 0)
		{
			if (ValuecfgTemp.Vel < 0.000001)
				result += "0";
			else
				result += "1";
		}
	}
	MACHINECTRL.m_pAutoUpdateData->SwitchWorkTask(IODEBUG, Moudle); //自动更新任务切换到当前模组
	return result;
}


