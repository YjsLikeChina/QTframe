#include "OP_MachineStatusCtrl.h"
#include "OP_MachineSoftWareMain.h"
#include "DP_LaserInteraction.h"
#include "DP_CfgInterface.hpp"
#include "DP_MotorCtrlInteraction.h"
#include "ui_UI_MessageBox.h"


QString g_qstrMachineCfgPath = QString::fromLocal8Bit("/System/FilmTrimmer.cfg");
QString g_qstrPackageFilePath = QString::fromLocal8Bit("/Data/Package/");

OP_MachineStatusCtrl::OP_MachineStatusCtrl()
{
	InitVal();
	LASERINTERFACE.ConnectLaser(); //test
}


OP_MachineStatusCtrl::~OP_MachineStatusCtrl()
{
	//delete m_pMessageBox;
}

void OP_MachineStatusCtrl::InitVal()
{
	m_qstrFilmCfgPath = QCoreApplication::applicationDirPath() + g_qstrMachineCfgPath;
	m_cstrFilmCfgPath = m_qstrFilmCfgPath.toStdWString().data();
	m_qstrPackageFilePath = QCoreApplication::applicationDirPath() + g_qstrPackageFilePath;
	m_bSoftwareIsFirstStart = true;
	//是否为脱机卡
	m_bComputerCard = ReadIntFromFile(_T("Run"), _T("ComputerCard"), 1, m_cstrFilmCfgPath);
	LASERINTERFACE.SetLaserType(m_bComputerCard); 
	m_bIsAutoMoveToPos = false;
}

void OP_MachineStatusCtrl::run()
{
	while (true)
	{
		switch (m_emMachineWorkTask)
		{
		case SET_CURRENT_PACKAGE:
			
			break;
		case SET_MACHINE_START:
			break;
		case SET_MACHINE_RESET:
			break;
		case SET_MACHINE_STOP:
			break;
		case SET_MACHINE_ESTOP:
			break;
		default:
			break;
		}
		Sleep(50);
	}
}

bool OP_MachineStatusCtrl::MachineCtrlStart()
{
	//判断是否勾选电机自动定位
	if (GetIsAutoMovePos())
	{
		//1、判断电机位置是否正确
		if (!GetMotorIsInplace())
		{
			emit MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("有电机不在工作位"),DOMODEL,0);
			return false;
		}
	}
	//上传激光
	QString qstrPath = m_qstrPackageFilePath + m_qstrCurPkgName + QString::fromLocal8Bit(".pkg");

	ST_LASER_DATA stLaserData = m_stCurLaserData;

	if (!LASERINTERFACE.UploadLaserData(stLaserData))
	{
		//上传激光数据失败
		return false;
	}

	//获取启动地址

	//启动

	return true;
}

bool OP_MachineStatusCtrl::MachineCtrlStop()
{
	return true;
}

bool OP_MachineStatusCtrl::MachineCtrlReset()
{
	if (m_bMachineCurModel)//自动
	{
		switch (m_emMachineStatusCtrl)
		{
		case BEGIN_STATUS:
			{
				if (m_bMachineCurModel)//自动
				{
					//
				}
				else
				{
					//
				}
			}
			break;
		case INITIALIZATION_STATUS:
			if (m_bMachineCurModel)//自动
			{
				//
			}
			else
			{
				//进行初始化
				InitMachineCtrl();
			}
			break;
		case READY_STATUS:
			break;
		case RUN_STATUS:
			break;
		case ERROR_STATUS:
			break;
		default:
			break;
		}
	}
	return true;
}

bool OP_MachineStatusCtrl::MachineCtrlEStop()
{
	return true;
}

bool OP_MachineStatusCtrl::MachineCtrlMaintain()
{
	return true;
}

