#include "OP_AutoUpdateData.h"
#include "DP_HCPLCInteraction.h"
#include <QFile>
#include <QTextStream>

OP_AutoUpdateData::OP_AutoUpdateData()
{
	initVal();
}


OP_AutoUpdateData::~OP_AutoUpdateData()
{
	
}

void OP_AutoUpdateData::initVal()
{

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
		m_qslMachineAlarmList.clear();
		MachineAlarmUpdata(m_qslMachineAlarmList);
		emit SigMachineAlarm(m_qslMachineAlarmList);
		Sleep(50);
	}
	return;
}

void OP_AutoUpdateData::AutoUpdateCommon(QList<ST_UPDATEDATA>& _qLisAutoUpdata)
{
	QList<ST_UPDATEDATA> CommonAutoUpdate = m_qMapAutoUpdateData->value(m_nCurPage); //获取该页面中对应的自动更新数据列表
	int nLength = CommonAutoUpdate.length();
	
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
	if (m_bReadHistoryInfoLock)
		return;
	ST_UPDATEDATA _updata;
	m_bReadHistoryInfoLock = true;
	QString strFilePath = m_qslHistoryInfoFilePath.at(m_nCurModule);
	QFile file(strFilePath);
	if (!file.open(QIODevice::ReadOnly))
		return;

	QTextStream * out = new QTextStream(&file);//文本流  
	_updata.qstrData = out->readAll();//每行以\n区分
	_qLisAutoUpdata.insert(m_nCurModule, _updata);

	file.close();//操作完成后记得关闭文件 

	m_bReadHistoryInfoLock = false;
}

bool OP_AutoUpdateData::MachineAlarmUpdata(QStringList& qslAlarm)
{
	return true;
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
		m_qslHistoryInfoFilePath << _HistoryInfoFilePath.at(i).qstrData;	//将历史文件路径保存下来
	}
	if (!this->isRunning())
	{
		m_bRunFlag = true;
		this->start();
	}
}

