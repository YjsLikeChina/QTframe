#include "OP_MachineSoftWareMain.h"
#include "UI_filmtrimmer.h"
#include <QtWidgets/QApplication>
#include "DP_HCPLCInteraction.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	//Model
	MACHINECTRL.initTask();
	HC_PLC_INTERFACE.Init_HC_DLL();
	HC_PLC_INTERFACE.Connect_HC_PLC();

	//View
	UI_FilmTrimmer    FilmTrimmer;
	FilmTrimmer.show();
	return a.exec();
}