bool OP_MachineStatusCtrl::SetOtherData()
{
	//运行方向
	DWORD dwAddr = MACHINECTRL.m_QveAutoProduction.at(0).Value_.at(MACHINE_RUN_DIR).Addr.toInt();
	EM_Type emType = MACHINECTRL.m_QveAutoProduction.at(0).Value_.at(MACHINE_RUN_DIR).Addr_Type;
	int nVel = MACHINECTRL.m_QveAutoProduction.at(0).Value_.at(MACHINE_RUN_DIR).Vel;
	HC_PLC_INTERFACE.SetBOOLToPLC(nVel,dwAddr,emType);
	//放卷方向
	dwAddr = MACHINECTRL.m_QveAutoProduction.at(0).Value_.at(MACHINE_ONLOAD_DIR).Addr.toInt();
	emType = MACHINECTRL.m_QveAutoProduction.at(0).Value_.at(MACHINE_ONLOAD_DIR).Addr_Type;
	nVel = MACHINECTRL.m_QveAutoProduction.at(0).Value_.at(MACHINE_ONLOAD_DIR).Vel;
	HC_PLC_INTERFACE.SetBOOLToPLC(nVel, dwAddr, emType);
	//工作速度
	dwAddr = MACHINECTRL.m_QveDefaultParam.at(0).Value_.at(CTRL_MACHINE_WORKSPEED).Addr.toInt();
	emType = MACHINECTRL.m_QveDefaultParam.at(0).Value_.at(CTRL_MACHINE_WORKSPEED).Addr_Type;
	nVel = MACHINECTRL.m_QveDefaultParam.at(0).Value_.at(CTRL_MACHINE_WORKSPEED).Vel;
	int nAccuracy = MACHINECTRL.m_QveDefaultParam.at(0).Value_.at(CTRL_MACHINE_WORKSPEED).Vel_Accuracy;
	HC_PLC_INTERFACE.SetBOOLToPLC(nVel*nAccuracy, dwAddr, emType);

	//参数设置页面数据下发
	QVector<ST_MODULE> qVecParemInfo = MACHINECTRL.m_QveParameterSetting;
	int nLength = qVecParemInfo.length();
	for (int i = 0; i < nLength; i++)
	{
		int nChildNum = qVecParemInfo.at(i).m_nModuleLength();
		for (int j = 0; j < nChildNum; j++)
		{
			if (_BOOL == qVecParemInfo.at(i).Value_.at(j).Vel_Type)
			{
				bool bData = false;
				if (qVecParemInfo.at(i).Value_.at(j).Vel != 0.0)
					bData = true;
				else
					bData = false;

				HC_PLC_INTERFACE.SetBOOLToPLC(bData
					, qVecParemInfo.at(i).Value_.at(j).Addr.toInt()
					, qVecParemInfo.at(i).Value_.at(j).Addr_Type);
			}
			else
			{
				HC_PLC_INTERFACE.SetDWORDToPLC(
					qVecParemInfo.at(i).Value_.at(j).Vel * qVecParemInfo.at(i).Value_.at(j).Vel_Accuracy,
					qVecParemInfo.at(i).Value_.at(j).Addr.toInt(),
					qVecParemInfo.at(i).Value_.at(j).Addr_Type);
			}
		}
	}
	return true;
}

