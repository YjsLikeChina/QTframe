#include "OP_FSM.h"
#include "DP_HCPLCInteraction.h"
#include "OP_MachineSoftWareMain.h"

OP_FSM::OP_FSM(void)
{
	InitVal();
}


void OP_FSM::InitVal()
{
	qRegisterMetaType<MACHINE_STATUSTOOL_COLOR>("MACHINE_STATUSTOOL_COLOR");
	m_stMachineStatus = MACHINECTRL.m_QveFilmParam.at(0).Value_.at(CTRL_MACHINE_STATUS);
	m_stMachineStatusAlarm = MACHINECTRL.m_QveFilmParam.at(0).Value_.at(CTRL_MACHINE_ALARM);
	m_stMachineFlag = MACHINECTRL.m_QveFilmParam.at(0).Value_.at(CTRL_MACHINE_FLAG);
	m_stMachineHardwareStatus = MACHINECTRL.m_QveFilmParam.at(0).Value_.at(CTRL_MACHINE_HARDWARE_STATUS);
	m_emPLCLasetEvnet = NULL_EVENT;
	m_emPCEvent = NULL_EVENT;
}

OP_FSM::~OP_FSM(void)
{
}

void OP_FSM::InitFSM()
{
	//这里插入状态机任务。。。待完善
	InsertTask(BEGIN_STATUS,RESET_EVENT,&OP_FSM::BeginToInitProc); //初始化任务
	InsertTask(READY_STATUS, RESET_EVENT, &OP_FSM::InitToReadyProc); //复位任务
	InsertTask(READY_STATUS,START_EVENT,&OP_FSM::ReadyToRunProc);//启动任务
	InsertTask(RUN_STATUS, RESET_EVENT, &OP_FSM::AlarmCleanProc);//运行时清除报警任务
	InsertTask(RUN_STATUS, STOP_EVENT, &OP_FSM::RunToStopProc);	//停止任务
	InsertTask(RUN_STATUS, ESTOP_EVENT, &OP_FSM::RunToEStopProc);//急停任务
	InsertTask(ALARM_STATUS, RESET_EVENT, &OP_FSM::AlarmCleanProc);//报警清除
}

MACHINE_STATUS OP_FSM::GetCurStatus()
{
	//这里是从PLC获取当前状态
	//先获取报警状态
	if (HC_PLC_INTERFACE.GetBOOLFromPLC(m_stMachineStatusAlarm.Addr.toInt(), m_stMachineStatusAlarm.Addr_Type))
	{
		return ALARM_STATUS;
	}

	return  (MACHINE_STATUS)HC_PLC_INTERFACE.GetDWORDFromPLC(m_stMachineStatus.Addr.toInt(),m_stMachineStatus.Addr_Type);
}

bool OP_FSM::GetCurAlarmStatus()
{
	return HC_PLC_INTERFACE.GetBOOLFromPLC(m_stMachineStatusAlarm.Addr.toInt(), m_stMachineStatusAlarm.Addr_Type);
}

MACHINE_EVENT OP_FSM::GetCurEvent()
{
	//这里是从PLC或者软件获取当前事件
	//从PLC中获取状态
	MACHINE_EVENT LoadPLCStatus = (MACHINE_EVENT)HC_PLC_INTERFACE.GetDWORDFromPLC(m_stMachineHardwareStatus.Addr.toInt(), m_stMachineHardwareStatus.Addr_Type);
	if (m_emPLCLasetEvnet != LoadPLCStatus)
	{
		m_emPLCLasetEvnet = LoadPLCStatus;
		return m_emPLCLasetEvnet;
	}

	//从上位机获取
	if (NULL_EVENT != m_emPCEvent)
	{
		MACHINE_EVENT emTmp = m_emPCEvent;
		m_emPCEvent = NULL_EVENT;
		return emTmp;
	}
	return NULL_EVENT;
}

MACHINE_FLAG OP_FSM::GetCurFlag()
{
	return (MACHINE_FLAG)HC_PLC_INTERFACE.GetDWORDFromPLC(m_stMachineFlag.Addr.toInt(), m_stMachineFlag.Addr_Type);
}

void OP_FSM::TransferFSM(MACHINE_STATUS MachineStatus, MACHINE_EVENT MachineEvent)
{
	for (int i = 0; i < m_FSMList.size(); i++)
	{
		if ((m_FSMList[i].CurEvent == MachineEvent)
			&& (m_FSMList[i].CurStatus == MachineStatus))
		{
			pFSMFun CurFun = m_FSMList[i].pTaskProc;
            (this->*CurFun)();
		}
	}
}

bool OP_FSM::BeginToInitProc()
{
	return MACHINECTRL.m_pMachineStatusCtrl->SetMachineTask(MACHINE_INIT_TASK);
}

bool OP_FSM::InitToReadyProc()
{
	return MACHINECTRL.m_pMachineStatusCtrl->SetMachineTask(MACHINE_RESET_TASK);
}

