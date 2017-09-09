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
// //1.消息字符串2.弹窗模式3.自动关闭时间(给0则没有），4.是否需要优先弹出，5.如果是domodel是哪一种domodel
 	EN_Resoult SlotNewMessAgeBoxData(QString message, int model, int time = 2000, bool precedence = false, DOMODELTYPE DomodelType = TWOBUTTON);

Q_SIGNALS:
	void SigNalMessAgeBoxData(QString message, int model, int time = 2000, bool precedence = false, DOMODELTYPE DomodelType = TWOBUTTON);
	void SigNalCloseMessageBox();	//关闭窗口
};
#define UI_MESSAGEBOX (*CTRL_Messagebox::GetInstanceObj())
#endif // CTRL_MESSAGEBOX_H
