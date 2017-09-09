#pragma once
#include "UI_InterfaceBase.h"
#include "qwidget.h"
#include "ui_UI_AutoProduction.h"
#include "BaseDataType.h"
#include <QVector>
#include <QPainter>
#include "CTRL_autoproduction.h"

class UI_AutoProduction :
	public QWidget, virtual public UI_InterfaceBase
{
	Q_OBJECT

public:
	UI_AutoProduction(QWidget* parent = Q_NULLPTR);
	~UI_AutoProduction();

private:
	Ui::AutoProduWidget ui;
	int m_nModuleNum;											//ģ�����
	QPainter *m_Painter;										//����ʵ��
	//UI_AutoDynamic  *UiAutoDynamic;							//��̬����
	double m_ReMaxtension  =20000;
	double m_ReMintension =0 ;
	double m_ReCurtension=0;
	double m_PuMaxtension = 20000;
	double m_PuMintension = 0;
	double m_PuCurtension = 0;
	double m_ReRollingDiameter = 0;
	double m_PuRollingDiameter = 0;
	double m_WorkSpeed = 0;
	bool   m_isOneTwo = true;
	bool   m_PuisOneTwo = true;
	QVector<ST_MODULEITEM> m_ModuleVector;						//ÿ��ģ���ָ���Լ�����ָ��
	QVector<ST_CHANGE_POINT> m_qVecModifyVal;					//�޸ĵ�ģ�������Լ�ֵ
	bool m_bAutoUpdateLock;										//�Զ�������
	QTreeWidgetItem* m_LastDoubleChickItem;						//��¼˫����Item
	CTRL_AutoProduction *m_pCtrlAutoProduction;
private:
	void initConnect();
	void initUI();
	void initVal();
	void paintEvent(QPaintEvent*);
	void PaintElectronicMeter(double x, double y, double r, bool Release = true);
	void PaintConnectLine();
	bool eventFilter(QObject *obj, QEvent *ev);
	void DataListShowClick();									//��ʾ���������б�

public:
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal);//��ȡ���޸ĵ�����
	bool insertModule(QVector<ST_MODULE>* );					//���ģ��
	bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);		//�Զ�����
	virtual void SkipCurrentPage();										//��ת����ǰҳ��
	void SetDefault(double MaxRe,double MinRe,double MaxPu,double MinPu,bool isOneTwo,bool PuisOneTwo);//����Ĭ������
	void ShowSimpleWorkSpeed(); //��ʾ�����ٶ�����
	
protected Q_SLOTS:
	void SlotItemChanged(QTreeWidgetItem *item, int column);	//�������޸�

Q_SIGNALS:
	void SigItemChanged(int nModuleNum,int nChildNum,double dlData);
};

