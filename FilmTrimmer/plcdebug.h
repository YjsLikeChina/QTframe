#pragma once
#include <QWidget>
#include "ui_UI_Plcdebug.h"

class PlcDebug : public QWidget {
	Q_OBJECT

public:
	PlcDebug(QWidget * parent = Q_NULLPTR);
	~PlcDebug();

private:
	Ui::PlcDebug ui;

public Q_SLOTS:
   //启动
    void SlotRead();
	void SlotWrite();
public:
	static PlcDebug *m_pPLCdebug;
	static PlcDebug* PLCdebugGetObject();
};
#define PLCADDRTEST (*(PlcDebug::PLCdebugGetObject()))