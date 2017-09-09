#ifndef FILMTRIMMER_H
#define FILMTRIMMER_H

#include <QtWidgets/QMainWindow>
#include "ui_UI_filmtrimmer.h"
#include "UI_InterfaceBase.h"
#include "UI_AutoProduction.h"
#include "UI_IODebug.h"
#include "UI_MotorDebug.h"
#include "UI_ParameterSetting.h"
#include "UI_ProductEditor.h"
#include "UI_HistoricalInformation.h"
#include <QButtonGroup>
#include <QMap>
#include "CTRL_filmtrimmer.h"
#include <QTimer>
#include "UI_InterfaceBase.h"

class UI_FilmTrimmer : public QMainWindow,virtual public UI_InterfaceBase
{
	Q_OBJECT
public:
	UI_FilmTrimmer(QMainWindow* parentWin = 0);
	~UI_FilmTrimmer();

private:
	Ui::FrameWidget ui;
	QButtonGroup* m_pButtonGruop;						//ҳ���л�buttongroup
	bool m_bParamModifyFlag;							//�����Ƿ��޸�
	QVector<ST_CHANGE_POINT> m_qVecModifyVal;			//���޸ĵĲ���
	int m_nCurPageItem;									//��ǰҳ��ID
	QString m_qstrAlarmList;							//������Ϣ�б�
	int m_nAlarmCurPoint;								//��������λ��
	QMap<int, UI_InterfaceBase*> m_qMapWidgetInfo;		//���ÿ��ҳ����Ϣ
	QMap<int, QVector<ST_MODULE>> m_qMapPageModuleInfo;	//ģ����Ϣ
	int m_nRunDirection;								//���з���
	int m_nOnloadDirection;								//�ž���
	CTRL_FilmTrimmer *m_pCtrlFilmTrimmer;               //Controllerָ��
	QTimer* m_pUserTimer;								//�û�����Ȩ�޶�ʱ��
	QTimer* m_pSystemTimeTimer;							//ϵͳʱ�����
	QIcon m_qIconRunDirFW;								//��������
	QIcon m_qIconRunDirRE;								//��������
	QIcon m_qIconOnloadDirFW;							//˳ʱ��
	QIcon m_qIconOnloadDirRE;							//��ʱ��

private:
	void initVal();
	void initUI();
	void initConnect();
	bool eventFilter(QObject *obj, QEvent *ev);
	void initPageModule();																			//��ʼ��ÿ��ҳ��ģ��
	void AddModule();																				//���ҳ��ģ��
	bool insertModule(int nModuleItem, QString qstrPageName, QString qstrIcon, QWidget* pageWidget);//���ģ��
	bool GetPageConfigInfo();
	bool SwitchPage(bool flag, int nPageItem);														//�л�����
	bool SetCtrlShow(bool bFlag);																	//������ͣ��λ��ʾ(TRUE)����(FALSE)

public:
	//ҳ��ʵ��
	UI_AutoProduction* m_pAutoProduction;
	UI_IODebug* m_pIODebug;
	UI_MotorDebug* m_pMotorDebug;
	UI_ParameterSetting* m_pParameterSetting;
	UI_ProductEditor* m_pProductEditor;
	UI_HistoricalInformation* m_pHistoricalInformation;

public:
	bool AutoUpdateData(const QString qstrAlarmInfo);								//���±���
	void SetModuleInfo(int nPage, QVector<ST_MODULE>& ModuleInfo);					//��ȡģ����Ϣ
	void SetMachineRunModel(int nModel);											//�����豸����ģʽ(���Զ�)1Ϊ�Զ���0Ϊ�ֶ�
	void SetMachineRunDirection(int nDir);											//�����豸���з���(1Ϊ����,0Ϊ����)
	void SetMachineOnloadDirection(int OnloadDirection);							//���÷ž���(1Ϊ˳ʱ��,0Ϊ��ʱ��)

protected Q_SLOTS:
	void SlotSwitchPage(int nPageItem);												//�л�ҳ��ۺ���
	void SlotMachineStart();
	void SlotMachineReset();
	void SlotMachineStop();
	void SlotMachineEStop();
	void SlotRunDirection();														//���з���ѡ��
	void SlotOnloadDirection();														//�ž���
	void SlotUserLogin();															//�û���¼
	void SlotUserTypeUpdata();														//�û�Ȩ�޸���
	void SlotUpdataSystemtime();													//����ϵͳʱ��
//	void SlotOnloadConfigFinish();													//�����ļ��������

//Q_SIGNALS:
//	void SigSwitchPage(int nNextPage, bool bFlag, QMap<QString, QString>& ModifyVal);//�л�ҳ���ź�,����˳�ʱ��һ��ҳ��Ϊ-1
//	void SigMachineCtrl(EM_MACHINE_SIGNAL emCtrl);									 //�豸����
};

#endif // FILMTRIMMER_H
