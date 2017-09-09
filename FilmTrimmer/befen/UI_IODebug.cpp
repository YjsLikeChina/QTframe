#include "UI_IODebug.h"
#define ROWWIDTH	311
#define ROWHEIGHT	40

UI_IODebug::UI_IODebug(QWidget* parent /*= Q_NULLPTR*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
	:QWidget(parent),UI_InterfaceBase(parent)
{
	ui.setupUi(this);
	initVal();
	initUI();
	initConnect();
}

UI_IODebug::~UI_IODebug()
{
	delete m_qvecModuleInfo;
}

void UI_IODebug::initConnect()
{
	connect(ui.LW_ModuleList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SlotSwitchModule(QListWidgetItem*)));
	connect(ui.LW_OutputList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SlotOutputClicked(QListWidgetItem*)));
}

void UI_IODebug::initUI()
{
	QString qstrIconFile = QCoreApplication::applicationDirPath();
	QString qstrIconPath = qstrIconFile + "/Image/Diaphaneity2.png";
	ui.LB_Background1->setPixmap(QPixmap(qstrIconPath));
	ui.LB_Background1->setStyleSheet("background:transparent;");
}

void UI_IODebug::initVal()
{
	m_qstrStatusOn = QCoreApplication::applicationDirPath() + QString::fromLocal8Bit("/Image/");
	m_qstrStatusOff = m_qstrStatusOn;
	m_qstrStatusOn += QString::fromLocal8Bit("Enable.png");
	m_qstrStatusOff += QString::fromLocal8Bit("NoEnable.png");
	m_OnStatuIcon.addFile(m_qstrStatusOn);
	m_OffStatuIcon.addFile(m_qstrStatusOff);
	m_bAutoUpdateLock = false;
	m_CurrentModule = 0;
	m_PCtrlIODebug = new CTRL_IODebug;
	m_PCtrlIODebug->SetUIInterface(this);
}

bool UI_IODebug::insertModule(QVector<ST_MODULE>* pQVector)
{
	int nParentLength = pQVector->length(); //模组个数
	m_qvecModuleInfo = new QVector<ST_MODULE>;
	*m_qvecModuleInfo = *pQVector;
	for (int i = 0; i < nParentLength; i++)
	{
		//添加模组
		QListWidgetItem* pListWidgetItem = new QListWidgetItem(pQVector->at(i).ModuleName);
		pListWidgetItem->setSizeHint(QSize(ROWWIDTH, ROWHEIGHT));
		ui.LW_ModuleList->addItem(pListWidgetItem);
		//添加输入输出项
		int nChildNum = pQVector->at(i).m_nModuleLength();
		if (i == 0) //显示第一个模组信息
		{
			for (int j = 0; j < nChildNum; j++)
			{
				QListWidgetItem* qListWidgetItem;
				if (INPUT_ == pQVector->at(i).Value_.at(j).OtherAttribute) //输入点
				{
					qListWidgetItem = new QListWidgetItem(m_OffStatuIcon, pQVector->at(i).Value_.at(j).Function_name);
					qListWidgetItem->setSizeHint(QSize(ROWWIDTH, ROWHEIGHT));
					ui.LW_InputList->addItem(qListWidgetItem);
				}
				else
				{
					qListWidgetItem = new QListWidgetItem(m_OffStatuIcon, pQVector->at(i).Value_.at(j).Function_name);
					qListWidgetItem->setSizeHint(QSize(ROWWIDTH, ROWHEIGHT));
					ui.LW_OutputList->addItem(qListWidgetItem);
				}
			}
		}
	}
	return true;
}

bool UI_IODebug::AutoUpdateData(QList<ST_UPDATEDATA> InputStatuslist)
{
	if (m_bAutoUpdateLock)
		return false;
	m_bAutoUpdateLock = true;
	//只更新Input点
	int nLenght = InputStatuslist.length();
	for (int i = 0; i < nLenght; i++)
	{
		if (0 == InputStatuslist.at(i).dlData)
		{
			ui.LW_InputList->item(i)->setIcon(m_OffStatuIcon);
		}
		else
		{
			ui.LW_InputList->item(i)->setIcon(m_OnStatuIcon);
		}
	}
	m_bAutoUpdateLock = false;
	return true;
}

void UI_IODebug::SkipCurrentPage()
{
	ui.LW_ModuleList->setCurrentRow(0);
	SlotSwitchModule(ui.LW_ModuleList->item(0));
	m_PCtrlIODebug->ChangeMoudle(0);
}

bool UI_IODebug::GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal)
{
	return false;
}

void UI_IODebug::SlotOutputClicked(QListWidgetItem *item)
{
	int nButtonNum = ui.LW_OutputList->currentRow();
 	bool bRes = m_PCtrlIODebug->ButtonClickedChanged(m_CurrentModule, nButtonNum);
	if (bRes)
	{
		item->setIcon(m_OnStatuIcon);
	}
	else
	{
		item->setIcon(m_OffStatuIcon);
	}
	//emit SigOutputClicked(ui.LW_ModuleList->currentRow(), nButtonNum);
}

void UI_IODebug::SlotSwitchModule(QListWidgetItem *item)
{
	int nModuleNum = ui.LW_ModuleList->currentRow();
	if (m_CurrentModule == nModuleNum)
		return;
	m_CurrentModule = nModuleNum;
	//修改UI
	ui.LW_InputList->clear();
	ui.LW_OutputList->clear();
	int nLength = m_qvecModuleInfo->at(nModuleNum).m_nModuleLength();
	for (int i = 0; i < nLength; i++)
	{
		QListWidgetItem* qListWidgetItem;
		if (INPUT_ == m_qvecModuleInfo->at(m_CurrentModule).Value_.at(i).OtherAttribute) //输入点
		{
			qListWidgetItem = new QListWidgetItem(m_OffStatuIcon, m_qvecModuleInfo->at(m_CurrentModule).Value_.at(i).Function_name);
			qListWidgetItem->setSizeHint(QSize(ROWWIDTH, ROWHEIGHT));
			ui.LW_InputList->addItem(qListWidgetItem);
		}
		else
		{
			qListWidgetItem = new QListWidgetItem(m_OffStatuIcon, m_qvecModuleInfo->at(m_CurrentModule).Value_.at(i).Function_name);
			qListWidgetItem->setSizeHint(QSize(ROWWIDTH, ROWHEIGHT));
			ui.LW_OutputList->addItem(qListWidgetItem);
		}
	}
	//emit SigModuleSwitch(nModuleNum);
	QString qstrOutputStatus = m_PCtrlIODebug->ChangeMoudle(nModuleNum);
	nLength = qstrOutputStatus.length();
	for (int i = 0; i < nLength; i++)
	{
		if (qstrOutputStatus.at(i) == '1')
		{
			ui.LW_OutputList->item(i)->setIcon(m_OnStatuIcon);
		}
		else
		{
			ui.LW_OutputList->item(i)->setIcon(m_OffStatuIcon);
		}
	}
}
