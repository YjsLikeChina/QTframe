#include "CTRL_producteditor.h"
#include "UI_MessageBox.h"

CTRL_ProductEditor::CTRL_ProductEditor(QObject * parent) : CTRL_Base(parent) {

	
}

CTRL_ProductEditor::~CTRL_ProductEditor() {
	
}

void CTRL_ProductEditor::InitVal()
{
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
	QString qstrPath = QCoreApplication::applicationDirPath();
	if (FileNewAndOldName.length() == 2)
	{
		QString path = "/Data/package/";
		QDir *dir = new QDir(qstrPath+path);
		QStringList filter;
		filter << "*.pkg";
		dir->setNameFilters(filter);
		QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
		for (int i = 0; i < fileInfo->count(); i++)
		{
			if (fileInfo->at(i).fileName() == ProductFileName)
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
		if (ValuecfgTemp->Function_name.endsWith(QString::fromLocal8Bit("激光文件名称")))//找到产品名称
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
	CFGINTERFACE.WriteValue(&QVeStModule, 0, MACHINECTRL.ReturnPageCfgPath(PARAMETERSET));
	CFGINTERFACE.WriteValue(&QVeStModule, 1, MACHINECTRL.ReturnPageCfgPath(PARAMETERSET));


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

	CFGINTERFACE.WriteValue(&QVeStModule, 0, qstrPath + "/Data/package/"+ ProductFileName+".pkg");
	CFGINTERFACE.WriteValue(&QVeStModule, 1, qstrPath + "/Data/package/" + ProductFileName + ".pkg");
	CFGINTERFACE.WriteValue(&QVeStModule, 2, qstrPath + "/Data/package/" + ProductFileName + ".pkg");
	QMap<QString, QString> MstrTemp;
	MstrTemp.insert(QString::fromLocal8Bit("当前产品"), ProductFileName);
	CFGINTERFACE.WriteValue(MstrTemp, "/Data/Machine.cfg");
	return result;
}

bool CTRL_ProductEditor::ChangeCurproduct(QString ProductFileName)
{
	if (firstStart)
	{
		//上传激光
		firstStart = false;
		QString qstrPath = ".\\Data\\Package"+ ProductFileName + QString::fromLocal8Bit(".pkg");
		QVector<ST_MODULE> m_qVecPackageInfo;
		QFileInfo temp(qstrPath);
		if (!temp.exists())
		{
			MESSAGEBOX.SlotNewMessAgeBoxData(ProductFileName + QString::fromLocal8Bit("产品文件打开失败！"), 1, 2000, true);
			return false;
		}
		CFGINTERFACE.initCfgValue(m_qVecPackageInfo, qstrPath);

		ST_LASER_DATA stLaserData;
		stLaserData.nLaserStep =  m_qVecPackageInfo.at(1).m_nModuleLength();
		CString cstrStepInfo = "";
		for (int j = 0; j < stLaserData.nLaserStep; j++)
		{
			double dlStepDist = m_qVecPackageInfo.at(1).Value_.at(j).Vel;
			cstrStepInfo.Format(_T(".3f"), dlStepDist);
			stLaserData.strLaserStepInfo = stLaserData.strLaserStepInfo + cstrStepInfo + "-";
		}
		stLaserData.strLaserStepInfo.Left(stLaserData.strLaserStepInfo.GetLength() - 1); //除掉最后那个‘-’

		CString strFilePath = qstrPath.toStdWString().data();
		//默认参数
		stLaserData.strLaserFileName = ReadStringFromFile(_T("激光文件"), _T("addr"), _T("Demo"), strFilePath);
	/*	stLaserData.strLaserFilePath = ReadStringFromFile(_T("Run"), _T("LaserFilePath"), _T(""), m_cstrMachineCfgPath)
			+ stLaserData.strLaserFileName + _T(".hms");*/
		stLaserData.dlEarWidth = ReadDoubleFromFile(_T("极耳宽度"), _T("Vel"), 20.0, strFilePath);
		stLaserData.dlEarHeight = ReadDoubleFromFile(_T("极耳高度"), _T("Vel"), 15.0, strFilePath);
		stLaserData.dlLaser1Power = ReadDoubleFromFile(_T("激光1功率"), _T("Vel"), 30.0, strFilePath);
		stLaserData.dlLaser1Freq = ReadDoubleFromFile(_T("激光1频率"), _T("Vel"), 30.0, strFilePath);
		stLaserData.dlLaser2Power = ReadDoubleFromFile(_T("激光2功率"), _T("Vel"), 30.0, strFilePath);
		stLaserData.dlLaser2Freq = ReadDoubleFromFile(_T("激光2频率"), _T("Vel"), 30.0, strFilePath);

		if (!LASERINTERFACE.UploadLaserData(stLaserData, true))
		{
			MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("上传失败！") , 1, 2000, true);
			return false;
		}
		LastUpdateTime = temp.lastModified();
		CurFileName = ProductFileName;
	}
	else
	{
		if (ProductFileName == CurFileName)
		{
			QString qstrPath = ".\\Data\\Package" + ProductFileName + QString::fromLocal8Bit(".pkg");
			QFileInfo temp(qstrPath);
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
				firstStart = false;
				QString qstrPath = ".\\Data\\Package" + ProductFileName + QString::fromLocal8Bit(".pkg");
				QVector<ST_MODULE> m_qVecPackageInfo;
				QFileInfo temp(qstrPath);
				if (!temp.exists())
				{
					MESSAGEBOX.SlotNewMessAgeBoxData(ProductFileName + QString::fromLocal8Bit("产品文件打开失败！"), 1, 2000, true);
					return false;
				}
				CFGINTERFACE.initCfgValue(m_qVecPackageInfo, qstrPath);

				ST_LASER_DATA stLaserData;
				stLaserData.nLaserStep = m_qVecPackageInfo.at(1).m_nModuleLength();
				CString cstrStepInfo = "";
				for (int j = 0; j < stLaserData.nLaserStep; j++)
				{
					double dlStepDist = m_qVecPackageInfo.at(1).Value_.at(j).Vel;
					cstrStepInfo.Format(_T(".3f"), dlStepDist);
					stLaserData.strLaserStepInfo = stLaserData.strLaserStepInfo + cstrStepInfo + "-";
				}
				stLaserData.strLaserStepInfo.Left(stLaserData.strLaserStepInfo.GetLength() - 1); //除掉最后那个‘-’

				CString strFilePath = qstrPath.toStdWString().data();
				//默认参数
				stLaserData.strLaserFileName = ReadStringFromFile(_T("激光文件"), _T("addr"), _T("Demo"), strFilePath);
				/*	stLaserData.strLaserFilePath = ReadStringFromFile(_T("Run"), _T("LaserFilePath"), _T(""), m_cstrMachineCfgPath)
				+ stLaserData.strLaserFileName + _T(".hms");*/
				stLaserData.dlEarWidth = ReadDoubleFromFile(_T("极耳宽度"), _T("Vel"), 20.0, strFilePath);
				stLaserData.dlEarHeight = ReadDoubleFromFile(_T("极耳高度"), _T("Vel"), 15.0, strFilePath);
				stLaserData.dlLaser1Power = ReadDoubleFromFile(_T("激光1功率"), _T("Vel"), 30.0, strFilePath);
				stLaserData.dlLaser1Freq = ReadDoubleFromFile(_T("激光1频率"), _T("Vel"), 30.0, strFilePath);
				stLaserData.dlLaser2Power = ReadDoubleFromFile(_T("激光2功率"), _T("Vel"), 30.0, strFilePath);
				stLaserData.dlLaser2Freq = ReadDoubleFromFile(_T("激光2频率"), _T("Vel"), 30.0, strFilePath);

				if (!LASERINTERFACE.UploadLaserData(stLaserData, true))
				{
					MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("上传失败！"), 1, 2000, true);
					return false;
				}
				LastUpdateTime = temp.lastModified();
				CurFileName = ProductFileName;
			}
		}

	}
	return true;
}

