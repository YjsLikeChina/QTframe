#include "UI_ParameterSetting.h"
#include <QLineEdit>
#include "DP_LaserInteraction.h"

UI_ParameterSetting::UI_ParameterSetting(QWidget* parent /*= Q_NULLPTR*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
	:QWidget(parent),UI_InterfaceBase(parent)
{
	ui.setupUi(this);
	initVal();
	initUI();
	initConnect();
}
UI_ParameterSetting::~UI_ParameterSetting()
{
	
}

void UI_ParameterSetting::initVal()
{
	m_bAutoUpdateLock = false;
	m_pParameterSet = new CTRL_ParameterSet;
	m_pParameterSet->SetUIInterface(this);
	m_UserMangerUi = new UI_UserManagerCtrol;
}

void UI_ParameterSetting::initUI()
{
	//设置列宽
	ui.TRW_DataModule->setColumnWidth(0, 200);
	ui.TRW_BoolModule->setColumnWidth(0, 200);
	//设置UI
	QString qstrIconFile = QCoreApplication::applicationDirPath();
	QString qstrIconPath = qstrIconFile + "/Image/Save2.png";
	ui.PB_ParamerSave->setIcon(QIcon(qstrIconPath));
	ui.PB_ParamerSave->setIconSize(QSize(35, 25));
	ui.PB_ParamerSave->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/LaserSoftwareShow.png";
	ui.PB_LaserDataSet->setIcon(QIcon(qstrIconPath));
	ui.PB_LaserDataSet->setIconSize(QSize(35, 25));
	ui.PB_LaserDataSet->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/UserManage.png";
	ui.PB_UserManage->setIcon(QIcon(qstrIconPath));
	ui.PB_UserManage->setIconSize(QSize(35, 25));
	ui.PB_UserManage->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/MESSet.png";
	ui.PB_MESUploadSet->setIcon(QIcon(qstrIconPath));
	ui.PB_MESUploadSet->setIconSize(QSize(35, 25));
	ui.PB_MESUploadSet->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
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
	connect(ui.TRW_BoolModule, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(SlotBoolItemChanged(QTreeWidgetItem*, int)));
	connect(ui.PB_LaserDataSet, SIGNAL(clicked()), this, SLOT(SlotLaserSoftwareShow()));
	connect(ui.PB_UserManage, SIGNAL(clicked()), m_UserMangerUi, SLOT(Dialog_show()));
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
				if (ENABLEEDIT == cfgModuleInfo->at(i).Value_.at(j).OtherAttribute)
				{
					UI_LineEdit* UserLineEdit = new UI_LineEdit(i,j,ui.TRW_DataModule);
					ui.TRW_DataModule->setItemWidget(ChildModule, 1, UserLineEdit);
					connect(UserLineEdit, SIGNAL(editingFinished()), this, SLOT(SlotDataItemChanged()));
				}
				//else
				//{
				//	ChildModule->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
				//}
				ChildModule->setSizeHint(1, QSize(100, 30));

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
				QTreeWidgetItem* LineEditItem = m_ModuleVector.at(i).ChildModuleItems.at(j);// 
				UI_LineEdit* _LineEdit = (UI_LineEdit*)ui.TRW_DataModule->itemWidget(LineEditItem, 1);
				_LineEdit->setText(QString::number(qVecParameterSetting.at(i).Value_.at(j).Vel, 'g', 7));
			}
		}
	}
	m_qVecModifyVal.clear();
}

bool UI_ParameterSetting::SaveParamer()
{
	SlotParameSave();
	m_qVecModifyVal.clear();
	return true;
}

void UI_ParameterSetting::SlotParameSave()
{
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:点击保存按钮").arg(__func__));
	m_pParameterSet->SaveParmentterset(m_qVecModifyVal);
	QString strtem = MACHINECTRL.ReturnPageCfgPath(PARAMETERSET);
	CString strPath = strtem.toStdWString().data();
	LASERINTERFACE.m_bEnableLaser[0] = ReadIntFromFile(_T("激光1使能"), _T("Vel"), 1, strPath);
	LASERINTERFACE.m_bEnableLaser[1] = ReadIntFromFile(_T("激光2使能"), _T("Vel"), 1, strPath);
	m_qVecModifyVal.clear();
	//emit SigSave(m_qVecModifyVal);
}

void UI_ParameterSetting::SlotDataItemChanged()
{
	UI_LineEdit* ChangeItem = (UI_LineEdit*)QObject::sender();
	ST_CHANGE_POINT temp;
	temp.dlData = ChangeItem->text().toDouble();
	temp.nChildNum = ChangeItem->nChildNum;
	temp.nModuleNum = ChangeItem->nModuleNum;
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:设置可选项%2为%3状态").arg(__func__).arg(temp.nModuleNum).arg(temp.dlData));
	m_qVecModifyVal.push_back(temp);
}

void UI_ParameterSetting::SlotLaserSoftwareShow()
{
	if (LASERINTERFACE.GetLaserType())
	{
		LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:打开激光软件").arg(__func__));
		LASERINTERFACE.m_pLaserCardCtrl->HMSShowEditWindow();
	}
}

void UI_ParameterSetting::SlotBoolItemChanged(QTreeWidgetItem* item, int column)
{
	QTreeWidgetItem* CurItemParent = item->parent();
	if (NULL == CurItemParent || column != 1)
		return;
	int nModuleNum = ui.TRW_BoolModule->indexOfTopLevelItem(CurItemParent);
	int nChildNum = CurItemParent->indexOfChild(item);

	ST_CHANGE_POINT temp;
	temp.dlData = item->checkState(1);
	temp.nChildNum = nChildNum;
	temp.nModuleNum = m_qMapBoolOrder.value(nModuleNum);\
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:设置可选项%2为%3状态").arg(__func__).arg(temp.nModuleNum).arg(item->checkState(1)));
	m_qVecModifyVal.push_back(temp);
}