bool OP_MachineStatusCtrl::SetMotorSpeed()
{
	int nModuleNum = MACHINECTRL.m_QveMotorDebug.length();
	double dlStartSpeed = 0;	//启动速度
	double dlMaxSpeed = 0;		//最大速度
	double dlAddSpeed = 0;		//加速时间
	double dlDecSpeed = 0;		//减速时间
	double dlHomeOffSet = 0;	//零点偏移
	double dlGotoHomeSpeed = 0;	//回零速度
	for (int i = 0; i < nModuleNum; i++)
	{
		dlStartSpeed = MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_START_SPEED).Vel * MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_START_SPEED).Vel_Accuracy;
		HC_PLC_INTERFACE.SetDWORDToPLC(dlStartSpeed,
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_START_SPEED).Addr.toInt(),
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_START_SPEED).Addr_Type);

		dlMaxSpeed = MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_MAX_SPEED).Vel * MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_MAX_SPEED).Vel_Accuracy;
		HC_PLC_INTERFACE.SetDWORDToPLC(dlStartSpeed,
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_MAX_SPEED).Addr.toInt(),
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_MAX_SPEED).Addr_Type);

		dlAddSpeed = MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_ADD_SPEED).Vel * MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_ADD_SPEED).Vel_Accuracy;
		HC_PLC_INTERFACE.SetDWORDToPLC(dlStartSpeed,
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_ADD_SPEED).Addr.toInt(),
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_ADD_SPEED).Addr_Type);

		dlDecSpeed = MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_DEC_SPEED).Vel * MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_DEC_SPEED).Vel_Accuracy;
		HC_PLC_INTERFACE.SetDWORDToPLC(dlStartSpeed,
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_DEC_SPEED).Addr.toInt(),
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_DEC_SPEED).Addr_Type);

		dlHomeOffSet = MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_HOME_OFFSET).Vel * MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_HOME_OFFSET).Vel_Accuracy;
		HC_PLC_INTERFACE.SetDWORDToPLC(dlStartSpeed,
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_HOME_OFFSET).Addr.toInt(),
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_HOME_OFFSET).Addr_Type);

		dlGotoHomeSpeed = MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_GOTOHOME_SPEED).Vel * MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_GOTOHOME_SPEED).Vel_Accuracy;
		HC_PLC_INTERFACE.SetDWORDToPLC(dlStartSpeed,
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_GOTOHOME_SPEED).Addr.toInt(),
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_GOTOHOME_SPEED).Addr_Type);
	}
	return true;
}

bool OP_MachineStatusCtrl::GetMotorIsInplace()
{
	ST_MODULE stModuleInfo = m_qVecPackageInfo.at(2);
	return MACHINECTRL.GetAllMotorInplace(stModuleInfo);
}

bool OP_MachineStatusCtrl::GetIsAutoMovePos()
{
	QString qstrPath = MACHINECTRL.ReturnPageCfgPath(PARAMETERSET);
	CString cstrPath = qstrPath.toStdWString().data();
	return ReadBoolFromFile(_T("复位时电机自动定位"), _T("Vel"), false, cstrPath);
}

bool OP_MachineStatusCtrl::SetMachineAlarm()
{
	return true;
}

bool OP_MachineStatusCtrl::InitMachineCtrl()
{
	//下发设备基本参数(电机速度、产品参数、基本运行数据)
	DWORD dwStartTime = GetTickCount();
	while (1)
	{
		if (MACHINECTRL.GetOnloadConfigStatus())
		{
			//连接激光
			if (!LASERINTERFACE.GetLaserIsConnect())
			{
				LASERINTERFACE.ConnectLaser();
			}
			//1、下发电机参数
			SetMotorSpeed();
			//2、下发产品数
			//获取当前产品
			CString m_cstrCurPkgName = ReadStringFromFile(_T("Run"), _T("当前产品文件名"), _T("Demo"), m_cstrFilmCfgPath);
			QString qstrCurPkgName = QString::fromStdWString(m_cstrCurPkgName.GetBuffer());
			m_cstrCurPkgName.ReleaseBuffer();
			if (!SetCrurentPackage(qstrCurPkgName))
			{
				QString strMsg = QString::fromLocal8Bit("设置当前产品\"%1\"失败").arg(qstrCurPkgName);
				emit MESSAGEBOX.SigNalMessAgeBoxData(strMsg, DOMODEL,0);
				return false;
			}
			//3、下发其他参数
			if (!SetOtherData())
			{
				emit MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("下发数据到PLC失败!"), DOMODEL,0);
				return false;
			}
			break;
		}
		else
		{
			if (GetTickCount() - dwStartTime > 10000)	//加载配置文件超时
			{
				emit MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("获取设备数据失败!"), DOMODEL,0);
				return false;
			}
			Sleep(10);
		}
	}
	return true;
}

