#pragma once
#include "UI_InterfaceBase.h"
#include <qwidget.h>
#include "ui_UI_AutoProduction.h"
#include <QVector>
#include <QPainter>
#include "CTRL_autoproduction.h"
#include "UI_WorkSpeedInputDialog.h"

class UI_AutoProduction :
	public QWidget, virtual public UI_InterfaceBase
{
	Q_OBJECT
public:
	UI_AutoProduction(QWidget* parent = Q_NULLPTR);
	~UI_AutoProduction();

	Ui::AutoProduWidget ui;

private:
	int m_nModuleNum;									//ģ�����
	QPainter *m_Painter;								//����ʵ��
	//UI_AutoDynamic  *UiAutoDynamic;					//��̬����
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
	QVector<ST_MODULEITEM> m_ModuleVector;				//ÿ��ģ���ָ���Լ�����ָ��
	QVector<ST_CHANGE_POINT> m_qVecModifyVal;			//�޸ĵ�ģ�������Լ�ֵ
	bool m_bAutoUpdateLock;								//�Զ�������
	QTreeWidgetItem* m_LastDoubleChickItem;				//��¼˫����Item
	CTRL_AutoProduction *m_pCtrlAutoProduction;
	QPixmap m_qPixmapOtherDataShow;						//�����б���ʾ
	QPixmap m_qPixmapOtherDataHide;						//�����б���ʾ
	QIcon m_qIconRunDirFW;								//��������
	QIcon m_qIconRunDirRE;								//��������
	QIcon m_qIconOnloadDirFW;							//˳ʱ��
	QIcon m_qIconOnloadDirRE;							//��ʱ��
	UI_WorkSpeedInputDlg* m_pWorkSpeedInputDlg;			//�����ٶ��趨
	int m_nLastSetWorkSpeed;							//���һ���趨�Ĺ����ٶ�
	CString m_cstrFilmTrimmerCfgPath;					//Ĭ�ϲ����ļ�·��
	/*����״̬ͼ��*/
	QPixmap m_qPixmapLaserStatusNoEnable;				//����δʹ��
	QPixmap m_qPixmapLaserStatusEnableNoConnect;		//ʹ��δ����
	QPixmap m_qPixmapLaserStatusConnectNoRun;			//����δ����
	QPixmap m_qPixmapLaserStatusRun;					//����������
	
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
	virtual void SkipCurrentPage();								//��ת����ǰҳ��
	void SetDefault(double MaxRe,double MinRe,double MaxPu,double MinPu,bool isOneTwo,bool PuisOneTwo);//����Ĭ������
	void SetButtonAttribute(bool bFlag);						//�����Զ����ҳ�水ť(TRUE��ʾ)
	bool SaveParamer();
protected Q_SLOTS:
	void SlotItemChanged(QTreeWidgetItem *item, int column);	//�������޸�

	void SlotRunDirection();									//���з���ѡ��
	void SlotOnloadDirection();									//�ž���

	void SlotOnloadClockwiseP();								//�ž���ת(��ѹ)
	void SlotOnloadClockwiseR();								//�ž���ת(�ͷ�)

	void SlotOnloadAnticlockwiseP();							//�ž�ת
	void SlotOnloadAnticlockwiseR();							//�ž�ת

	void SlotMainAxisClockwiseP();								//��ǣ����ת
	void SlotMainAxisClockwiseR();								//��ǣ����ת

	void SlotMainAxisAnticlockwiseP();							//��ǣ����ת
	void SlotMainAxisAnticlockwiseR();							//��ǣ����ת

	void SlotRecvClockwiseP();									//�վ���ת
	void SlotRecvClockwiseR();									//�վ���ת

	void SlotRecvAnticlockwiseP();								//�վ�ת
	void SlotRecvAnticlockwiseR();								//�վ�ת

	void SlotSetWorkSpeed();									//���ù����ٶ�

Q_SIGNALS:
	void SigItemChanged(int nModuleNum,int nChildNum,double dlData);
	void SigSetLaserParam(int nCard);							//���ü�����������źŷ��͵�FilmTrimmer
	void SigMachineRunDir(bool bFlag);							//���豸���з��򴫵ݸ�UI_FilmTrimmer
};

