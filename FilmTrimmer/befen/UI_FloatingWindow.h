#pragma once
#include "qwidget.h"
#include "ui_UI_FloatingWindow.h"
#include "BaseDataType.h"
#include <QMouseEvent>

class UI_FloatingWindow :
	public QWidget
{
	Q_OBJECT

public:
	UI_FloatingWindow();
	~UI_FloatingWindow();

private:
	bool m_bFloatWindowIsMove;								//是否进行过移动
	bool m_bFirstPress;
	Ui::FloatingWindow ui;

protected:
	bool eventFilter(QObject *watched, QEvent *event);		//事件监听
	void mouseMoveEvent(QMouseEvent *ev);					//监控鼠标移动事件
	void mouseReleaseEvent(QMouseEvent *event);				//监控鼠标是否事件

protected Q_SLOTS:
	void SlotMachineStart();								//设备启动
	void SlotMachineStop();									//设备停止
	void SlotMachineReset();								//设备复位
	void SlotMachineEStop();								//设备急停 
	void SlotRunSchema();									//手自动切换
	void SlotRunDirection();								//运行方向选择
	void SlotOnloadDirection();								//放卷方向

Q_SIGNALS:
	void SigMachineStatusCtrl(EM_MACHINE_SIGNAL emMachineStatus);//控制设备状态
};

