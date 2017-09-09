#include "OP_MachineSoftWareMain.h"
#include "DP_CfgInterface.hpp"
#include <QCoreApplication>
#include <QDateTime>
OP_MachineSoftWareMain* OP_MachineSoftWareMain::m_pInstanceObj = Q_NULLPTR;
OP_MachineSoftWareMain* OP_MachineSoftWareMain::GetInstanceObj()
{
	if (Q_NULLPTR == m_pInstanceObj)
		m_pInstanceObj = new OP_MachineSoftWareMain;

	return m_pInstanceObj;
}

OP_MachineSoftWareMain::OP_MachineSoftWareMain(QObject* parent /*= Q_NULLPTR*/)
{
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
	QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
	QString qstrPath = QCoreApplication::applicationDirPath();
	QString str = time.toString("yyyy-MM-dd hh.mm.ss"); //设置显示格式
	str = qstrPath+ "/System/"+ str + ".log";
	string logpath = str.toLocal8Bit().toStdString();
	m_Log = LOGMANANGER(logpath.c_str());
	for (int i = 0; i < 500; i++)
	{
		QString temp = QString(QString::fromLocal8Bit("log测试来了！log_Text_%1")).arg(i);

		m_Log->WriteLogQstring(CLog::LL_WARN, temp);
	}
}

void OP_MachineSoftWareMain::initConnect()
{
}

void OP_MachineSoftWareMain::LoadModuleInfo()
{
	//自动生产页面
	CFGINTERFACE.initCfgValue(m_QveAutoProduction, ReturnPageCfgPath(AUTOMATICPRODUCT));
	QList<ST_UPDATEDATA> _AutoUpdateData;
	GetAutoUpdateData(m_QveAutoProduction, _AutoUpdateData);
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

