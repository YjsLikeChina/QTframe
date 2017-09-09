#pragma once
#include <QObject>
#include "OP_MachineSoftWareMain.h"
#include "CTRL_Base.h"
class CTRL_ParameterSet : public CTRL_Base {


public:
	CTRL_ParameterSet(QObject * parent = Q_NULLPTR);
	~CTRL_ParameterSet();

	bool SaveParmentterset(QVector<ST_CHANGE_POINT> VeChangePoint);	//保存数据
	void Initconnect();
	void InitVal();
private:
	
};
