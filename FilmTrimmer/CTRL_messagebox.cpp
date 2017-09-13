#include "UI_MessageBox.h"

CTRL_Messagebox* CTRL_Messagebox::m_pInstanceObj = NULL;

CTRL_Messagebox::CTRL_Messagebox(QObject *parent)
	: QObject(parent)
{
	UI_MESSAGEBOX.GetInstanceObj();
}

CTRL_Messagebox::~CTRL_Messagebox()
{
	
}

CTRL_Messagebox* CTRL_Messagebox::GetInstanceObj()
{
	if (NULL == m_pInstanceObj)
		m_pInstanceObj = new CTRL_Messagebox;

	return m_pInstanceObj;
}


void CTRL_Messagebox::initConnect()
{
	//connect(this, SIGNAL(SigNalMessAgeBoxData(QString, int, int)), this, SLOT(SlotMessageTransmitCreate(QString, int, int)));
	//connect(this, SIGNAL(SigNalCloseMessageBox()), this, SLOT(SlotMessageTransmitDelete()));
	connect(this, SIGNAL(SigNalMessAgeBoxData(QString, int, int, bool, DOMODELTYPE)), m_pMessagePoint, SLOT(SlotNewMessAgeBoxData1(QString, int, int, bool, DOMODELTYPE)), Qt::QueuedConnection);
	connect(this, SIGNAL(SigNalCloseMessageBox()), m_pMessagePoint, SLOT(SlotCloseDomodel()), Qt::QueuedConnection);
}

void CTRL_Messagebox::initVal(void* pTmp)
{
	m_pMessagePoint = (UI_MessageBox*)pTmp;
	qRegisterMetaType<DOMODELTYPE>("DOMODELTYPE");
	initConnect();
}

//void CTRL_Messagebox::SlotMessageTransmitCreate(QString message, int model, int time /*= 2000*/, bool precedence /*= false*/, DOMODELTYPE DomodelType /*= TWOBUTTON*/)
//{
//	//m_pMessageBox->SlotNewMessAgeBoxData(message, model, time, precedence, DomodelType);
//}
//
//void CTRL_Messagebox::SlotMessageTransmitDelete()
//{
//	m_pMessageBox->SlotCloseDomodel();
//}

void CTRL_Messagebox::SlotCloseDomodel()
{
	//m_pMessageBox->SlotCloseDomodel();
}

EN_Resoult CTRL_Messagebox::SlotNewMessAgeBoxData(QString message, int model, int time /*= 2000*/, bool precedence /*= false*/, DOMODELTYPE DomodelType /*= TWOBUTTON*/)
{
	//return m_pMessageBox->SlotNewMessAgeBoxData(message, model, time, precedence, DomodelType);
	return CANCEL;
}
