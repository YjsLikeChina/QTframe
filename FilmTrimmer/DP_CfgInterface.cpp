#include "DP_CfgInterface.hpp"
#include <QDir>
#include "UI_MessageBox.h"
#include <QDateTime>

DP_CfgInterface* DP_CfgInterface::m_pInstanceObj = NULL;

DP_CfgInterface* DP_CfgInterface::GetInstanceObj()
{
	if (NULL == m_pInstanceObj)
		m_pInstanceObj = new DP_CfgInterface;

	return m_pInstanceObj;
}


DP_CfgInterface::DP_CfgInterface(QObject * parent) : QObject(parent)
{
	m_qstrHistoryInfoPath = QCoreApplication::applicationDirPath();
	m_qstrHistoryInfoPath += QString::fromLocal8Bit("/Log/Lot History/");
	m_bFirstWriteHistoryFile = true;
}

DP_CfgInterface::~DP_CfgInterface()
{

}

QString DP_CfgInterface::AddrTranSlate(QString Addr, EM_Type AddrType, bool Forward)
{
	QString Value;
	if (Forward) {
		switch (AddrType)
		{
		case INVALID:Value= Addr;
			break;
		case MD:Value = Addr;
			break;
		case MW:Value = QString::number(Addr.toInt() * 2);
			break;
		case MX:
		{int temp = (int)Addr.toDouble() * 8;
		double temps = (Addr.toDouble() - temp / 8) * 10;
		Value = QString::number(temp + (temps));;
		}
		break;
		case QX:
		{int temp = (int)(Addr.toDouble() *2) *8;
		Value = QString::number(temp + (int)((Addr.toDouble() * 2 - (int)(Addr.toDouble() * 2)) * 10));
		}
		break;
		case IX:Value = "0";
			break;
		default:Value = "0";
			break;
		}
	}
	else
	{
		switch (AddrType)
		{
		case INVALID:Value = Addr;
			break;
		case MD:Value = Addr;
			break;
		case MW:Value = QString::number(Addr.toInt()/2);
			break;
		case MX:
		{int temp = Addr.toInt() / 8;
		Value = QString::number(temp + ((Addr.toInt() - temp * 8) ? (double)((Addr.toInt() - temp * 8) / 10.0) : 0));
		}
		break;
		case QX:
		{int temp = Addr.toInt() /8;
		Value = QString::number((temp + ((Addr.toInt() - temp * 8) ? (double)((Addr.toInt() - temp * 8) / 10.0) : 0))/2.0);
		}
		break;
		case IX:Value = "error";
			break;
		default:Value = "error";
			break;
		}
	}
	return Value;
}

