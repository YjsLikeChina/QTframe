#include "OP_AutoUpdateData.h"
#include "DP_HCPLCInteraction.h"
#include <QFile>
#include <QTextStream>
#include "DP_LaserInteraction.h"
#include "OP_MachineSoftWareMain.h"

OP_AutoUpdateData::OP_AutoUpdateData()
{
	initVal();
}


OP_AutoUpdateData::~OP_AutoUpdateData()
{
	
}

void OP_AutoUpdateData::initVal()
{
	m_bReadHistoryInfoLock = false;
	m_dwMachineModelAddr = MACHINECTRL.m_QveFilmParam.at(0).Value_.at(CTRL_MACHINE_MODEL).Addr.toInt();
	m_emMachineModelType = MACHINECTRL.m_QveFilmParam.at(0).Value_.at(CTRL_MACHINE_MODEL).Addr_Type;
	m_qstrAlarmList = "";
	m_qstrErrorList = "";
}

void OP_AutoUpdateData::run()
{
	while (m_bRunFlag)
	{
		m_qLisAutoUpdata.clear();
		switch (m_nCurPage)
		{
		case AUTOMATICPRODUCT:
			AutoUpdateCommon(m_qLisAutoUpdata);
			emit SigAutoProduction(m_qLisAutoUpdata);
				break;
		case MOTORDEBUG:
			AutoUpdateCommon(m_qLisAutoUpdata);
			emit SigMotorDebug(m_qLisAutoUpdata);
			break;
		case PARAMETERSET:
			AutoUpdateCommon(m_qLisAutoUpdata);
			emit SigParameterSetting(m_qLisAutoUpdata);
			break;
		case PRODUCTEDITOR:
			AutoUpdateCommon(m_qLisAutoUpdata);
			emit SigProductEditor(m_qLisAutoUpdata);
			break;
		case IODEBUG:
			AutoUpdateIOStatus(m_qLisAutoUpdata);
			emit SigIODebug(m_qLisAutoUpdata);
			break;
		case HISTORICALINFO:
			AutoUpdataHistoryInfo(m_qLisAutoUpdata);
			emit SigHistoricalInformation(m_qLisAutoUpdata);
			break;
		default:
			Sleep(200);
			break;
		}
		//�豸�������豸���Զ�ģʽ
		MachineAlarmUpdata(m_qstrAlarmList, m_qstrErrorList);
		emit SigMachineAlarm(m_qstrAlarmList, m_qstrErrorList);
		MachineModelUpdata(m_bMachineModel);
		emit SigMachineModel(m_bMachineModel);
		Sleep(50);
	}
	return;
}

void OP_AutoUpdateData::AutoUpdateCommon(QList<ST_UPDATEDATA>& _qLisAutoUpdata)
{
	QList<ST_UPDATEDATA> CommonAutoUpdate = m_qMapAutoUpdateData->value(m_nCurPage); //��ȡ��ҳ���ж�Ӧ���Զ����������б�
	int nLength = CommonAutoUpdate.length();
	static int j = 0;
	j += 10;
	for (int i = 0; i < nLength; i++)
	{
		ST_UPDATEDATA _updata;
		if (MD == CommonAutoUpdate.at(i).PLCAddrType || MW == CommonAutoUpdate.at(i).PLCAddrType || QW == CommonAutoUpdate.at(i).PLCAddrType)
		{
			_updata.dlData = HC_PLC_INTERFACE.GetDWORDFromPLC(CommonAutoUpdate.at(i).dwPLCAddr, CommonAutoUpdate.at(i).PLCAddrType) / CommonAutoUpdate.at(i).nAccuracy;
		}
		else
		{
			_updata.dlData = HC_PLC_INTERFACE.GetBOOLFromPLC(CommonAutoUpdate.at(i).dwPLCAddr, CommonAutoUpdate.at(i).PLCAddrType);
		}
		_updata.dwPLCAddr = CommonAutoUpdate.at(i).dwPLCAddr;
		_updata.nAccuracy = CommonAutoUpdate.at(i).nAccuracy;
		_updata.nChildItem = CommonAutoUpdate.at(i).nChildItem;
		_updata.nModuleItem = CommonAutoUpdate.at(i).nModuleItem;
		_updata.PLCAddrType = CommonAutoUpdate.at(i).PLCAddrType;

		_qLisAutoUpdata.insert(i, _updata);
	}
	//�Զ�����ҳ����¼���״̬
	if (AUTOMATICPRODUCT == m_nCurPage)
	{
		ST_UPDATEDATA _updata;
		for (int i = 0; i < 2; i++)
		{
			int nLaserStatus = LASERINTERFACE.GetLaserStatus(i);
			_updata.dlData = nLaserStatus;
			_updata.dwPLCAddr = 0;
			_updata.nAccuracy = 0;
			_updata.nChildItem = 0;
			_updata.nModuleItem = 0;
			_updata.PLCAddrType = INVALID;

			_qLisAutoUpdata.push_back(_updata);
		}
	}
}

