#include "CTRL_autoproduction.h"
#include<qdebug.h>
#include "QCoreApplication"
#include <UI_MessageBox.h>

CTRL_AutoProduction::CTRL_AutoProduction(QObject * parent):CTRL_Base(parent) 
{
	Initconnect();
	QString qstrCfgPath = QCoreApplication::applicationDirPath();

	CString m_cstrFilmTrimmerCfgPath = qstrCfgPath.toStdWString().data();
	m_cstrFilmTrimmerCfgPath += _T("/System/FilmTrimmer.cfg");
	m_nSetMaxSpeed = ReadIntFromFile(_T("Run"), _T("工作速度最大值"), 30, m_cstrFilmTrimmerCfgPath);
}

CTRL_AutoProduction::~CTRL_AutoProduction() 
{
	
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
	CFGINTERFACE.WriteValue(QmapString,QString::fromLocal8Bit("Vel"),MACHINECTRL.ReturnPageCfgPath(AUTOMATICPRODUCT));
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

bool CTRL_AutoProduction::SetMachineRunDir()
{
	DWORD dwAddr = MACHINECTRL.m_QveAutoProduction.at(0).Value_.at(MACHINE_RUN_DIR).Addr.toInt();
	EM_Type emType = MACHINECTRL.m_QveAutoProduction.at(0).Value_.at(MACHINE_RUN_DIR).Addr_Type;
	bool bCurRunDir = HC_PLC_INTERFACE.GetBOOLFromPLC(dwAddr, emType);//0表示第一个模组，MACHINE_RUN_DIR表示设备运行方向在文件中位置
	HC_PLC_INTERFACE.SetBOOLToPLC(!bCurRunDir, dwAddr, emType);
	Sleep(100);

	return bCurRunDir = HC_PLC_INTERFACE.GetBOOLFromPLC(dwAddr, emType); //返回实际获取的值
}

bool CTRL_AutoProduction::SetMachineOnloadDir()
{
	DWORD dwAddr = MACHINECTRL.m_QveAutoProduction.at(0).Value_.at(MACHINE_ONLOAD_DIR).Addr.toInt();
	EM_Type emType = MACHINECTRL.m_QveAutoProduction.at(0).Value_.at(MACHINE_ONLOAD_DIR).Addr_Type;
	bool bCurOnloadDir = HC_PLC_INTERFACE.GetBOOLFromPLC(dwAddr, emType);//0表示第一个模组
	HC_PLC_INTERFACE.SetBOOLToPLC(!bCurOnloadDir, dwAddr, emType);
	Sleep(100);

	return bCurOnloadDir = HC_PLC_INTERFACE.GetBOOLFromPLC(dwAddr, emType); //返回实际获取的值
}

bool CTRL_AutoProduction::SetWorkSpeed(int nSetSpeed)
{
	if (nSetSpeed > m_nSetMaxSpeed)
	{
		QString strMsg("工作速度设定最大值为%1");
		strMsg.arg(m_nSetMaxSpeed);
		MESSAGEBOX.SlotNewMessAgeBoxData(strMsg, DOMODEL,0);
		return false;
	}
	//设置工作速度
	DWORD dwAddr = MACHINECTRL.m_QveFilmParam.at(0).Value_.at(CTRL_MACHINE_WORKSPEED).Addr.toInt();//地址
	EM_Type emType = MACHINECTRL.m_QveFilmParam.at(0).Value_.at(CTRL_MACHINE_WORKSPEED).Addr_Type;//类型
	int nAccuracy = MACHINECTRL.m_QveFilmParam.at(0).Value_.at(CTRL_MACHINE_WORKSPEED).Vel_Accuracy;//精度
	if (HC_PLC_INTERFACE.SetDWORDToPLC(nSetSpeed * nAccuracy, dwAddr, emType))
	{
		//写入配置文件中
		return true;
	}
	return false;
}

/*电机配置页面默认配置放卷轴、主牵引、收卷轴*/
void CTRL_AutoProduction::SetOnloadClockwise(bool bFlag)
{
	DWORD dwAddr = MACHINECTRL.m_QveMotorDebug.at(0).Value_.at(ORDER_JOG_CW).Addr.toInt(); 
	EM_Type emType = MACHINECTRL.m_QveMotorDebug.at(0).Value_.at(ORDER_JOG_CW).Addr_Type;
	HC_PLC_INTERFACE.SetBOOLToPLC(bFlag,dwAddr,emType);
}

void CTRL_AutoProduction::SetOnloadAnticlockwise(bool bFlag)
{
	DWORD dwAddr = MACHINECTRL.m_QveMotorDebug.at(0).Value_.at(ORDER_JOG_CCW).Addr.toInt();
	EM_Type emType = MACHINECTRL.m_QveMotorDebug.at(0).Value_.at(ORDER_JOG_CCW).Addr_Type;
	HC_PLC_INTERFACE.SetBOOLToPLC(bFlag, dwAddr, emType);
}

void CTRL_AutoProduction::SetMainAxisClockwise(bool bFlag)
{
	DWORD dwAddr = MACHINECTRL.m_QveMotorDebug.at(1).Value_.at(ORDER_JOG_CW).Addr.toInt();
	EM_Type emType = MACHINECTRL.m_QveMotorDebug.at(1).Value_.at(ORDER_JOG_CW).Addr_Type;
	HC_PLC_INTERFACE.SetBOOLToPLC(bFlag, dwAddr, emType);
}

void CTRL_AutoProduction::SetMainAxisAnticlockwise(bool bFlag)
{
	DWORD dwAddr = MACHINECTRL.m_QveMotorDebug.at(1).Value_.at(ORDER_JOG_CCW).Addr.toInt();
	EM_Type emType = MACHINECTRL.m_QveMotorDebug.at(1).Value_.at(ORDER_JOG_CCW).Addr_Type;
	HC_PLC_INTERFACE.SetBOOLToPLC(bFlag, dwAddr, emType);
}

void CTRL_AutoProduction::SetRecvClockwise(bool bFlag)
{
	DWORD dwAddr = MACHINECTRL.m_QveMotorDebug.at(2).Value_.at(ORDER_JOG_CW).Addr.toInt();
	EM_Type emType = MACHINECTRL.m_QveMotorDebug.at(2).Value_.at(ORDER_JOG_CW).Addr_Type;
	HC_PLC_INTERFACE.SetBOOLToPLC(bFlag, dwAddr, emType);
}

void CTRL_AutoProduction::SetRecvAnticlockwise(bool bFlag)
{
	DWORD dwAddr = MACHINECTRL.m_QveMotorDebug.at(2).Value_.at(ORDER_JOG_CCW).Addr.toInt();
	EM_Type emType = MACHINECTRL.m_QveMotorDebug.at(2).Value_.at(ORDER_JOG_CCW).Addr_Type;
	HC_PLC_INTERFACE.SetBOOLToPLC(bFlag, dwAddr, emType);
}
