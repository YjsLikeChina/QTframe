#include "OP_MachineSoftWareMain.h"
#include "DP_CfgInterface.hpp"
#include <QCoreApplication>

OP_MachineSoftWareMain* OP_MachineSoftWareMain::m_pInstanceObj = Q_NULLPTR;
OP_MachineSoftWareMain* OP_MachineSoftWareMain::GetInstanceObj()
{
	if (Q_NULLPTR == m_pInstanceObj)
		m_pInstanceObj = new OP_MachineSoftWareMain;

	return m_pInstanceObj;
}

OP_MachineSoftWareMain::OP_MachineSoftWareMain(QObject* parent /*= Q_NULLPTR*/)
{
	MESSAGEBOX.GetInstanceObj();

	initVal();
	LoadModuleInfo();
	initConnect();
}

OP_MachineSoftWareMain::~OP_MachineSoftWareMain()
{
}

void OP_MachineSoftWareMain::initVal()
{
	m_bOnloadConfigFinish = false;
	m_User = new CUserManager;
	m_User->AddUser(L"中国人", L"123455", USER_ADMIN);
	CStringList name;
	name.InsertBefore(0, L"管理员");
	m_User->DeleteUsers(name);
	m_User->Login(0);
	

}

void OP_MachineSoftWareMain::initConnect()
{
}

void OP_MachineSoftWareMain::LoadModuleInfo()
{
	//自动生产页面
	CFGINTERFACE.initCfgValue(m_QveAutoProduction, ReturnPageCfgPath(AUTOMATICPRODUCT));
	QList<ST_UPDATEDATA> _AutoUpdateData;
	GetAutoUpdateData(m_QveAutoProduction, _AutoUpdateData,AUTOMATICPRODUCT);
	m_qMapAutoUpdateData.insert(AUTOMATICPRODUCT, _AutoUpdateData);
	//IO调试
	CFGINTERFACE.initCfgValue(m_QveIODebug, ReturnPageCfgPath(IODEBUG));
	_AutoUpdateData.clear();
	GetAutoUpdateData(m_QveIODebug, _AutoUpdateData,IODEBUG);
	m_qMapAutoUpdateData.insert(IODEBUG, _AutoUpdateData);
	//电机控制
	CFGINTERFACE.initCfgValue(m_QveMotorDebug, ReturnPageCfgPath(MOTORDEBUG));
	_AutoUpdateData.clear();
	GetAutoUpdateData(m_QveMotorDebug, _AutoUpdateData);
	m_qMapAutoUpdateData.insert(MOTORDEBUG, _AutoUpdateData);
	//参数设置
	CFGINTERFACE.initCfgValue(m_QveParameterSetting, ReturnPageCfgPath(PARAMETERSET));
	_AutoUpdateData.clear();
	GetAutoUpdateData(m_QveParameterSetting, _AutoUpdateData);
	m_qMapAutoUpdateData.insert(PARAMETERSET, _AutoUpdateData);
	//产品编辑
	CFGINTERFACE.initCfgValue(m_QveProductEditor, ReturnPageCfgPath(PRODUCTEDITOR));
	_AutoUpdateData.clear();
	GetAutoUpdateData(m_QveProductEditor, _AutoUpdateData);
	m_qMapAutoUpdateData.insert(PRODUCTEDITOR, _AutoUpdateData);
	//历史信息
	CFGINTERFACE.initCfgValue(m_QveHistoricalInfo, ReturnPageCfgPath(HISTORICALINFO));
	_AutoUpdateData.clear();
	GetAutoUpdateData(m_QveHistoricalInfo, _AutoUpdateData,HISTORICALINFO);
	m_qMapAutoUpdateData.insert(HISTORICALINFO, _AutoUpdateData);

	//按照页面顺序
	QVector<ST_MODULE> tmp; //设备维护
	m_qVecAllPageData.insert(MAINTENANCE, tmp);
	m_qVecAllPageData.insert(AUTOMATICPRODUCT,m_QveAutoProduction);
	m_qVecAllPageData.insert(PRODUCTEDITOR,m_QveProductEditor);
	m_qVecAllPageData.insert(HISTORICALINFO, m_QveHistoricalInfo);
	m_qVecAllPageData.insert(IODEBUG,m_QveIODebug);
	m_qVecAllPageData.insert(MOTORDEBUG,m_QveMotorDebug);
	m_qVecAllPageData.insert(PARAMETERSET, m_QveParameterSetting);
	//默认参数
	CFGINTERFACE.initCfgValue(m_QveDefaultParam, ReturnPageCfgPath(FILMTRIMMER));
	//UI主框架(报警)
	//MES
	//emit SigOnloadConfigFinish();
	m_bOnloadConfigFinish = true;
}

