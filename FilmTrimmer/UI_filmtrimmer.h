#ifndef FILMTRIMMER_H
#define FILMTRIMMER_H

#include <QtWidgets/QMainWindow>
#include "ui_UI_filmtrimmer.h"
#include "UI_InterfaceBase.h"
#include "UI_Maintenance.h"
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
#include "UI_MachineErrorList.h"

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
	int m_nLastPageItem;
	QString m_qstrAlarmList;							//������Ϣ�б�
	int m_nAlarmCurPoint;								//��������λ��
	QMap<int, UI_InterfaceBase*> m_qMapWidgetInfo;		//���ÿ��ҳ����Ϣ
	QMap<int, QVector<ST_MODULE>> m_qMapPageModuleInfo;	//ģ����Ϣ
	int m_nRunDirection;								//���з���
	int m_nOnloadDirection;								//�ž���
	CTRL_FilmTrimmer *m_pCtrlFilmTrimmer;               //Controllerָ��
	QTimer* m_pUserTimer;								//�û�����Ȩ�޶�ʱ��
	QTimer* m_pSystemTimeTimer;							//ϵͳʱ�����
	QString m_qstrIconFile;								//ICon·��
	bool m_bMachineModel;								//�豸ģʽ(���Զ�)
	QPixmap m_qPixmapGreen;								//��������ɫ
	QPixmap m_qPixmapYellow;							//��ɫ
	QPixmap m_qPixmapGray;								//��ɫ
	QPixmap m_qPixmapRed;								//��ɫ
	QVector<UI_InterfaceBase> m_PAllPage;
	UI_MachineErrorList* m_pMachineErrorList;
	bool    m_isEventFilter = false;							//�ж��Ƿ�������eventFilterʱ�ڣ����������ѭ��

private:
	void initVal();
	void initUI();
	void initConnect();
	bool eventFilter(QObject *obj, QEvent *ev);
	void initPageModule();																			//��ʼ��ÿ��ҳ��ģ��
	void AddModule();																				//���ҳ��ģ��
	bool insertModule(int nModuleItem, QString qstrPageName, QString qstrIcon, QWidget* pageWidget);//���ģ��
	bool GetPageConfigInfo();
	bool SwitchPage(bool flag, int nNextPage,int nPrePage);											//�л�����
	bool SetCtrlShow(bool bFlag);																	//������ͣ��λ��ʾ(TRUE)����(FALSE)
	bool SetAlarmStatusTool(MACHINE_STATUSTOOL_COLOR emColor);										//���ñ�������ɫ
	bool ShowMachineAlarm();

public:
	//ҳ��ʵ��
	UI_Maintenance* m_pMachineMaintenance;
	UI_AutoProduction* m_pAutoProduction;
	UI_IODebug* m_pIODebug;
	UI_MotorDebug* m_pMotorDebug;
	UI_ParameterSetting* m_pParameterSetting;
	UI_ProductEditor* m_pProductEditor;
	UI_HistoricalInformation* m_pHistoricalInformation;

public:
	void SetModuleInfo(int nPage, QVector<ST_MODULE>& ModuleInfo);		//��ȡģ����Ϣ
	void SetMachineRunDirection(int nDir);								//�����豸���з���(1Ϊ����,0Ϊ����)
	void SetMachineOnloadDirection(int OnloadDirection);				//���÷ž���(1Ϊ˳ʱ��,0Ϊ��ʱ��)
	bool GetMachineModel();												//��ȡ�豸���Զ�ģʽ(1Ϊ�Զ���0Ϊ�ֶ�)


protected Q_SLOTS:
	void SlotSwitchPage(int nPageItem, bool Switchover =true);									//�л�ҳ��ۺ��� ����2Ϊ���������л�����ǿ���л����磺��Ȩ���û��ڸ�Ȩ���û�ҳ���¼��ǿת���Զ�����ҳ��
	void SlotMachineStart();
	void SlotMachineReset();
	void SlotMachineStop();
	void SlotMachineEStop();
	void SlotUserLogin();												//�û���¼
	void SlotUserTypeUpdata();											//�û�Ȩ�޸���
	void SlotUpdataSystemtime();										//����ϵͳʱ��
	void SlotMachineRunModel(bool bModel);								//�����豸����ģʽ(���Զ�)1Ϊ�Զ���0Ϊ�ֶ�
	void SlotMachineRunDir(bool bFlag);
	bool SlotAutoUpdateData(QString qstrAlarmList,QString qstrErrorList);//���±���
	bool SlotSetStatusFlagTest(QString strStatusIndicate, QString strOperIndicate, MACHINE_STATUSTOOL_COLOR AlarmStatus);//����״̬��������ʾ����
	void SlotExitMaintenance();
	
	void SlotSetPutPid();
	void SlotSetGetPid();
	void SlotSetLaserParam(int nCard);
	void SlotNewUserLogin();

Q_SIGNALS:
	void SigMachineCtrl(EM_MACHINE_SIGNAL emEvent);
};

#endif // FILMTRIMMER_H
