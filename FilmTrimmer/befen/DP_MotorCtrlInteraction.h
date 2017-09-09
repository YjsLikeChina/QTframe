#pragma once
#include <QObject>
#include "BaseDataType.h"
#include "DP_HCPLCInteraction.h"
#include <QThread>

enum MOTOR_MOVE_CTRL
{
	MOVE_GOTOHOME = 0,	//����
	MOVE_TOPOS,		//��λ
};

class DP_MotorCtrlInteraction;

class MotorCtrlThread
	:public QThread
{
	Q_OBJECT
public:
	~MotorCtrlThread();
private:
	MotorCtrlThread(DP_MotorCtrlInteraction*);
	void run();
	void SetMotorRunModel(double dlDist,MOTOR_MOVE_CTRL MoveType);
	MOTOR_MOVE_CTRL m_emMoveCtrl;
	double m_dlMoveDist;
	DP_MotorCtrlInteraction* m_pMotorCtrlInteraction;
	friend DP_MotorCtrlInteraction;
};


class DP_MotorCtrlInteraction
	:public QObject
{
	Q_OBJECT
public:
	DP_MotorCtrlInteraction();
	~DP_MotorCtrlInteraction();

private:
	QVector<ST_VALUECFG> m_qVecMotorsInfo;

private:
	bool m_bIsMoveing;													//�Ƿ��е�����ƶ�
	int m_nMotorNum;													//������
	QString m_qstrAxisName;												//������
	int m_nAxisAttribute;												//������
	MotorCtrlThread* m_pMotorMoveThread;								//����ƶ��߳�
	double m_dlMoveDist;
	friend MotorCtrlThread;

private:
	void MotorMove(double dlDist, EM_AXIS_MOVE_SIGNAL emMoveModel = ABSOLUTE_MOVE);	//
	void MotorGotoHome();

public:
	bool	InitMotorsInfo(int nAxis,QVector<ST_VALUECFG> MotorsInfo);
	bool	SetMotorGotoHome();
	bool	SetMotorMove(double dlDist, EM_AXIS_MOVE_SIGNAL emMoveModel = ABSOLUTE_MOVE, bool bRunDir = false, bool flag = false); //�����ƶ�
	bool	SetMotorEnable(bool bAutoGetCurrentStatus = true, bool bEnableStatu = false);//���õ��ʹ��
	bool	SetMotorStop(bool bAutoGetCurrentStatus = true, bool bRunStatu = false);	//���õ������״̬
	bool	SetMotorAlarmClean();										//�������
	int		GetMotorStatus();											//��ȡ���״̬
	bool	GetMotorEanble();											//���ߵ��ʹ��״̬
	double	GetMotorCurrentPos();										//��ȡ�����ǰλ��
	double	GetMotorCurrnetSpeed();										//��ȡ��ǰ����ٶ�
	bool	GetMoveStatus();											//�ж��Ƿ������ƶ���
	bool	GetAxisAttribute(QString& qstrAxisName,int& nAxisAttribute);//��ȡ�����ơ�����
};


