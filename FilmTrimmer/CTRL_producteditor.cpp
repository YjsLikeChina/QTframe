#include "CTRL_producteditor.h"
#include "UI_MessageBox.h"
#include <QCoreApplication>

#define FILMTRIMMER_CFG  _T("/System/FilmTrimmer.cfg")

CTRL_ProductEditor::CTRL_ProductEditor(QObject * parent) : CTRL_Base(parent) 
{
	InitVal();
}

CTRL_ProductEditor::~CTRL_ProductEditor() 
{
	
}

void CTRL_ProductEditor::InitVal()
{
	QString strPath = QCoreApplication::applicationDirPath();
	m_qstrCfgPath = strPath;
	m_cstrFilmTrimmerPath = strPath.toStdWString().data();
	m_cstrFilmTrimmerPath += FILMTRIMMER_CFG;
	CString cstrCurFileName = ReadStringFromFile(_T("Run"), _T("当前产品文件名"), _T("Demo"), m_cstrFilmTrimmerPath);
	m_qstrCurFileName = QString::fromStdWString(cstrCurFileName.GetBuffer());
	cstrCurFileName.ReleaseBuffer();
}

void CTRL_ProductEditor::InitConnect()
{
}

bool CTRL_ProductEditor::SaveProducteData(QVector<ST_CHANGE_POINT> VeChangePoint,QVector<double> pitch, QStringList FileNewAndOldName, QString LaserFileName)
{
	ST_CHANGE_POINT ChangeTemp;
	ST_VALUECFG*     ValuecfgTemp;
	QMap<QString, QString> QmapString;
	QString ProductFileName = FileNewAndOldName.at(0);
	if (FileNewAndOldName.length() == 2&& FileNewAndOldName.at(0)!= FileNewAndOldName.at(1))
	{
		QString path = "/Data/Package/";
		QDir *dir = new QDir(m_qstrCfgPath +path);
		QStringList filter;
		filter << "*.pkg";
		dir->setNameFilters(filter);
		QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
		for (int i = 0; i < fileInfo->count(); i++)
		{
			if (fileInfo->at(i).fileName() == ProductFileName+".pkg")
			{
				MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("文件名重复！"), 1, 2000, true);
				return false;
			}
		}
	
	}
	ST_MODULE StModuleTemp;
	bool result = true;
	int nLength = VeChangePoint.size();
	for (int i = 0; i < nLength; i++)  //先修改容器中的值
	{
		ChangeTemp = VeChangePoint.at(i);
		StModuleTemp = *(MACHINECTRL.m_QveProductEditor.data() + ChangeTemp.nModuleNum);
		ValuecfgTemp = (MACHINECTRL.m_QveProductEditor.data() + ChangeTemp.nModuleNum)->Value_.data() + ChangeTemp.nChildNum;
		ValuecfgTemp->Vel = ChangeTemp.dlData;  //修改全局容器中的值
		if (ValuecfgTemp->Function_name.endsWith(QString::fromLocal8Bit("产品名称")))//找到产品名称
		{
			ValuecfgTemp->Addr = ProductFileName;
		}
		if (ValuecfgTemp->Function_name.endsWith(QString::fromLocal8Bit("激光文件")))//找到产品名称
		{
			ValuecfgTemp->Addr = LaserFileName;
		}
	}
	StModuleTemp = *(MACHINECTRL.m_QveProductEditor.data() + 1);
	ValuecfgTemp = StModuleTemp.Value_.data();
	if (StModuleTemp.ModuleName == QString::fromLocal8Bit("极耳间距"))//当确定为极耳间距模块时
	{
		QVector<ST_VALUECFG> QvStTemp;
		double addr = ValuecfgTemp->Addr.toDouble();
		StModuleTemp.Value_.clear();
		for (int j = 0; j < pitch.length(); j++) //循环将极耳数据放入新容器
		{
			ST_VALUECFG StTemp;
			StTemp.Addr = QString::number(addr++);
			StTemp.Addr_Type = MD;
			StTemp.Vel = pitch.at(j);
			StTemp.Function_name = QString::fromLocal8Bit("极耳间距%1").arg(j);
			QvStTemp.push_back(StTemp);
		}
		StModuleTemp.Value_ = QvStTemp;
	}
	else  //若找不到极耳间距模块则报错
	{
		MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("产品编辑配置文件格式不正确!"), 1, 2000, true);
		return false;	
	}
	QVector<ST_MODULE> QVeStModule = MACHINECTRL.m_QveProductEditor; //新容器创建 ，先读写配置文件
	if(0 != VeChangePoint.length())//基本参数没有修改不需要保存
		CFGINTERFACE.WriteValue(&QVeStModule, 0, MACHINECTRL.ReturnPageCfgPath(PRODUCTEDITOR));

	//if (0 != QVeStModule.at(1).m_nModuleLength())//极耳间距不需要保存到页面配置文件中
	CFGINTERFACE.WriteValue(&QVeStModule, 1, MACHINECTRL.ReturnPageCfgPath(PRODUCTEDITOR));


	*(QVeStModule.data() + 1) = StModuleTemp;
	ST_MODULE StModuleTemp2;
	StModuleTemp2.ModuleName = QString::fromLocal8Bit("电机位置");  //为新容器添加模块电机位置
	nLength = MACHINECTRL.m_QveMotorDebug.length();
	QVector<ST_VALUECFG> QvStTemp;
	for (int i = 0; i < nLength; i++)
	{	
		ST_VALUECFG StTemp = MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_GET_POS); //反馈位置
		QvStTemp.push_back(StTemp);
	}
	StModuleTemp2.Value_ = QvStTemp;
	QVeStModule.push_back(StModuleTemp2);

	//*(QVeStModule.data() + 1) = StModuleTemp;  //将极耳间距赋值给要写入产品文件的容器
	//将三个模块写入产品文件
	QString qstrPath = QCoreApplication::applicationDirPath();
	//if (0 != VeChangePoint.length())//基本参数没有修改不需要保存
		CFGINTERFACE.WriteValue(&QVeStModule, 0, qstrPath + "/Data/Package/"+ ProductFileName+".pkg");

	//if (0 != QVeStModule.at(1).m_nModuleLength())
		CFGINTERFACE.WriteValue(&QVeStModule, 1, qstrPath + "/Data/Package/" + ProductFileName + ".pkg");

