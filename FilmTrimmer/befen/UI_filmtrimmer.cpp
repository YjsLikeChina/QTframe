#include "UI_filmtrimmer.h"
#include "BaseDataType.h"
#include <QPushButton>
#include <QDir>
#include "OP_MachineSoftWareMain.h"
#include <QDateTime>
#include "QDebug"
UI_FilmTrimmer::UI_FilmTrimmer(QMainWindow* parentWin /*= 0*/)
	:QMainWindow(parentWin),UI_InterfaceBase(parentWin)
{
	
	ui.setupUi(this);
	setStyleSheet("background-image: url(:/FilmTrimmer/Image/Background.png)");
	setWindowFlags(Qt::FramelessWindowHint);
	initVal();
	initUI();
	
	GetPageConfigInfo();
	//��Controller
	m_pCtrlFilmTrimmer = new CTRL_FilmTrimmer;
	m_pCtrlFilmTrimmer->SetUIInterface(this);
	m_pUserTimer = new QTimer;
	m_pUserTimer->start(60000);
	m_pSystemTimeTimer = new QTimer;
	m_pSystemTimeTimer->start(1000);

	initConnect();


	tempLOG->WriteLogQstring(CLog::LL_WARN, "wolail1e");
}

UI_FilmTrimmer::~UI_FilmTrimmer()
{
	delete m_pButtonGruop;
	delete m_pAutoProduction;
	delete m_pIODebug;
	delete m_pMotorDebug;
	delete m_pParameterSetting;
	delete m_pProductEditor;
	delete m_pHistoricalInformation;
}

void UI_FilmTrimmer::initVal()
{
	m_pButtonGruop = new QButtonGroup;
	m_nCurPageItem = 1;
	m_nAlarmCurPoint = 0;
	m_nRunDirection = 0;
	int m_nOnloadDirection = 0;

	//ҳ��
	m_pAutoProduction = new UI_AutoProduction;
	m_qMapWidgetInfo.insert(AUTOMATICPRODUCT, m_pAutoProduction);
	m_pIODebug = new UI_IODebug;
	m_qMapWidgetInfo.insert(IODEBUG, m_pIODebug);
	m_pMotorDebug = new UI_MotorDebug;
	m_qMapWidgetInfo.insert(MOTORDEBUG, m_pMotorDebug);
	m_pParameterSetting = new UI_ParameterSetting;
	m_qMapWidgetInfo.insert(PARAMETERSET, m_pParameterSetting);
	m_pProductEditor = new UI_ProductEditor;
	m_qMapWidgetInfo.insert(PRODUCTEDITOR, m_pProductEditor);
	m_pHistoricalInformation = new UI_HistoricalInformation;
	m_qMapWidgetInfo.insert(HISTORICALINFO, m_pHistoricalInformation);
}