bool DP_CfgInterface::initCfgValue(QVector<ST_MODULE>& VMoudel, QString path)
{
	CArray<CString> Moudul;
	CString cstrPath = StringTranSlate(path);
	QFileInfo isOpen(path);
	if (!isOpen.exists())
	{
		isOpen.refresh();
		QFile temp(path);
		bool tqc = temp.open(QIODevice::WriteOnly);
		temp.close();
		return false;
	}
	for (int i = 1;; i++)
	{
		CString strDefault;
		strDefault.Format(_T("%d"), i);
		CString value = ReadStringFromFile("Head", strDefault, "NOFOUND", cstrPath);
		if (value == "NOFOUND")
			break;
		Moudul.Add(value);
	}
	for (int i = 0; i < Moudul.GetSize(); i++)
	{
		QVector<ST_VALUECFG> OfMoudeValueKye;
		ST_MODULE MoudeAndValue; //模组信息
		ST_UPDATEDATA AutoUpdata; //自动更新数据
		CString strModuleName = Moudul.GetAt(i); //模块名
		CString cstrvalue;
		QString qstrValue;
		int j = 0;
		for (j = 0;; j++)
		{
			ST_VALUECFG Value_key;
			CString strDefault;
			strDefault.Format(_T("%d"), j + 1);

			CString strChlidName = ReadStringFromFile(strModuleName, strDefault, _T("NOFOUND"), cstrPath);
			if (strChlidName == _T("NOFOUND"))
				break;
			//模组名称
			Value_key.Function_name = QString::fromStdWString(strChlidName.GetBuffer());
			strChlidName.ReleaseBuffer();
			//PLC地址
			cstrvalue = ReadStringFromFile(strChlidName, _T("Addr"), _T("0"), cstrPath); //读取配置地址
			qstrValue = StringTranSlate(cstrvalue);
			cstrvalue.ReleaseBuffer();
			Value_key.Addr_Type = ReadTypeFromFile(strChlidName, _T("Addr_Type"), INVALID, cstrPath); //地址类型
			Value_key.Addr = AddrTranSlate(qstrValue, Value_key.Addr_Type); //换算配置地址

			Value_key.Vel = ReadDoubleFromFile(strChlidName, _T("Vel"), 0.0, cstrPath); //读取值

			cstrvalue = ReadStringFromFile(strChlidName, _T("Vel_Type"), _T("NOFOUND"), cstrPath); //读取值类型

			if (cstrvalue == _T("BOOL"))
				Value_key.Vel_Type = _BOOL;
			else if (cstrvalue == _T("INT"))
				Value_key.Vel_Type = _INT;
			else
				Value_key.Vel_Type = _FLOAT;

			Value_key.Vel_Accuracy = ReadIntFromFile(strChlidName, _T("Vel_Accuracy"), 1, cstrPath);

			CString cstrOtherAttribute = ReadStringFromFile(strChlidName, _T("OtherAttribute"), _T("EnalbleEdit"), cstrPath);
			if (cstrOtherAttribute == _T("InPut"))
				Value_key.OtherAttribute = INPUT_;
			else if(cstrOtherAttribute == _T("OutPut"))
				Value_key.OtherAttribute = OUTPUT;
			else if (cstrOtherAttribute == _T("EnalbleEdit"))
				Value_key.OtherAttribute = ENABLEEDIT;
			else if (cstrOtherAttribute == _T("DisableEdit"))
				Value_key.OtherAttribute = DISABLEEDIT;
			else if (cstrOtherAttribute == _T("AutoUpdata"))
			{
				Value_key.OtherAttribute = AUTOUPDATA;
			}

			OfMoudeValueKye.push_back(Value_key);
		}
		MoudeAndValue.Value_ = OfMoudeValueKye;
		MoudeAndValue.ModuleName = QString::fromStdWString(strModuleName.GetBuffer());
		strModuleName.ReleaseBuffer();
		//MoudeAndValue.m_nModuleLength() = j;
		VMoudel.push_back(MoudeAndValue);
	}

	return true;
}

