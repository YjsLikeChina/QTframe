#include "CTRL_filmtrimmer.h"

CTRL_FilmTrimmer::CTRL_FilmTrimmer(QObject * parent) : CTRL_Base(parent) {

	InitValue();
	InitConnect();
}

CTRL_FilmTrimmer::~CTRL_FilmTrimmer() {

}

EN_Resoult CTRL_FilmTrimmer::SwitchPage(int NextPage,bool bFlag)
{
	EN_Resoult reslout = NORESOULT;
	if (!bFlag)
	{
		MACHINECTRL.m_pAutoUpdateData->SwitchWorkTask(NextPage, 0);
		reslout = COMPEL;
	}
	else
	{
	 EN_Resoult resoult = MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("页面有数据修改,请注意是否保存！"),
		 0, 0, true,THREEBUTTON);
	 switch (resoult)
	 {
	 case OK:MACHINECTRL.m_pAutoUpdateData->SwitchWorkTask(NextPage, 0); reslout = OK; break;
	 case CANCEL:reslout = CANCEL;
		 break;
	 case COMPEL:MACHINECTRL.m_pAutoUpdateData->SwitchWorkTask(NextPage, 0);
		 reslout = COMPEL;
		 break;
	 case NORESOULT:MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("弹框异常，请联系售后人员"),
		 2000, 1);
		 reslout = NORESOULT;
		 break;
	 default:
		 reslout = NORESOULT;
		 break;
	 }
	}
	return reslout;
}

bool CTRL_FilmTrimmer::MachineCtrl(EM_MACHINE_SIGNAL emCtrl)
{
	return true;
}


void CTRL_FilmTrimmer::InitConnect()
{
	//connect(m_pUiFimeTrimmer, SIGNAL(SigSwitchPage(int, bool, QMap<QString, QString>&)), this, SLOT(ChangePage(int, bool, QMap<QString, QString>&)));//连接切换页面信号
}

void CTRL_FilmTrimmer::InitValue()
{

}

QString CTRL_FilmTrimmer::UserLogin()
{
	return "";
}

bool CTRL_FilmTrimmer::ResultUserName()
{
	return false;
}