QString OP_MachineSoftWareMain::ReturnPageCfgPath(EM_CHILDPAGEITEM emPageItem)
{
	m_qstrCfgPath = QCoreApplication::applicationDirPath();
	switch (emPageItem)
	{
	case AUTOMATICPRODUCT:
		return m_qstrCfgPath + QString::fromLocal8Bit("/System/AutoProduction.cfg");
		break;
	case IODEBUG:
		return m_qstrCfgPath + QString::fromLocal8Bit("/System/IODebug.cfg");
		break;
	case MOTORDEBUG:
		return m_qstrCfgPath + QString::fromLocal8Bit("/System/MotorDebug.cfg");
		break;
	case PARAMETERSET:
		return m_qstrCfgPath + QString::fromLocal8Bit("/System/ParameterSet.cfg");
		break;
	case PRODUCTEDITOR:
		return m_qstrCfgPath + QString::fromLocal8Bit("/System/ProductEditor.cfg");
		break;
	case HISTORICALINFO:
		return m_qstrCfgPath + QString::fromLocal8Bit("/System/Historicalinfo.cfg");
		break;
	case MESONLOAD:
		return m_qstrCfgPath + QString::fromLocal8Bit("/System/MESOnload.cfg");
		break;
	case FILMTRIMMER:
		return m_qstrCfgPath + QString::fromLocal8Bit("/System/FilmTrimmer.cfg");
	default:
		return m_qstrCfgPath + QString::fromLocal8Bit("");
		break;
	}
};


