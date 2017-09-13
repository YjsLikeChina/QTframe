#pragma once
#include "qwidget.h"
#include "ui_UI_MachineErrorList.h"
#include <QTimer>

class UI_MachineErrorList :
	public QWidget
{
	Q_OBJECT
public:
	UI_MachineErrorList(QWidget* parent = Q_NULLPTR,Qt::WindowFlags f = Qt::WindowFlags());
	~UI_MachineErrorList();
	void ShowWidget(QString);
	bool CloseWidget();

private:
	Ui::MachineErrorInfoList ui;
	void initVal();
	void initUI();
	void initConnect();
	QTimer* m_pTimer;
	QStringList m_strlistInfo;
	QString m_strLastErrorList;

public slots:
	void SlotCloseBtn();
	void SlotTimeOut();
};

