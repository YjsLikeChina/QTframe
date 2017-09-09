#include "CTRL_autoproduction.h"
#include<qdebug.h>
CTRL_AutoProduction::CTRL_AutoProduction(QObject * parent):CTRL_Base(parent) {
	Initconnect();
}

CTRL_AutoProduction::~CTRL_AutoProduction() {
	
}

void CTRL_AutoProduction::Initconnect()
{
	connect(MACHINECTRL.m_pAutoUpdateData, SIGNAL(SigAutoProduction(QList<ST_UPDATEDATA>)), this, SLOT(SlotAutoUpdateData(QList<ST_UPDATEDATA>)));
}

bool CTRL_AutoProduction::ItemChanged(QVector<ST_CHANGE_POINT> VeChangePoint)
{
	ST_CHANGE_POINT ChangeTemp;
	ST_VALUECFG*     ValuecfgTemp;
	QMap<QString, QString> QmapString;
	bool result = true;
	for (int i = 0; i < VeChangePoint.size(); i++)
	{
		ChangeTemp = VeChangePoint.at(i);
		ValuecfgTemp = (MACHINECTRL.m_QveAutoProduction.data() + ChangeTemp.nModuleNum)->Value_.data() + ChangeTemp.nChildNum;
		ValuecfgTemp->Vel = ChangeTemp.dlData;  //修改全局容器中的值
		//生产写入PLC所需的参数
		int Accuracy = ValuecfgTemp->Vel_Accuracy;
		int addr = ValuecfgTemp->Addr.toInt();
		EM_Type addType = ValuecfgTemp->Addr_Type;

		HC_PLC_INTERFACE.SetDWORDToPLC(Accuracy*ChangeTemp.dlData, addr, addType);//写入PLC
		QmapString.insert(ValuecfgTemp->Function_name, QString::number(ValuecfgTemp->Vel));
	}	
	CFGINTERFACE.WriteValue(QmapString,MACHINECTRL.ReturnPageCfgPath(AUTOMATICPRODUCT));
	for (int i = 0; i < VeChangePoint.size(); i++)
	{
		ChangeTemp = VeChangePoint.at(i);
		ValuecfgTemp = (MACHINECTRL.m_QveAutoProduction.data() + ChangeTemp.nModuleNum)->Value_.data() + ChangeTemp.nChildNum;

		int addr = ValuecfgTemp->Addr.toInt();
		EM_Type addType = ValuecfgTemp->Addr_Type;
		if (HC_PLC_INTERFACE.GetDWORDFromPLC(addr, addType) != ValuecfgTemp->Vel*ValuecfgTemp->Vel_Accuracy)
			result = false;

	}
	return result;
}