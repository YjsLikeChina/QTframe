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
	//�������״̬�����񡣡���������
	InsertTask(BEGIN_STATUS,RESET_EVENT,&OP_FSM::BeginToInitProc); //��ʼ������
	InsertTask(READY_STATUS, RESET_EVENT, &OP_FSM::InitToReadyProc); //��λ����
	InsertTask(READY_STATUS,START_EVENT,&OP_FSM::ReadyToRunProc);//��������
	InsertTask(RUN_STATUS, RESET_EVENT, &OP_FSM::AlarmCleanProc);//����ʱ�����������
	InsertTask(RUN_STATUS, STOP_EVENT, &OP_FSM::RunToStopProc);	//ֹͣ����
	InsertTask(RUN_STATUS, ESTOP_EVENT, &OP_FSM::RunToEStopProc);//��ͣ����
	InsertTask(ALARM_STATUS, RESET_EVENT, &OP_FSM::AlarmCleanProc);//�������
}

MACHINE_STATUS OP_FSM::GetCurStatus()
{
	//�����Ǵ�PLC��ȡ��ǰ״̬
	//�Ȼ�ȡ����״̬
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
	//�����Ǵ�PLC���������ȡ��ǰ�¼�
	//��PLC�л�ȡ״̬
	MACHINE_EVENT LoadPLCStatus = (MACHINE_EVENT)HC_PLC_INTERFACE.GetDWORDFromPLC(m_stMachineHardwareStatus.Addr.toInt(), m_stMachineHardwareStatus.Addr_Type);
	if (m_emPLCLasetEvnet != LoadPLCStatus)
	{
		m_emPLCLasetEvnet = LoadPLCStatus;
		return m_emPLCLasetEvnet;
	}

	//����λ����ȡ
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
	//��ȡ�豸��ǰ״̬
	MACHINE_STATUS emMachineStatus = GetCurStatus();
	//��ȡ��ǰ�豸�Ƿ�ӵ���µ��¼�
	MACHINE_EVENT emMachineEvent = GetCurEvent();

	TransferFSM(emMachineStatus, emMachineEvent);
	//����Film��״̬�����Լ�������ʾ
	QString qstrStatusTest;
	QString qstrOperTest;
	MACHINE_STATUSTOOL_COLOR nAlarmStatus = COLOR_GRAY;
	MACHINE_FLAG emFlag = GetCurFlag();
	switch (emMachineStatus)
	{
	case BEGIN_STATUS:
		{
			qstrStatusTest = QString::fromLocal8Bit("��ʼ״̬");
			break;
		}
	case INITIALIZATION_STATUS:
		{
			qstrStatusTest = QString::fromLocal8Bit("��ʼ��״̬\n");
			if (OPERATOR_ING == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("��ʼ��������");
				qstrOperTest = "";
			}
			else if (OPERATOR_END == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("��ʼ�����");
				qstrOperTest = QString::fromLocal8Bit("���л����Զ�״̬");
			}
			else if (OPERATOR_FAIL == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("��ʼ��ʧ��");
				qstrOperTest = QString::fromLocal8Bit("������λ");
				nAlarmStatus = COLOR_YELLOW;
			}
			else
			{
				qstrOperTest = QString::fromLocal8Bit("������λ");
			}
			break;
		}
	case READY_STATUS:
		{
			qstrStatusTest = QString::fromLocal8Bit("׼��״̬\n");
			if (OPERATOR_ING == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("׼����");
				qstrOperTest = "";
			}
			else if (OPERATOR_END == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("׼�����");
				qstrOperTest = QString::fromLocal8Bit("�豸������������");
			}
			else if (OPERATOR_FAIL == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("׼��ʧ��");
				qstrOperTest = QString::fromLocal8Bit("������λ");
				nAlarmStatus = COLOR_YELLOW;
			}
			else
			{
				qstrOperTest = QString::fromLocal8Bit("������λ");
			}
			break;
		}
	case RUN_STATUS:
		{
			qstrStatusTest = QString::fromLocal8Bit("����״̬\n");
			if (OPERATOR_ING == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("������");
				nAlarmStatus = COLOR_GREEN;
				qstrOperTest = "";
			}
			else if (OPERATOR_END == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("ֹͣ��");
				qstrOperTest = QString::fromLocal8Bit("�豸������������");
			}
			else if (OPERATOR_FAIL == emFlag)
			{
				qstrStatusTest += QString::fromLocal8Bit("׼��ʧ��");
				qstrOperTest = QString::fromLocal8Bit("������λ");
				nAlarmStatus = COLOR_YELLOW;
			}
			else
			{
				qstrOperTest = QString::fromLocal8Bit("������λ");
			}
			break;
		}
	case ALARM_STATUS:
		{
			qstrStatusTest = QString::fromLocal8Bit("����״̬");
			qstrOperTest = QString::fromLocal8Bit("������λ");
			nAlarmStatus = COLOR_RED;
			break;
		}
	default:
		break;
	}
	emit SigSetStatusFlagTest(qstrStatusTest, qstrOperTest,nAlarmStatus);
}