bool DP_CfgInterface::WriteValue(const QVector<ST_MODULE>* CfgValue, int nModuleItem,QString strCfgPath)
{
	if (!JudgeFileIsExist(strCfgPath))
	{
		if (!DP_CfgInterface::CreateFile(strCfgPath))
		{
			QString strMsg(QString::fromLocal8Bit("创建产品文件%1s失败!"));
			strMsg.arg(strCfgPath);
			MESSAGEBOX.SlotNewMessAgeBoxData(strMsg, NODOMODEL);
		}
	}

	CString cstrCfgPath = strCfgPath.toStdWString().data();
	//重新文件头
	int nModuleNum = CfgValue->length();
	CString strHeadKey;
	CString strHeadInfo;
	strHeadKey.Format(_T("%d"), nModuleItem + 1);
	strHeadInfo = CfgValue->at(nModuleItem).ModuleName.toStdWString().data();
	WriteStringToFile(_T("Head"), strHeadKey, strHeadInfo, cstrCfgPath);
	//重写子项文件头
	int nChildNum = CfgValue->at(nModuleItem).m_nModuleLength();
	CString strChildSection, strChildKey, strChildInfo, RemoveTempName;
	strChildSection = CfgValue->at(nModuleItem).ModuleName.toStdWString().data();
	for (int i = 0; i < nChildNum; i++)
	{
		strChildKey.Format(_T("%d"), i + 1);
		strChildInfo = CfgValue->at(nModuleItem).Value_.at(i).Function_name.toStdWString().data();
		CString tempname = ReadStringFromFile(strChildSection, strChildKey, _T("NOFOUND"), cstrCfgPath);
		WriteStringToFile(strChildSection, strChildKey, strChildInfo, cstrCfgPath);
		if (tempname != strChildInfo)
			RemoveTempName = tempname;
	}
	strChildKey.Format(_T("%d"), nChildNum + 1);
	WriteStringToFile(strChildSection, strChildKey, NULL, cstrCfgPath);


	WriteStringToFile(RemoveTempName, NULL, NULL, cstrCfgPath);
	//保存各子项的值
	for (int j = 0; j < nChildNum; j++)
	{
		QString qstrtmp = CfgValue->at(nModuleItem).Value_.at(j).Function_name;
		CString strSection = qstrtmp.toStdWString().data();
		//Addr
		CString strinfo = CfgValue->at(nModuleItem).Value_.at(j).Addr.toStdWString().data();
		WriteStringToFile(strSection, _T("Addr"), strinfo, cstrCfgPath);
		//Addr_type
		switch (CfgValue->at(nModuleItem).Value_.at(j).Addr_Type)
		{
		case MD:
			strinfo = _T("MD");
			break;
		case MW:
			strinfo = _T("MW");
			break;
		case MX:
			strinfo = _T("MX");
			break;
		case QX:
			strinfo = _T("QX");
			break;
		case IX:
			strinfo = _T("IX");
			break;
		default:
			strinfo = _T("INVALID");
			break;
		}
		WriteStringToFile(strSection, _T("Addr_Type"), strinfo, cstrCfgPath);
	
		//Vel
		WriteDoubleToFile(strSection, _T("Vel"), CfgValue->at(nModuleItem).Value_.at(j).Vel, cstrCfgPath);
		//Vel_Type
		switch (CfgValue->at(nModuleItem).Value_.at(j).Vel_Type)
		{
		case _INT:
			strinfo = _T("INT");
			break;
		case _FLOAT:
			strinfo = _T("FLOAT");
			break;
		case _BOOL:
			strinfo = _T("BOOL");
			break;
		default:
			break;
		}
		WriteStringToFile(strSection, _T("Vel_Type"), strinfo, cstrCfgPath);
		//设定精度
		WriteIntToFile(strSection, _T("Vel_Accuracy"), CfgValue->at(nModuleItem).Value_.at(j).Vel_Accuracy, cstrCfgPath);
		//是否可编辑
		switch (CfgValue->at(nModuleItem).Value_.at(j).OtherAttribute)
		{
		case INPUT_:
			strinfo = _T("InPut");
			break;
		case OUTPUT:
			strinfo = _T("OutPut");
			break;
		case ENABLEEDIT:
			strinfo = _T("EnalbleEdit");
			break;
		case DISABLEEDIT:
			strinfo = _T("DisableEdit");
			break;
		case AUTOUPDATA:
			strinfo = _T("AutoUpdata");
			break;
		default:
			break;
		}
		WriteStringToFile(strSection, _T("OtherAttribute"), strinfo, cstrCfgPath);
	}
	return true;
}

bool DP_CfgInterface::WriteValue(const QMap<QString, QString>& ModifyVal, QString strKey,QString qstrCfgPath)
{
	if (ModifyVal.isEmpty())
		return true;
	QMap<QString, QString> qMapTmp = ModifyVal;
	int nLength = qMapTmp.size();
	CString cstrChildKey = ""; //Section
	CString cstrChildVal = ""; //Val
	CString cstrFilePath = qstrCfgPath.toStdWString().data();
	QString qstrChildInfoTmp = "";
	for (int i = 0; i < nLength; i++)
	{
		qstrChildInfoTmp = qMapTmp.first(); //Val
		cstrChildVal = qstrChildInfoTmp.toStdWString().data();
		
		qstrChildInfoTmp = qMapTmp.firstKey(); //Key
		cstrChildKey = qstrChildInfoTmp.toStdWString().data();

		CString cstrKey = strKey.toStdWString().data();
		if (!WriteStringToFile(cstrChildKey, cstrKey, cstrChildVal, cstrFilePath))
		{
			return false;
		}
		qMapTmp.remove(qstrChildInfoTmp); //remove Key
	}
	return true;
}