bool CTRL_ProductEditor::CopyPackage(QString qstrPkgName)
{
	bool result = true;
	QString prototype = qstrPkgName;
	qstrPkgName = qstrPkgName + "_COPY";
	QString path = "/Data/package/";
	QDir *dir = new QDir(path);
	QStringList filter;
	filter<<"*.pkg";
	dir->setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
	for (int i = 0; i < fileInfo->count(); i++)
	{
		if (fileInfo->at(i).fileName() == qstrPkgName)
		{
			qstrPkgName += "_COPY";
			i = 0;
		}	
	}
	result = QFile::copy(prototype, qstrPkgName);
	QMap<QString, QString> MstrTemp;
	MstrTemp.insert(QString::fromLocal8Bit("产品名称"), qstrPkgName);
	CFGINTERFACE.WriteValue(MstrTemp, "/Data/"+ qstrPkgName+".cfg");
	return result;
}

bool CTRL_ProductEditor::DeletePackage(QString qstrPkgName)
{
	if (CurFileName == qstrPkgName)
	{
		MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("不能删除当前产品文件！"), 1, 2000, true);
		return false;
	}
	else
	{
		QFile temp("/Data/package/" + qstrPkgName + ".pkg");
		if (temp.open(QIODevice::WriteOnly))
		{
			temp.remove();
			return true;
		}
	}
	return true;
}

bool CTRL_ProductEditor::NewPackage(QVector<ST_CHANGE_POINT> VeChangePoint, QVector<double> LaserStepInfo, QString FileName, QString LaserFileName)
{
	QString path = "/Data/package/";
	QDir *dir = new QDir(path);
	QStringList filter;
	filter << "*.pkg";
	dir->setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
	for (int i = 0; i < fileInfo->count(); i++)
	{
		if (fileInfo->at(i).fileName() == FileName)
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
	QString qstrPath = QCoreApplication::applicationDirPath();
	if (!CFGINTERFACE.initCfgValue(QVeStModule, qstrPath+"./Data/package/" + qstrPkgName + ".pkg"))
	{
		MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("产品文件打开失败！"), 1, 2000, true);
		return false;
	}
	for (int i = 0; i < 2; i++)
	{
		ST_CHANGE_POINT Potemp;
		for (int j = 0; j < QVeStModule.at(i).Value_.length();j++)
		{
			Potemp.dlData = QVeStModule.at(i).Value_.at(j).Vel;
			Potemp.nModuleNum = i;
			Potemp.nChildNum = j;
			if (QVeStModule.at(i).Value_.at(j).Function_name.endsWith(QString::fromLocal8Bit("激光文件名称")))//找到产品名称
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
