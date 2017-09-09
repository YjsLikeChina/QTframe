#pragma once
#include "UI_InterfaceBase.h"
#include <qwidget.h>
#include "ui_UI_ProductEditor.h"
#include "CTRL_producteditor.h"

class UI_ProductEditor :
	public QWidget, virtual public UI_InterfaceBase
{
	Q_OBJECT

public:
	UI_ProductEditor(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
	~UI_ProductEditor();

private:
	Ui::ProductEditorWidget ui;
	QVector<ST_CHANGE_POINT> m_qVecPkgModifyInfo; //�޸ĵĲ���
	QString m_qstrIconFile;
	QPushButton* m_pAddStepButton;				//��Ӽ������Button
	QButtonGroup m_ButtonGroup;					//ɾ����������ButtonGroup
	QTreeWidgetItem* m_qrwStepItem;				//�������Item
	QVector<ST_MODULEITEM> m_ModuleVector;		//ÿ��ģ���ָ���Լ�����ָ��
	bool m_bAddStepLock;
	CTRL_ProductEditor* m_pProductEditor;		//Ctrlָ��
	QListWidgetItem* m_pCurrentSelPkgItem;		//�����ͬ��Ʒʱ����¼��ǰѡ�е�Item
	QVector<double> m_qVecLaserStepDist;			//�������

private:
	void initVal();
	void initUI();
	void initConnect();
	void ShowSimpleProduictEditor(int laser); //��ʾ����Ʒ���ý���
protected Q_SLOTS:
	void SlotSetCurrentPackage();								//���õ�ǰ��Ʒ
	void SlotCopyPackage();										//���Ʋ�Ʒ
	void SlotDeletePackage();									//ɾ����Ʒ
	void SlotNewPackage();										//�½���Ʒ
	void SlotSavePackage();										//�����Ʒ��Ϣ
	void SlotAddPackageStep();									//��Ӳ�Ʒ�������
	void SlotSwitchPackage(QListWidgetItem *item);				//�л���Ʒ
	void SlotDeleteStep(int nButton);							//ɾ���������
	void SlotItemChanged(QTreeWidgetItem* item, int nColumn);	//��Ʒ�������޸�

public:
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal);//��ȡ���޸ĵ�����
	bool insertModule(QVector<ST_MODULE>* cfgModuleInfo);				//���ģ��
	bool AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo);				//�Զ�����
	virtual void SkipCurrentPage();										//��ת����ǰҳ��
	void UpdataPackageInfo(QVector<ST_CHANGE_POINT> qliOnloadpkg,QString LaserFileName,QString strPkgName);		//�����Ʒ��Ϣ��
	void AddNewPackage(QString& strNewPkgName);							//��Ʒ���б�����²�Ʒ����

//Q_SIGNALS:
//	void SigSetCurrentPackage(QString qstrPkgName); //���õ�ǰ��Ʒ
//	void SigCopyPackage(QString qstrPkgName);		//��Ʒ����
//	void SigDeletePackage(QString qstrPkgName);		//ɾ����Ʒ
//	void SigNewPackage(QString qstrPkgName);		//�½���Ʒ
//	void SigSavePackage(QMap<QString, QString>);	//��Ʒ��������
//	void SigSwitchPackage(QString qstrPkgName);		//��Ʒ�л�
};

