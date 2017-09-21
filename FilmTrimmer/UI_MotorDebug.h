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
	bool m_bParamModify;										//点击移动、前进、后退时
	QVector<ST_CHANGE_POINT> m_qVecAxisVal;						//轴参数
	CTRL_MotorDebug* m_pCtrlMotorDebug;
	QPixmap m_qPixmapOnStatus;
	QPixmap m_qPixmapOffStatus;

private:
	void initUI();
	void initVal();
	void initConnect();

protected Q_SLOTS:
	void SlotSave();											//保存
	void SlotAbsMove();											//绝对移动
	void SlotAdvanceMovePress();								//前进
	void SlotAdvanceMoveRelease();								//前进
	void SlotRetreatMovePress();								//后退
	void SlotRetreatMoveRelease();								//后退
	void SlotGotoHome();										//归零
	void SlotEnable();											//使能
	void SlotStop();											//停止
	void SlotCleanAlarm();										//报警清除
	void SlotSwitchAxis(int nAxis);								//切换轴
	
public:
	bool insertModule(QVector<ST_MODULE>*);								//添加模组
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& VecModifyVal);//获取有修改的数据
	bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);				//自动更新
	virtual void SkipCurrentPage();										//跳转到当前页面
	bool SaveParamer();

//Q_SIGNALS:
//	void SigAxisSave(QMap<QString, QString>);
//	void SigAxisMove(int nAxisNum, double nDist, EM_AXIS_MOVE_SIGNAL MoveModel,bool RunDir = true);	//轴移动信号,RunDir使用点动时为运行方向，真为顺时针
//	void SigAxisCtrl(int nAxisNum,EM_AXIS_CTRL_SIGNAL CtrlModel);									//轴使能、停止、报警清除
};

