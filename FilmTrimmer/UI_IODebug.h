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
	QString m_qstrStatusOn;									//IO状态图标
	QString m_qstrStatusOff;								//IO状态图标
	bool m_bAutoUpdateLock;
	QIcon m_OffStatuIcon;									//状态指示，关
	QIcon m_OnStatuIcon;									//状态指示，开
	int m_CurrentModule;									//当前模组号

	QVector<ST_MODULE>* m_qvecModuleInfo;
	CTRL_IODebug* m_PCtrlIODebug;							//ctrl指针

private:
	void initConnect();
	void initUI();
	void initVal();

public:
	bool insertModule(QVector<ST_MODULE>*);								//添加模组
	bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);				//自动更新(Input)
	virtual void SkipCurrentPage();										//跳转到该页面
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal);//获取有修改的数据

public Q_SLOTS:
	void SlotOutputClicked(QListWidgetItem *item);			//获取点击的输出点
	void SlotSwitchModule(QListWidgetItem *item);			//切换不同模组

//Q_SIGNALS:
//	void SigOutputClicked(int nModuleNum,int nButtonNum);	//点击输出点，发送信号，包含模组名及按钮位置
//	void SigModuleSwitch(int nModuleNum);					//切换不同模组，发送模组号
};

