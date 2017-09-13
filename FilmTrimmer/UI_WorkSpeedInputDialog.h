#pragma once
#include "qdialog.h"
#include "ui_UI_WorkSpeedInputDialog.h"
class UI_WorkSpeedInputDlg :
	public QDialog
{
	Q_OBJECT
public:
	UI_WorkSpeedInputDlg(QDialog* parent = Q_NULLPTR);
	~UI_WorkSpeedInputDlg();
	int DoModal(int);

private:
	Ui::WorkSpeedInputDialog ui;
	bool m_bFlag;
	void initVal();
	void initUI();
	void initConnect();

	public slots:
	void SlotOK();
	void SlotCancel();
};

