#pragma once
#include "qdialog.h"
#include "ui_UI_MessageBox.h"
//#include "UI_MessageBox.h"
#include <QTimer>
#include <QVector>

enum DOMODELTYPE //domodel类型枚举
{
	TWOBUTTON,
	THREEBUTTON,
	NOBUTTON
};

enum EN_Resoult //返回值枚举
{
	OK = 0,
	CANCEL,
	COMPEL,
	NORESOULT
};

struct ST_MessageBoxData  //消息结构体
{
	QString message;
	int model;
	int time = 2000;
	DOMODELTYPE DoModelType;
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
	bool isOhterMessageData();//判断是否还有消息未弹出
	EN_Resoult Domodel(const QString qstrInfo, int Time, DOMODELTYPE ); //模式对话框
	void NoDomodel(const QString qstrInfo, unsigned int nChokeTime = 2000); //非模式对话框
	EN_Resoult NewMessage(ST_MessageBoxData data);//队列弹出message
	EN_Resoult m_bResult; //DOMODEL返回结果
	QTimer* m_pTimeout; 
	QVector<ST_MessageBoxData> m_STMessAgeData; //消息容器
	int CurMessageDataNumber = 0; //默认处理序号
	int m_CurStatius = 2;	//对应EM_DIALOG_MODEL中的NOMESSAGE
	//CTRL_Messagebox* m_pCtrlMessageBox;

public:
	static UI_MessageBox* GetInstanceObj();
	static UI_MessageBox* m_pInstanceObj;

protected Q_SLOTS:
	void SlotOk();
	void SlotCancel();
	void SlotNever();
	void SlotTimeout();

public Q_SLOTS:
		//关闭窗口
	void SlotCloseDomodel();

	//1.消息字符串2.弹窗模式3.自动关闭时间(给0则没有），4.是否需要优先弹出，5.如果是domodel是哪一种domodel
	EN_Resoult SlotNewMessAgeBoxData(QString message, int model, int time = 2000, bool precedence = false,DOMODELTYPE DomodelType = TWOBUTTON);
	void SlotNewMessAgeBoxData1(QString message, int model, int time = 2000, bool precedence = false, DOMODELTYPE DomodelType = TWOBUTTON);
Q_SIGNALS:
	void SigNalMessAgeBoxData(QString message, int model, int time = 2000, bool precedence = false,DOMODELTYPE DomodelType = TWOBUTTON);
	void SigNalCloseMessageBox();	//关闭窗口
};

#define MESSAGEBOX (*UI_MessageBox::GetInstanceObj())
