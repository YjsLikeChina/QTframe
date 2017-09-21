#pragma once
#include "qdialog.h"
#include "ui_UI_StopCauseListDialog.h"
#include <QButtonGroup>
#include <QPushButton>

class My_PushButton : public QPushButton
{
public:
	My_PushButton(int nStopCard,QWidget* parent = Q_NULLPTR);
	~My_PushButton();
	int m_dwStopCord;
};

class UI_StopCauseListDialog :
	public QDialog
{
	Q_OBJECT
public:
	UI_StopCauseListDialog();
	~UI_StopCauseListDialog();

private:
	Ui::StopCauseListDialog ui;
	QButtonGroup* m_pStopList1ButtonGroup;
	QButtonGroup* m_pStopList2ButtonGroup;
	QButtonGroup* m_pStopList3ButtonGroup;
	QButtonGroup* m_pStopList4ButtonGroup;
	QButtonGroup* m_pStopList5ButtonGroup;
	QStringList m_qslStopCause1;
	QStringList m_qslStopCause2;
	QStringList m_qslStopCause3;
	QStringList m_qslStopCause4;
	QStringList m_qslStopCause5;

	int m_nSelStopCode = -1;
	QString m_qstrStopCause;

private:
	void InitUI();
	void InitVal();
	void InitConnect();

	protected slots:
	void SlotButtonGroup1Click(QAbstractButton *button);
	void SlotButtonGroup2Click(QAbstractButton *button);
	void SlotButtonGroup3Click(QAbstractButton *button);
	void SlotButtonGroup4Click(QAbstractButton *button);
	void SlotButtonGroup5Click(QAbstractButton *button);
	
public:
	//每一个参数中存放停机原因button的文字，停机编码,中间使用‘，’分隔
	void SetStopButton(QStringList qslStopCause1, QStringList qslStopCause2, QStringList qslStopCause3, QStringList qslStopCause4, QStringList qslStopCause5);
	void SetAlarmInfo(QString strAlarmInfo);

	bool DoModel(int& nStopCard,QString& strStopCause);	//参数返回停机编码以及停机原因
};

