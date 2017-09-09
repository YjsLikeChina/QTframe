#pragma once
#include "UI_InterfaceBase.h"
#include <qwidget.h>
#include "ui_UI_ProductEditor.h"
#include "CTRL_producteditor.h"

class UI_ProductEditor :
	public QWidget, virtual public UI_InterfaceBase
{
	Q_OBJECT

public:
	UI_ProductEditor(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
	~UI_ProductEditor();

private:
	Ui::ProductEditorWidget ui;
	QVector<ST_CHANGE_POINT> m_qVecPkgModifyInfo; //修改的参数
	QString m_qstrIconFile;
	QPushButton* m_pAddStepButton;				//添加极耳间距Button
	QButtonGroup m_ButtonGroup;					//删除极耳间距的ButtonGroup
	QTreeWidgetItem* m_qrwStepItem;				//极耳间距Item
	QVector<ST_MODULEITEM> m_ModuleVector;		//每个模组的指针以及子项指针
	bool m_bAddStepLock;
	CTRL_ProductEditor* m_pProductEditor;		//Ctrl指针
	QListWidgetItem* m_pCurrentSelPkgItem;		//点击不同产品时，记录当前选中的Item
	QVector<double> m_qVecLaserStepDist;			//极耳间距

private:
	void initVal();
	void initUI();
	void initConnect();
	void ShowSimpleProduictEditor(int laser); //显示简版产品设置界面
protected Q_SLOTS:
	void SlotSetCurrentPackage();								//设置当前产品
	void SlotCopyPackage();										//复制产品
	void SlotDeletePackage();									//删除产品
	void SlotNewPackage();										//新建产品
	void SlotSavePackage();										//保存产品信息
	void SlotAddPackageStep();									//添加产品极耳间距
	void SlotSwitchPackage(QListWidgetItem *item);				//切换产品
	void SlotDeleteStep(int nButton);							//删除极耳间距
	void SlotItemChanged(QTreeWidgetItem* item, int nColumn);	//产品参数被修改

public:
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal);//获取有修改的数据
	bool insertModule(QVector<ST_MODULE>* cfgModuleInfo);				//添加模组
	bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);				//自动更新
	virtual void SkipCurrentPage();										//跳转到当前页面
	void UpdataPackageInfo(QVector<ST_CHANGE_POINT> qliOnloadpkg,QString LaserFileName,QString strPkgName);		//导入产品信息，
	void AddNewPackage(QString& strNewPkgName);							//产品名列表添加新产品名字

//Q_SIGNALS:
//	void SigSetCurrentPackage(QString qstrPkgName); //设置当前产品
//	void SigCopyPackage(QString qstrPkgName);		//产品复制
//	void SigDeletePackage(QString qstrPkgName);		//删除产品
//	void SigNewPackage(QString qstrPkgName);		//新建产品
//	void SigSavePackage(QMap<QString, QString>);	//产品参数保存
//	void SigSwitchPackage(QString qstrPkgName);		//产品切换
};

