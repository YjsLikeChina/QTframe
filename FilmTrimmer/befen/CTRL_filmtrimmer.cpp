#include "CTRL_filmtrimmer.h"

CTRL_FilmTrimmer::CTRL_FilmTrimmer(QObject * parent) : CTRL_Base(parent) {

	InitValue();
	InitConnect();
}

CTRL_FilmTrimmer::~CTRL_FilmTrimmer() {

}

bool CTRL_FilmTrimmer::SwitchPage(int nCurPage, int newPage, bool bFlag, QVector<ST_CHANGE_POINT>& ModifyVal)
{
	if (!bFlag)
		return true;
	else
	{
	 EN_Resoult resoult = MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("页面有数据修改,请注意是否保存！"),
		 0, 0, true,true);
	 switch (resoult)
	 {
	 case OK: break;
	 case CANCEL:return false;
		 break;
	 case COMPEL:MACHINECTRL.m_pAutoUpdateData->SwitchWorkTask(newPage, 0); 
		 return true;
		 break;
	 case NORESOULT:MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("弹框异常，请联系售后人员"),
		 2000, 1);
		 return false;
		 break;
	 default:
		 return false;
		 break;
	 }
	}
	ST_CHANGE_POINT ChangeTemp;
	ST_VALUECFG*     ValuecfgTemp;
	QMap<QString, QString> QmapString;
	bool result = true;
	for (int i = 0; i < ModifyVal.size(); i++)
	{
		ChangeTemp = ModifyVal.at(i);
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
	CFGINTERFACE.WriteValue(QmapString, MACHINECTRL.ReturnPageCfgPath(PARAMETERSET));
	for (int i = 0; i < ModifyVal.size(); i++)
	{
		ChangeTemp = ModifyVal.at(i);
		ValuecfgTemp = (MACHINECTRL.m_QveParameterSetting.data() + ChangeTemp.nModuleNum)->Value_.data() + ChangeTemp.nChildNum;

		int addr = ValuecfgTemp->Addr.toInt();
		EM_Type addType = ValuecfgTemp->Addr_Type;
		EM_MODULE_DATA_TYPE valueType = ValuecfgTemp->Vel_Type;
		if (valueType == EM_MODULE_DATA_TYPE::_BOOL)
		{
			if ((bool)ValuecfgTemp->Vel && HC_PLC_INTERFACE.GetBOOLFromPLC(addr, addType))
			{
				MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("保存数据异常"),
					2000, 1);
				return  false;
			}
		}
		else
		{
			if (HC_PLC_INTERFACE.GetDWORDFromPLC(addr, addType) != ValuecfgTemp->Vel*ValuecfgTemp->Vel_Accuracy)
			{
				MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("保存数据异常"),
					2000, 1);
				return  false;
			}
		}
	}
	MACHINECTRL.m_pAutoUpdateData->SwitchWorkTask(newPage, 0);
	return true;
}

bool CTRL_FilmTrimmer::MachineCtrl(EM_MACHINE_SIGNAL emCtrl)
{
	return true;
}

bool CTRL_FilmTrimmer::SetUiPage()
{
	//m_pUiFimeTrimmer->SetModuleInfo();
	return false;
}

void CTRL_FilmTrimmer::InitConnect()
{
	//connect(m_pUiFimeTrimmer, SIGNAL(SigSwitchPage(int, bool, QMap<QString, QString>&)), this, SLOT(ChangePage(int, bool, QMap<QString, QString>&)));//连接切换页面信号
}

void CTRL_FilmTrimmer::InitValue()
{

}

QString CTRL_FilmTrimmer::UserLogin()
{
	return "";
}

bool CTRL_FilmTrimmer::ResultUserName()
{
	return false;
}