bool DP_CfgInterface::WriteHistoryInfo(QString qstrInfo, QString qstrFileName, bool bScreenFlag/* = false*/)
{
	HistoryLock.lock();
	QDateTime systemtime = QDateTime::currentDateTime();
	QString qstrPath = m_qstrHistoryInfoPath + qstrFileName + QString::fromLocal8Bit(".csv");
	if (m_bFirstWriteHistoryFile) //第一次写文件时判断文件大小，是否存在
	{
		m_bFirstWriteHistoryFile = false;
		//判断文件是否存在
		if (!JudgeFileIsExist(qstrPath)) //不存在
		{
			if (!DP_CfgInterface::CreateFile(qstrPath))
			{
				MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("创建历史文件失败!"), DOMODEL, 0);
				HistoryLock.unlock();
				return false;
			}
		}
		else //判断文件大小，超过1M时，新建历史文件
		{
			QFileInfo fileinfo(qstrPath);
			long long fileSize = fileinfo.size();
			if (fileSize > 1024 * 1024)
			{
				QString qstrNewName = systemtime.toString("yyyyMMdd");
				qstrNewName = m_qstrHistoryInfoPath + qstrNewName + "_" + qstrFileName + QString::fromLocal8Bit(".csv");
				if (!QFile::rename(qstrPath, qstrNewName)) //重命名
				{
					MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("重命名历史文件失败!"), DOMODEL, 0);
					HistoryLock.unlock();
					return false;
				}
				else //重命名成功后新建历史文件
				{
					if (!DP_CfgInterface::CreateFile(qstrPath)) //新建历史文件
					{
						MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("创建历史文件失败!"), DOMODEL, 0);
						HistoryLock.unlock();
						return false;
					}
				}
			}
		}
	}
	//写入历史文件
	FILE* m_pLotfile;
	CString cstrFilePath = qstrPath.toStdWString().data();
	if (_tfopen_s(&m_pLotfile, cstrFilePath, _T("a+, ccs=UTF-8")) == 0)//, ccs=UNICODE
	{
	}
	else
	{
		HistoryLock.unlock();
		MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("打开历史文件失败!"), NODOMODEL);
		return false;
	}
	if (!bScreenFlag) //写入文件信息,+ 时间
	{
		qstrInfo = qstrInfo + QString::fromLocal8Bit(",") + systemtime.toString("yyyy/MM/dd hh:mm:ss");
		CString cstrWriteInfo = qstrInfo.toStdWString().data();
		_ftprintf_s(m_pLotfile, _T("%s\n"), cstrWriteInfo.GetBuffer());
		cstrWriteInfo.ReleaseBuffer();
	}
	else
	{
		CString cstrWriteInfo = qstrInfo.toStdWString().data();
		_ftprintf_s(m_pLotfile, _T("%s"), cstrWriteInfo.GetBuffer());
		cstrWriteInfo.ReleaseBuffer();
	}
	fclose(m_pLotfile);
	HistoryLock.unlock();
	return true;
}

bool DP_CfgInterface::JudgeDirIsExist(const QString qstrDir)
{
	QDir JudgeDirIsExist(qstrDir);
	if (JudgeDirIsExist.exists())
		return true;
	else
		return false;
}

bool DP_CfgInterface::JudgeFileIsExist(const QString qstrDir)
{
	QFileInfo JudgeFileIsExist(qstrDir);
	if (JudgeFileIsExist.exists())
		return true;
	else
		return false;
}

bool DP_CfgInterface::CreateDir(const QString qstrDir)
{
	QDir _CreateDir;
	QString qstrDirInfo = qstrDir;
	if (_CreateDir.mkpath(qstrDirInfo))
		return true;
	else
		return false;
}

bool DP_CfgInterface::CreateFile(const QString qstrFilePath)
{
	QFile _CreateFile(qstrFilePath);
	if (_CreateFile.open(QIODevice::WriteOnly))
	{
		_CreateFile.close();
		return true;
	}
	else
		return false;
}

QString DP_CfgInterface::StringTranSlate(const CString & cstr)
{
	CString temp = cstr;
	if (cstr.GetLength() < 1)
		return "0";
	return QString::fromStdWString(temp.GetBuffer());
}

CString DP_CfgInterface::StringTranSlate(const QString & qstr)
{
	QString temp = qstr;
	if (temp.length() < 1)
		return "0";
	return  temp.toStdWString().c_str();
}
