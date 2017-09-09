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
	QButtonGroup* m_pButtonGruop;						//页面切换buttongroup
	bool m_bParamModifyFlag;							//参数是否被修改
	QVector<ST_CHANGE_POINT> m_qVecModifyVal;			//被修改的参数
	int m_nCurPageItem;									//当前页面ID
	QString m_qstrAlarmList;							//报警信息列表
	int m_nAlarmCurPoint;								//报警滚动位置
	QMap<int, UI_InterfaceBase*> m_qMapWidgetInfo;		//存放每个页面信息
	QMap<int, QVector<ST_MODULE>> m_qMapPageModuleInfo;	//模组信息
	int m_nRunDirection;								//运行方向
	int m_nOnloadDirection;								//放卷方向
	CTRL_FilmTrimmer *m_pCtrlFilmTrimmer;               //Controller指针
	QTimer* m_pUserTimer;								//用户管理权限定时器
	QTimer* m_pSystemTimeTimer;							//系统时间更新
	QIcon m_qIconRunDirFW;								//正向运行
	QIcon m_qIconRunDirRE;								//反向运行
	QIcon m_qIconOnloadDirFW;							//顺时针
	QIcon m_qIconOnloadDirRE;							//逆时针

private:
	void initVal();
	void initUI();
	void initConnect();
	bool eventFilter(QObject *obj, QEvent *ev);
	void initPageModule();																			//初始化每个页面模块
	void AddModule();																				//添加页面模块
	bool insertModule(int nModuleItem, QString qstrPageName, QString qstrIcon, QWidget* pageWidget);//添加模组
	bool GetPageConfigInfo();
	bool SwitchPage(bool flag, int nPageItem);														//切换切面
	bool SetCtrlShow(bool bFlag);																	//设置启停复位显示(TRUE)隐藏(FALSE)

public:
	//页面实例
	UI_AutoProduction* m_pAutoProduction;
	UI_IODebug* m_pIODebug;
	UI_MotorDebug* m_pMotorDebug;
	UI_ParameterSetting* m_pParameterSetting;
	UI_ProductEditor* m_pProductEditor;
	UI_HistoricalInformation* m_pHistoricalInformation;

public:
	bool AutoUpdateData(const QString qstrAlarmInfo);								//更新报警
	void SetModuleInfo(int nPage, QVector<ST_MODULE>& ModuleInfo);					//获取模组信息
	void SetMachineRunModel(int nModel);											//设置设备运行模式(手自动)1为自动，0为手动
	void SetMachineRunDirection(int nDir);											//设置设备运行方向(1为正向,0为反向)
	void SetMachineOnloadDirection(int OnloadDirection);							//设置放卷方向(1为顺时针,0为逆时针)

protected Q_SLOTS:
	void SlotSwitchPage(int nPageItem);												//切换页面槽函数
	void SlotMachineStart();
	void SlotMachineReset();
	void SlotMachineStop();
	void SlotMachineEStop();
	void SlotRunDirection();														//运行方向选择
	void SlotOnloadDirection();														//放卷方向
	void SlotUserLogin();															//用户登录
	void SlotUserTypeUpdata();														//用户权限更新
	void SlotUpdataSystemtime();													//更新系统时间
//	void SlotOnloadConfigFinish();													//配置文件加载完毕

//Q_SIGNALS:
//	void SigSwitchPage(int nNextPage, bool bFlag, QMap<QString, QString>& ModifyVal);//切换页面信号,点击退出时下一个页面为-1
//	void SigMachineCtrl(EM_MACHINE_SIGNAL emCtrl);									 //设备控制
};

#endif // FILMTRIMMER_H
