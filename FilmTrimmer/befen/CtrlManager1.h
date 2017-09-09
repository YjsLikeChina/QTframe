#pragma once
#include <QObject>
#include "CTRL_filmtrimmer.h"
#include "CTRL_autoproduction.h"
#include "UI_filmtrimmer.h"

class CtrlManager : public QObject {
	Q_OBJECT
public:
	CtrlManager(QObject * parent);
	~CtrlManager();
	void InitController();
	bool BindUI(UI_FilmTrimmer* pUI_FilmTrimmer);
	void InitConnect();
private:
	CTRL_FilmTrimmer    *m_pCTRL_FilmTrimmer;
	CTRL_AutoProduction *m_pCTRL_AutoProduction;
	UI_FilmTrimmer      *m_pUI_FilmTrimmer;
};

