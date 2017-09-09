#include "UI_ProductEditor.h"

#define ROWWIDTH	280
#define ROWHEIGHT	35

UI_ProductEditor::UI_ProductEditor(QWidget* parent /*= Q_NULLPTR*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
	:QWidget(parent),UI_InterfaceBase(parent)
{
	ui.setupUi(this);
	initVal();
	initUI();
	initConnect();
}

UI_ProductEditor::~UI_ProductEditor()
{
	delete m_pAddStepButton;
	delete m_qrwStepItem;
}

void UI_ProductEditor::initVal()
{
	m_qstrIconFile = QCoreApplication::applicationDirPath();
	m_pAddStepButton = new QPushButton;
	m_qrwStepItem = new QTreeWidgetItem;
	m_qrwStepItem = Q_NULLPTR;
	m_bAddStepLock = false;
}

void UI_ProductEditor::initUI()
{
	//设置UI
	QString qstrIconPath = m_qstrIconFile + "/Image/Diaphaneity2.png";
	ui.LB_Background1->setScaledContents(true);
	ui.LB_Background1->setPixmap(QPixmap(qstrIconPath));
	ui.LB_Background2->setScaledContents(true);
	ui.LB_Background2->setPixmap(QPixmap(qstrIconPath));

	qstrIconPath = m_qstrIconFile + "/Image/CurrentPackage.png";
	ui.PB_Package_SetCurrent->setIcon(QIcon(qstrIconPath));
	ui.PB_Package_SetCurrent->setIconSize(QSize(35, 25));
	ui.PB_Package_SetCurrent->setStyleSheet(
		"QPushButton:pressed{background-color:blue;color: white; border-radius: 10px; border: 1px groove gray; border-style: outset;border-style: inset; }"
		);

	qstrIconPath = m_qstrIconFile + "/Image/PackageNew.png";
	ui.PB_Package_New->setIcon(QIcon(qstrIconPath));
	ui.PB_Package_New->setIconSize(QSize(35, 25));
	ui.PB_Package_New->setStyleSheet(
		"QPushButton:pressed{background-color:blue;color: white; border-radius: 10px; border: 1px groove gray; border-style: outset;border-style: inset; }"
		);

	qstrIconPath = m_qstrIconFile + "/Image/PackageDelete.png";
	ui.PB_Package_Delete->setIcon(QIcon(qstrIconPath));
	ui.PB_Package_Delete->setIconSize(QSize(35, 25));
	ui.PB_Package_Delete->setStyleSheet(
		"QPushButton:pressed{background-color:blue;color: white; border-radius: 10px; border: 1px groove gray; border-style: outset;border-style: inset; }"
		);

	qstrIconPath = m_qstrIconFile + "/Image/PackageCopy.png";
	ui.PB_Package_Copy->setIcon(QIcon(qstrIconPath));
	ui.PB_Package_Copy->setIconSize(QSize(35, 25));
	ui.PB_Package_Copy->setStyleSheet(
		"QPushButton:pressed{background-color:blue;color: white; border-radius: 10px; border: 1px groove gray; border-style: outset;border-style: inset; }"
		);

	qstrIconPath = m_qstrIconFile + "/Image/Save.png";
	ui.PB_Package_Save->setIcon(QIcon(qstrIconPath));
	ui.PB_Package_Save->setIconSize(QSize(35, 25));
	ui.PB_Package_Save->setStyleSheet(
		"QPushButton:pressed{background-color:blue;color: white; border-radius: 10px; border: 1px groove gray; border-style: outset;border-style: inset; }"
		);

	//设置控件宽度
	ui.TRW_PkgParticularInfo->setColumnWidth(0, 200);
	ui.TRW_PkgParticularInfo->setColumnWidth(1, 300);
	ui.TRW_PkgParticularInfo->setColumnWidth(2, 70);
}

void UI_ProductEditor::initConnect()
{
	connect(ui.PB_Package_SetCurrent, SIGNAL(clicked()), this, SLOT(SlotSetCurrentPackage()));
	connect(ui.PB_Package_Copy, SIGNAL(clicked()), this, SLOT(SlotCopyPackage()));
	connect(ui.PB_Package_Delete, SIGNAL(clicked()), this, SLOT(SlotDeletePackage()));
	connect(ui.PB_Package_New, SIGNAL(clicked()), this, SLOT(SlotNewPackage()));
	connect(ui.PB_Package_Save, SIGNAL(clicked()), this, SLOT(SlotSavePackage()));
	connect(m_pAddStepButton, SIGNAL(clicked()), this, SLOT(SlotAddPackageStep()));
	connect(&m_ButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(SlotDeleteStep(int)));
	connect(ui.TRW_PkgParticularInfo, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(SlotItemChanged(QTreeWidgetItem*, int)));
	connect(ui.LW_PackageList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SlotSwitchPackage(QListWidgetItem*)));
}

void UI_ProductEditor::ShowSimpleProduictEditor(int laser)
{
	QList<QTreeWidgetItem *> temp1;
	QList<QTreeWidgetItem *> temp2;
	QStringList Name;
	if (laser == 1)
	{
		temp1 = ui.TRW_PkgParticularInfo->findItems(QString::fromLocal8Bit("激光1功率"),Qt::MatchFlags());
		temp2 = ui.TRW_PkgParticularInfo->findItems(QString::fromLocal8Bit("激光1频率"), Qt::MatchFlags());
		Name << QString::fromLocal8Bit("激光1功率") << QString::fromLocal8Bit("激光1频率");
	}
	else
	{
		temp1 = ui.TRW_PkgParticularInfo->findItems(QString::fromLocal8Bit("激光2功率"), Qt::MatchFlags());
		temp2 = ui.TRW_PkgParticularInfo->findItems(QString::fromLocal8Bit("激光2频率"), Qt::MatchFlags());
		Name << QString::fromLocal8Bit("激光2功率") << QString::fromLocal8Bit("激光2频率");
	}
	QVector<ST_CHANGE_POINT> Sttemp;
	m_UiSimPleDialog->SetShow(Name, Sttemp);
	//Sttemp.nChildNum = ui.TRW_PkgParticularInfo->indexOfTopLevelItem(temp1.at(0));
	//Sttemp.nModuleNum = 0;
}

void UI_ProductEditor::SlotSetCurrentPackage()
{
	QString qstrCurPkgName = m_pCurrentSelPkgItem->text();
	m_pProductEditor->ChangeCurproduct(qstrCurPkgName);
}

void UI_ProductEditor::SlotCopyPackage()
{
	QString qstrCopyPkgName = m_pCurrentSelPkgItem->text();
	if (m_pProductEditor->CopyPackage(qstrCopyPkgName))
	{
		QString qstrCopyNewPkgName = qstrCopyPkgName + QString::fromLocal8Bit("Copy");
		ui.LW_PackageList->addItem(qstrCopyNewPkgName);
	}
}

void UI_ProductEditor::SlotDeletePackage()
{
	QString qstrDelPkgName = m_pCurrentSelPkgItem->text();
	if (m_pProductEditor->DeletePackage(qstrDelPkgName))
	{
		ui.LW_PackageList->removeItemWidget(m_pCurrentSelPkgItem);
		m_pCurrentSelPkgItem = ui.LW_PackageList->item(0);
	}
}

void UI_ProductEditor::SlotNewPackage()
{
	QString qstrNewPkgName;
	AddNewPackage(qstrNewPkgName);
	QListWidgetItem* _NewItem = new QListWidgetItem(qstrNewPkgName);
	ui.LW_PackageList->addItem(_NewItem);
}

void UI_ProductEditor::SlotSavePackage()
{
	int nLength = m_qrwStepItem->childCount();
	QVector<double> qVecStepDist;
	for (int i = 0; i < nLength; i++)
	{
		qVecStepDist.push_back(m_qrwStepItem->text(1).toDouble());
	}
	QString qstrOldPkgName = m_pCurrentSelPkgItem->text();
	QTreeWidgetItem* PkgNameItem = ui.TRW_PkgParticularInfo->topLevelItem(0);
	QString qstrNewPkgName = PkgNameItem->child(0)->text(1);
	QString qstrLaserName = PkgNameItem->child(1)->text(1);
	QStringList qslPkgName;
	qslPkgName << qstrNewPkgName << qstrOldPkgName;
	m_pProductEditor->SaveProducteData(m_qVecPkgModifyInfo, qVecStepDist, qslPkgName, qstrLaserName);
}

void UI_ProductEditor::SlotAddPackageStep()
{
	if (m_bAddStepLock)
		return;
	m_bAddStepLock = true;
	int nCurStep = m_qrwStepItem->childCount();
	QString qstrStep = QString::number(nCurStep);
	QStringList qslStepInit;
	qslStepInit << qstrStep << QString::fromLocal8Bit("30") << QString::fromLocal8Bit("");
	QTreeWidgetItem* StepItem = new QTreeWidgetItem(m_qrwStepItem, qslStepInit);
	StepItem->setFlags(StepItem->flags() | Qt::ItemIsEditable);

	QFont _font(QString::fromLocal8Bit("微软雅黑"), 10);
	QPushButton* _DelStep = new QPushButton;
	_DelStep->setText(QString::fromLocal8Bit("删除"));
	_DelStep->setMaximumSize(80, 25);
	_DelStep->setFont(_font);
	_DelStep->setStyleSheet(
		"QPushButton{background: transparent;color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);
	m_ButtonGroup.addButton(_DelStep, nCurStep);
	ui.TRW_PkgParticularInfo->setItemWidget(StepItem, 2, (QWidget*)_DelStep);
	m_bAddStepLock = false;
	return;
}

void UI_ProductEditor::SlotSwitchPackage(QListWidgetItem *item)
{
	QString qstrPkgName = item->text();
	m_pCurrentSelPkgItem = item;

	QVector<ST_CHANGE_POINT> qVecOnloadPkgInfo;
	QString qstrLaserFileName;

	m_pProductEditor->SwitchPackage(qVecOnloadPkgInfo, qstrLaserFileName, qstrPkgName);
	UpdataPackageInfo(qVecOnloadPkgInfo, qstrLaserFileName, qstrPkgName);
}

void UI_ProductEditor::SlotDeleteStep(int nButton)
{
	int nDelRow = nButton;
	QTreeWidgetItem* DelItem = m_qrwStepItem->child(nDelRow);
	m_qrwStepItem->removeChild(DelItem);
	QAbstractButton* DelButton = m_ButtonGroup.button(nButton);
	m_ButtonGroup.removeButton(DelButton);
	QList<QAbstractButton*> ButtonList = m_ButtonGroup.buttons();
	int nLength = ButtonList.length();
	for (int i = nButton; i < nLength; i++)
	{
		m_ButtonGroup.setId(ButtonList.at(i), i);
		DelItem = m_qrwStepItem->child(i);
		DelItem->setText(0, QString::number(i));
	}
}

void UI_ProductEditor::SlotItemChanged(QTreeWidgetItem* item, int nColumn)
{
	QTreeWidgetItem* CurItemParent = item->parent();
	if (CurItemParent != m_qrwStepItem)
	{
		QString strModifyItem = item->text(0);
		ST_CHANGE_POINT stqVecChangeVal;
		if (strModifyItem.endsWith(QString::fromLocal8Bit("名")))
		{
			//
		}
		else
		{
			if (CurItemParent == NULL)
				return;
			int nModuleNum = ui.TRW_PkgParticularInfo->indexOfTopLevelItem(CurItemParent);
			int nChildNum = CurItemParent->indexOfChild(item);
			double dlData = item->text(1).toDouble();

			ST_CHANGE_POINT temp;
			temp.dlData = dlData;
			temp.nChildNum = nChildNum;
			temp.nModuleNum = nModuleNum;
			m_qVecPkgModifyInfo.push_back(temp);
		}
	}
	else
	{
		//
	}
}

bool UI_ProductEditor::GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal)
{
	qVecModifyVal = m_qVecPkgModifyInfo;
	return true;
}

bool UI_ProductEditor::insertModule(QVector<ST_MODULE>* cfgModuleInfo)
{
	int nLength = cfgModuleInfo->length();
	for (int i = 0; i < nLength; i++)
	{
		if (i == 0)
		{
			ST_MODULEITEM _ModuleItem;
			QTreeWidgetItem* _Moduleitem = new QTreeWidgetItem(ui.TRW_PkgParticularInfo, QStringList(cfgModuleInfo->at(i).ModuleName));
			_ModuleItem.ParentModuleItem = _Moduleitem;

			int ChildNum = cfgModuleInfo->at(i).m_nModuleLength();
			for (int j = 0; j < ChildNum; j++)
			{
				QTreeWidgetItem* ChildModule = new QTreeWidgetItem(_Moduleitem, QStringList(cfgModuleInfo->at(i).Value_.at(j).Function_name));
				ChildModule->setSizeHint(0, QSize(ROWWIDTH, ROWHEIGHT));
				QString strVal;
				if (cfgModuleInfo->at(i).Value_.at(j).Vel_Type == _INT)
					strVal = QString::number(cfgModuleInfo->at(i).Value_.at(j).Vel);
				else
					strVal = QString::number(cfgModuleInfo->at(i).Value_.at(j).Vel, 'g', 8);

				if (ENABLEEDIT == cfgModuleInfo->at(i).Value_.at(j).OtherAttribute)
					ui.TRW_PkgParticularInfo->openPersistentEditor(ChildModule, 1);
				//ChildModule->setFlags(ChildModule->flags() | Qt::ItemIsEditable);
				else
					ChildModule->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

				ChildModule->setData(1, Qt::DisplayRole, strVal);

				_ModuleItem.ChildModuleItems.push_back(ChildModule);
			}
			m_ModuleVector.push_back(_ModuleItem);
		}
		else if(i == 1)
		{
			//设置TRW_PkgParticularInfo，默认包含极耳间距
			QStringList qslStepItemName(QString::fromLocal8Bit("极耳间距"));
			m_qrwStepItem = new QTreeWidgetItem(ui.TRW_PkgParticularInfo, qslStepItemName);
			m_qrwStepItem->setSizeHint(0, QSize(ROWWIDTH, ROWHEIGHT));
			QFont _font(QString::fromLocal8Bit("微软雅黑"), 10);

			m_pAddStepButton->setText(QString::fromLocal8Bit("添加"));
			m_pAddStepButton->setMaximumSize(80, 25);
			m_pAddStepButton->setFont(_font);
			m_pAddStepButton->setIcon(QIcon(m_qstrIconFile + "/Image/LaserStepAdd.png"));
			m_pAddStepButton->setStyleSheet(
				"QPushButton{background: transparent;color: white; border-radius: 10px; border-style: outset;}"
				"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
				);
			ui.TRW_PkgParticularInfo->setItemWidget(m_qrwStepItem, 1, (QWidget*)m_pAddStepButton);
		}
	}
	return true;
}

bool UI_ProductEditor::AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo)
{
	return true;
}

void UI_ProductEditor::SkipCurrentPage()
{
	//获取当前产品
	QString qstrCfgPath = QCoreApplication::applicationDirPath();
	CString cstrCfgPath = qstrCfgPath.toStdWString().data();
	cstrCfgPath += _T("/Data/Machine.cfg");
	CString cstrPkgName = ReadStringFromFile(_T("Run"), _T("CurrentPackage"), _T("Demo"), cstrCfgPath);
	QString qstrPkgName = QString::fromStdWString(cstrPkgName.GetBuffer());
	cstrPkgName.ReleaseBuffer();
	//数据容器
	QVector<ST_CHANGE_POINT> qVecOnloadPkgInfo;
	QString qstrLaserFileName;

	m_pProductEditor->SwitchPackage(qVecOnloadPkgInfo, qstrLaserFileName, qstrPkgName);
	UpdataPackageInfo(qVecOnloadPkgInfo, qstrLaserFileName, qstrPkgName);
	m_qVecPkgModifyInfo.clear();
}

void UI_ProductEditor::UpdataPackageInfo(QVector<ST_CHANGE_POINT> qVecOnloadPkgInfo,  QString LaserFileName, QString strPkgName)
{
	int nLength = qVecOnloadPkgInfo.length();
	QStringList qslpkgStep;
	for (int i = 0; i < nLength; i++)
	{
		if (qVecOnloadPkgInfo.at(i).nModuleNum != 1) //非极耳间距
		{
			int ModuleNum = qVecOnloadPkgInfo.at(i).nModuleNum;
			int ChildNum = qVecOnloadPkgInfo.at(i).nChildNum;
			QString strVal = QString::number(qVecOnloadPkgInfo.at(i).dlData, 'g', 7);
			QTreeWidgetItem* setValItem = m_ModuleVector.at(ModuleNum).ChildModuleItems.at(ChildNum);
			setValItem->setText(1, strVal);
		}
		else //设置极耳间距
		{
			qslpkgStep.insert(qVecOnloadPkgInfo.at(i).nChildNum, QString::number(qVecOnloadPkgInfo.at(i).dlData, 'g', 6));
		}
	}
	QTreeWidgetItem* BaseItem = ui.TRW_PkgParticularInfo->topLevelItem(0);
	BaseItem->child(0)->setText(1, strPkgName);
	BaseItem->child(1)->setText(1, LaserFileName);	//激光文件名

	//设置极耳间距
	int nPreStepNum = m_qrwStepItem->childCount();
	int nCurStepNum = qslpkgStep.length();
	if (nPreStepNum > nCurStepNum) //之前产品间距个数大于当前间距个数
	{
		//设置当前间距个数及值
		for (int i = 0; i < nCurStepNum; i++)
		{
			QTreeWidgetItem* ModifyItem = m_qrwStepItem->child(i);
			ModifyItem->setText(1, qslpkgStep.at(i));
		}
		//删除多余间距(倒序button不需要再次修改ID)
		for (int j = nPreStepNum - 1; j >= nCurStepNum; j--)
		{
			QTreeWidgetItem* RemoveItem = m_qrwStepItem->child(j);
			m_qrwStepItem->removeChild(RemoveItem);
			QAbstractButton* DelButton = m_ButtonGroup.button(j);
			m_ButtonGroup.removeButton(DelButton);
			RemoveItem = NULL;
		}
	}
	else
	{
		//设置当前间距，修改之前已经拥有的Item
		for (int i = 0; i < nPreStepNum; i++)
		{
			QTreeWidgetItem* ModifyItem = m_qrwStepItem->child(i);
			ModifyItem->setText(1, qslpkgStep.at(i));
		}
		//添加不足的间距
		for (int j = nPreStepNum; j < nCurStepNum; j++)
		{
			int nCurStep = m_qrwStepItem->childCount(); //当前步数
			QString qstrStep = QString::number(nCurStep);
			QStringList qslStepInit;
			qslStepInit << qstrStep << qslpkgStep.at(j) << QString::fromLocal8Bit("");
			QTreeWidgetItem* StepItem = new QTreeWidgetItem(m_qrwStepItem, qslStepInit);
			StepItem->setFlags(StepItem->flags() | Qt::ItemIsEditable);

			QFont _font(QString::fromLocal8Bit("微软雅黑"), 10);
			QPushButton* _DelStep = new QPushButton;
			_DelStep->setText(QString::fromLocal8Bit("删除"));
			_DelStep->setMaximumSize(80, 25);
			_DelStep->setFont(_font);
			_DelStep->setStyleSheet(
				"QPushButton{background: transparent;color: white; border-radius: 10px; border-style: outset;}"
				"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
				);
			m_ButtonGroup.addButton(_DelStep, nCurStep);
			ui.TRW_PkgParticularInfo->setItemWidget(StepItem, 2, (QWidget*)_DelStep);
		}
	}
}

void UI_ProductEditor::AddNewPackage(QString& strNewPkgName)
{
	int nLaserStepNum = m_qrwStepItem->childCount();
	for (int i = 0; i < nLaserStepNum; i++)
	{
		m_qVecLaserStepDist.push_back(m_qrwStepItem->child(i)->text(1).toDouble());
	}
	QTreeWidgetItem* PkgNameItem = ui.TRW_PkgParticularInfo->topLevelItem(0);
	QString qstrPkgName = PkgNameItem->child(0)->text(1);
	QString qstrLaserName = PkgNameItem->child(1)->text(1);
	if (m_pProductEditor->NewPackage(m_qVecPkgModifyInfo, m_qVecLaserStepDist, qstrPkgName, qstrLaserName))
		strNewPkgName = qstrPkgName;
}
