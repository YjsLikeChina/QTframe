#include "UI_MotorDebug.h"
#include <direct.h>

UI_MotorDebug::UI_MotorDebug(QWidget* parent /*= Q_NULLPTR*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
	:QWidget(parent),UI_InterfaceBase(parent)
{
	ui.setupUi(this);
	initVal();
	initUI();
	initConnect();
}

UI_MotorDebug::~UI_MotorDebug()
{
}

void UI_MotorDebug::initUI()
{
	QString qstrIconFile = QCoreApplication::applicationDirPath();
	QString strIcon = qstrIconFile + "/Image/NoEnable.png";

	m_qPixmapOffStatus = QPixmap(strIcon);
	strIcon = qstrIconFile + "/Image/Enable.png";
	m_qPixmapOnStatus = QPixmap(strIcon);

	strIcon = qstrIconFile + "/Image/Diaphaneity2.png";
	ui.LB_AxisSelectToolbar->setScaledContents(true);
	ui.LB_AxisSelectToolbar->setPixmap(QPixmap(strIcon));

	ui.LB_Show6->setScaledContents(true);
	ui.LB_Show6->setPixmap(QPixmap(strIcon));

	ui.LB_Show7->setScaledContents(true);
	ui.LB_Show7->setPixmap(QPixmap(strIcon));

	ui.LB_Show8->setScaledContents(true);
	ui.LB_Show8->setPixmap(QPixmap(strIcon));

	ui.LB_Show9->setScaledContents(true);
	ui.LB_Show9->setPixmap(QPixmap(strIcon));

	ui.LB_Show10->setScaledContents(true);
	ui.LB_Show10->setPixmap(QPixmap(strIcon));

	ui.LB_Show11->setScaledContents(true);
	ui.LB_Show11->setPixmap(QPixmap(strIcon));

	ui.LB_Show29->setScaledContents(true);
	ui.LB_Show29->setPixmap(QPixmap(strIcon));

	strIcon = qstrIconFile + "/Image/AxisMove.png";
	ui.PB_AxisMove->setIcon(QIcon(strIcon));
	ui.PB_AxisMove->setIconSize(QSize(35, 25));
	ui.PB_AxisMove->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white;border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	strIcon = qstrIconFile + "/Image/GoHome.png";
	ui.PB_AxisGoHome->setIcon(QIcon(strIcon));
	ui.PB_AxisGoHome->setIconSize(QSize(35, 25));
	ui.PB_AxisGoHome->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	strIcon = qstrIconFile + "/Image/Advance.png";
	ui.PB_AxisAdvance->setIcon(QIcon(strIcon));
	ui.PB_AxisAdvance->setIconSize(QSize(35, 25));
	ui.PB_AxisAdvance->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	strIcon = qstrIconFile + "/Image/Retreat.png";
	ui.PB_AxisRetreat->setIcon(QIcon(strIcon));
	ui.PB_AxisRetreat->setIconSize(QSize(35, 25));
	ui.PB_AxisRetreat->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	strIcon = qstrIconFile + "/Image/Save.png";
	ui.PB_AxisSave->setIcon(QIcon(strIcon));
	ui.PB_AxisSave->setIconSize(QSize(35, 25));
	ui.PB_AxisSave->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	strIcon = qstrIconFile + "/Image/AxisEnable.png";
	ui.PB_AxisEnable->setIcon(QIcon(strIcon));
	ui.PB_AxisEnable->setIconSize(QSize(35, 25));
	ui.PB_AxisEnable->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white;border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	strIcon = qstrIconFile + "/Image/Alarm.png";
	ui.PB_AxisAlarmClear->setIcon(QIcon(strIcon));
	ui.PB_AxisAlarmClear->setIconSize(QSize(35, 25));
	ui.PB_AxisAlarmClear->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	strIcon = qstrIconFile + "/Image/AxisStop.png";
	ui.PB_AxisStop->setIcon(QIcon(strIcon));
	ui.PB_AxisStop->setIconSize(QSize(40, 35));
	ui.PB_AxisStop->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	ui.LE_StartSpeed->setStyleSheet("background-color:rgb(13,74,185); border: 1px groove white;");
	ui.LE_MaxSpeed->setStyleSheet("background-color:rgb(13,74,185); border: 1px groove white;");
	ui.LE_AccSpeedTime->setStyleSheet("background-color:rgb(13,74,185); border: 1px groove white;");
	ui.LE_DecSpeedTime->setStyleSheet("background-color:rgb(13,74,185); border: 1px groove white;");
	ui.LE_HomeOffset->setStyleSheet("background-color:rgb(13,74,185); border: 1px groove white;");
	ui.LE_HomeSpeed->setStyleSheet("background-color:rgb(13,74,185); border: 1px groove white;");
	ui.LE_AxisMoveTargetVel->setStyleSheet("background-color:rgb(13,74,185); border: 1px groove white;");
	ui.LE_AxisMoveVel->setStyleSheet("background-color:rgb(13,74,185); border: 1px groove white;");
	ui.CB_AxisSelect->setStyleSheet("background-color:rgb(13,74,185);color: white;");

	//输入限定
	QRegExp regx("([0-9]{0,3}[.][0-9]{0,4})");
	QValidator *validator = new QRegExpValidator(regx, ui.LE_StartSpeed);
	ui.LE_StartSpeed->setValidator(validator);
	ui.LE_StartSpeed->setContextMenuPolicy(Qt::NoContextMenu);

	validator = new QRegExpValidator(regx, ui.LE_MaxSpeed);
	ui.LE_MaxSpeed->setValidator(validator);
	ui.LE_MaxSpeed->setContextMenuPolicy(Qt::NoContextMenu);

	validator = new QRegExpValidator(regx, ui.LE_AccSpeedTime);
	ui.LE_AccSpeedTime->setValidator(validator);
	ui.LE_AccSpeedTime->setContextMenuPolicy(Qt::NoContextMenu);

	validator = new QRegExpValidator(regx, ui.LE_DecSpeedTime);
	ui.LE_DecSpeedTime->setValidator(validator);
	ui.LE_DecSpeedTime->setContextMenuPolicy(Qt::NoContextMenu);

	validator = new QRegExpValidator(regx, ui.LE_HomeOffset);
	ui.LE_HomeOffset->setValidator(validator);
	ui.LE_HomeOffset->setContextMenuPolicy(Qt::NoContextMenu);

	validator = new QRegExpValidator(regx, ui.LE_HomeSpeed);
	ui.LE_HomeSpeed->setValidator(validator);
	ui.LE_HomeSpeed->setContextMenuPolicy(Qt::NoContextMenu);

	validator = new QRegExpValidator(regx, ui.LE_AxisMoveTargetVel);
	ui.LE_AxisMoveTargetVel->setValidator(validator);
	ui.LE_AxisMoveTargetVel->setContextMenuPolicy(Qt::NoContextMenu);

	validator = new QRegExpValidator(regx, ui.LE_AxisMoveVel);
	ui.LE_AxisMoveVel->setValidator(validator);
	ui.LE_AxisMoveVel->setContextMenuPolicy(Qt::NoContextMenu);
}

void UI_MotorDebug::initVal()
{
	m_pCtrlMotorDebug = new CTRL_MotorDebug;
	m_pCtrlMotorDebug->SetUIInterface(this);
}

void UI_MotorDebug::initConnect()
{
	//connect(ui.PB_AxisAdvance, SIGNAL(clicked()), this, SLOT(SlotAdvanceMove()));
	//connect(ui.PB_AxisRetreat, SIGNAL(clicked()), this, SLOT(SlotRetreatMove()));
	connect(ui.PB_AxisAdvance, SIGNAL(pressed()), this, SLOT(SlotAdvanceMovePress()));
	connect(ui.PB_AxisAdvance, SIGNAL(released()), this, SLOT(SlotAdvanceMoveRelease()));
	connect(ui.PB_AxisRetreat, SIGNAL(pressed()), this, SLOT(SlotRetreatMovePress()));
	connect(ui.PB_AxisRetreat, SIGNAL(released()), this, SLOT(SlotRetreatMoveRelease()));
	connect(ui.PB_AxisMove, SIGNAL(clicked()), this, SLOT(SlotAbsMove()));
	connect(ui.PB_AxisGoHome, SIGNAL(clicked()), this, SLOT(SlotGotoHome()));

	connect(ui.PB_AxisEnable, SIGNAL(clicked()), this, SLOT(SlotEnable()));
	connect(ui.PB_AxisStop, SIGNAL(clicked()), this, SLOT(SlotStop()));
	connect(ui.PB_AxisAlarmClear, SIGNAL(clicked()), this, SLOT(SlotCleanAlarm()));

	connect(ui.PB_AxisSave, SIGNAL(clicked()), this, SLOT(SlotSave()));

	connect(ui.CB_AxisSelect, SIGNAL(activated(int)), this, SLOT(SlotSwitchAxis(int)));
}

/*保存*/
void UI_MotorDebug::SlotSave()
{
	QVector<ST_CHANGE_POINT> qVecMotorInfo;
	GetModifyParam(qVecMotorInfo);
	m_pCtrlMotorDebug->SaveMotolData(qVecMotorInfo);
	ui.LE_AxisMoveTargetVel->setText(ui.LB_PointFBVal->text());

	ui.LE_StartSpeed->setModified(false);
	ui.LE_MaxSpeed->setModified(false);
	ui.LE_AccSpeedTime->setModified(false);
	ui.LE_DecSpeedTime->setModified(false);
	ui.LE_HomeOffset->setModified(false);
	ui.LE_HomeSpeed->setModified(false);
	ui.LB_PointFBVal->setWindowModified(false);
}

//移动信号
void UI_MotorDebug::SlotAbsMove()
{
	int nAxis = ui.CB_AxisSelect->currentIndex();
	double dlDist = ui.LE_AxisMoveTargetVel->text().toDouble();
	m_pCtrlMotorDebug->AxisleMove(nAxis, dlDist, ABSOLUTE_MOVE);
}

void UI_MotorDebug::SlotAdvanceMovePress()
{
	if (0 == ui.CB_MoveModel->currentIndex())
	{
		int nAxis = ui.CB_AxisSelect->currentIndex();
		double dlDist = ui.LE_AxisMoveVel->text().toDouble();
		dlDist += ui.LB_PointFBVal->text().toDouble();
		m_pCtrlMotorDebug->AxisleMove(nAxis, 0, ABSOLUTE_MOVE);
	}
	else
	{
		int nAxis = ui.CB_AxisSelect->currentIndex();
		m_pCtrlMotorDebug->AxisleMove(nAxis, 0, INCHING_MOVE, true, true);
	}
}

void UI_MotorDebug::SlotAdvanceMoveRelease()
{
	int nAxis = ui.CB_AxisSelect->currentIndex();
	m_pCtrlMotorDebug->AxisleMove(nAxis, 0, INCHING_MOVE, true, false);
}

void UI_MotorDebug::SlotRetreatMovePress()
{
	if (0 == ui.CB_MoveModel->currentIndex())
	{
		int nAxis = ui.CB_AxisSelect->currentIndex();
		double dlDist = ui.LE_AxisMoveVel->text().toDouble();
		dlDist = ui.LB_PointFBVal->text().toDouble() - dlDist;
		m_pCtrlMotorDebug->AxisleMove(nAxis, 0, ABSOLUTE_MOVE);
	}
	else
	{
		int nAxis = ui.CB_AxisSelect->currentIndex();
		m_pCtrlMotorDebug->AxisleMove(nAxis, 0, INCHING_MOVE, false, true);
	}
}

void UI_MotorDebug::SlotRetreatMoveRelease()
{
	int nAxis = ui.CB_AxisSelect->currentIndex();
	m_pCtrlMotorDebug->AxisleMove(nAxis, 0, INCHING_MOVE, false, false);
}


void UI_MotorDebug::SlotGotoHome()
{
	int nAxis = ui.CB_AxisSelect->currentIndex();
	double dlDist = 0;
	m_pCtrlMotorDebug->AxisleMove(nAxis, 0, GOTOHOME_MOVE);
}
//end 移动信号

//控制信号
void UI_MotorDebug::SlotEnable()
{
	int nAxis = ui.CB_AxisSelect->currentIndex();
	m_pCtrlMotorDebug->SetMotorEnable(nAxis);
}

void UI_MotorDebug::SlotStop()
{
	int nAxis = ui.CB_AxisSelect->currentIndex();
	m_pCtrlMotorDebug->SetMotorStop(nAxis);
}

void UI_MotorDebug::SlotCleanAlarm()
{
	int nAxis = ui.CB_AxisSelect->currentIndex();
	m_pCtrlMotorDebug->SetMotorCleanAlarm(nAxis);
}

void UI_MotorDebug::SlotSwitchAxis(int nAxis)
{
	QVector<ST_CHANGE_POINT> qVecMotorInfo;
	m_pCtrlMotorDebug->SwitchMotor(nAxis, qVecMotorInfo);

	if (qVecMotorInfo.isEmpty())
		return;
	
	ui.LE_StartSpeed->setText(QString::number(qVecMotorInfo.at(0).dlData, 'g'));
	ui.LE_MaxSpeed->setText(QString::number(qVecMotorInfo.at(1).dlData, 'g'));
	ui.LE_HomeSpeed->setText(QString::number(qVecMotorInfo.at(2).dlData, 'g'));
	ui.LE_AccSpeedTime->setText(QString::number(qVecMotorInfo.at(3).dlData, 'g'));
	ui.LE_DecSpeedTime->setText(QString::number(qVecMotorInfo.at(4).dlData, 'g'));
	ui.LE_HomeOffset->setText(QString::number(qVecMotorInfo.at(5).dlData, 'g'));
	ui.LE_AxisMoveTargetVel->setText(QString::number(qVecMotorInfo.at(6).dlData, 'g'));
}

//end 控制信号

bool UI_MotorDebug::insertModule(QVector<ST_MODULE>* cfgModuleInfo)
{
	int nLength = cfgModuleInfo->length();
	for (int i = 0; i < nLength; i++)
	{
		ui.CB_AxisSelect->addItem(cfgModuleInfo->at(i).ModuleName);
	}

	return true;
}

bool UI_MotorDebug::GetModifyParam(QVector<ST_CHANGE_POINT>& VecModifyVal)
{
	ST_CHANGE_POINT stModifyParam;

	stModifyParam.nModuleNum = ui.CB_AxisSelect->currentIndex();
	if (ui.LE_StartSpeed->isModified())
	{
		stModifyParam.nChildNum = ORDER_START_SPEED;
		stModifyParam.dlData = ui.LE_StartSpeed->text().toDouble();
	}
	VecModifyVal.push_back(stModifyParam);

	if (ui.LE_MaxSpeed->isModified())
	{
		stModifyParam.nChildNum = ORDER_MAX_SPEED;
		stModifyParam.dlData = ui.LE_MaxSpeed->text().toDouble();
	}
	VecModifyVal.push_back(stModifyParam);

	if (ui.LE_AccSpeedTime->isModified())
	{
		stModifyParam.nChildNum = ORDER_ADD_SPEED;
		stModifyParam.dlData = ui.LE_AccSpeedTime->text().toDouble();
	}
	VecModifyVal.push_back(stModifyParam);

	if (ui.LE_DecSpeedTime->isModified())
	{
		stModifyParam.nChildNum = ORDER_DEC_SPEED;
		stModifyParam.dlData = ui.LE_DecSpeedTime->text().toDouble();
	}
	VecModifyVal.push_back(stModifyParam);

	if (ui.LE_HomeOffset->isModified())
	{
		stModifyParam.nChildNum = ORDER_HOME_OFFSET;
		stModifyParam.dlData = ui.LE_HomeOffset->text().toDouble();
	}
	VecModifyVal.push_back(stModifyParam);

	if (ui.LE_HomeSpeed->isModified())
	{
		stModifyParam.nChildNum = ORDER_GOTOHOME_SPEED;
		stModifyParam.dlData = ui.LE_HomeSpeed->text().toDouble();
	}
	VecModifyVal.push_back(stModifyParam);

	if(ui.LB_PointFBVal->isWindowModified())
	{
		stModifyParam.nChildNum = ORDER_GET_POS;
		stModifyParam.dlData = ui.LB_PointFBVal->text().toDouble();
	}
	VecModifyVal.push_back(stModifyParam);
	return true;
}

bool UI_MotorDebug::AutoUpdateData(QList<ST_UPDATEDATA> AutoUpdataInfo)
{
	int nLength = AutoUpdataInfo.length();
	for (int i = 0; i < nLength; i++)
	{
		if (i == 0)
		{
			int nStatus = (int)AutoUpdataInfo.at(i).dlData;
			if (nStatus & AXIS_STATU_ORIGIN)
			{
				ui.LB_Status_Origin->setPixmap(m_qPixmapOnStatus);
			}
			else
			{
				ui.LB_Status_Origin->setPixmap(m_qPixmapOffStatus);
			}

			if (nStatus & AXIS_STATU_LIMIT_PLUS)
			{
				ui.LB_Status_Limit_Plus->setPixmap(m_qPixmapOnStatus);
			}
			else
			{
				ui.LB_Status_Limit_Plus->setPixmap(m_qPixmapOffStatus);
			}

			if (nStatus & AXIS_STATU_LIMIT_MINUS)
			{
				ui.LB_Status_Limit_Minus->setPixmap(m_qPixmapOnStatus);
			}
			else
			{
				ui.LB_Status_Limit_Minus->setPixmap(m_qPixmapOffStatus);
			}

			if (nStatus & AXIS_ENABLE)
			{
				ui.LB_Status_Enable->setPixmap(m_qPixmapOnStatus);
			}
			else
			{
				ui.LB_Status_Enable->setPixmap(m_qPixmapOffStatus);
			}

			if (nStatus & AXIS_STATU_READY)
			{
				ui.LB_Status_Ready->setPixmap(m_qPixmapOnStatus);
			}
			else
			{
				ui.LB_Status_Ready->setPixmap(m_qPixmapOffStatus);
			}

			if (nStatus & AXIS_STATU_INPLACE)
			{
				ui.LB_Status_Inplace->setPixmap(m_qPixmapOnStatus);
			}
			else
			{
				ui.LB_Status_Inplace->setPixmap(m_qPixmapOffStatus);
			}

			if (nStatus & AXIS_STATU_ALARM)
			{
				ui.LB_Status_Aralm->setPixmap(m_qPixmapOnStatus);
			}
			else
			{
				ui.LB_Status_Aralm->setPixmap(m_qPixmapOffStatus);
			}

			if (nStatus & AXIS_STATU_STOP)
			{
				ui.LB_Status_Stop->setPixmap(m_qPixmapOnStatus);
			}
			else
			{
				ui.LB_Status_Stop->setPixmap(m_qPixmapOffStatus);
			}
		}
		else if (i == 1)
		{
			ui.LB_PointFBVal->setText(QString::number(AutoUpdataInfo.at(i).dlData, 'g', 8));
		}
		else if (i == 2)
		{
			ui.LB_SpeedFBVal->setText(QString::number(AutoUpdataInfo.at(i).dlData, 'g', 8));
		}
	}
	return true;
}

void UI_MotorDebug::SkipCurrentPage()
{
	m_qVecAxisVal.clear();
	//获取当前页面数据
	ui.CB_AxisSelect->setCurrentIndex(0);
	SlotSwitchAxis(0);
}

bool UI_MotorDebug::SaveParamer()
{
	SlotSave();
	return true;
}
