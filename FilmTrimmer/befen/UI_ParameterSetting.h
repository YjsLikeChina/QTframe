#pragma once
#include "UI_InterfaceBase.h"
#include <qwidget.h>
#include "ui_UI_ParameterSetting.h"
#include "CTRL_parameterset.h"

class UI_ParameterSetting :
	public QWidget,virtual public UI_InterfaceBase
{
	Q_OBJECT
public:
	UI_ParameterSetting(QWidget* parent = Q_NULLPTR,Qt::WindowFlags f = Qt::WindowFlags());
	~UI_ParameterSetting();

	
private:
	Ui::ParameterSettingWidget ui;
	QVector<ST_CHANGE_POINT> m_qVecModifyVal;	//�޸ĵ�ģ�������Լ�ֵ
	QVector<ST_MODULEITEM> m_ModuleVector;		//ģ��ָ�뼰����ָ��
	bool m_bAutoUpdateLock;						//�Զ�������
	QMap<int, int>	m_qMapDataOrder;			//
	QMap<int, int>	m_qMapBoolOrder;

	CTRL_ParameterSet* m_pParameterSet;			//Ctrlָ��
private:
	void initVal();
	void initUI();
	void initConnect();

protected Q_SLOTS:
	void SlotParameSave();
	void SlotDataItemChanged(QTreeWidgetItem* item, int column);//�������͵Ĳ������޸�
	void SlotBoolItemChanged(QTreeWidgetItem* item, int);

public:
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& mapModifyVal);//��ȡ���޸ĵ�����
	bool insertModule(QVector<ST_MODULE>*);								//���ģ��
	bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);				//�Զ�����
	virtual void SkipCurrentPage();										//��ת����ǰҳ��
	void ShowSimpleParameterSetting(int UpOrPu);						// ����PID����  

//Q_SIGNALS:
//	void SigSave(QMap<QString, QString>);
};