void UI_FilmTrimmer::initUI()
{
	setWindowFlags(Qt::FramelessWindowHint);

	//�豸ά��
	QPushButton* pMaintenanceButton = new QPushButton;
	pMaintenanceButton->setText(QString::fromLocal8Bit("�豸ά��"));
	QFont qfont(QString::fromLocal8Bit("΢���ź�"), 11);
	pMaintenanceButton->setFont(qfont);
	pMaintenanceButton->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);
	pMaintenanceButton->setMinimumHeight(45);
	m_pButtonGruop->addButton(pMaintenanceButton, MAINTENANCE);
	ui.HL_PageButtonLayout->insertWidget(MAINTENANCE, pMaintenanceButton);
	//�˳�
	QPushButton* pExitButton = new QPushButton;
	pExitButton->setText(QString::fromLocal8Bit("�˳�"));
	pExitButton->setFont(qfont);
	pExitButton->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);
	pExitButton->setMinimumHeight(45);
	m_pButtonGruop->addButton(pExitButton, EXIT);
	ui.HL_PageButtonLayout->insertWidget(EXIT, pExitButton);

	//UIͼ�걳������
	QString qstrIconFile = QCoreApplication::applicationDirPath();
	
	QString qstrIconPath = qstrIconFile + "/Image/Alarm_Error.png";
	ui.LB_AlarmOrError_Show->setScaledContents(true);
	ui.LB_AlarmOrError_Show->setPixmap(QPixmap(qstrIconPath));
	ui.LB_AlarmOrError_Show->setStyleSheet("background:transparent;");

	qstrIconPath = qstrIconFile + "/Image/LeftPic.png";
	ui.LB_Show1->setScaledContents(true);
	ui.LB_Show1->setPixmap(QPixmap(qstrIconPath));
	ui.LB_Show1->setStyleSheet("background: transparent;");

	qstrIconPath = qstrIconFile + "/Image/RightPic.png";
	ui.LB_Show2->setScaledContents(true);
	ui.LB_Show2->setPixmap(QPixmap(qstrIconPath));
	ui.LB_Show2->setStyleSheet("background: transparent");

	qstrIconPath = qstrIconFile + "/Image/Diaphaneity2.png";
	ui.LB_Show3->setScaledContents(true);
	ui.LB_Show3->setPixmap(QPixmap(qstrIconPath));

	qstrIconPath = qstrIconFile + "/Image/ClickedStute.png";
	ui.LB_Sel_Background->setScaledContents(true);
	ui.LB_Sel_Background->setPixmap(QPixmap(qstrIconPath));
	ui.LB_Sel_Background->setStyleSheet(
		"border-radius: 10px;}"
		);

	qstrIconPath = qstrIconFile + "/Image/EStopIcon.png";
	ui.PB_MachineEStop->setIcon(QIcon(qstrIconPath));
	ui.PB_MachineEStop->setIconSize(QSize(30, 30));
	ui.PB_MachineEStop->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/ResetPicture.png";
	ui.PB_MachineReset->setIcon(QIcon(qstrIconPath));
	ui.PB_MachineReset->setIconSize(QSize(30, 30));
	ui.PB_MachineReset->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/StartPicture.png";
	ui.PB_MachineStart->setIcon(QIcon(qstrIconPath));
	ui.PB_MachineStart->setIconSize(QSize(30, 30));
	ui.PB_MachineStart->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/StopPicture.png";
	ui.PB_MachineStop->setIcon(QIcon(qstrIconPath));
	ui.PB_MachineStop->setIconSize(QSize(30, 30));
	ui.PB_MachineStop->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/OnloadDirectionA.png";
	m_qIconOnloadDirFW.addFile(qstrIconPath);
	qstrIconPath = qstrIconFile + "/Image/OnloadDirectionB.png";
	m_qIconOnloadDirRE.addFile(qstrIconPath);
	ui.PB_OnloadDirection->setIcon(m_qIconOnloadDirFW);
	ui.PB_OnloadDirection->setIconSize(QSize(30, 30));
	ui.PB_OnloadDirection->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/RunDirB.png";
	m_qIconRunDirFW.addFile(qstrIconPath);
	qstrIconPath = qstrIconFile + "/Image/RunDirF.png";
	m_qIconRunDirRE.addFile(qstrIconPath);
	ui.PB_RunDirection->setIcon(m_qIconRunDirFW);
	ui.PB_RunDirection->setIconSize(QSize(30, 30));
	ui.PB_RunDirection->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/UserLogin.png";
	ui.PB_UserLogin->setIcon(QIcon(qstrIconPath));
	ui.PB_UserLogin->setIconSize(QSize(30, 30));
	ui.PB_UserLogin->setStyleSheet("QPushButton{background: transparent;color: white; border-radius: 10px; border-style: outset;text-align : left;}"
		"QPushButton:pressed{background-color:blue;color: white; border-radius: 10px; border: 1px groove gray; border-style: outset;border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/FloatingWindowShow.png";
	ui.LB_CtrlShow->setScaledContents(true);
	ui.LB_CtrlShow->setPixmap(QPixmap(qstrIconPath));
	qstrIconPath = qstrIconFile + "/Image/FloatingWindowShow2.png";
	ui.LB_CtrlHide->setScaledContents(true);
	ui.LB_CtrlHide->setPixmap(QPixmap(qstrIconPath));
	
	//������ͣ��λ��ť����
	ui.PB_MachineEStop->setVisible(false);
	ui.PB_MachineReset->setVisible(false);
	ui.PB_MachineStart->setVisible(false);
	ui.PB_MachineStop->setVisible(false);
	ui.LB_CtrlHide->setVisible(false);
}

