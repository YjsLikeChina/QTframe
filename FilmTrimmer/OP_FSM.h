#pragma once
#include <vector>
#include <QObject>
#include "BaseDataType.h"

using namespace std;
//�豸״̬
/*
Ŀǰֻ�����˳�����״̬����û�м���С��״̬����־λ����Ҫȷ��
*/

class OP_FSM;

typedef bool (OP_FSM::*pFSMFun)();

//״̬��Item
typedef struct TAG_FSM_ITEM
{
	MACHINE_STATUS    CurStatus;	    //��ǰ״̬
	MACHINE_EVENT     CurEvent;	        //��ǰ�¼�
	pFSMFun           pTaskProc;	    //�¼�������ָ��
}FSM_ITEM;

class OP_FSM : public QObject
{
	Q_OBJECT
public:
	~OP_FSM(void);
	OP_FSM(void);

private:
	std::vector<FSM_ITEM> m_FSMList;    //״̬���б�
	MACHINE_EVENT m_emPCEvent;		//�豸��ͣ����
	MACHINE_EVENT m_emPLCLasetEvnet;	//PLC����豸�����¼�
	VALUECFG m_stMachineStatus;			//�豸��ǰ״̬
	VALUECFG m_stMachineStatusAlarm;	//�豸��ǰ״̬(����״̬)
	VALUECFG m_stMachineFlag;			//�豸״̬��־
	VALUECFG m_stMachineHardwareStatus;	//�豸Ӳ����ť״̬(��ͣ��λֹͣ��ͣ)

private:
	void InitVal();
	//�¼�������
	bool BeginToInitProc();	//���г�ʼ������
	bool InitToReadyProc();	//���и�λ���� 
	bool ReadyToRunProc();	//������������
	bool RunToStopProc();	//����ֹͣ����
	bool RunToEStopProc();	//���м�ͣ����
	bool AlarmCleanProc();	//���б����������

public:
	void InitFSM();                  //��ʼ��״̬��
	MACHINE_STATUS GetCurStatus();   //��ȡ��ǰ״̬
	bool GetCurAlarmStatus();		 //��ȡ�豸����״̬
	MACHINE_EVENT  GetCurEvent();    //��ȡ��ǰ�¼�
	MACHINE_FLAG   GetCurFlag();	 //��ȡ��ǰ��־
	void TransferFSM(MACHINE_STATUS MachineStatus,MACHINE_EVENT MachineEvent); //ǣ��״̬��
    void InsertTask(MACHINE_STATUS CurMachineStatus,MACHINE_EVENT MachineEvent,pFSMFun pTaskProc); //��������

	void GetMachineTask();

protected Q_SLOTS:
	void SlotMachineCtrl(EM_MACHINE_SIGNAL emEvent);

Q_SIGNALS:
	void SigSetStatusFlagTest(QString strStatusHint,QString strOperHint, MACHINE_STATUSTOOL_COLOR AlarmStatus);
};

