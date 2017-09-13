#pragma once
#include "qdialog.h"
#include "ui_UI_StopCauseListDialog.h"

class UI_StopCauseListDialog :
	public QDialog
{
	Q_OBJECT
public:
	UI_StopCauseListDialog();
	~UI_StopCauseListDialog();

private:
	Ui::StopCauseListDialog ui;

private:
	void InitUI();
	void InitConnect();

};

