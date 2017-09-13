#pragma once
#include <QThread>
#include "BaseDataType.h"

class OP_MachineStatusCtrl
	: QThread
{
	Q_OBJECT

public:
	OP_MachineStatusCtrl();
	~OP_MachineStatusCtrl();

private:
	QString m_qstrCurPkgName;			//��Ʒ�ļ���
	int m_nCurMachineStatus;			//��ǰ�豸״̬
	QString m_qstrFilmCfgPath;			//FilmTrimmer.cfg·��
	CString m_cstrFilmCfgPath;			//FilmTrimmer.cfg·��
	QString m_qstrPackageFilePath;
	bool m_bSetCurPkgLock;				//���õ�ǰ��Ʒ��
	bool m_bSoftwareIsFirstStart;		//�Ƿ��һ�������豸
	bool m_bComputerCard;				//�Ƿ�Ϊ�ѻ���
	bool m_bIsAutoMoveToPos;			//����Ƿ��Զ���λ
	QVector<ST_MODULE> m_qVecPackageInfo;//��ǰ��Ʒ�ļ�����
	MACHINE_STATUS m_emMachineStatusCtrl;//�豸״̬��
	ST_LASER_DATA m_stCurLaserData;		//��ǰ��������
	bool m_bMachineLasetStatus;			//�豸���һ��״̬
	bool m_bMachineRunDir;				//�豸���з���
	QString m_qstrHistoryFilePath;		//��ʷ�ļ�·��
	ST_VALUECFG m_stCurSpeed;				//��ǰ(����)�ٶȵ�ַ

	//�豸״̬�����Ʊ���
	MACHINE_TASK m_emMachineTask;		//�豸��Ҫִ�е�����

	//��ͣ��λ��ͣ��ַ
	ST_VALUECFG m_stStart;
	ST_VALUECFG m_stReset;
	ST_VALUECFG m_stStop;
	ST_VALUECFG m_stEStop;
	ST_VALUECFG m_stMaintain;

private:
	void InitVal();
	void run();
	bool MachineCtrlStart();			//�豸����
	bool MachineCtrlStop();				//�豸ֹͣ
	bool MachineCtrlReset();			//�豸��λ
	bool MachineCtrlEStop();			//�豸��ͣ
	bool MachineCtrlMaintain();			//�豸ά��
	bool MachineCtrlInit();				//�豸��ʼ��
	bool MachineCtrlCleanAlarm();		//�������
	bool SetCurrentPackage();			//���õ�ǰ��Ʒ

	bool SetOtherData();				//��������������Ʒ�޹ص�����(��������ҳ��)
	bool SetMotorSpeed();				//���õ���ٶȵȲ���
	bool GetMotorIsInplace();			//�жϵ���Ƿ񵽴﹤��λ
	bool GetIsAutoMovePos();			//�ж��Ƿ�ѡ����Զ���λ

	bool CheckMachineStop();
	void WriteWorkHistoryLog();
	void WriteAlarmHistoryLog();

public:
	bool InitMachineWork();
	bool SetCrurentPackage(QString qstrCurPkgName);
	bool SetMachineTask(MACHINE_TASK emMachineTask);
	ST_LASER_DATA GetCurLaserData();	//��ȡ��ǰ��������
	void SetLaserData(ST_LASER_DATA stLaserData);
	void SetMachineRunDir(bool bFlag);

Q_SIGNALS:
	void SigMachineStatusResult(bool);		//�豸�������
	void SigMachineResetResult(bool);		//�豸��λ���
	void SigSetCurrentPackage(bool);		//���õ�ǰ��Ʒ
};