void OP_AutoUpdateData::AutoUpdateIOStatus(QList<ST_UPDATEDATA>& _qLisAutoUpdata)
{
	//
	QList<ST_UPDATEDATA> IOUpdateData = m_qMapAutoUpdateData->value(m_nCurPage);
	int nLength = IOUpdateData.length();
	for (int i = 0; i < nLength; i++)
	{
		if (IOUpdateData.at(i).nModuleItem == m_nCurModule)
		{
			ST_UPDATEDATA _updata;
			_updata.dlData = HC_PLC_INTERFACE.GetBOOLFromPLC(IOUpdateData.at(i).dwPLCAddr, IOUpdateData.at(i).PLCAddrType);
			_updata.dwPLCAddr = IOUpdateData.at(i).dwPLCAddr;
			_updata.nAccuracy = IOUpdateData.at(i).nAccuracy;
			_updata.nChildItem = IOUpdateData.at(i).nChildItem;
			_updata.nModuleItem = IOUpdateData.at(i).nModuleItem;
			_updata.PLCAddrType = IOUpdateData.at(i).PLCAddrType;

			_qLisAutoUpdata.insert(i, _updata);
		}
	}
}

void OP_AutoUpdateData::AutoUpdataHistoryInfo(QList<ST_UPDATEDATA>& _qLisAutoUpdata)
{
	if (_qLisAutoUpdata.isEmpty())
	{
		return;
	}
	if (m_bReadHistoryInfoLock)
		return;
	ST_UPDATEDATA _updata;
	m_bReadHistoryInfoLock = true;
	QString strFilePath = m_qslHistoryInfoFilePath.at(m_nCurModule);
	QFile file(strFilePath);
	if (!file.open(QIODevice::ReadOnly))
		return;

	QTextStream * out = new QTextStream(&file);//�ı���  
	_updata.qstrData = out->readAll();//ÿ����\n����
	_qLisAutoUpdata.insert(m_nCurModule, _updata);

	file.close();//������ɺ�ǵùر��ļ� 

	m_bReadHistoryInfoLock = false;
}

bool OP_AutoUpdateData::MachineAlarmUpdata(QString& qslAlarm, QString& qslError)
{
	//�����豸����
	int nLength = m_qVecAlarmList.length();
	qslAlarm.clear();
	qslError.clear();
	for (int i = 0; i < nLength; i++)
	{
		qslAlarm += m_qVecAlarmList.at(i).Function_name + ",";
		//if (HC_PLC_INTERFACE.GetBOOLFromPLC(m_qVecAlarmList.at(i).Addr.toInt(), m_qVecAlarmList.at(i).Addr_Type))
		//{
		//	qslAlarm = qslAlarm + m_qVecAlarmList.at(i).Function_name + ",";
		//}
	}
	//�����豸����
	nLength = m_qVecErrorList.length();
	for (int i = 0; i < nLength; i++)
	{
		qslError = qslError + m_qVecErrorList.at(i).Function_name + ",";
		//if (HC_PLC_INTERFACE.GetBOOLFromPLC(m_qVecErrorList.at(i).Addr.toInt(), m_qVecErrorList.at(i).Addr_Type))
		//{
		//	qslError = qslError + m_qVecErrorList.at(i).Function_name + ",";
		//}
	}
	return true;
}

void OP_AutoUpdateData::MachineModelUpdata(bool& bMachineModel)
{
	//��ȡ�豸���Զ�ģʽ
	bMachineModel = HC_PLC_INTERFACE.GetBOOLFromPLC(m_dwMachineModelAddr, m_emMachineModelType);
}

void OP_AutoUpdateData::SwitchWorkTask(int nCurPage, int nCurModule)
{
	m_nCurPage = nCurPage;
	m_nCurModule = nCurModule;
}

void OP_AutoUpdateData::insertWorkTask(QMap<int, QList<ST_UPDATEDATA>>& AutoUpdateData)
{
	m_qMapAutoUpdateData = &AutoUpdateData;

	QList<ST_UPDATEDATA> _HistoryInfoFilePath = AutoUpdateData.value(HISTORICALINFO);
	int nLength = _HistoryInfoFilePath.length();
	for (int i = 0; i < nLength; i++)
	{
		m_qslHistoryInfoFilePath << _HistoryInfoFilePath.at(i).qstrData;	//����ʷ�ļ�·����������
	}
	if (!this->isRunning())
	{
		m_bRunFlag = true;
		this->start();
	}
}

