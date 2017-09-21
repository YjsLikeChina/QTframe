#pragma once
#include <QObject>
#include "BaseDataType.h"
#include "OP_AutoUpdateData.h"
#include "OP_MachineStatusCtrl.h"
#include <vector>
#include "DP_MotorCtrlInteraction.h"
#include "LogManager.h"
#include "OP_FSM.h"

class OP_MachineSoftWareMain
	: public QObject
{
	Q_OBJECT
public:
	~OP_MachineSoftWareMain();

private:
	int m_nCurentPage;											//��ǰҳ��
	QString m_qstrCfgPath;										//�����ļ�·��
	QMap<int, QList<ST_UPDATEDATA>> m_qMapAutoUpdateData;		//�Զ���������							//Filmtrimmer.cfg·��
public:
	//Work
	OP_AutoUpdateData* m_pAutoUpdateData;
	OP_MachineStatusCtrl* m_pMachineStatusCtrl;					//�豸��ͣ�����⡢��Ʒ�ȹ���
	OP_FSM* m_pFSM;
	std::vector<DP_MotorCtrlInteraction*> m_MotorList;			//����б�
private:
	OP_MachineSoftWareMain(QObject* parent = NULL);
	void initVal();
	void initConnect();
	void LoadModuleInfo();										//����ģ����Ϣ
	void LoadMotorInfo();                                       //���ص����Ϣ

																//��ȡ�Զ���������,nPage��������IO����\��ʷҳ��\����ҳ��
	bool GetAutoUpdateData(const QVector<ST_MODULE>& QVecSource,QList<ST_UPDATEDATA>& AutoUpdateData,int nPage = -1);
	bool m_bOnloadConfigFinish;									//�����ļ��������(UI_FilmTrimmer��OP_MachineCtrlOrAlarmStatus��ʹ��)
	
public:
	//�Զ�����ҳ��
	QVector<ST_MODULE> m_QveAutoProduction;						//�Զ�����ҳ��ģ����Ϣ
	QList<ST_UPDATEDATA> m_QliAutoProduction_AutoUpdateData;	//�Զ����µ�������Ϣ
																//�豸����ҳ��
	QVector<ST_MODULE> m_QveIODebug;							//IO����ҳ��ģ����Ϣ
	QVector<QList<ST_UPDATEDATA>> m_QliIODebug_AutoUpdateData;	//�Զ�����һ��ģ���Input //QList<ST_UPDATEDATA>һ��ģ��,QVector�а������ģ��
	ST_MODULE m_UpdateDataModule;								//�л�ҳ��ʱ���µ���ģ��,�������������
																//�������ҳ��
	QVector<ST_MODULE> m_QveMotorDebug;							//�������ģ����Ϣ
	QList<ST_UPDATEDATA> m_QliMotorDebug_AutoUpdateData;		//�Զ����µ�������Ϣ
																//��������ҳ��
	QVector<ST_MODULE> m_QveParameterSetting;					//��������ģ����Ϣ
	QList<ST_UPDATEDATA> m_QliParameterSetting_AutoUpdateData;	//�Զ����µ�������Ϣ
																//��Ʒ�༭
	QVector<ST_MODULE> m_QveProductEditor;						//��������ģ����Ϣ
	QList<ST_UPDATEDATA> m_QliProductEditor_AutoUpdateData;		//�Զ����µ�������Ϣ
																//��ʷ��Ϣ
	QVector<ST_MODULE> m_QveHistoricalInfo;						//��������ģ����Ϣ
	QList<ST_UPDATEDATA> m_QliHistoricalInfo_AutoUpdateData;	//�Զ����µ�������Ϣ

	QVector<QVector<ST_MODULE>> m_qVecAllPageData;				//����ҳ�����

	QVector<ST_MODULE> m_QveFilmParam;						//����Ĭ�ϲ���(FilmTrimmer),��һ��ΪĬ�ϲ�����˳����EM_FILM_DEFAULT_ORDER

	static OP_MachineSoftWareMain* m_pInstanceObj;
	QString ReturnPageCfgPath(EM_CHILDPAGEITEM emPageItem);		//���������ļ�����
	CLog *m_Clog;												//��־��д��

public:
	void initTask();											//��ʼ����������
	bool GetOnloadConfigStatus();								//��ȡ�����ļ�����״̬
	static OP_MachineSoftWareMain* GetInstanceObj();
	bool AllMotorGotoHome();									//���е������
	bool AllMotorMoveToPos(QVector<ST_MODULE> qVecMotorInfo);	//���е���ƶ���λ
	bool GetAllMotorIsOrigin();									//�ж���Ҫ�Զ���λ�����Ƿ�ӵ��ԭ��λ
	bool GetAllMotorInplace(ST_MODULE stModuleInfo);			//�жϵ���Ƿ�ȫ����λ

//Q_SIGNALS:
//	void SigOnloadConfigFinish();
};

#define MACHINECTRL (*OP_MachineSoftWareMain::GetInstanceObj())
#define MOTORSCTRL  (OP_MachineSoftWareMain::GetInstanceObj()->m_MotorList)
#define MACHINELOG	(OP_MachineSoftWareMain::GetInstanceObj()->m_Clog);