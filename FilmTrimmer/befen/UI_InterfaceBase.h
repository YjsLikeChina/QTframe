#pragma once
#include "BaseDataType.h"
#include <qwidget.h>
#include "UI_Simpledialog.h"
class UI_InterfaceBase
	//: public QWidget
{
public:
	UI_InterfaceBase(QWidget* parent = Q_NULLPTR);
	~UI_InterfaceBase();
private:
	QWidget* m_pQObject;

public:
	SimPleDialog * m_UiSimPleDialog;
	virtual void SkipCurrentPage();										//��תҳ��
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal);//��ȡ�޸Ĺ��Ĳ���
	virtual bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);			//�Զ�����
	virtual bool AutoUpdateData(int nIndex, QStringList qstrListInfo);		//�Զ�����(��ʷ��Ϣҳ��)
	virtual bool AutoUpdateData(const QString qstrAlarmInfo);				//�Զ�����(Filmtrimmer���±���)
	virtual bool insertModule(QVector<ST_MODULE>*);							//���ģ��
	void temp22();
};

