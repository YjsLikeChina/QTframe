#include"CTRL_Base.h"
CTRL_Base::CTRL_Base(QObject * parent)
{
	m_pUI_Interface = NULL;
	qRegisterMetaType<QList<ST_UPDATEDATA>>("QList<ST_UPDATEDATA>");
}

CTRL_Base::~CTRL_Base()
{

}

BOOL CTRL_Base::SetUIInterface(UI_InterfaceBase *pUI_Interface)
{
	if (NULL == pUI_Interface)
		return FALSE;

	m_pUI_Interface = pUI_Interface;
	    return TRUE;
}

UI_InterfaceBase * CTRL_Base::GetUIInterface()
{
	return m_pUI_Interface; 
}

DP_HCPLCInteraction * CTRL_Base::GetDpHCPLCInteraction()
{
	return m_pHCPLCInteraction;
}

DP_CfgInterface * CTRL_Base::GetDpCfgInterface()
{
	return m_pCfgInerface;
}

void CTRL_Base::initvalue()
{
	m_pHCPLCInteraction = DP_HCPLCInteraction::GetInstanceObj();
	m_pCfgInerface = DP_CfgInterface::GetInstanceObj();
}

void CTRL_Base::SlotAutoUpdateData(QList<ST_UPDATEDATA> DataList)
{
	GetUIInterface()->AutoUpdateData(DataList);
}
