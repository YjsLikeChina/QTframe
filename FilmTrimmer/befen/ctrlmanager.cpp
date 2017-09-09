#include "ctrlmanager.h"
#include <QMetaType>
CtrlManager::CtrlManager(QObject *parent)
	: QObject(parent)
{
	m_pCTRL_FilmTrimmer = NULL;
	m_pCTRL_AutoProduction = NULL;

	//初始化控制器类
	InitController();

	//注册参数类型  
	qRegisterMetaType<QList<ST_UPDATEDATA>>("QList<ST_UPDATEDATA>");
}

CtrlManager::~CtrlManager()
{

}

void CtrlManager::InitController()
{
	m_pCTRL_FilmTrimmer = new CTRL_FilmTrimmer;
	m_pCTRL_AutoProduction = new CTRL_AutoProduction;
	m_pCTRL_IODebug = new CTRL_IODebug;
}

bool CtrlManager::BindUI(UI_FilmTrimmer* pUI_FilmTrimmer)
{
	if (NULL == pUI_FilmTrimmer)
		return false;

	m_pUI_FilmTrimmer = pUI_FilmTrimmer;
	m_pCTRL_FilmTrimmer->SetUIInterface((UI_InterfaceBase*)(m_pUI_FilmTrimmer));
	m_pCTRL_AutoProduction->SetUIInterface((UI_InterfaceBase*)(m_pUI_FilmTrimmer->m_pAutoProduction));
	m_pCTRL_IODebug->SetUIInterface((UI_InterfaceBase*)(m_pUI_FilmTrimmer->m_pIODebug));
	return true;
}

void CtrlManager::InitConnect()
{
	//FilmTrimmer界面
	connect(m_pUI_FilmTrimmer, SIGNAL(SigSwitchPage(int, bool, QMap<QString, QString>&)),
		m_pCTRL_FilmTrimmer, SLOT(SlotSwitchPage(int, bool, QMap<QString, QString>&)));
	connect(m_pUI_FilmTrimmer, SIGNAL(SigMachineCtrl(EM_MACHINE_SIGNAL)),
		m_pCTRL_FilmTrimmer, SLOT(SlotMachineCtrl(EM_MACHINE_SIGNAL)));

	//AutoProduction界面
	connect(m_pUI_FilmTrimmer->m_pAutoProduction, SIGNAL(SigItemChanged(int, int, double)),
		m_pCTRL_AutoProduction, SLOT(SlotItemChanged(int, int, double)));
	//IODebug界面
	connect(MACHINECTRL.m_pAutoUpdateData, SIGNAL(SigAutoUpdateData(QList<ST_UPDATEDATA>)),
		m_pCTRL_AutoProduction, SLOT(SlotAutoUpdateData(QList<ST_UPDATEDATA>)));
	//OP_AutoUpdateData工作线程
	connect(MACHINECTRL.m_pAutoUpdateData, SIGNAL(SigAutoUpdateData(QList<ST_UPDATEDATA>)),
		m_pCTRL_AutoProduction, SLOT(SlotAutoUpdateData(QList<ST_UPDATEDATA>)));
}
