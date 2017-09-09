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
	int m_nModuleNum;											//模组个数
	QPainter *m_Painter;										//画笔实例
	//UI_AutoDynamic  *UiAutoDynamic;							//动态窗口
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
	QVector<ST_MODULEITEM> m_ModuleVector;						//每个模组的指针以及子项指针
	QVector<ST_CHANGE_POINT> m_qVecModifyVal;					//修改的模组名称以及值
	bool m_bAutoUpdateLock;										//自动更新锁
	QTreeWidgetItem* m_LastDoubleChickItem;						//记录双击的Item
	CTRL_AutoProduction *m_pCtrlAutoProduction;
private:
	void initConnect();
	void initUI();
	void initVal();
	void paintEvent(QPaintEvent*);
	void PaintElectronicMeter(double x, double y, double r, bool Release = true);
	void PaintConnectLine();
	bool eventFilter(QObject *obj, QEvent *ev);
	void DataListShowClick();									//显示隐藏数据列表

public:
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal);//获取有修改的数据
	bool insertModule(QVector<ST_MODULE>* );					//添加模组
	bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);		//自动更新
	virtual void SkipCurrentPage();										//跳转到当前页面
	void SetDefault(double MaxRe,double MinRe,double MaxPu,double MinPu,bool isOneTwo,bool PuisOneTwo);//设置默认数据
	void ShowSimpleWorkSpeed(); //显示工作速度设置
	
protected Q_SLOTS:
	void SlotItemChanged(QTreeWidgetItem *item, int column);	//参数被修改

Q_SIGNALS:
	void SigItemChanged(int nModuleNum,int nChildNum,double dlData);
};

