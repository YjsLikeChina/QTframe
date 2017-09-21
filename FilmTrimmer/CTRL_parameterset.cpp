#include "CTRL_parameterset.h"

CTRL_ParameterSet::CTRL_ParameterSet(QObject * parent) : CTRL_Base(parent) {

}

CTRL_ParameterSet::~CTRL_ParameterSet() {
	
}

bool CTRL_ParameterSet::SaveParmentterset(QVector<ST_CHANGE_POINT> VeChangePoint)
{
	ST_CHANGE_POINT ChangeTemp;
	ST_VALUECFG*     ValuecfgTemp;
	QMap<QString, QString> QmapString;
	bool result = true;
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: 控制层]_[函数名 : %1]_操作:保存数据").arg(__func__));
	for (int i = 0; i < VeChangePoint.size(); i++)
	{
		ChangeTemp = VeChangePoint.at(i);
		ValuecfgTemp = (MACHINECTRL.m_QveParameterSetting.data() + ChangeTemp.nModuleNum)->Value_.data() + ChangeTemp.nChildNum;
		ValuecfgTemp->Vel = ChangeTemp.dlData;  //修改全局容器中的值
												//生产写入PLC所需的参数
		int Accuracy = ValuecfgTemp->Vel_Accuracy;
		int addr = ValuecfgTemp->Addr.toInt();
		EM_Type addType = ValuecfgTemp->Addr_Type;
		EM_MODULE_DATA_TYPE valueType = ValuecfgTemp->Vel_Type;

		if (valueType == EM_MODULE_DATA_TYPE::_BOOL)
		{
			HC_PLC_INTERFACE.SetBOOLToPLC(ChangeTemp.dlData, addr, addType);//写入PLC
		}
		else
		{
			HC_PLC_INTERFACE.SetDWORDToPLC(Accuracy*ChangeTemp.dlData, addr, addType);//写入PLC
		}
		
		QmapString.insert(ValuecfgTemp->Function_name, QString::number(ValuecfgTemp->Vel));
	}
	CFGINTERFACE.WriteValue(QmapString, QString::fromLocal8Bit("Vel"),MACHINECTRL.ReturnPageCfgPath(PARAMETERSET));
	for (int i = 0; i < VeChangePoint.size(); i++)
	{
		ChangeTemp = VeChangePoint.at(i);
		ValuecfgTemp = (MACHINECTRL.m_QveParameterSetting.data() + ChangeTemp.nModuleNum)->Value_.data() + ChangeTemp.nChildNum;

		int addr = ValuecfgTemp->Addr.toInt();
		EM_Type addType = ValuecfgTemp->Addr_Type;
		EM_MODULE_DATA_TYPE valueType = ValuecfgTemp->Vel_Type;
		if (valueType == EM_MODULE_DATA_TYPE::_BOOL)
		{
			if ((bool)ValuecfgTemp->Vel && HC_PLC_INTERFACE.GetBOOLFromPLC(addr, addType))
				result = false;
		}
		else
		{
			if (HC_PLC_INTERFACE.GetDWORDFromPLC(addr, addType) != ValuecfgTemp->Vel*ValuecfgTemp->Vel_Accuracy)
				result = false;
		}
	}
	return result;
}

void CTRL_ParameterSet::Initconnect()
{
	connect(MACHINECTRL.m_pAutoUpdateData, SIGNAL(SigParameterSetting(QList<ST_UPDATEDATA>)), this, SLOT(SlotAutoUpdateData(QList<ST_UPDATEDATA>)));
}

void CTRL_ParameterSet::InitVal()
{
}
