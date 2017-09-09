#pragma once
#include <QObject>
#include "CTRL_Base.h"
class CTRL_AutoProduction : public CTRL_Base {
	Q_OBJECT

public:
	CTRL_AutoProduction(QObject * parent = Q_NULLPTR);
	~CTRL_AutoProduction();
	void Initconnect(); 
	bool ItemChanged(QVector<ST_CHANGE_POINT> VeChangePoint); //参数修改
	//槽函数
protected Q_SLOTS:
	
};