bool OP_MachineSoftWareMain::GetAutoUpdateData(const QVector<ST_MODULE>& QVecSource, QList<ST_UPDATEDATA>& AutoUpdateData, int nPage /*=  1*/)
{
	if (HISTORICALINFO == nPage)
	{
		int nModuleNum = QVecSource.length();
		for (int i = 0; i < nModuleNum; i++)
		{
			if (AUTOUPDATA == QVecSource.at(i).Value_.at(0).OtherAttribute)
			{
				ST_UPDATEDATA _Updata;
				_Updata.qstrData = QVecSource.at(i).Value_.at(0).Function_name; //历史信息配置文件中文件路径为

				AutoUpdateData.push_back(_Updata);
			}
		}
	}
	if (IODEBUG == nPage)
	{
		int nModuleNum = QVecSource.length();
		for (int i = 0; i < nModuleNum; i++)
		{
			int nChildNum = QVecSource.at(i).m_nModuleLength();
			for (int j = 0; j < nChildNum; j++)
			{
				ST_UPDATEDATA _Updata;
				if (INPUT_ == QVecSource.at(i).Value_.at(j).OtherAttribute)
				{

					_Updata.dwPLCAddr = QVecSource.at(i).Value_.at(j).Addr.toInt();
					_Updata.nAccuracy = QVecSource.at(i).Value_.at(j).Vel_Accuracy;
					_Updata.nChildItem = j;
					_Updata.nModuleItem = i;
					_Updata.PLCAddrType = QVecSource.at(i).Value_.at(j).Addr_Type;
					_Updata.qstrModultName = QVecSource.at(i).Value_.at(j).Function_name;

					AutoUpdateData.push_back(_Updata);
				}
			}
		}
	}
	else if (AUTOMATICPRODUCT == nPage)
	{
		QString qstrFilCfgPath = ReturnPageCfgPath(FILMTRIMMER);
		CString strFilmCfgPath = qstrFilCfgPath.toStdWString().data();
		int nCard = ReadIntFromFile(_T("Run"), _T("LaserNum"), 2, strFilmCfgPath); //获取激光个数
		int nModuleNum = QVecSource.length();
		for (int i = 0; i < nModuleNum; i++)
		{
			int nChildNum = QVecSource.at(i).m_nModuleLength();
			for (int j = 0; j < nChildNum; j++)
			{
				ST_UPDATEDATA _Updata;
				if (AUTOUPDATA == QVecSource.at(i).Value_.at(j).OtherAttribute)
				{
					_Updata.dwPLCAddr = QVecSource.at(i).Value_.at(j).Addr.toInt();
					_Updata.nAccuracy = QVecSource.at(i).Value_.at(j).Vel_Accuracy;
					_Updata.nChildItem = j;
					_Updata.nModuleItem = i;
					_Updata.PLCAddrType = QVecSource.at(i).Value_.at(j).Addr_Type;
					_Updata.qstrModultName = QVecSource.at(i).Value_.at(j).Function_name;
					AutoUpdateData.push_back(_Updata);

					//添加额外的激光自动更新数据，激光步数、当班产量、总产量均分别以连续的地址出现
					if (j == LASER_STEP)	//激光步数位置
					{
						for (int k = 0; k < nCard - 1; k++) //k < nCard - 1:前面已经添加了第一组激光自动更新数据
						{
							_Updata.dwPLCAddr = QVecSource.at(i).Value_.at(j).Addr.toInt() + k + 1;
							_Updata.nAccuracy = QVecSource.at(i).Value_.at(j).Vel_Accuracy;
							_Updata.nChildItem = j;
							_Updata.nModuleItem = i;
							_Updata.PLCAddrType = QVecSource.at(i).Value_.at(j).Addr_Type;
							_Updata.qstrModultName = QVecSource.at(i).Value_.at(j).Function_name;
							AutoUpdateData.push_back(_Updata);
						}
					}
					if (j == LASER_YIELD) //激光当班产量
					{
						for (int k = 0; k < nCard - 1; k++)
						{
							_Updata.dwPLCAddr = QVecSource.at(i).Value_.at(j).Addr.toInt() + k + 1;
							_Updata.nAccuracy = QVecSource.at(i).Value_.at(j).Vel_Accuracy;
							_Updata.nChildItem = j;
							_Updata.nModuleItem = i;
							_Updata.PLCAddrType = QVecSource.at(i).Value_.at(j).Addr_Type;
							_Updata.qstrModultName = QVecSource.at(i).Value_.at(j).Function_name;
							AutoUpdateData.push_back(_Updata);
						}
					}
					if (j == LASER_SUM_YIELD) //激光总产量
					{
						for (int k = 0; k < nCard - 1; k++)
						{
							_Updata.dwPLCAddr = QVecSource.at(i).Value_.at(j).Addr.toInt() + k + 1;
							_Updata.nAccuracy = QVecSource.at(i).Value_.at(j).Vel_Accuracy;
							_Updata.nChildItem = j;
							_Updata.nModuleItem = i;
							_Updata.PLCAddrType = QVecSource.at(i).Value_.at(j).Addr_Type;
							_Updata.qstrModultName = QVecSource.at(i).Value_.at(j).Function_name;
							AutoUpdateData.push_back(_Updata);
						}
					}
					
				}
			}
		}
	}
	else
	{
		int nModuleNum = QVecSource.length();
		for (int i = 0; i < nModuleNum; i++)
		{
			int nChildNum = QVecSource.at(i).m_nModuleLength();
			for (int j = 0; j < nChildNum; j++)
			{
				ST_UPDATEDATA _Updata;
				if (AUTOUPDATA == QVecSource.at(i).Value_.at(j).OtherAttribute)
				{

					_Updata.dwPLCAddr = QVecSource.at(i).Value_.at(j).Addr.toInt();
					_Updata.nAccuracy = QVecSource.at(i).Value_.at(j).Vel_Accuracy;
					_Updata.nChildItem = j;
					_Updata.nModuleItem = i;
					_Updata.PLCAddrType = QVecSource.at(i).Value_.at(j).Addr_Type;
					_Updata.qstrModultName = QVecSource.at(i).Value_.at(j).Function_name;

					AutoUpdateData.push_back(_Updata);
				}
			}
		}
	}
	return true;
}

