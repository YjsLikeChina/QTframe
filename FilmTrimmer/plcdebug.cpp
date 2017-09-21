#include "plcdebug.h"
#include "DP_HCPLCInteraction.h"
PlcDebug* PlcDebug::m_pPLCdebug = NULL;
PlcDebug::PlcDebug(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
	connect(ui.pushButton_R, SIGNAL(clicked()), this, SLOT(SlotRead()));
	connect(ui.pushButton_W, SIGNAL(clicked()), this, SLOT(SlotWrite()));
}

PlcDebug::~PlcDebug() {

}

void PlcDebug::SlotRead()
{
	int addr = ui.lineEdit_RAddr->text().toInt();
	int addr_pos = ui.lineEdit_RPos->text().toInt();
	int ntype = ui.comboBox_R->currentIndex();
	if (ntype <= 2)
	{
		WORD wtmp = HC_PLC_INTERFACE.GetDWORDFromPLC(addr, EM_Type(ntype));
		QString str = QString::number((int)wtmp, 10);
		ui.lineEdit_RVal->setText(str);

	}
	else
	{
		int  alladdr = addr * 8 + addr_pos;
		BOOL btmp = HC_PLC_INTERFACE.GetBOOLFromPLC(alladdr, EM_Type(ntype));
		QString str = QString::number((int)btmp, 10);
		ui.lineEdit_RVal->setText(str);
	}
}
void PlcDebug::SlotWrite()
{
	int addr = ui.lineEdit_WAddr->text().toInt();
	int addr_pos = ui.lineEdit_WPos->text().toInt();
	int val  =  ui.lineEdit_WVal->text().toInt();
	int ntype = ui.comboBox_W->currentIndex();
	if (ntype <= 2)
	{
		WORD wtmp = HC_PLC_INTERFACE.SetDWORDToPLC(addr,bool(val), EM_Type(ntype));

	}
	else
	{
		int  alladdr = addr * 8 + addr_pos;
		BOOL btmp = HC_PLC_INTERFACE.SetBOOLToPLC(alladdr, bool(val), EM_Type(ntype));
	}
}

PlcDebug* PlcDebug::PLCdebugGetObject()
{
	if (m_pPLCdebug == NULL)
		m_pPLCdebug = new PlcDebug;
	return m_pPLCdebug;
}