bool OP_FSM::ReadyToRunProc()
{
	return MACHINECTRL.m_pMachineStatusCtrl->SetMachineTask(MACHINE_START_TASK);
}

bool OP_FSM::RunToStopProc()
{
	return MACHINECTRL.m_pMachineStatusCtrl->SetMachineTask(MACHINE_STOP_TASK);
}

bool OP_FSM::RunToEStopProc()
{
	return MACHINECTRL.m_pMachineStatusCtrl->SetMachineTask(MACHINE_STOP_TASK);
}

bool OP_FSM::AlarmCleanProc()
{
	return MACHINECTRL.m_pMachineStatusCtrl->SetMachineTask(MACHINE_CLEAN_ALARM_TASK);
}

void OP_FSM::SlotMachineCtrl(EM_MACHINE_SIGNAL emEvent)
{
	switch (emEvent)
	{
	case MACHINE_START:
		m_emPCEvent = START_EVENT;
		break;
	case MACHINE_RESET:
		m_emPCEvent = RESET_EVENT;
		break;
	case MACHINE_STOP:
		m_emPCEvent = STOP_EVENT;
		break;
	case MACHINE_ESTOP:
		m_emPCEvent = ESTOP_EVENT;
		break;
	default:
		break;
	}
}

void OP_FSM::InsertTask(MACHINE_STATUS CurMachineStatus, MACHINE_EVENT MachineEvent, pFSMFun pTaskProc)
{
	FSM_ITEM Fsm_Item;
	Fsm_Item.CurStatus  = CurMachineStatus;
	Fsm_Item.CurEvent   = MachineEvent;
	Fsm_Item.pTaskProc  = pTaskProc;
	m_FSMList.push_back(Fsm_Item);
}

void OP_FSM::GetMachineTask()
{
	//获取设备当前状态
	MACHINE_STATUS emMachineStatus = GetCurStatus();
	//获取当前设备是否拥有新的事件
	MACHINE_EVENT emMachineEvent = GetCurEvent();

	TransferFSM(emMachineStatus, emMachineEvent);
	//设置Film上状态显现以及操作提示
	QString qstrStatusTest;
	QString qstrOperTest;
	MACHINE_STATUSTOOL_COLOR nAlarmStatus = COLOR_GRAY;
	MACHINE_FLAG emFlag = GetCurFlag();
	switch (emMachineStatus)
	{
	case BEGIN_STATUS:
		{
			qstrStatusTest = QString::fromLocal8Bit("开始状态");
			break;
		}
	case INITIALIZATION_STATUS:
		{
			qstrStatusTest = QString::fromLocal8Bit("初始化状态\n");
			if (OPERATOR_ING == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("初始化进行中");
				qstrOperTest = "";
			}
			else if (OPERATOR_END == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("初始化完成");
				qstrOperTest = QString::fromLocal8Bit("请切换到自动状态");
			}
			else if (OPERATOR_FAIL == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("初始化失败");
				qstrOperTest = QString::fromLocal8Bit("请点击复位");
				nAlarmStatus = COLOR_YELLOW;
			}
			else
			{
				qstrOperTest = QString::fromLocal8Bit("请点击复位");
			}
			break;
		}
	case READY_STATUS:
		{
			qstrStatusTest = QString::fromLocal8Bit("准备状态\n");
			if (OPERATOR_ING == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("准备中");
				qstrOperTest = "";
			}
			else if (OPERATOR_END == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("准备完成");
				qstrOperTest = QString::fromLocal8Bit("设备满足启动条件");
			}
			else if (OPERATOR_FAIL == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("准备失败");
				qstrOperTest = QString::fromLocal8Bit("请点击复位");
				nAlarmStatus = COLOR_YELLOW;
			}
			else
			{
				qstrOperTest = QString::fromLocal8Bit("请点击复位");
			}
			break;
		}
	case RUN_STATUS:
		{
			qstrStatusTest = QString::fromLocal8Bit("运行状态\n");
			if (OPERATOR_ING == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("运行中");
				nAlarmStatus = COLOR_GREEN;
				qstrOperTest = "";
			}
			else if (OPERATOR_END == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("停止中");
				qstrOperTest = QString::fromLocal8Bit("设备满足启动条件");
			}
			else if (OPERATOR_FAIL == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("准备失败");
				qstrOperTest = QString::fromLocal8Bit("请点击复位");
				nAlarmStatus = COLOR_YELLOW;
			}
			else
			{
				qstrOperTest = QString::fromLocal8Bit("请点击复位");
			}
			break;
		}
	case ALARM_STATUS:
		{
			qstrStatusTest = QString::fromLocal8Bit("报警状态");
			qstrOperTest = QString::fromLocal8Bit("请点击复位");
			nAlarmStatus = COLOR_RED;
			break;
		}
	default:
		break;
	}
	emit SigSetStatusFlagTest(qstrStatusTest, qstrOperTest,nAlarmStatus);
}
