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
	bool m_bFloatWindowIsMove;								//�Ƿ���й��ƶ�
	bool m_bFirstPress;
	Ui::FloatingWindow ui;

protected:
	bool eventFilter(QObject *watched, QEvent *event);		//�¼�����
	void mouseMoveEvent(QMouseEvent *ev);					//�������ƶ��¼�
	void mouseReleaseEvent(QMouseEvent *event);				//�������Ƿ��¼�

protected Q_SLOTS:
	void SlotMachineStart();								//�豸����
	void SlotMachineStop();									//�豸ֹͣ
	void SlotMachineReset();								//�豸��λ
	void SlotMachineEStop();								//�豸��ͣ 
	void SlotRunSchema();									//���Զ��л�
	void SlotRunDirection();								//���з���ѡ��
	void SlotOnloadDirection();								//�ž���

Q_SIGNALS:
	void SigMachineStatusCtrl(EM_MACHINE_SIGNAL emMachineStatus);//�����豸״̬
};

