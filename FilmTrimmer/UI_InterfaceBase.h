#pragma once
#include "BaseDataType.h"
#include <qwidget.h>
#include <QLineEdit>
class UI_InterfaceBase
	//: public QWidget
{
public:
	UI_InterfaceBase(QWidget* parent = Q_NULLPTR);
	~UI_InterfaceBase();
private:
	QWidget* m_pQObject;
public:

	bool isChanged = false;

	virtual void SkipCurrentPage();											//跳转页面
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal);	//获取修改过的参数
	virtual bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);			//自动更新
	virtual bool AutoUpdateData(int nIndex, QStringList qstrListInfo);		//自动更新(历史信息页面)
	virtual bool AutoUpdateData(const QString qstrAlarmInfo);				//自动更新(Filmtrimmer更新报警)
	virtual bool insertModule(QVector<ST_MODULE>*);							//添加模组
	virtual bool SaveParamer();
};

class UI_LineEdit
	:public QLineEdit
{
public:
	UI_LineEdit(int i, int j, QWidget* parent = Q_NULLPTR);
	UI_LineEdit(QWidget* parent = Q_NULLPTR);
	~UI_LineEdit();

	int nModuleNum;
	int nChildNum;

private:
	void initUI();

public:
	void SetStyleSheet(QFont qfont, QRegExp regx);//设置字体、字体颜色、大小
};

