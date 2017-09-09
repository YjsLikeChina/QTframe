#pragma once
#include <QObject>
#include "BaseDataType.h"
#include "DP_CfgInterface.hpp"
#include "UI_InterfaceBase.h"
#include "DP_HCPLCInteraction.h"
#include "OP_MachineSoftWareMain.h"
#include "UI_MessageBox.h"
#include "DP_LaserInteraction.h"
class CTRL_Base : public QObject {
	Q_OBJECT
public:
	CTRL_Base(QObject * parent);
	~CTRL_Base();
private:
	UI_InterfaceBase *m_pUI_Interface;				 //ui����ָ��
	DP_HCPLCInteraction *m_pHCPLCInteraction;		//PLC��дָ��
	DP_CfgInterface      *m_pCfgInerface;			//ģ���ļ���дָ��
public:
	BOOL SetUIInterface(UI_InterfaceBase *pUI_Interface);
	UI_InterfaceBase* GetUIInterface();
	DP_HCPLCInteraction* GetDpHCPLCInteraction();
	DP_CfgInterface* GetDpCfgInterface();
	void initvalue();
//�ۺ���
protected Q_SLOTS:
	void SlotAutoUpdateData(QList<ST_UPDATEDATA>  DataList);			//����ҳ��ҳ��
	
};
