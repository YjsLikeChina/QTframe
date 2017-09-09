#pragma once
#include "qdialog.h"
#include "ui_UI_MessageBox.h"
#include <QTimer>
#include <QVector>

struct ST_MessageBoxData
{
	QString message;
	int model;
	int time = 2000;
	bool streebutton;
};
enum EN_Resoult
{
	OK = 0,
	CANCEL ,
	COMPEL,
	NORESOULT
};
class UI_MessageBox :
	public QDialog
{
	Q_OBJECT
public:
	~UI_MessageBox();
private:
	UI_MessageBox();
	Ui::QMessageBox ui;
	void initConnect();
	void initVal();
	void initUI();
	bool Domodel(const QString qstrInfo, int Time); //模式对话框
	void NoDomodel(const QString qstrInfo, unsigned int nChokeTime = 2000); //非模式对话框
	EN_Resoult NewMessage(ST_MessageBoxData data);//队列弹出message
	bool m_bResult;
	QTimer* m_pTimeout;
	QVector<ST_MessageBoxData> m_STMessAgeData;
	int CurMessageDataNumber = 0;
	int m_CurStatius = 2;	//对应EM_DIALOG_MODEL中的NOMESSAGE

public:
	static UI_MessageBox* GetInstanceObj();
	static UI_MessageBox* m_pInstanceObj;

protected Q_SLOTS:
	void SlotOk();
	void SlotCancel();
	void SlotTimeout();

public Q_SLOTS:
	void SlotCloseDomodel();
	EN_Resoult SlotNewMessAgeBoxData(QString message, int model, int time = 2000, bool precedence = false,bool streeButton = false);
Q_SIGNALS:
	void SigNalMessAgeBoxData(QString message, int model, int time = 2000, bool precedence = false);
	void SigNalCloseMessageBox();	//关闭窗口
};

#define MESSAGEBOX (*UI_MessageBox::GetInstanceObj())
