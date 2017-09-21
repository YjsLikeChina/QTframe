#include "UI_ProductEditor.h"
#include <QFileDialog>
#include "UI_MessageBox.h"
#include <QCheckBox>

#define ROWWIDTH	280
#define ROWHEIGHT	35

UI_ProductEditor::UI_ProductEditor(QWidget* parent /*= Q_NULLPTR*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
	:QWidget(parent),UI_InterfaceBase(parent)
{
	ui.setupUi(this);
	initVal();
	initUI();
	initConnect();
	GetPackageList();
}

UI_ProductEditor::~UI_ProductEditor()
{
	delete m_pAddStepButton;
	delete m_qrwStepItem;
	delete m_pSimpledialog;
	delete m_pCtrlProductEditor;
}

void UI_ProductEditor::initVal()
{
	m_qstrIconFile = QCoreApplication::applicationDirPath();
	m_pAddStepButton = new QPushButton;
	m_qrwStepItem = new QTreeWidgetItem;
	m_qrwStepItem = Q_NULLPTR;
	m_pCtrlProductEditor = new CTRL_ProductEditor;
	m_bAddStepLock = false;

	m_qstrLaserFilePath = QCoreApplication::applicationDirPath() + QString::fromLocal8Bit("/LaserFiles/");

	m_qstrPkgFilePath = m_qstrIconFile + QString::fromLocal8Bit("/Data/Package/");

	QString strPath = QString::fromLocal8Bit("/System/FilmTrimmer.cfg");
	m_cstrCfgPath = m_qstrIconFile.toStdWString().data();
	m_cstrCfgPath += strPath.toStdWString().data();
	m_pSimpledialog = new UI_Simpledialog;
	m_qIconCurPkgIndicate.addFile(m_qstrIconFile + QString::fromLocal8Bit("/Image/CurrentPackageIndicate.png"));
	m_qIconLastPkgIndicate.addFile(m_qstrIconFile + QString::fromLocal8Bit("/Image/CurrentPackageIndicateNULL.png"));
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
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = m_qstrIconFile + "/Image/PackageNew.png";
	ui.PB_Package_New->setIcon(QIcon(qstrIconPath));
	ui.PB_Package_New->setIconSize(QSize(35, 25));
	ui.PB_Package_New->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = m_qstrIconFile + "/Image/PackageDelete.png";
	ui.PB_Package_Delete->setIcon(QIcon(qstrIconPath));
	ui.PB_Package_Delete->setIconSize(QSize(35, 25));
	ui.PB_Package_Delete->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = m_qstrIconFile + "/Image/PackageCopy.png";
	ui.PB_Package_Copy->setIcon(QIcon(qstrIconPath));
	ui.PB_Package_Copy->setIconSize(QSize(35, 25));
	ui.PB_Package_Copy->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = m_qstrIconFile + "/Image/Save.png";
	ui.PB_Package_Save->setIcon(QIcon(qstrIconPath));
	ui.PB_Package_Save->setIconSize(QSize(35, 25));
	ui.PB_Package_Save->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white;border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	//设置控件宽度
	ui.TRW_PkgParticularInfo->setColumnWidth(0, 180);
	ui.TRW_PkgParticularInfo->setColumnWidth(1, 230);
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
	connect(ui.TRW_PkgParticularInfo, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(SlotBoolItemClick(QTreeWidgetItem*, int)));
	connect(ui.LW_PackageList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SlotSwitchPackage(QListWidgetItem*)));

}

void UI_ProductEditor::GetPackageList()
{
	if (!CFGINTERFACE.JudgeDirIsExist(m_qstrPkgFilePath))
	{
		MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("产品文件路径不存在"),DOMODEL,0);
		return;
	}
	int nCurPkgItem = 0;
	CString strCurPkgName = ReadStringFromFile(_T("Run"), _T("当前产品文件名"), _T("Demo"), m_cstrCfgPath);
	m_qstrCurPkgName = QString::fromStdWString(strCurPkgName.GetBuffer());
	strCurPkgName.ReleaseBuffer();
	//获取产品名称
	QDir PkgFileDir(m_qstrPkgFilePath);
	PkgFileDir.setNameFilters(QStringList("*.pkg"));
	QStringList qslPkgName = PkgFileDir.entryList();
	int nLength = qslPkgName.length();
	for (int i = 0; i < nLength; i++)
	{
		QString qstrName = qslPkgName.at(i).left(qslPkgName.at(i).length() - 4); //去掉.pkg
		QListWidgetItem* addItem = new QListWidgetItem(qstrName);
		if (m_qstrCurPkgName == qstrName)//获取当前产品位置与Item
		{
			nCurPkgItem = i;
			m_pCurrentSelPkgItem = addItem; //当前选中的Item
			m_pCurPkgItem = addItem;		//当前产品的Item
			addItem->setSizeHint(QSize(300, 35));
			addItem->setIcon(m_qIconCurPkgIndicate);
			ui.LW_PackageList->addItem(addItem);
			continue;
		}
		else
		{
			addItem->setSizeHint(QSize(300, 35));
			addItem->setIcon(m_qIconLastPkgIndicate);
			ui.LW_PackageList->addItem(addItem);
		}
		
	}
	ui.LW_PackageList->setIconSize(QSize(30,30));
	ui.LW_PackageList->setCurrentRow(nCurPkgItem);
}

void UI_ProductEditor::SlotSetCurrentPackage()
{
	QString qstrCurPkgName = m_pCurrentSelPkgItem->text();
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:点击设为当前产品，产品为%2").arg(__func__).arg(qstrCurPkgName));
	if (m_pCtrlProductEditor->ChangeCurproduct(qstrCurPkgName))
	{
		m_qstrCurPkgName = qstrCurPkgName;
		CString strPkgName = m_qstrCurPkgName.toStdWString().data();
	
		WriteStringToFile(_T("Run"), _T("当前产品文件名"), strPkgName, m_cstrCfgPath);
		WriteStringToFile(_T("Run"), _T("当前激光文件名"), MACHINECTRL.m_pMachineStatusCtrl->GetCurLaserData().strLaserFileName, m_cstrCfgPath);
		m_pCurPkgItem->setIcon(m_qIconLastPkgIndicate);
		m_pCurPkgItem = m_pCurrentSelPkgItem;
		m_pCurPkgItem->setIcon(m_qIconCurPkgIndicate); //设置当前产品图标
	}
}

void UI_ProductEditor::SlotCopyPackage()
{
	QString qstrCopyPkgName = m_pCurrentSelPkgItem->text();
	QString qstrNewCopyPkgName;
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:点击复制产品，被复制产品为%2").arg(__func__).arg(qstrCopyPkgName));
	if (m_pCtrlProductEditor->CopyPackage(qstrCopyPkgName, qstrNewCopyPkgName))
	{
		QListWidgetItem* addItem = new QListWidgetItem(qstrNewCopyPkgName);
		addItem->setSizeHint(QSize(300, 35));
		addItem->setIcon(m_qIconLastPkgIndicate);
		ui.LW_PackageList->addItem(addItem);
	}
}

void UI_ProductEditor::SlotDeletePackage()
{
	QString qstrDelPkgName = m_pCurrentSelPkgItem->text();
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:点击删除产品，产品名为%2").arg(__func__).arg(qstrDelPkgName));
	if (m_pCtrlProductEditor->DeletePackage(qstrDelPkgName))
	{
		int CurRow = ui.LW_PackageList->currentRow();
		QListWidgetItem* RemoveItem = ui.LW_PackageList->takeItem(CurRow);
		m_pCurrentSelPkgItem = m_pCurPkgItem;
		delete RemoveItem;
		RemoveItem = NULL;
		ui.LW_PackageList->setCurrentItem(m_pCurrentSelPkgItem);
	}
}

void UI_ProductEditor::SlotNewPackage()
{
	QString qstrNewPkgName;
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:点击新建产品").arg(__func__));
	AddNewPackage(qstrNewPkgName);
	QListWidgetItem* _NewItem = new QListWidgetItem(qstrNewPkgName);
	_NewItem->setSizeHint(QSize(300, 35));
	ui.LW_PackageList->addItem(_NewItem);
}

void UI_ProductEditor::SlotSavePackage()
{
	int nLength = m_qrwStepItem->childCount();
	QVector<double> qVecStepDist;
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:点击保存产品").arg(__func__));
	for (int i = 0; i < nLength; i++)
	{
		qVecStepDist.push_back(m_qrwStepItem->child(i)->text(1).toDouble());
	}
	QString qstrOldPkgName = m_pCurrentSelPkgItem->text();
	QTreeWidgetItem* PkgDefaultItem = ui.TRW_PkgParticularInfo->topLevelItem(0);//获取产品默认模组

	UI_LineEdit* PkgNameEdit = (UI_LineEdit*)ui.TRW_PkgParticularInfo->itemWidget(PkgDefaultItem->child(PACKAGE_NAME),1); //产品名称
	QString qstrNewPkgName = PkgNameEdit->text();

	UI_LineEdit* LaserNameEdit = (UI_LineEdit*)ui.TRW_PkgParticularInfo->itemWidget(PkgDefaultItem->child(PACKAGE_LASERNAME), 1); //产品名称
	QString qstrLaserName = LaserNameEdit->text();
	QStringList qslPkgName;
	qslPkgName << qstrNewPkgName << qstrOldPkgName;
	//将产品文件名称、激光文件名称的Item项放入容器中
	ST_CHANGE_POINT stSupplData;
	stSupplData.dlData = -1;
	stSupplData.nChildNum = PACKAGE_NAME;
	stSupplData.nModuleNum = 0;
	m_qVecPkgModifyInfo.push_back(stSupplData);
	stSupplData.dlData = -1;
	stSupplData.nChildNum = PACKAGE_LASERNAME;
	stSupplData.nModuleNum = 0;
	m_qVecPkgModifyInfo.push_back(stSupplData);
	
	if (m_pCtrlProductEditor->SaveProducteData(m_qVecPkgModifyInfo, qVecStepDist, qslPkgName, qstrLaserName))
	{
		if(qstrNewPkgName != qstrOldPkgName)
			m_pCurrentSelPkgItem->setText(qstrNewPkgName); //保存成功时，将列表中的产品名称替换成新修改的名字
	}
}

void UI_ProductEditor::SlotAddPackageStep()
{
	if (m_bAddStepLock)
		return;
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:点击新增极耳间距").arg(__func__));
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
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:切换产品,要切换产品名:%1").arg(__func__).arg(qstrPkgName));
	m_pCtrlProductEditor->SwitchPackage(qVecOnloadPkgInfo, qstrLaserFileName, qstrPkgName);
	UpdataPackageInfo(qVecOnloadPkgInfo, qstrLaserFileName, qstrPkgName);
	m_qVecPkgModifyInfo.clear();
}

void UI_ProductEditor::SlotDeleteStep(int nButton)
{
	int nDelRow = nButton;
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:点击删除极耳间距，删除编号为%2").arg(__func__).arg(nDelRow));
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

void UI_ProductEditor::SlotBoolItemClick(QTreeWidgetItem* item, int nColumn)
{
	QTreeWidgetItem* CurItemParent = item->parent();
	if (NULL == CurItemParent || nColumn != 1)
		return;
	int nModuleNum = ui.TRW_PkgParticularInfo->indexOfTopLevelItem(CurItemParent);
	int nChildNum = CurItemParent->indexOfChild(item);

	ST_CHANGE_POINT temp;
	temp.dlData = item->checkState(1);
	temp.nChildNum = nChildNum;
	temp.nModuleNum = nModuleNum;
	m_qVecPkgModifyInfo.push_back(temp);
	if (PACKAGE_STRAT_LINE == nChildNum)
	{
		if (Qt::Unchecked == temp.dlData)
		{
			m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_RISE_TRIGGER)->setFlags(Qt::NoItemFlags);
			m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_FALL_TRIGGER)->setFlags(Qt::NoItemFlags);
		}
		else
		{
			Qt::ItemFlags _DefultFlag = item->flags();
			m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_RISE_TRIGGER)->setFlags(_DefultFlag);
			m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_FALL_TRIGGER)->setFlags(_DefultFlag);
		}
	}
	else if (PACKAGE_FALL_TRIGGER == temp.nChildNum)
	{
		if (temp.dlData < 0.1) // == 0
		{
			m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_RISE_TRIGGER)->setCheckState(1, Qt::Checked);
			temp.dlData = Qt::Checked;
		}
		else
		{
			m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_RISE_TRIGGER)->setCheckState(1, Qt::Unchecked);
			temp.dlData = Qt::Unchecked;
		}
		temp.nChildNum = PACKAGE_RISE_TRIGGER;
		temp.nModuleNum = nModuleNum;
		m_qVecPkgModifyInfo.push_back(temp);
	}
	else
	{
		if (temp.dlData < 0.1) // == 0
		{
			m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_FALL_TRIGGER)->setCheckState(1, Qt::Checked);
			temp.dlData = Qt::Checked;
		}
		else
		{
			m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_FALL_TRIGGER)->setCheckState(1, Qt::Unchecked);
			temp.dlData = Qt::Unchecked;
		}
		temp.nChildNum = PACKAGE_FALL_TRIGGER;
		temp.nModuleNum = nModuleNum;
		m_qVecPkgModifyInfo.push_back(temp);
	}
}

void UI_ProductEditor::SlotLaserFileSel()
{
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:点击选择激光文件").arg(__func__));
	//if (item->text(0) == QString::fromLocal8Bit("激光文件") && 1 == nColumn)
	{
		if (!CFGINTERFACE.JudgeDirIsExist(m_qstrLaserFilePath))
		{
			MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("激光文件夹不存在!"), DOMODEL, 0);
			return;
		}
		QString qstrLaserFileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("激光文件选择"), m_qstrLaserFilePath, tr("*.hms"));//文件对话框
		if (qstrLaserFileName.isEmpty())
			return;
		qstrLaserFileName = qstrLaserFileName.section('/', -1); //截取最后一个‘/’后的字符串
		qstrLaserFileName = qstrLaserFileName.left(qstrLaserFileName.length() - 4);
		m_pLaserLineEdit->setText(qstrLaserFileName);
		//占位符，保存时使用，修改激光文件名称
		ST_CHANGE_POINT temp;
		temp.dlData = -1;
		temp.nChildNum = 1;
		temp.nModuleNum = 0;
		m_qVecPkgModifyInfo.push_back(temp);
	}
}


void UI_ProductEditor::SlotItemChanged()
{
	UI_LineEdit* ChangeItem = (UI_LineEdit*)QObject::sender();
	if (ChangeItem->text() == QString::fromLocal8Bit("产品名称"))
	{
		LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:修改产品名称").arg(__func__));
		return;
	}
		
	ST_CHANGE_POINT temp;
	temp.dlData = ChangeItem->text().toDouble();
	temp.nChildNum = ChangeItem->nChildNum;
	temp.nModuleNum = ChangeItem->nModuleNum;
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:修改%2o数据,修改为%3").arg(__func__).arg(ChangeItem->text()).arg(temp.dlData));
	m_qVecPkgModifyInfo.push_back(temp);
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
				//QString strVal;
				//if (cfgModuleInfo->at(i).Value_.at(j).Vel_Type == _INT)
				//	strVal = QString::number(cfgModuleInfo->at(i).Value_.at(j).Vel);
				//else
				//	strVal = QString::number(cfgModuleInfo->at(i).Value_.at(j).Vel, 'g', 8);

				if (ENABLEEDIT == cfgModuleInfo->at(i).Value_.at(j).OtherAttribute) //可编辑
				{
					UI_LineEdit* UserLineEdit = new UI_LineEdit(i, j, this);
					if (cfgModuleInfo->at(i).Value_.at(j).Function_name == QString::fromLocal8Bit("产品名称"))
					{
						QFont font(QString::fromLocal8Bit("微软雅黑"), 10);
						QRegExp regx("^(?![\\p{P}\\p{S}])[\u4e00-\u9fa5,A-Z,a-z,0-9,-]+$"); //限定除中文、字母A-Z、字母a-z、以及-之外的其他字符
						UserLineEdit->SetStyleSheet(font, regx);
						UserLineEdit->setMinimumSize(QSize(150,28));
					}
					ui.TRW_PkgParticularInfo->setItemWidget(ChildModule, 1, UserLineEdit);
					connect(UserLineEdit, SIGNAL(editingFinished()), this, SLOT(SlotItemChanged()));
				}
				else if (DISABLEEDIT == cfgModuleInfo->at(i).Value_.at(j).OtherAttribute) //不可编辑
				{
					if (cfgModuleInfo->at(i).Value_.at(j).Function_name == QString::fromLocal8Bit("激光文件"))
					{
						m_qrwLaserItem = ChildModule;
						m_pLaserLineEdit = new UI_LineEdit(i, j, this);
						QFont font(QString::fromLocal8Bit("微软雅黑"), 10);
						QRegExp regx("^(?![\\p{P}\\p{S}])[\u4e00-\u9fa5,A-Z,a-z,0-9,-]+$"); //限定除中文、字母A-Z、字母a-z、以及-之外的其他字符
						m_pLaserLineEdit->SetStyleSheet(font, regx);
						m_pLaserLineEdit->setReadOnly(true);
						ui.TRW_PkgParticularInfo->setItemWidget(ChildModule, 1, m_pLaserLineEdit);

						QFont _font(QString::fromLocal8Bit("微软雅黑"), 10);
						QPushButton* _PushButton = new QPushButton;
						_PushButton->setText(QString::fromLocal8Bit("激光文件选择"));
						_PushButton->setMaximumSize(100, 25);
						_PushButton->setFont(_font);
						_PushButton->setIcon(QIcon(m_qstrIconFile + "/Image/LaserFileSel.png"));
						_PushButton->setStyleSheet(
							"QPushButton{background: transparent;color: white; border-radius: 10px; border-style: outset;}"
							"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
							);
						ui.TRW_PkgParticularInfo->setItemWidget(m_qrwLaserItem, 2, (QWidget*)_PushButton);
						connect(_PushButton, SIGNAL(clicked()), this, SLOT(SlotLaserFileSel()));
					}
					else if (_BOOL == cfgModuleInfo->at(i).Value_.at(j).Vel_Type) //勾选框
					{
						ChildModule->setCheckState(1, Qt::Unchecked);
					}
					else
					{
						UI_LineEdit* UserLineEdit = new UI_LineEdit(i, j, this);
						QFont font(QString::fromLocal8Bit("微软雅黑"), 10);
						QRegExp regx("^(?![\\p{P}\\p{S}])[\u4e00-\u9fa5,A-Z,a-z,0-9,-]+$"); //限定除中文、字母A-Z、字母a-z、以及-之外的其他字符
						UserLineEdit->SetStyleSheet(font, regx);
						UserLineEdit->setReadOnly(true);
						ui.TRW_PkgParticularInfo->setItemWidget(ChildModule, 1, UserLineEdit);
					}
				}
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
	//主页面快捷设置激光参数，添加模块后，需要导入界面数据
	m_ModuleVector.at(0).ParentModuleItem->setExpanded(true);
	m_qrwStepItem->setExpanded(true);
	SkipCurrentPage();
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
	cstrCfgPath += _T("/System/FilmTrimmer.cfg");
	CString cstrPkgName = ReadStringFromFile(_T("Run"), _T("当前产品文件名"), _T("Demo"), cstrCfgPath);
	QString qstrPkgName = QString::fromStdWString(cstrPkgName.GetBuffer());
	cstrPkgName.ReleaseBuffer();
	//数据容器
	QVector<ST_CHANGE_POINT> qVecOnloadPkgInfo;
	QString qstrLaserFileName;

	m_pCtrlProductEditor->SwitchPackage(qVecOnloadPkgInfo, qstrLaserFileName, qstrPkgName);
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
			QTreeWidgetItem* setValItem = m_ModuleVector.at(ModuleNum).ChildModuleItems.at(ChildNum);

			QObject* childItem = ui.TRW_PkgParticularInfo->itemWidget(setValItem, 1);
			//写入Edit
			if(NULL != childItem) 
			{
				QString strVal = QString::number(qVecOnloadPkgInfo.at(i).dlData, 'g', 7);
				UI_LineEdit* _LineEdit = (UI_LineEdit*)childItem;
				_LineEdit->setText(strVal);
				continue;
			}
			//设置CheckBox
			if (0.1 < qVecOnloadPkgInfo.at(i).dlData) //!=0
				setValItem->setCheckState(1, Qt::Checked);
			else
				setValItem->setCheckState(1, Qt::Unchecked);
			if (m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_STRAT_LINE)->checkState(1) == Qt::Checked)
			{
				Qt::ItemFlags _DefultFlag = m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_STRAT_LINE)->flags();
				m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_RISE_TRIGGER)->setFlags(_DefultFlag);
				m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_FALL_TRIGGER)->setFlags(_DefultFlag);
			}
			else
			{
				m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_RISE_TRIGGER)->setFlags(Qt::NoItemFlags);
				m_ModuleVector.at(0).ChildModuleItems.at(PACKAGE_FALL_TRIGGER)->setFlags(Qt::NoItemFlags);
			}
		}
		else //设置极耳间距
		{
			qslpkgStep.insert(qVecOnloadPkgInfo.at(i).nChildNum, QString::number(qVecOnloadPkgInfo.at(i).dlData, 'g', 6));
		}
	}
	QTreeWidgetItem* BaseItem = ui.TRW_PkgParticularInfo->topLevelItem(0);
	UI_LineEdit* _LineEdit = (UI_LineEdit*)ui.TRW_PkgParticularInfo->itemWidget(BaseItem->child(0), 1); //获取产品名的Item
	if (NULL != _LineEdit)
		_LineEdit->setText(strPkgName);	//设置产品名称
	m_pLaserLineEdit->setText(LaserFileName);

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
	if (m_pCtrlProductEditor->NewPackage(m_qVecPkgModifyInfo, m_qVecLaserStepDist, qstrPkgName, qstrLaserName))
		strNewPkgName = qstrPkgName;
}

void UI_ProductEditor::SetLaserData(int nCard)
{
	QStringList qslHeadInfo;
	if (nCard)
		qslHeadInfo << QString::fromLocal8Bit("激光2功率") << QString::fromLocal8Bit("激光2频率");
	else
		qslHeadInfo << QString::fromLocal8Bit("激光1功率") << QString::fromLocal8Bit("激光1频率");
	QVector<ST_CHANGE_POINT> qVecChangData;
	m_pSimpledialog->SetShow(qslHeadInfo, qVecChangData);

	if (qVecChangData.isEmpty())
		return;
	if (m_pCtrlProductEditor->SetLaserData(nCard, qVecChangData.at(0).dlData, qVecChangData.at(1).dlData))
	{
		m_qVecPkgModifyInfo.clear();
		if (0 == nCard)
		{
			ST_CHANGE_POINT temp;
			temp.dlData = qVecChangData.at(0).dlData;
			temp.nChildNum = PACKAGE_LASER1_POWER;
			temp.nModuleNum = 0;
			m_qVecPkgModifyInfo.push_back(temp);

			temp.dlData = qVecChangData.at(1).dlData;
			temp.nChildNum = PACKAGE_LASER1_FREQ;
			temp.nModuleNum = 0;
			m_qVecPkgModifyInfo.push_back(temp);
		}
	}
	else
	{
		ST_CHANGE_POINT temp;
		temp.dlData = qVecChangData.at(0).dlData;
		temp.nChildNum = PACKAGE_LASER2_POWER;
		temp.nModuleNum = 0;
		m_qVecPkgModifyInfo.push_back(temp);

		temp.dlData = qVecChangData.at(1).dlData;
		temp.nChildNum = PACKAGE_LASER2_FREQ;
		temp.nModuleNum = 0;
		m_qVecPkgModifyInfo.push_back(temp);
	}

	SlotSavePackage();
}

bool UI_ProductEditor::SaveParamer()
{
	SlotSavePackage();
	m_qVecPkgModifyInfo.clear();
	return true;
}
