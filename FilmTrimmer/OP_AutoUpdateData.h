#pragma once
#include <QThread>
#include "BaseDataType.h"
#include <QMutex>

class OP_AutoUpdateData :
	public QThread
{
	Q_OBJECT

public:
	OP_AutoUpdateData();
	~OP_AutoUpdateData();

private:
	int m_nCurPage;											//��ǰҳ��
	QMap<int, QList<ST_UPDATEDATA>>* m_qMapAutoUpdateData;	//�Զ����������б�
	bool m_bRunFlag;										//���б�־
	int m_nCurModule;										//��ǰģ��
	QStringList m_qslHistoryInfoFilePath;					//��ʷ��Ϣ�ļ�·��
	bool m_bReadHistoryInfoLock;							//��ȡ��ʷ�ļ�����
	QList<ST_UPDATEDATA> m_qLisAutoUpdata;					//�Զ����¹��������
	QStringList m_qslMachineAlarmList;						//�豸�����б�

private:
	void initVal();
	void run();
	void AutoUpdateCommon(QList<ST_UPDATEDATA>&);
	void AutoUpdateIOStatus(QList<ST_UPDATEDATA>&);
	void AutoUpdataHistoryInfo(QList<ST_UPDATEDATA>&);
	bool MachineAlarmUpdata(QStringList& qslAlarm);								//���±���
public:
	bool StartAutoUpdateDataThread(bool bFlag = true);							//bflagΪ��ʱ�����Զ�ˢ���߳�,flagΪ��ʱ�߳̽���
	void SwitchWorkTask(int nCurPage,int nCurModule);							//�л���������,
	void insertWorkTask(QMap<int, QList<ST_UPDATEDATA>>& qMapAutoUpdateData);	//����Զ������б�

Q_SIGNALS:
	void SigAutoProduction(QList<ST_UPDATEDATA>);								//�Զ�����ҳ��
	void SigIODebug(QList<ST_UPDATEDATA>);										//IO����
	void SigMotorDebug(QList<ST_UPDATEDATA>);									//�������
	void SigParameterSetting(QList<ST_UPDATEDATA>);								//��������
	void SigProductEditor(QList<ST_UPDATEDATA>);								//��Ʒ�༭
	void SigHistoricalInformation(QList<ST_UPDATEDATA>);						//��ʷ��Ϣ
	void SigMachineAlarm(QStringList qslMachineAlarm);							//�豸�����б�
};