//	if (0 != QVeStModule.at(2).m_nModuleLength())
		CFGINTERFACE.WriteValue(&QVeStModule, 2, qstrPath + "/Data/Package/" + ProductFileName + ".pkg");
	return result;
}

bool CTRL_ProductEditor::ChangeCurproduct(QString ProductFileName)
{
	if (m_bfirstStart)
	{
		//上传激光
		m_bfirstStart = false;
		QString qstrPath = m_qstrCfgPath + "/Data/Package/"+ ProductFileName + QString::fromLocal8Bit(".pkg");
		QFileInfo temp(qstrPath);
		if (!temp.exists())
		{
			MESSAGEBOX.SlotNewMessAgeBoxData(ProductFileName + QString::fromLocal8Bit("产品文件打开失败！"), 1, 2000, true);
			return false;
		}
		if (MACHINECTRL.m_pMachineStatusCtrl->SetCrurentPackage(ProductFileName))
		{
			LastUpdateTime = temp.lastModified();
			m_qstrCurFileName = ProductFileName;
		}
		else
		{
			return false;
		}
	}
	else
	{
		QString qstrPath = m_qstrCfgPath + "/Data/Package/" + ProductFileName + QString::fromLocal8Bit(".pkg");
		QFileInfo temp(qstrPath);
		if (ProductFileName == m_qstrCurFileName)
		{
			if (!temp.exists())
			{
				MESSAGEBOX.SlotNewMessAgeBoxData(ProductFileName+QString::fromLocal8Bit("产品文件打开失败！"), 1, 2000, true);
				return false;
			}
			if (LastUpdateTime == temp.lastModified())
			{
				MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("请勿重复上传相同产品文件！"), 1, 2000, true);
				return false;		
			}
			else
			{	
				m_bfirstStart = false;
				if (MACHINECTRL.m_pMachineStatusCtrl->SetCrurentPackage(ProductFileName))
				{
					LastUpdateTime = temp.lastModified();
					m_qstrCurFileName = ProductFileName;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			if (MACHINECTRL.m_pMachineStatusCtrl->SetCrurentPackage(ProductFileName))
			{
				LastUpdateTime = temp.lastModified();
				m_qstrCurFileName = ProductFileName;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

bool CTRL_ProductEditor::CopyPackage(QString qstrPkgName, QString& qstrNewPkgName)
{
	bool result = true;
	QString prototype = qstrPkgName;
	qstrPkgName = qstrPkgName + "_COPY";
	QString path = m_qstrCfgPath + "/Data/Package/";
	QDir *dir = new QDir(path);
	QStringList filter;
	filter<<"*.pkg";
	dir->setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
	for (int i = 0; i < fileInfo->count(); i++)
	{
		if (fileInfo->at(i).fileName() == qstrPkgName+".pkg")
		{
			qstrPkgName += "_COPY";
			i = 0;
		}	
	}
	result = QFile::copy(path + prototype + ".pkg", path + qstrPkgName + ".pkg");
	qstrNewPkgName = qstrPkgName;
	QMap<QString, QString> MstrTemp;
	MstrTemp.insert(QString::fromLocal8Bit("产品名称"), qstrPkgName);
	CFGINTERFACE.WriteValue(MstrTemp, QString::fromLocal8Bit("Addr"),m_qstrCfgPath+"/Data/Package/"+ qstrPkgName+".pkg");
	return result;
}

bool CTRL_ProductEditor::DeletePackage(QString qstrPkgName)
{
	if (m_qstrCurFileName == qstrPkgName)
	{
		MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("不能删除当前产品文件！"), 1, 2000, true);
		return false;
	}
	else
	{
		QFile temp(m_qstrCfgPath+ "/Data/Package/" + qstrPkgName + ".pkg");
		if (temp.open(QIODevice::WriteOnly))
		{
			if (temp.remove())
			{
				QString strMsg(QString::fromLocal8Bit("删除成功"));
				MESSAGEBOX.SlotNewMessAgeBoxData(strMsg, NODOMODEL);
				return true;
			}
			else
			{
				QString strMsg(QString::fromLocal8Bit("删除产品文件%1失败").arg(qstrPkgName));
				MESSAGEBOX.SlotNewMessAgeBoxData(strMsg, NODOMODEL);
				return false;
			}
		}
		else
		{
			QString strMsg(QString::fromLocal8Bit("产品文件%1不存在").arg(qstrPkgName));
			MESSAGEBOX.SlotNewMessAgeBoxData(strMsg,NODOMODEL);
			return true;
		}
	}
	return true;
}

bool CTRL_ProductEditor::NewPackage(QVector<ST_CHANGE_POINT> VeChangePoint, QVector<double> LaserStepInfo, QString FileName, QString LaserFileName)
{
	QString path = "/Data/Package/";
	QDir *dir = new QDir(m_qstrCfgPath+path);
	QStringList filter;
	filter << "*.pkg";
	dir->setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
	for (int i = 0; i < fileInfo->count(); i++)
	{
		if (fileInfo->at(i).fileName() == FileName + ".pkg")
		{
			MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("文件名重复！"), 1, 2000, true);
			return false;
		}
		
	}
	QStringList Temp(FileName);
	SaveProducteData(VeChangePoint, LaserStepInfo, Temp, LaserFileName);
	return true;
}

bool CTRL_ProductEditor::SwitchPackage(QVector<ST_CHANGE_POINT> &Data, QString &LaserFileName, QString qstrPkgName)
{
	QVector<ST_MODULE> QVeStModule;
	if (!CFGINTERFACE.initCfgValue(QVeStModule, m_qstrCfgPath +"./Data/Package/" + qstrPkgName + ".pkg"))
	{
		MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("产品文件打开失败！"), 1, 2000, true);
		return false;
	}
	if (QVeStModule.length()<=0)
	{
		MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("产品文件无内容或者内容格式错误！"), 1, 2000, true);
		return false;
	}
	for (int i = 0; i < 2; i++)
	{
		ST_CHANGE_POINT Potemp;
		int nLength = QVeStModule.at(i).m_nModuleLength();
		for (int j = 0; j < nLength;j++)
		{
			Potemp.dlData = QVeStModule.at(i).Value_.at(j).Vel;
			Potemp.nModuleNum = i;
			Potemp.nChildNum = j;
			if (QVeStModule.at(i).Value_.at(j).Function_name.endsWith(QString::fromLocal8Bit("激光文件")))//找到产品名称
			{
				LaserFileName = QVeStModule.at(i).Value_.at(j).Addr;
			}
			if (QVeStModule.at(i).Value_.at(j).Function_name.endsWith(QString::fromLocal8Bit("产品名称")))//找到产品名称
			{
				if (QVeStModule.at(i).Value_.at(j).Addr != qstrPkgName)
				{
					MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("产品文件内所记录文件名与本文件不匹配！"), 1, 2000, true);
					return false;
				}
			}
			Data.push_back(Potemp);
		}
	
	}
	return true;
}

bool CTRL_ProductEditor::SetLaserData(int nCard, double dlLaserPower, double dlLaserpFreq)
{
	//判断设备运行状态

	//获取激光目前参数
	ST_LASER_DATA stLaserData = MACHINECTRL.m_pMachineStatusCtrl->GetCurLaserData();
	//修改激光重新设置的参数
	if (0 == nCard)
	{
		stLaserData.dlLaser1Power = dlLaserPower;
		stLaserData.dlLaser1Freq = dlLaserpFreq;
	}
	else
	{
		stLaserData.dlLaser2Power = dlLaserPower;
		stLaserData.dlLaser2Freq = dlLaserpFreq;
	}
	//设置运行时激光数据
	MACHINECTRL.m_pMachineStatusCtrl->SetLaserData(stLaserData);
	return true;
}
