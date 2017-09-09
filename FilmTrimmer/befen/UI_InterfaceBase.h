#pragma once
#include "BaseDataType.h"
#include <qwidget.h>
#include "UI_Simpledialog.h"
class UI_InterfaceBase
	//: public QWidget
{
public:
	UI_InterfaceBase(QWidget* parent = Q_NULLPTR);
	~UI_InterfaceBase();
private:
	QWidget* m_pQObject;

public:
	SimPleDialog * m_UiSimPleDialog;
	virtual void SkipCurrentPage();										//跳转页面
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal);//获取修改过的参数
	virtual bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);			//自动更新
	virtual bool AutoUpdateData(int nIndex, QStringList qstrListInfo);		//自动更新(历史信息页面)
	virtual bool AutoUpdateData(const QString qstrAlarmInfo);				//自动更新(Filmtrimmer更新报警)
	virtual bool insertModule(QVector<ST_MODULE>*);							//添加模组
	void temp22();
};

