#pragma once
#include <QThread>
#include "UI_MessageBox.h"
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
	QString m_qstrMachineCfgPath;		//Machine.cfg·��
	CString m_cstrMachineCfgPath;		//Machine.cfg·��
	QString m_qstrPackageFilePath;
	UI_MessageBox* m_pMessageBox;
	bool m_bSetCurPkgLock;				//���õ�ǰ��Ʒ��
	bool m_bSoftwareIsFirstStart;		//�Ƿ��һ�������豸
	bool m_bComputerCard;				//�Ƿ�Ϊ�ѻ���
	bool m_bIsAutoMoveToPos;			//����Ƿ��Զ���λ
	QVector<ST_MODULE> m_qVecPackageInfo;//��ǰ��Ʒ�ļ�����
	bool m_bMachineCurModel;			//�豸��ǰģʽ(1�Զ�ģʽ,0Ϊ�ֶ�ģʽ)
	int m_nMachineCurWork;				//�豸��ǰ��������
private:
	void InitVal();
	void run();
	bool MachineCtrlStart();			//�豸����
	bool MachineCtrlStop();				//�豸ֹͣ
	bool MachineCtrlReset();			//�豸��λ
	bool MachineCtrlEStop();			//�豸��ͣ
	bool MachineCtrlMaintain();			//�豸ά��
	bool SetCurrentPackage();			//���õ�ǰ��Ʒ

	bool RunProcess();					//�Զ������߳�
	bool SetOtherData();				//��������������Ʒ�޹ص�����(��������ҳ��)
	bool SetMotorSpeed();				//���õ���ٶȵȲ���
	bool GetMotorIsInplace();			//�жϵ���Ƿ񵽴﹤��λ
	bool GetIsAutoMovePos();			//�ж��Ƿ�ѡ����Զ���λ

public:
	bool InitMachineCtrl();
	bool SetMachineStatus(int nModel,bool bFlag);	//�����豸״̬,�豸״̬�����Զ�ģʽ(1�Զ�ģʽ,0Ϊ�ֶ�ģʽ)
	bool SetCrurentPackage(QString qstrCurPkgName);

Q_SIGNALS:
	void SigMachineStatusResult(bool);		//�豸�������
	void SigMachineResetResult(bool);		//�豸��λ���
	void SigSetCurrentPackage(bool);		//���õ�ǰ��Ʒ
};

