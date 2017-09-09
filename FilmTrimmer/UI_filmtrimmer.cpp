#include "UI_filmtrimmer.h"
#include "BaseDataType.h"
#include <QPushButton>
#include <QDir>
#include "OP_MachineSoftWareMain.h"
#include <QDateTime>

UI_FilmTrimmer::UI_FilmTrimmer(QMainWindow* parentWin /*= 0*/)
	:QMainWindow(parentWin),UI_InterfaceBase(parentWin)
{
	ui.setupUi(this);
	setStyleSheet("background-image: url(:/FilmTrimmer/Image/Background.png)");
	setWindowFlags(Qt::FramelessWindowHint);
	initVal();
	initUI();
	
	GetPageConfigInfo();
	//绑定Controller
	m_pCtrlFilmTrimmer = new CTRL_FilmTrimmer;
	m_pCtrlFilmTrimmer->SetUIInterface(this);
	m_pUserTimer = new QTimer;
	m_pUserTimer->start(60000);
	m_pSystemTimeTimer = new QTimer;
	m_pSystemTimeTimer->start(1000);
	initConnect();
//	SetMachineRunModel(true);
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

	//页面
	m_pAutoProduction = new UI_AutoProduction;
	m_qMapWidgetInfo.insert(AUTOMATICPRODUCT, m_pAutoProduction);
	m_pProductEditor = new UI_ProductEditor;
	m_qMapWidgetInfo.insert(PRODUCTEDITOR, m_pProductEditor);
	m_pHistoricalInformation = new UI_HistoricalInformation;
	m_qMapWidgetInfo.insert(HISTORICALINFO, m_pHistoricalInformation);
	m_pIODebug = new UI_IODebug;
	m_qMapWidgetInfo.insert(IODEBUG, m_pIODebug);
	m_pMotorDebug = new UI_MotorDebug;
	m_qMapWidgetInfo.insert(MOTORDEBUG, m_pMotorDebug);
	m_pParameterSetting = new UI_ParameterSetting;
	m_qMapWidgetInfo.insert(PARAMETERSET, m_pParameterSetting);
}

