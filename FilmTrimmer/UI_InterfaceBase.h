#pragma once
#include "BaseDataType.h"
#include <qwidget.h>
#include <QLineEdit>
class UI_InterfaceBase
	//: public QWidget
{
public:
	UI_InterfaceBase(QWidget* parent = Q_NULLPTR);
	~UI_InterfaceBase();
private:
	QWidget* m_pQObject;
public:

	bool isChanged = false;

	virtual void SkipCurrentPage();											//��תҳ��
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal);	//��ȡ�޸Ĺ��Ĳ���
	virtual bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);			//�Զ�����
	virtual bool AutoUpdateData(int nIndex, QStringList qstrListInfo);		//�Զ�����(��ʷ��Ϣҳ��)
	virtual bool AutoUpdateData(const QString qstrAlarmInfo);				//�Զ�����(Filmtrimmer���±���)
	virtual bool insertModule(QVector<ST_MODULE>*);							//���ģ��
	virtual bool SaveParamer();
};

class UI_LineEdit
	:public QLineEdit
{
public:
	UI_LineEdit(int i, int j, QWidget* parent = Q_NULLPTR);
	UI_LineEdit(QWidget* parent = Q_NULLPTR);
	~UI_LineEdit();

	int nModuleNum;
	int nChildNum;

private:
	void initUI();

public:
	void SetStyleSheet(QFont qfont, QRegExp regx);//�������塢������ɫ����С
};

