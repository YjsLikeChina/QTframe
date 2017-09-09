#pragma once
#include "UI_InterfaceBase.h"
#include <qwidget.h>
#include "ui_UI_IODebug.h"
#include "BaseDataType.h"
#include "CTRL_iodebug.h"
#include <QIcon>

class UI_IODebug :
	public QWidget,virtual public UI_InterfaceBase
{
	Q_OBJECT

public:
	UI_IODebug(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
	~UI_IODebug();

private: 
	Ui::IODebugWidget ui;
	int m_nModuleNum;
	QString m_qstrStatusOn;									//IO״̬ͼ��
	QString m_qstrStatusOff;								//IO״̬ͼ��
	bool m_bAutoUpdateLock;
	QIcon m_OffStatuIcon;									//״ָ̬ʾ����
	QIcon m_OnStatuIcon;									//״ָ̬ʾ����
	int m_CurrentModule;									//��ǰģ���

	QVector<ST_MODULE>* m_qvecModuleInfo;
	CTRL_IODebug* m_PCtrlIODebug;							//ctrlָ��

private:
	void initConnect();
	void initUI();
	void initVal();

public:
	bool insertModule(QVector<ST_MODULE>*);								//���ģ��
	bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);				//�Զ�����(Input)
	virtual void SkipCurrentPage();										//��ת����ҳ��
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal);//��ȡ���޸ĵ�����

public Q_SLOTS:
	void SlotOutputClicked(QListWidgetItem *item);			//��ȡ����������
	void SlotSwitchModule(QListWidgetItem *item);			//�л���ͬģ��

//Q_SIGNALS:
//	void SigOutputClicked(int nModuleNum,int nButtonNum);	//�������㣬�����źţ�����ģ��������ťλ��
//	void SigModuleSwitch(int nModuleNum);					//�л���ͬģ�飬����ģ���
};

