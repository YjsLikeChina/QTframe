#ifndef CTRL_MESSAGEBOX_H
#define CTRL_MESSAGEBOX_H
#include "UI_MessageBox.h"
#include <QObject>

class CTRL_Messagebox : public QObject
{
	Q_OBJECT

public:
	~CTRL_Messagebox();
 
	static CTRL_Messagebox* GetInstanceObj();
	static CTRL_Messagebox* m_pInstanceObj;
	void initVal(void* pTmp);

private:
	CTRL_Messagebox(QObject *parent = NULL);
	void initConnect();
	UI_MessageBox* m_pMessagePoint;

public Q_SLOTS:
// 	void SlotMessageTransmitCreate(QString message, int model, int time = 2000, bool precedence = false, DOMODELTYPE DomodelType = TWOBUTTON);
 	void SlotCloseDomodel();
// 
// //1.��Ϣ�ַ���2.����ģʽ3.�Զ��ر�ʱ��(��0��û�У���4.�Ƿ���Ҫ���ȵ�����5.�����domodel����һ��domodel
 	EN_Resoult SlotNewMessAgeBoxData(QString message, int model, int time = 2000, bool precedence = false, DOMODELTYPE DomodelType = TWOBUTTON);

Q_SIGNALS:
	void SigNalMessAgeBoxData(QString message, int model, int time = 2000, bool precedence = false, DOMODELTYPE DomodelType = TWOBUTTON);
	void SigNalCloseMessageBox();	//�رմ���
};
#define UI_MESSAGEBOX (*CTRL_Messagebox::GetInstanceObj())
#endif // CTRL_MESSAGEBOX_H
