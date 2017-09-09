#include "CtrlManager.h"

CtrlManager::CtrlManager(QObject * parent)
{
	m_pCTRL_FilmTrimmer    = NULL;
	m_pCTRL_AutoProduction = NULL;

	//初始化控制器类
	InitController();
}


CtrlManager::~CtrlManager()
{
}

void CtrlManager::InitController()
{
	m_pCTRL_FilmTrimmer     = new CTRL_FilmTrimmer;
	m_pCTRL_AutoProduction  = new CTRL_AutoProduction;
}

bool CtrlManager::BindUI(UI_FilmTrimmer* pUI_FilmTrimmer)
{
	if (NULL == pUI_FilmTrimmer)
		return false;

	m_pUI_FilmTrimmer = pUI_FilmTrimmer;
	m_pCTRL_FilmTrimmer->SetUIInterface((UI_InterfaceBase*)(m_pUI_FilmTrimmer));
	m_pCTRL_AutoProduction->SetUIInterface((UI_InterfaceBase*)(m_pUI_FilmTrimmer->m_pAutoProduction));

	return true;
}

void CtrlManager::InitConnect()
{
	//FilmTrimmer界面
	connect(m_pUI_FilmTrimmer, SIGNAL(SigSwitchPage(int nNextPage, bool bFlag, QMap<QString, QString>& ModifyVal)),
		m_pCTRL_FilmTrimmer, SLOT(SlotSwitchPage(int nNextPage, bool bFlag, QMap<QString, QString>& ModifyVal)));
	connect(m_pUI_FilmTrimmer, SIGNAL(SigMachineCtrl(EM_MACHINE_SIGNAL emCtrl)),
		m_pCTRL_FilmTrimmer, SLOT(SlotMachineCtrl(EM_MACHINE_SIGNAL emCtrl)));

	//AutoProduction界面
	connect(m_pUI_FilmTrimmer->m_pAutoProduction, SIGNAL(SigItemChanged(int nModuleNum, int nChildNum, double dlData)),
		m_pCTRL_AutoProduction, SLOT(SlotItemChanged(int nModuleNum, int nChildNum, double dlData)));
}