#include "UI_ParameterSetting.h"
#include <QCheckBox>

UI_ParameterSetting::UI_ParameterSetting(QWidget* parent /*= Q_NULLPTR*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
	:QWidget(parent),UI_InterfaceBase(parent)
{
	ui.setupUi(this);
	initVal();
	initUI();
	initConnect();
//	ShowSimpleParameterSetting(1);
}

UI_ParameterSetting::~UI_ParameterSetting()
{
}

void UI_ParameterSetting::initVal()
{
	m_UiSimPleDialog = new SimPleDialog;
	m_bAutoUpdateLock = false;
	m_pParameterSet = new CTRL_ParameterSet;
	m_pParameterSet->SetUIInterface(this);
}

void UI_ParameterSetting::initUI()
{
	//设置列宽
	ui.TRW_DataModule->setColumnWidth(0, 200);
	ui.TRW_BoolModule->setColumnWidth(0, 200);
	//设置UI
	QString qstrIconFile = QCoreApplication::applicationDirPath();
	QString qstrIconPath = qstrIconFile + "/Image/Save.png";
	ui.PB_ParamerSave->setIcon(QIcon(qstrIconPath));
	ui.PB_ParamerSave->setIconSize(QSize(35, 25));
	ui.PB_ParamerSave->setStyleSheet(
		"QPushButton:pressed{background-color:blue;color: white; border-radius: 10px; border: 1px groove gray; border-style: outset;border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/LaserSoftwareShow.png";
	ui.PB_LaserDataSet->setIcon(QIcon(qstrIconPath));
	ui.PB_LaserDataSet->setIconSize(QSize(35, 25));
	ui.PB_LaserDataSet->setStyleSheet(
		"QPushButton:pressed{background-color:blue;color: white; border-radius: 10px; border: 1px groove gray; border-style: outset;border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/Diaphaneity2.png";
	ui.LB_Background1->setScaledContents(true);
	ui.LB_Background1->setPixmap(QPixmap(qstrIconPath));
	ui.LB_Background2->setScaledContents(true);
	ui.LB_Background2->setPixmap(QPixmap(qstrIconPath));
	ui.LB_Background3->setScaledContents(true);
	ui.LB_Background3->setPixmap(QPixmap(qstrIconPath));
}

void UI_ParameterSetting::initConnect()
{
	connect(ui.PB_ParamerSave, SIGNAL(clicked()), this, SLOT(SlotParameSave()));
	connect(ui.TRW_DataModule, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(SlotDataItemChanged(QTreeWidgetItem*, int)));
	connect(ui.TRW_BoolModule, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(SlotBoolItemChanged(QTreeWidgetItem*, int)));
	//connect(ui.TRW_BoolModule, SIGNAL(clicked()), this, SLOT(SlotBoolItemChanged()));
}

bool UI_ParameterSetting::GetModifyParam(QVector<ST_CHANGE_POINT>& mapModifyVal)
{
	mapModifyVal = m_qVecModifyVal;
	return true;
}

bool UI_ParameterSetting::insertModule(QVector<ST_MODULE>* cfgModuleInfo)
{
	int nParentLength = cfgModuleInfo->length(); //模组个数
	for (int i = 0; i < nParentLength; i++)
	{
		ST_MODULEITEM _moduleItem;
		if (cfgModuleInfo->at(i).Value_.at(0).Vel_Type == _BOOL)
		{
			int nKey = ui.TRW_BoolModule->topLevelItemCount();
			m_qMapBoolOrder.insert(nKey, i);
			QTreeWidgetItem* boolModule = new QTreeWidgetItem(ui.TRW_BoolModule, QStringList(cfgModuleInfo->at(i).ModuleName));
			_moduleItem.ParentModuleItem = boolModule;
			int nChildLength = cfgModuleInfo->at(i).m_nModuleLength();
			for (int j = 0; j < nChildLength; j++) //子项
			{
				QTreeWidgetItem* ChildModule = new QTreeWidgetItem(boolModule, QStringList(cfgModuleInfo->at(i).Value_.at(j).Function_name));
				
				if (cfgModuleInfo->at(i).Value_.at(j).Vel)
					ChildModule->setCheckState(1, Qt::Checked);
				else
					ChildModule->setCheckState(1, Qt::Unchecked);

				_moduleItem.ChildModuleItems.push_back(ChildModule);
			}
		}
		else
		{
			int nKey = ui.TRW_DataModule->topLevelItemCount();
			m_qMapDataOrder.insert(nKey, i);
			QTreeWidgetItem* DataModule = new QTreeWidgetItem(ui.TRW_DataModule, QStringList(cfgModuleInfo->at(i).ModuleName));
			_moduleItem.ParentModuleItem = DataModule;
			int nChildLength = cfgModuleInfo->at(i).m_nModuleLength();
			for (int j = 0; j < nChildLength; j++) //子项
			{
				QTreeWidgetItem* ChildModule = new QTreeWidgetItem(DataModule, QStringList(cfgModuleInfo->at(i).Value_.at(j).Function_name));
				QString strVal;
				if (cfgModuleInfo->at(i).Value_.at(j).Vel_Type == _INT)
					strVal = QString::number(cfgModuleInfo->at(i).Value_.at(j).Vel);
				else
					strVal = QString::number(cfgModuleInfo->at(i).Value_.at(j).Vel, 'g', 8);

				if (ENABLEEDIT == cfgModuleInfo->at(i).Value_.at(j).OtherAttribute)
				{
					ui.TRW_DataModule->openPersistentEditor(ChildModule, 1);
				}
				else
					ChildModule->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

				ChildModule->setData(1, Qt::DisplayRole, strVal);
				_moduleItem.ChildModuleItems.push_back(ChildModule);
			}
		}
		m_ModuleVector.push_back(_moduleItem);
	}
	return true;
}

bool UI_ParameterSetting::AutoUpdateData(QList<ST_UPDATEDATA> qliAutoUpdata)
{
	if (m_bAutoUpdateLock)
		return false;
	m_bAutoUpdateLock = true;
	int nLength = qliAutoUpdata.length();
	int nModuleItem = -1, nChildItem = -1;
	for (int i = 0; i < nLength; i++)
	{
		nModuleItem = qliAutoUpdata.at(i).nModuleItem;
		nChildItem = qliAutoUpdata.at(i).nChildItem;

		//获取更新数据
		QString qstrVal = QString::number(qliAutoUpdata.at(i).dlData, 'g');
		//查找到修改的Item
		m_ModuleVector.at(nModuleItem).ChildModuleItems.at(nChildItem)->setText(1, qstrVal);
	}
	m_bAutoUpdateLock = false;
	return true;
}

void UI_ParameterSetting::SkipCurrentPage()
{
	//获取当前页面真实数据
	QVector<ST_MODULE> qVecParameterSetting;
	CFGINTERFACE.initCfgValue(qVecParameterSetting, MACHINECTRL.ReturnPageCfgPath(PARAMETERSET));
	int nModuleNum = qVecParameterSetting.length();
	for (int i = 0; i < nModuleNum; i++)
	{
		int nChildNum = qVecParameterSetting.at(i).m_nModuleLength();
		for (int j = 0; j < nChildNum; j++)
		{
			if (qVecParameterSetting.at(i).Value_.at(0).Vel_Type == _BOOL)//每个模组中数据类型相同，只需要判断第一个
			{
				if (qVecParameterSetting.at(i).Value_.at(j).Vel != 0)
					m_ModuleVector.at(i).ChildModuleItems.at(j)->setCheckState(1, Qt::Checked);
				else
					m_ModuleVector.at(i).ChildModuleItems.at(j)->setCheckState(1, Qt::Unchecked);
			}
			else
			{
				m_ModuleVector.at(i).ChildModuleItems.at(j)->setText(1,QString::number(qVecParameterSetting.at(i).Value_.at(j).Vel,'g',7));
			}
		}
	}
	m_qVecModifyVal.clear();
}

void UI_ParameterSetting::SlotParameSave()
{
	m_pParameterSet->SaveParmentterset(m_qVecModifyVal);
	m_qVecModifyVal.clear();
	//emit SigSave(m_qVecModifyVal);
}

void UI_ParameterSetting::SlotDataItemChanged(QTreeWidgetItem *item, int column)
{
	QTreeWidgetItem* CurItemParent = item->parent();
	int nModuleNum = ui.TRW_DataModule->indexOfTopLevelItem(CurItemParent);
	int nChildNum = CurItemParent->indexOfChild(item);
	double dlData = item->text(1).toDouble();

	ST_CHANGE_POINT temp;
	temp.dlData = dlData;
	temp.nChildNum = nChildNum;
	temp.nModuleNum = m_qMapDataOrder.value(nModuleNum);
	m_qVecModifyVal.push_back(temp);
}

void UI_ParameterSetting::SlotBoolItemChanged(QTreeWidgetItem* item, int column)
{
	QTreeWidgetItem* CurItemParent = item->parent();
	int nModuleNum = ui.TRW_BoolModule->indexOfTopLevelItem(CurItemParent);
	int nChildNum = CurItemParent->indexOfChild(item);

	ST_CHANGE_POINT temp;
	temp.dlData = item->checkState(1);
	temp.nChildNum = nChildNum;
	temp.nModuleNum = m_qMapBoolOrder.value(nModuleNum);
	m_qVecModifyVal.push_back(temp);
}

void UI_ParameterSetting::ShowSimpleParameterSetting(int UpOrPu)
{
	QStringList Name;
	Name << QString::fromLocal8Bit("微分值") << QString::fromLocal8Bit("比例值") << QString::fromLocal8Bit("上限点值")
		<< QString::fromLocal8Bit("下限点值") << QString::fromLocal8Bit("平衡点值") << QString::fromLocal8Bit("手动复位值");
	QVector<ST_CHANGE_POINT> Sttemp;
	m_UiSimPleDialog->SetShow(Name, Sttemp);
}

