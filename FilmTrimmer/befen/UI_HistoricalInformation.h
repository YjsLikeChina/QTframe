#pragma once
#include "UI_InterfaceBase.h"
#include <qwidget.h>
#include "ui_UI_HistoricalInformation.h"
#include "BaseDataType.h"

class UI_HistoricalInformation :
	public QWidget, virtual public UI_InterfaceBase
{
	Q_OBJECT

public:
	UI_HistoricalInformation(QWidget* parent = Q_NULLPTR);
	~UI_HistoricalInformation();

private:
	Ui::HistoricalInformationWidget ui;
	QMap<int, QString> m_qMapHistoryInfoPath;							//ģ����ż��ļ�·��
	QMap<int, QStringList> m_qMapHistoryInfoHead;						//ģ����ż���ͷ
	QString m_strIconFile;
	int m_nLastIndex;													//
	bool m_bAutoUpdateLock;

private:
	void initVal();
	void initUI();
	void initConnect();

	protected Q_SLOTS:
	void SlotSwitchSection(int nIndex);									//�л���ͬ��ʷҳ��
	void SlotCleanHistoryFile();										//�����ʷ�ļ�

public:
	bool insertModule(QVector<ST_MODULE>* cfgModuleInfo);				//���ģ��
	bool AutoUpdateData(int nIndex, QStringList qstrListInfo);			//������ʷ��Ϣ,QStringList�а���ÿ����Ϣ��ÿ����Ϣ�е�����ʹ�� ',' ���
	virtual void SkipCurrentPage();										//��ת����ǰҳ��
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal);//��ȡ���޸ĵ�����

Q_SIGNALS:
	void SigSwitchSection(int nIndex, QString qstrHistoryFilePath);		//�л���ͬ��ʷ��Ϣ
	void SigCleanHistoryFile(QString qstrHistoryFilePath);				//�����ʷ�ļ�
};

