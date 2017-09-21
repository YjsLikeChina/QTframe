#pragma once
#include "UI_InterfaceBase.h"
#include <qwidget.h>
#include "ui_UI_MotorDebug.h"
#include "CTRL_motordebug.h"
#include <QPixmap>

class UI_MotorDebug :
	public QWidget,virtual public UI_InterfaceBase
{
	Q_OBJECT
public:
	UI_MotorDebug(QWidget* parent = Q_NULLPTR,Qt::WindowFlags f = Qt::WindowFlags());
	~UI_MotorDebug();

private:
	Ui::MotorDebugWidget ui;
	bool m_bParamModify;										//����ƶ���ǰ��������ʱ
	QVector<ST_CHANGE_POINT> m_qVecAxisVal;						//�����
	CTRL_MotorDebug* m_pCtrlMotorDebug;
	QPixmap m_qPixmapOnStatus;
	QPixmap m_qPixmapOffStatus;

private:
	void initUI();
	void initVal();
	void initConnect();

protected Q_SLOTS:
	void SlotSave();											//����
	void SlotAbsMove();											//�����ƶ�
	void SlotAdvanceMovePress();								//ǰ��
	void SlotAdvanceMoveRelease();								//ǰ��
	void SlotRetreatMovePress();								//����
	void SlotRetreatMoveRelease();								//����
	void SlotGotoHome();										//����
	void SlotEnable();											//ʹ��
	void SlotStop();											//ֹͣ
	void SlotCleanAlarm();										//�������
	void SlotSwitchAxis(int nAxis);								//�л���
	
public:
	bool insertModule(QVector<ST_MODULE>*);								//���ģ��
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& VecModifyVal);//��ȡ���޸ĵ�����
	bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);				//�Զ�����
	virtual void SkipCurrentPage();										//��ת����ǰҳ��
	bool SaveParamer();

//Q_SIGNALS:
//	void SigAxisSave(QMap<QString, QString>);
//	void SigAxisMove(int nAxisNum, double nDist, EM_AXIS_MOVE_SIGNAL MoveModel,bool RunDir = true);	//���ƶ��ź�,RunDirʹ�õ㶯ʱΪ���з�����Ϊ˳ʱ��
//	void SigAxisCtrl(int nAxisNum,EM_AXIS_CTRL_SIGNAL CtrlModel);									//��ʹ�ܡ�ֹͣ���������
};