void UI_FilmTrimmer::initConnect()
{
	connect(m_pButtonGruop, SIGNAL(buttonClicked(int)), this, SLOT(SlotSwitchPage(int)));
	connect(ui.PB_MachineStart, SIGNAL(clicked()), this, SLOT(SlotMachineStart()));
	connect(ui.PB_MachineReset, SIGNAL(clicked()), this, SLOT(SlotMachineReset()));
	connect(ui.PB_MachineStop, SIGNAL(clicked()), this, SLOT(SlotMachineStop()));
	connect(ui.PB_MachineEStop, SIGNAL(clicked()), this, SLOT(SlotMachineEStop()));
	connect(ui.PB_RunDirection, SIGNAL(clicked()), this, SLOT(SlotRunDirection()));
	connect(ui.PB_OnloadDirection, SIGNAL(clicked()), this, SLOT(SlotOnloadDirection()));
	connect(ui.PB_UserLogin, SIGNAL(clicked()), this, SLOT(SlotUserLogin()));
	connect(m_pUserTimer, SIGNAL(timeout()), this, SLOT(SlotUserTypeUpdata()));
	connect(m_pSystemTimeTimer, SIGNAL(timeout()), this, SLOT(SlotUpdataSystemtime()));
	ui.LB_CtrlHide->installEventFilter(this);
	ui.LB_CtrlShow->installEventFilter(this);
}


bool UI_FilmTrimmer::eventFilter(QObject *obj, QEvent *ev)
{
	if (obj == ui.LB_CtrlHide)
	{
		if (ev->type() == QEvent::MouseButtonPress)
		{
			SetCtrlShow(false);
			return true;
		}
		else
			return false;
	}
	else if (obj == ui.LB_CtrlShow)
	{
		if (ev->type() == QEvent::MouseButtonPress)
		{
			SetCtrlShow(true);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return UI_FilmTrimmer::eventFilter(obj, ev);
	}
}

bool UI_FilmTrimmer::insertModule(int nModuleItem, QString qstrPageName, QString qstrIcon, QWidget* pageWidget)
{
	//���
	ui.SW_ClientWidget->insertWidget(nModuleItem, pageWidget);
	pageWidget->setStyleSheet("background:transparent; ");
	QPushButton* pPushButton = new QPushButton;
	pPushButton->setMinimumHeight(45);
	pPushButton->setText(qstrPageName);
	QFont qfont(QString::fromLocal8Bit("΢���ź�"), 11);
	pPushButton->setFont(qfont);
	pPushButton->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);
	m_pButtonGruop->addButton((QAbstractButton*)pPushButton, nModuleItem);
	ui.HL_PageButtonLayout->insertWidget(nModuleItem, pPushButton);
	
	return true;
}

bool UI_FilmTrimmer::GetPageConfigInfo()
{
	DWORD dwStartTime = GetTickCount();
	bool bres = false;
	while (1)
	{
		if (MACHINECTRL.GetOnloadConfigStatus())
		{
			SetModuleInfo(AUTOMATICPRODUCT, MACHINECTRL.m_QveAutoProduction);
			SetModuleInfo(IODEBUG, MACHINECTRL.m_QveIODebug);
			SetModuleInfo(MOTORDEBUG, MACHINECTRL.m_QveMotorDebug);
			SetModuleInfo(PARAMETERSET, MACHINECTRL.m_QveParameterSetting);
			SetModuleInfo(PRODUCTEDITOR, MACHINECTRL.m_QveProductEditor);
			SetModuleInfo(HISTORICALINFO, MACHINECTRL.m_QveHistoricalInfo);
			//SetModuleInfo(MESONLOAD, MACHINECTRL.m_QveM);
			initPageModule();
			AddModule();
			bres = true;
			break;
		}
		else
		{
			if (GetTickCount() - dwStartTime > 10000)
			{
				bres = false;
				break;
			}
				
		}
		Sleep(10);
	}
	return bres;
}

bool UI_FilmTrimmer::AutoUpdateData(const QString qstrAlarmInfo)
{
	if (qstrAlarmInfo == m_qstrAlarmList)
	{
		m_nAlarmCurPoint += 5;
		QString qstrAlamrTmp = m_qstrAlarmList.mid(m_nAlarmCurPoint);
		ui.LB_AlarmOrError_Show->setText(qstrAlamrTmp);
	}
	else
	{
		m_qstrAlarmList = qstrAlarmInfo;
		m_nAlarmCurPoint = 0;
		ui.LB_AlarmOrError_Show->setText(m_qstrAlarmList);
	}
	return true;
}

