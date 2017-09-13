#include "OP_MachineSoftWareMain.h"
#include "UI_filmtrimmer.h"
#include <QtWidgets/QApplication>
#include "DP_HCPLCInteraction.h"
#include "QCUserManager.h"
#include "LogManager.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//Model
	MACHINECTRL.initTask();
	HC_PLC_INTERFACE.Init_HC_DLL();
	HC_PLC_INTERFACE.Connect_HC_PLC();

	//View
	UI_FilmTrimmer    FilmTrimmer;
	QObject::connect(MACHINECTRL.m_pFSM, SIGNAL(SigSetStatusFlagTest(QString, QString, MACHINE_STATUSTOOL_COLOR)), &FilmTrimmer, SLOT(SlotSetStatusFlagTest(QString, QString, MACHINE_STATUSTOOL_COLOR)));
	FilmTrimmer.show();
	a.installEventFilter(&FilmTrimmer);
	while (1)
	{
		QStringList UserNameAndType = USERMANAGER.Login();
		LOGSTR.SetCurSoftWarever(L"1.0.0.1");
		if (UserNameAndType.at(0) != "error")
		{
			LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: mian函数]_[函数名 : main]_{[操作: 登录用户][用户名：%1,权限：%2]").arg(UserNameAndType.at(0)).arg(UserNameAndType.at(1)));
			break;
		}
		USERMANAGER.LogOut();
	}
	return a.exec();
}
