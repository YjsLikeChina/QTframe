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
	int m_nModuleNum;									//模组个数
	QPainter *m_Painter;								//画笔实例
	//UI_AutoDynamic  *UiAutoDynamic;					//动态窗口
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
	QVector<ST_MODULEITEM> m_ModuleVector;				//每个模组的指针以及子项指针
	QVector<ST_CHANGE_POINT> m_qVecModifyVal;			//修改的模组名称以及值
	bool m_bAutoUpdateLock;								//自动更新锁
	QTreeWidgetItem* m_LastDoubleChickItem;				//记录双击的Item
	CTRL_AutoProduction *m_pCtrlAutoProduction;
	QPixmap m_qPixmapOtherDataShow;						//数据列表显示
	QPixmap m_qPixmapOtherDataHide;						//数据列表显示
	QIcon m_qIconRunDirFW;								//正向运行
	QIcon m_qIconRunDirRE;								//反向运行
	QIcon m_qIconOnloadDirFW;							//顺时针
	QIcon m_qIconOnloadDirRE;							//逆时针
	UI_WorkSpeedInputDlg* m_pWorkSpeedInputDlg;			//工作速度设定
	int m_nLastSetWorkSpeed;							//最后一次设定的工作速度
	CString m_cstrFilmTrimmerCfgPath;					//默认参数文件路径
	/*激光状态图标*/
	QPixmap m_qPixmapLaserStatusNoEnable;				//激光未使能
	QPixmap m_qPixmapLaserStatusEnableNoConnect;		//使能未连接
	QPixmap m_qPixmapLaserStatusConnectNoRun;			//连接未工作
	QPixmap m_qPixmapLaserStatusRun;					//激光运行中
	
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
	virtual void SkipCurrentPage();								//跳转到当前页面
	void SetDefault(double MaxRe,double MinRe,double MaxPu,double MinPu,bool isOneTwo,bool PuisOneTwo);//设置默认数据
	void SetButtonAttribute(bool bFlag);						//设置自动伸出页面按钮(TRUE显示)
	bool SaveParamer();
protected Q_SLOTS:
	void SlotItemChanged(QTreeWidgetItem *item, int column);	//参数被修改

	void SlotRunDirection();									//运行方向选择
	void SlotOnloadDirection();									//放卷方向

	void SlotOnloadClockwiseP();								//放卷正转(下压)
	void SlotOnloadClockwiseR();								//放卷正转(释放)

	void SlotOnloadAnticlockwiseP();							//放卷反转
	void SlotOnloadAnticlockwiseR();							//放卷反转

	void SlotMainAxisClockwiseP();								//主牵引正转
	void SlotMainAxisClockwiseR();								//主牵引正转

	void SlotMainAxisAnticlockwiseP();							//主牵引反转
	void SlotMainAxisAnticlockwiseR();							//主牵引反转

	void SlotRecvClockwiseP();									//收卷正转
	void SlotRecvClockwiseR();									//收卷正转

	void SlotRecvAnticlockwiseP();								//收卷反转
	void SlotRecvAnticlockwiseR();								//收卷反转

	void SlotSetWorkSpeed();									//设置工作速度

Q_SIGNALS:
	void SigItemChanged(int nModuleNum,int nChildNum,double dlData);
	void SigSetLaserParam(int nCard);							//设置激光参数，将信号发送到FilmTrimmer
	void SigMachineRunDir(bool bFlag);							//将设备运行方向传递给UI_FilmTrimmer
};