bool UI_FilmTrimmer::SwitchPage(bool flag, int nPageItem)
{
	if (EXIT == nPageItem) //�˳�
	{
		close();
		return true;
	}
	if (flag) //�л���ָ��ҳ��
	{
		ui.SW_ClientWidget->setCurrentIndex(nPageItem);
		//���ø�ҳ�����ת����
		m_qMapWidgetInfo.value(nPageItem)->SkipCurrentPage();
		return true;
	}
	return true;
}

bool UI_FilmTrimmer::SetCtrlShow(bool bFlag)
{
	if (bFlag)
	{
		ui.LB_CtrlShow->setVisible(false);
		ui.LB_CtrlHide->setVisible(true);
		ui.PB_MachineEStop->setVisible(true);
		ui.PB_MachineStop->setVisible(true);
		ui.PB_MachineStart->setVisible(true);
		ui.PB_MachineReset->setVisible(true);
	}
	else
	{
		ui.LB_CtrlShow->setVisible(true);
		ui.LB_CtrlHide->setVisible(false);
		ui.PB_MachineEStop->setVisible(false);
		ui.PB_MachineStop->setVisible(false);
		ui.PB_MachineStart->setVisible(false);
		ui.PB_MachineReset->setVisible(false);
	}
	return true;
}

void UI_FilmTrimmer::SetModuleInfo(int nPage, QVector<ST_MODULE>& ModuleInfo)
{
	m_qMapPageModuleInfo.insert(nPage, ModuleInfo);
}

void UI_FilmTrimmer::SetMachineRunModel(int nModel)
{
	if (nModel)
		ui.LB_MachineModel->setText(QString::fromLocal8Bit("�Զ�ģʽ"));
	else
		ui.LB_MachineModel->setText(QString::fromLocal8Bit("�ֶ�ģʽ"));
}

void UI_FilmTrimmer::SetMachineRunDirection(int nDir)
{
	if (nDir)
	{
		ui.PB_RunDirection->setText(QString::fromLocal8Bit("��������"));
		ui.PB_RunDirection->setIcon(m_qIconRunDirFW);
	}
	else
	{
		ui.PB_RunDirection->setText(QString::fromLocal8Bit("��������"));
		ui.PB_RunDirection->setIcon(m_qIconRunDirRE);
	}
}

void UI_FilmTrimmer::SetMachineOnloadDirection(int OnloadDirection)
{
	if (OnloadDirection)
	{
		ui.PB_OnloadDirection->setText(QString::fromLocal8Bit("˳ʱ��ž�"));
		ui.PB_OnloadDirection->setIcon(m_qIconOnloadDirFW);
	}
	else
	{
		ui.PB_OnloadDirection->setText(QString::fromLocal8Bit("��ʱ��ž�"));
		ui.PB_OnloadDirection->setIcon(m_qIconOnloadDirRE);
	}
}

void UI_FilmTrimmer::initPageModule()
{
	int nLength = m_qMapPageModuleInfo.size();
	for (int i = 0; i < nLength; i++)
	{
		QVector<ST_MODULE> qVecModuleInfo = m_qMapPageModuleInfo.value(i);
		switch (i)
		{
		case AUTOMATICPRODUCT:
			m_pAutoProduction->insertModule(&qVecModuleInfo);
			break;
		case IODEBUG:
			m_pIODebug->insertModule(&qVecModuleInfo);
			break;
		case MOTORDEBUG:
			m_pMotorDebug->insertModule(&qVecModuleInfo);
			break;
		case PARAMETERSET:
			m_pParameterSetting->insertModule(&qVecModuleInfo);
			break;
		case PRODUCTEDITOR:
			m_pProductEditor->insertModule(&qVecModuleInfo);
			break;
		case HISTORICALINFO:
			m_pHistoricalInformation->insertModule(&qVecModuleInfo);
			break;
		case MESONLOAD:
			//
			break;
		default:
			break;
		}
	}
}