void UI_FilmTrimmer::initUI()
{
	setWindowFlags(Qt::FramelessWindowHint);

	//设备维护
	QPushButton* pMaintenanceButton = new QPushButton;
	pMaintenanceButton->setText(QString::fromLocal8Bit("设备维护"));
	QFont qfont(QString::fromLocal8Bit("微软雅黑"), 11);
	pMaintenanceButton->setFont(qfont);
	pMaintenanceButton->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);
	pMaintenanceButton->setMinimumHeight(45);
	m_pButtonGruop->addButton(pMaintenanceButton, MAINTENANCE);
	ui.HL_PageButtonLayout->insertWidget(MAINTENANCE, pMaintenanceButton);
	//退出
	QPushButton* pExitButton = new QPushButton;
	pExitButton->setText(QString::fromLocal8Bit("退出"));
	pExitButton->setFont(qfont);
	pExitButton->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);
	pExitButton->setMinimumHeight(45);
	m_pButtonGruop->addButton(pExitButton, EXIT);
	ui.HL_PageButtonLayout->insertWidget(EXIT, pExitButton);

	//UI图标背景设置
	m_qstrIconFile = QCoreApplication::applicationDirPath();
	
	QString qstrIconPath = m_qstrIconFile + "/Image/MachineStatus_Stop.png";
	ui.LB_AlarmOrError_Show->setScaledContents(true);
	ui.LB_AlarmOrError_Show->setPixmap(QPixmap(qstrIconPath));
	ui.LB_AlarmOrError_Show->setStyleSheet("background:transparent;");

	qstrIconPath = m_qstrIconFile + "/Image/LeftPic.png";
	ui.LB_Show1->setScaledContents(true);
	ui.LB_Show1->setPixmap(QPixmap(qstrIconPath));
	ui.LB_Show1->setStyleSheet("background: transparent;");

	qstrIconPath = m_qstrIconFile + "/Image/RightPic.png";
	ui.LB_Show2->setScaledContents(true);
	ui.LB_Show2->setPixmap(QPixmap(qstrIconPath));
	ui.LB_Show2->setStyleSheet("background: transparent");

	qstrIconPath = m_qstrIconFile + "/Image/Diaphaneity2.png";
	ui.LB_Show3->setScaledContents(true);
	ui.LB_Show3->setPixmap(QPixmap(qstrIconPath));

	qstrIconPath = m_qstrIconFile + "/Image/EStopIcon.png";
	ui.PB_MachineEStop->setIcon(QIcon(qstrIconPath));
	ui.PB_MachineEStop->setIconSize(QSize(30, 30));
	ui.PB_MachineEStop->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = m_qstrIconFile + "/Image/ResetPicture.png";
	ui.PB_MachineReset->setIcon(QIcon(qstrIconPath));
	ui.PB_MachineReset->setIconSize(QSize(30, 30));
	ui.PB_MachineReset->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = m_qstrIconFile + "/Image/StartPicture.png";
	ui.PB_MachineStart->setIcon(QIcon(qstrIconPath));
	ui.PB_MachineStart->setIconSize(QSize(30, 30));
	ui.PB_MachineStart->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = m_qstrIconFile + "/Image/StopPicture.png";
	ui.PB_MachineStop->setIcon(QIcon(qstrIconPath));
	ui.PB_MachineStop->setIconSize(QSize(30, 30));
	ui.PB_MachineStop->setStyleSheet(
		"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = m_qstrIconFile + "/Image/UserLogin.png";
	ui.PB_UserLogin->setIcon(QIcon(qstrIconPath));
	ui.PB_UserLogin->setIconSize(QSize(30, 30));
	ui.PB_UserLogin->setStyleSheet("QPushButton{background: transparent;color: white; border-radius: 10px; border-style: outset;text-align : left;}"
		"QPushButton:pressed{background-color:blue;color: white; border-radius: 10px; border: 1px groove gray; border-style: outset;border-style: inset; }"
		);

	ui.LB_MachineStatusShow->setStyleSheet("background: transparent");

	qstrIconPath = m_qstrIconFile + "/Image/Slide.png";
	ui.LB_CtrlShow->setScaledContents(true);
	ui.LB_CtrlShow->setPixmap(QPixmap(qstrIconPath));
	ui.LB_CtrlShow->setStyleSheet("background:transparent;");
	qstrIconPath = m_qstrIconFile + "/Image/Slide2.png";
	ui.LB_CtrlHide->setScaledContents(true);
	ui.LB_CtrlHide->setPixmap(QPixmap(qstrIconPath));
	ui.LB_CtrlHide->setStyleSheet("background:transparent;");

	ui.LB_OperatorHintText->setStyleSheet("background:transparent;");
	ui.LB_OperatorHintText->setText(QString::fromLocal8Bit("请点击复位按钮"));
	
	//设置启停复位按钮隐藏
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
	connect(ui.PB_UserLogin, SIGNAL(clicked()), this, SLOT(SlotUserLogin()));
	connect(m_pUserTimer, SIGNAL(timeout()), this, SLOT(SlotUserTypeUpdata()));
	connect(m_pSystemTimeTimer, SIGNAL(timeout()), this, SLOT(SlotUpdataSystemtime()));
	//connect(m_pAutoProduction->ui.Btn_Put, SIGNAL(clicked()), this, SLOT(SetPutPid()));
	//connect(m_pAutoProduction->ui.Btn_Get, SIGNAL(clicked()), this, SLOT(SetGetPid()));
	connect(m_pAutoProduction, SIGNAL(SigSetLaserParam(int)), this, SLOT(SlotSetLaserParam(int)));
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
	//添加
	ui.SW_ClientWidget->insertWidget(nModuleItem, pageWidget);
	pageWidget->setStyleSheet("background:transparent; ");
	QPushButton* pPushButton = new QPushButton;
	pPushButton->setMinimumHeight(45);
	pPushButton->setText(qstrPageName);
	QFont qfont(QString::fromLocal8Bit("微软雅黑"), 11);
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
			//SetModuleInfo(MESONLOAD,);
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
	if (EXIT == nPageItem) //退出
	{
		close();
		return true;
	}
	if (flag) //切换到指定页面
	{
		ui.SW_ClientWidget->setCurrentIndex(nPageItem);
		//调用该页面的跳转函数
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
	{
		ui.LB_MachineModel->setText(QString::fromLocal8Bit("自动模式"));
		m_pAutoProduction->SetButtonAttribute(false);
	}
	else
	{
		ui.LB_MachineModel->setText(QString::fromLocal8Bit("手动模式"));
		m_pAutoProduction->SetButtonAttribute(true);
	}
}

void UI_FilmTrimmer::initPageModule()
{
	int nLength = m_qMapPageModuleInfo.size();
	for (int i = 0; i <= nLength; i++)
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
	insertModule(AUTOMATICPRODUCT, QString::fromLocal8Bit("自动生产"), QString::fromLocal8Bit(""), m_pAutoProduction);
	insertModule(PRODUCTEDITOR, QString::fromLocal8Bit("产品编辑"), QString::fromLocal8Bit(""), m_pProductEditor);
	insertModule(HISTORICALINFO, QString::fromLocal8Bit("历史信息"), QString::fromLocal8Bit(""), m_pHistoricalInformation);
	insertModule(IODEBUG, QString::fromLocal8Bit("IO调试"), QString::fromLocal8Bit(""), m_pIODebug);
	insertModule(MOTORDEBUG, QString::fromLocal8Bit("电机调试"), QString::fromLocal8Bit(""), m_pMotorDebug);
	insertModule(PARAMETERSET, QString::fromLocal8Bit("参数设置"), QString::fromLocal8Bit(""), m_pParameterSetting);

	ui.SW_ClientWidget->setCurrentIndex(AUTOMATICPRODUCT);
	m_qMapWidgetInfo.value(AUTOMATICPRODUCT)->SkipCurrentPage();
	m_pButtonGruop->button(AUTOMATICPRODUCT)->setStyleSheet(
		"QPushButton{background: rgb(255,172,179);color: white; border-radius: 10px; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);
}

void UI_FilmTrimmer::SlotSwitchPage(int nPageItem)
{
	//点击的是当前页面
	if (nPageItem == m_nCurPageItem)
		return;
	
	//关闭窗口,Test
	if (EXIT == nPageItem)
	{
		close();
		return;
	}
	//切换到指定页面
	m_qVecModifyVal.clear();
	//获取该页面修改的数据
	if (nPageItem != EXIT)
	{
		m_qMapWidgetInfo.value(m_nCurPageItem)->GetModifyParam(m_qVecModifyVal);
	}
	//发送信号的业务逻辑层
	if (m_qVecModifyVal.isEmpty())
		m_bParamModifyFlag = false;
	else
		m_bParamModifyFlag = true;

	EN_Resoult emResult = m_pCtrlFilmTrimmer->SwitchPage(nPageItem, m_bParamModifyFlag);
	if(NORESOULT == emResult || COMPEL == emResult) //不保存跳转到下一个页面
	{
		SwitchPage(true, nPageItem);
		m_pButtonGruop->button(nPageItem)->setStyleSheet(
			"QPushButton{background: rgb(255,172,179);color: white; border-radius: 10px; border-style: outset;}"
			"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
			); //当前选中的
		m_pButtonGruop->button(m_nCurPageItem)->setStyleSheet(
			"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
			"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
			);//上一个页面
		m_nCurPageItem = nPageItem;
	}
	else if(OK == emResult) // 保存参数跳转到指定页面
	{
		m_qMapWidgetInfo.value(m_nCurPageItem)->SaveParamer(); //保存
		SwitchPage(true, nPageItem);
		m_pButtonGruop->button(nPageItem)->setStyleSheet(
			"QPushButton{background: rgb(255,172,179);color: white; border-radius: 10px; border-style: outset;}"
			"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
			); //当前选中的
		m_pButtonGruop->button(m_nCurPageItem)->setStyleSheet(
			"QPushButton{background: rgb(1,172,179);color: white; border-radius: 10px; border-style: outset;}"
			"QPushButton:pressed{background-color:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
			);//上一个页面
		m_nCurPageItem = nPageItem;
	}
	else
	{
		//留在当前页面
	}
}

void UI_FilmTrimmer::SlotMachineStart()
{
	m_pCtrlFilmTrimmer->MachineCtrl(MACHINE_START);
	QString qstrIconPath = m_qstrIconFile + "/Image/MachineStatus_Run.png";
	ui.LB_AlarmOrError_Show->setPixmap(QPixmap(qstrIconPath));
}

void UI_FilmTrimmer::SlotMachineReset()
{
	m_pCtrlFilmTrimmer->MachineCtrl(MACHINE_RESET);
}

void UI_FilmTrimmer::SlotMachineStop()
{
	m_pCtrlFilmTrimmer->MachineCtrl(MACHINE_STOP);
	QString qstrIconPath = m_qstrIconFile + "/Image/MachineStatus_Stop.png";
	ui.LB_AlarmOrError_Show->setPixmap(QPixmap(qstrIconPath));
}

void UI_FilmTrimmer::SlotMachineEStop()
{
	m_pCtrlFilmTrimmer->MachineCtrl(MACHINE_ESTOP);
	QString qstrIconPath = m_qstrIconFile + "/Image/MachineStatus_Alarm.png";
	ui.LB_AlarmOrError_Show->setPixmap(QPixmap(qstrIconPath));
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
	QDateTime systemtime = QDateTime::currentDateTime();//获取系统现在的时间
	QString qstrSystem = systemtime.toString("yyyy/MM/dd hh:mm:ss ddd"); //设置显示格式
	ui.LB_SystemTime->setText(qstrSystem);
}

void UI_FilmTrimmer::SlotSetPutPid()
{

}

void UI_FilmTrimmer::SlotSetGetPid()
{

}

void UI_FilmTrimmer::SlotSetLaserParam(int nCard)
{
	m_pProductEditor->SetLaserData(nCard);
}