void OP_MachineSoftWareMain::initTask()
{
	LoadMotorInfo();
	//生成自动更新类对象
	m_pAutoUpdateData = new OP_AutoUpdateData;
	//添加工作任务
	m_pAutoUpdateData->insertWorkTask(m_qMapAutoUpdateData);
	m_pAutoUpdateData->SwitchWorkTask(AUTOMATICPRODUCT,0);

	//状态控制以及产品相关功能
	m_pMachineStatusCtrl = new OP_MachineStatusCtrl;
	m_pMachineStatusCtrl->InitMachineWork();//启动线程
}

bool OP_MachineSoftWareMain::GetOnloadConfigStatus()
{
	return m_bOnloadConfigFinish;
}

bool OP_MachineSoftWareMain::AllMotorGotoHome()
{
	int nLength = m_QveMotorDebug.length();
	for (int i = 0; i < nLength; i++)
	{
		if ((int)(m_QveMotorDebug.at(i).Value_.at(ORDER_OTHER_ATTRIBUTE).Vel) & 0x01) //允许自动定位
		{
			if (!MOTORSCTRL[i]->SetMotorGotoHome())
				return false;
		}
		else
			continue;
	}
	return true;
}

bool OP_MachineSoftWareMain::AllMotorMoveToPos(QVector<ST_MODULE> qVecMotorInfo)
{
	int nLength = m_QveMotorDebug.length();
	for (int i = 0; i < nLength; i++)
	{
		if ((int)(m_QveMotorDebug.at(i).Value_.at(ORDER_OTHER_ATTRIBUTE).Vel) & 0x01) //允许自动定位
		{
			double dlDist = m_QveMotorDebug.at(i).Value_.at(ORDER_SET_TARGET_POS).Vel;
			if (!MOTORSCTRL[i]->SetMotorMove(dlDist, ABSOLUTE_MOVE))
				return false;
		}
		else
			continue;
	}
	return true;
}

bool OP_MachineSoftWareMain::GetAllMotorIsOrigin()
{
	int nLength = m_QveMotorDebug.length();
	for (int i = 0; i < nLength; i++)
	{
		if ((int)(m_QveMotorDebug.at(i).Value_.at(ORDER_OTHER_ATTRIBUTE).Vel) & 0x01) //允许自动定位
		{
			if (MOTORSCTRL[i]->GetMotorStatus() & AXIS_STATU_ORIGIN)
			{
				continue;
			}
			else
				return false;
		}
		else
		{
			continue;
		}
	}
	return true;
}

bool OP_MachineSoftWareMain::GetAllMotorInplace(ST_MODULE stModuleInfo)
{
	int nLength = stModuleInfo.m_nModuleLength();
	for (int i = 0; i < nLength; i++)
	{
		if (stModuleInfo.Value_.at(i).OtherAttribute & 0x01) //允许自动定位
		{
			if (abs(stModuleInfo.Value_.at(i).Vel - MOTORSCTRL[i]->GetMotorCurrentPos() > 0.001))
				return false;
			else
				continue;
		}
		else
			continue;
	}
	return true;
}

void OP_MachineSoftWareMain::LoadMotorInfo()
{
	int nMotorSize = m_QveMotorDebug.size();
	if (nMotorSize <= 0)
		return;
	for (int i = 0; i < nMotorSize; i++)
	{
		DP_MotorCtrlInteraction* TmpMotor = new DP_MotorCtrlInteraction;
		TmpMotor->InitMotorsInfo(i+1, m_QveMotorDebug.at(i).Value_);
		MOTORSCTRL.push_back(TmpMotor);
	}
}