void UI_FilmTrimmer::AddModule()
{
	insertModule(AUTOMATICPRODUCT, QString::fromLocal8Bit("�Զ�����"), QString::fromLocal8Bit(""), m_pAutoProduction);
	insertModule(PRODUCTEDITOR, QString::fromLocal8Bit("��Ʒ�༭"), QString::fromLocal8Bit(""), m_pProductEditor);
	insertModule(HISTORICALINFO, QString::fromLocal8Bit("��ʷ��Ϣ"), QString::fromLocal8Bit(""), m_pHistoricalInformation);
	insertModule(IODEBUG, QString::fromLocal8Bit("IO����"), QString::fromLocal8Bit(""), m_pIODebug);
	insertModule(MOTORDEBUG, QString::fromLocal8Bit("�������"), QString::fromLocal8Bit(""), m_pMotorDebug);
	insertModule(PARAMETERSET, QString::fromLocal8Bit("��������"), QString::fromLocal8Bit(""), m_pParameterSetting);

	ui.SW_ClientWidget->setCurrentIndex(AUTOMATICPRODUCT);
	m_qMapWidgetInfo.value(AUTOMATICPRODUCT)->SkipCurrentPage();
	m_pButtonGruop->button(AUTOMATICPRODUCT)->setStyleSheet(
		"QPushButton{background: rgb(255,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);
}

void UI_FilmTrimmer::SlotSwitchPage(int nPageItem)
{
	//������ǵ�ǰҳ��
	if (nPageItem == m_nCurPageItem)
		return;
	
	//�رմ���,Test
	if (EXIT == nPageItem)
	{
		close();
		return;
	}
	//�л���ָ��ҳ��
	m_qVecModifyVal.clear();
	//��ȡ��ҳ���޸ĵ�����
	if (nPageItem != EXIT)
	{
		m_qMapWidgetInfo.value(m_nCurPageItem)->GetModifyParam(m_qVecModifyVal);
	}
	//�����źŵ�ҵ���߼���
	if (m_qVecModifyVal.isEmpty())
		m_bParamModifyFlag = false;
	else
		m_bParamModifyFlag = true;

	if (m_pCtrlFilmTrimmer->SwitchPage(nPageItem, m_bParamModifyFlag, m_qVecModifyVal))
	{
		SwitchPage(true, nPageItem);
		m_pButtonGruop->button(nPageItem)->setStyleSheet(
			"QPushButton{background: rgb(255,172,179);color: white; border-radius: 10px; border-style: outset;}"
			"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
			); //��ǰѡ�е�
		m_pButtonGruop->button(m_nCurPageItem)->setStyleSheet(
			"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
			"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
			);//��һ��ҳ��
		m_nCurPageItem = nPageItem;
	}
}

void UI_FilmTrimmer::SlotMachineStart()
{
	//emit SigMachineCtrl(MACHINE_START);
	m_pCtrlFilmTrimmer->MachineCtrl(MACHINE_START);
}

void UI_FilmTrimmer::SlotMachineReset()
{
	//emit SigMachineCtrl(MACHINE_RESET);
	m_pCtrlFilmTrimmer->MachineCtrl(MACHINE_RESET);
}

void UI_FilmTrimmer::SlotMachineStop()
{
	//emit SigMachineCtrl(MACHINE_STOP);
	m_pCtrlFilmTrimmer->MachineCtrl(MACHINE_STOP);
}

void UI_FilmTrimmer::SlotMachineEStop()
{
	m_pCtrlFilmTrimmer->MachineCtrl(MACHINE_STOP);
}

void UI_FilmTrimmer::SlotRunDirection()
{
	bool res = m_pCtrlFilmTrimmer->MachineCtrl(MACHINE_RUNDIR);
	SetMachineRunDirection(res);
}

void UI_FilmTrimmer::SlotOnloadDirection()
{
	bool res = m_pCtrlFilmTrimmer->MachineCtrl(MACHINE_ROLLDIR);
	SetMachineOnloadDirection(res);
}

void UI_FilmTrimmer::SlotUserLogin()
{
	QString qstrUserName = m_pCtrlFilmTrimmer->UserLogin();
	if (!qstrUserName.isEmpty())
	{
		ui.PB_UserLogin->setText(qstrUserName);
		m_pUserTimer->start(60000);
	}
}

void UI_FilmTrimmer::SlotUserTypeUpdata()
{
	if (m_pCtrlFilmTrimmer->ResultUserName())
	{
		if (m_pUserTimer->isActive())
			m_pUserTimer->stop();
	}
}

void UI_FilmTrimmer::SlotUpdataSystemtime()
{
	QDateTime systemtime = QDateTime::currentDateTime();//��ȡϵͳ���ڵ�ʱ��
	QString qstrSystem = systemtime.toString("yyyy/MM/dd hh:mm:ss ddd"); //������ʾ��ʽ
	ui.LB_SystemTime->setText(qstrSystem);
}