bool OP_MachineStatusCtrl::InitMachineWork()
{
	//启动线程
	start();
	return true;
}

bool OP_MachineStatusCtrl::SetMachineStatus(EM_MACHINE_STATUS_CTRL emStatus, bool bFlag)
{
	m_emMachineStatusCtrl = emStatus;
	m_bMachineCurModel = bFlag;
	return true;
}

bool OP_MachineStatusCtrl::SetMachineWorkTask(EM_MACHINE_WORK_TASK emWork, bool bFlag)
{
	m_emMachineWorkTask = emWork;
	m_bMachineCurModel = bFlag;
	return true;
}

bool OP_MachineStatusCtrl::SetCrurentPackage(QString qstrCurPkgName)
{
	QString qstrPath = m_qstrPackageFilePath + qstrCurPkgName + QString::fromLocal8Bit(".pkg");
	if (!CFGINTERFACE.JudgeFileIsExist(qstrPath))
	{
		QString qstrMsg = QString::fromLocal8Bit("查找产品文件\"%1\"失败!").arg(qstrCurPkgName);
		emit MESSAGEBOX.SigNalMessAgeBoxData(qstrMsg, DOMODEL,0);
		return false;
	}
	
	CFGINTERFACE.initCfgValue(m_qVecPackageInfo, qstrPath);
	int nModuleNum = m_qVecPackageInfo.length();
	if (0 == nModuleNum)
	{
		QString qstrMsg = QString::fromLocal8Bit("产品文件\"%1\"无效!").arg(qstrCurPkgName);
		emit MESSAGEBOX.SigNalMessAgeBoxData(qstrMsg, DOMODEL,0);
		return false;
	}
	
	ST_LASER_DATA stLaserData;
	for (int i = 0; i < nModuleNum; i++)
	{
		//获取激光数据
		if (i <= 1)
		{
			if (i == 1) //极耳间距
			{
				stLaserData.nLaserStep = m_qVecPackageInfo.at(i).m_nModuleLength();
				CString cstrStepInfo = "";
				for (int j = 0; j < stLaserData.nLaserStep; j++)
				{
					double dlStepDist = m_qVecPackageInfo.at(i).Value_.at(j).Vel;
					cstrStepInfo.Format(_T("%.3f"), dlStepDist);
					if (j == stLaserData.nLaserStep - 1)
					{
						stLaserData.strLaserStepInfo = stLaserData.strLaserStepInfo + cstrStepInfo;
					}
					else
					{
						stLaserData.strLaserStepInfo = stLaserData.strLaserStepInfo + cstrStepInfo + "-";
					}
				}
			}
			else //激光相关数据
			{
				CString strFilePath = qstrPath.toStdWString().data();
				int nLength = m_qVecPackageInfo.at(i).m_nModuleLength();
				//默认参数//0产品文件,1激光文件,2极耳宽度,3极耳高度,4激光1功率,5激光1频率,6激光2功率，7激光2频率
				stLaserData.strLaserFileName = ReadStringFromFile(_T("激光文件"), _T("addr"), _T("Demo"), strFilePath);
				stLaserData.strLaserFilePath = ReadStringFromFile(_T("Run"), _T("LaserFilePath"), _T(""), m_cstrFilmCfgPath)
					+ stLaserData.strLaserFileName + _T(".hms");
				stLaserData.dlEarWidth = ReadDoubleFromFile(_T("极耳宽度"), _T("Vel"), 20.0, strFilePath);
				stLaserData.dlEarHeight = ReadDoubleFromFile(_T("极耳高度"), _T("Vel"), 15.0, strFilePath);
				stLaserData.dlLaser1Power = ReadDoubleFromFile(_T("激光1功率"), _T("Vel"), 30.0, strFilePath);
				stLaserData.dlLaser1Freq = ReadDoubleFromFile(_T("激光1频率"), _T("Vel"), 30.0, strFilePath);
				stLaserData.dlLaser2Power = ReadDoubleFromFile(_T("激光2功率"), _T("Vel"), 30.0, strFilePath);
				stLaserData.dlLaser2Freq = ReadDoubleFromFile(_T("激光2频率"), _T("Vel"), 30.0, strFilePath);
				m_stCurLaserData = stLaserData;
				//其他配置参数(扩展参数)
				for (int j = 8; j < nLength; j++)
				{
					if (_BOOL == m_qVecPackageInfo.at(i).Value_.at(j).Vel_Type)
					{
						bool bData = false;
						if (m_qVecPackageInfo.at(i).Value_.at(j).Vel != 0.0)
							bData = true;
						else
							bData = false;
						HC_PLC_INTERFACE.SetBOOLToPLC(bData, m_qVecPackageInfo.at(i).Value_.at(j).Addr.toInt(),
							m_qVecPackageInfo.at(i).Value_.at(j).Addr_Type);
					}
					else
					{
						HC_PLC_INTERFACE.SetBOOLToPLC(m_qVecPackageInfo.at(i).Value_.at(j).Vel * m_qVecPackageInfo.at(i).Value_.at(j).Vel_Accuracy, 
							m_qVecPackageInfo.at(i).Value_.at(j).Addr.toInt(),
							m_qVecPackageInfo.at(i).Value_.at(j).Addr_Type);
					}
				}
			}
			continue;
		}
		else //下发PLC
		{
			if (!m_bSoftwareIsFirstStart) //第一次启动不需要设置电机位置,设置设备运行方向等
			{
				m_bSoftwareIsFirstStart = false;
			}
			else
			{
				ST_MODULE stMotorModuleInfo = m_qVecPackageInfo.at(i);
				//是否需要自动定位
				if (GetIsAutoMovePos())
				{
					if (MACHINECTRL.GetAllMotorIsOrigin())
					{
						MACHINECTRL.AllMotorMoveToPos(m_qVecPackageInfo);
					}
					else
					{
						if (MACHINECTRL.AllMotorGotoHome())
						{
							if (!MACHINECTRL.AllMotorMoveToPos(m_qVecPackageInfo))
							{
								//移动到位失败
								//emit MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("电机移动到位失败"), DOMODEL, 0);
								//return false;
							}
						}
						else
						{
							//回零失败
							//emit MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("电机归零失败"), DOMODEL, 0);
							//return false;
						}
					}
				}
			}
		}
		//上传激光数据
		//获取激光使能
		QString qstrParamCfgPath = MACHINECTRL.ReturnPageCfgPath(PARAMETERSET);
		CString cstrParamCfgPath = qstrParamCfgPath.toStdWString().data();
		LASERINTERFACE.m_bEnableLaser[0] = ReadIntFromFile(_T("激光1使能"), _T("Vel"), 0, cstrParamCfgPath);
		LASERINTERFACE.m_bEnableLaser[1] = ReadIntFromFile(_T("激光2使能"), _T("Vel"), 0, cstrParamCfgPath);

		if (!LASERINTERFACE.UploadLaserData(stLaserData))
		{
			//上传激光数据失败
			emit MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("上传激光数据失败"), DOMODEL, 0);
			return false;
		}
		//参数设置页面数据
		SetOtherData(); 
	}
	m_qstrCurPkgName = qstrCurPkgName;
	return true;
}

ST_LASER_DATA OP_MachineStatusCtrl::GetCurLaserData()
{
	return m_stCurLaserData;
}

void OP_MachineStatusCtrl::SetLaserData(ST_LASER_DATA stLaserData)
{
	m_stCurLaserData = stLaserData;

}
