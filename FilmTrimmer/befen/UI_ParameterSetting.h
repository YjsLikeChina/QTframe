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
	QVector<ST_CHANGE_POINT> m_qVecModifyVal;	//修改的模组名称以及值
	QVector<ST_MODULEITEM> m_ModuleVector;		//模组指针及子项指针
	bool m_bAutoUpdateLock;						//自动更新锁
	QMap<int, int>	m_qMapDataOrder;			//
	QMap<int, int>	m_qMapBoolOrder;

	CTRL_ParameterSet* m_pParameterSet;			//Ctrl指针
private:
	void initVal();
	void initUI();
	void initConnect();

protected Q_SLOTS:
	void SlotParameSave();
	void SlotDataItemChanged(QTreeWidgetItem* item, int column);//数据类型的参数被修改
	void SlotBoolItemChanged(QTreeWidgetItem* item, int);

public:
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& mapModifyVal);//获取有修改的数据
	bool insertModule(QVector<ST_MODULE>*);								//添加模组
	bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);				//自动更新
	virtual void SkipCurrentPage();										//跳转到当前页面
	void ShowSimpleParameterSetting(int UpOrPu);						// 弹框PID设置  

//Q_SIGNALS:
//	void SigSave(QMap<QString, QString>);
};

