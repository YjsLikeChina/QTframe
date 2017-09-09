#pragma once
#include "qdialog.h"
#include "ui_UI_MessageBox.h"
//#include "UI_MessageBox.h"
#include <QTimer>
#include <QVector>

enum DOMODELTYPE //domodel����ö��
{
	TWOBUTTON,
	THREEBUTTON,
	NOBUTTON
};

enum EN_Resoult //����ֵö��
{
	OK = 0,
	CANCEL,
	COMPEL,
	NORESOULT
};

struct ST_MessageBoxData  //��Ϣ�ṹ��
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
	bool isOhterMessageData();//�ж��Ƿ�����Ϣδ����
	EN_Resoult Domodel(const QString qstrInfo, int Time, DOMODELTYPE ); //ģʽ�Ի���
	void NoDomodel(const QString qstrInfo, unsigned int nChokeTime = 2000); //��ģʽ�Ի���
	EN_Resoult NewMessage(ST_MessageBoxData data);//���е���message
	EN_Resoult m_bResult; //DOMODEL���ؽ��
	QTimer* m_pTimeout; 
	QVector<ST_MessageBoxData> m_STMessAgeData; //��Ϣ����
	int CurMessageDataNumber = 0; //Ĭ�ϴ������
	int m_CurStatius = 2;	//��ӦEM_DIALOG_MODEL�е�NOMESSAGE
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
		//�رմ���
	void SlotCloseDomodel();

	//1.��Ϣ�ַ���2.����ģʽ3.�Զ��ر�ʱ��(��0��û�У���4.�Ƿ���Ҫ���ȵ�����5.�����domodel����һ��domodel
	EN_Resoult SlotNewMessAgeBoxData(QString message, int model, int time = 2000, bool precedence = false,DOMODELTYPE DomodelType = TWOBUTTON);
	void SlotNewMessAgeBoxData1(QString message, int model, int time = 2000, bool precedence = false, DOMODELTYPE DomodelType = TWOBUTTON);
Q_SIGNALS:
	void SigNalMessAgeBoxData(QString message, int model, int time = 2000, bool precedence = false,DOMODELTYPE DomodelType = TWOBUTTON);
	void SigNalCloseMessageBox();	//�رմ���
};

#define MESSAGEBOX (*UI_MessageBox::GetInstanceObj())
