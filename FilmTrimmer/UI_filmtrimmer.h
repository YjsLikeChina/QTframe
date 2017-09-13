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
	QButtonGroup* m_pButtonGruop;						//页面切换buttongroup
	bool m_bParamModifyFlag;							//参数是否被修改
	QVector<ST_CHANGE_POINT> m_qVecModifyVal;			//被修改的参数
	int m_nCurPageItem;									//当前页面ID
	int m_nLastPageItem;
	QString m_qstrAlarmList;							//报警信息列表
	int m_nAlarmCurPoint;								//报警滚动位置
	QMap<int, UI_InterfaceBase*> m_qMapWidgetInfo;		//存放每个页面信息
	QMap<int, QVector<ST_MODULE>> m_qMapPageModuleInfo;	//模组信息
	int m_nRunDirection;								//运行方向
	int m_nOnloadDirection;								//放卷方向
	CTRL_FilmTrimmer *m_pCtrlFilmTrimmer;               //Controller指针
	QTimer* m_pUserTimer;								//用户管理权限定时器
	QTimer* m_pSystemTimeTimer;							//系统时间更新
	QString m_qstrIconFile;								//ICon路径
	bool m_bMachineModel;								//设备模式(手自动)
	QPixmap m_qPixmapGreen;								//报警栏绿色
	QPixmap m_qPixmapYellow;							//黄色
	QPixmap m_qPixmapGray;								//灰色
	QPixmap m_qPixmapRed;								//红色
	QVector<UI_InterfaceBase> m_PAllPage;
	UI_MachineErrorList* m_pMachineErrorList;
	bool    m_isEventFilter = false;							//判断是否正处于eventFilter时期，以免造成死循环

private:
	void initVal();
	void initUI();
	void initConnect();
	bool eventFilter(QObject *obj, QEvent *ev);
	void initPageModule();																			//初始化每个页面模块
	void AddModule();																				//添加页面模块
	bool insertModule(int nModuleItem, QString qstrPageName, QString qstrIcon, QWidget* pageWidget);//添加模组
	bool GetPageConfigInfo();
	bool SwitchPage(bool flag, int nNextPage,int nPrePage);											//切换切面
	bool SetCtrlShow(bool bFlag);																	//设置启停复位显示(TRUE)隐藏(FALSE)
	bool SetAlarmStatusTool(MACHINE_STATUSTOOL_COLOR emColor);										//设置报警栏颜色
	bool ShowMachineAlarm();

public:
	//页面实例
	UI_Maintenance* m_pMachineMaintenance;
	UI_AutoProduction* m_pAutoProduction;
	UI_IODebug* m_pIODebug;
	UI_MotorDebug* m_pMotorDebug;
	UI_ParameterSetting* m_pParameterSetting;
	UI_ProductEditor* m_pProductEditor;
	UI_HistoricalInformation* m_pHistoricalInformation;

public:
	void SetModuleInfo(int nPage, QVector<ST_MODULE>& ModuleInfo);		//获取模组信息
	void SetMachineRunDirection(int nDir);								//设置设备运行方向(1为正向,0为反向)
	void SetMachineOnloadDirection(int OnloadDirection);				//设置放卷方向(1为顺时针,0为逆时针)
	bool GetMachineModel();												//获取设备手自动模式(1为自动，0为手动)


protected Q_SLOTS:
	void SlotSwitchPage(int nPageItem, bool Switchover =true);									//切换页面槽函数 参数2为代表正常切换还是强制切换，如：低权限用户在高权限用户页面登录则强转到自动生产页面
	void SlotMachineStart();
	void SlotMachineReset();
	void SlotMachineStop();
	void SlotMachineEStop();
	void SlotUserLogin();												//用户登录
	void SlotUserTypeUpdata();											//用户权限更新
	void SlotUpdataSystemtime();										//更新系统时间
	void SlotMachineRunModel(bool bModel);								//设置设备运行模式(手自动)1为自动，0为手动
	void SlotMachineRunDir(bool bFlag);
	bool SlotAutoUpdateData(QString qstrAlarmList,QString qstrErrorList);//更新报警
	bool SlotSetStatusFlagTest(QString strStatusIndicate, QString strOperIndicate, MACHINE_STATUSTOOL_COLOR AlarmStatus);//设置状态、操作提示文字
	void SlotExitMaintenance();
	
	void SlotSetPutPid();
	void SlotSetGetPid();
	void SlotSetLaserParam(int nCard);
	void SlotNewUserLogin();

Q_SIGNALS:
	void SigMachineCtrl(EM_MACHINE_SIGNAL emEvent);
};

#endif // FILMTRIMMER_H
