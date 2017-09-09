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
	QMap<int, QString> m_qMapHistoryInfoPath;							//模组序号及文件路径
	QMap<int, QStringList> m_qMapHistoryInfoHead;						//模组序号及列头
	QString m_strIconFile;
	int m_nLastIndex;													//
	bool m_bAutoUpdateLock;

private:
	void initVal();
	void initUI();
	void initConnect();

	protected Q_SLOTS:
	void SlotSwitchSection(int nIndex);									//切换不同历史页面
	void SlotCleanHistoryFile();										//清除历史文件

public:
	bool insertModule(QVector<ST_MODULE>* cfgModuleInfo);				//添加模组
	bool AutoUpdateData(int nIndex, QStringList qstrListInfo);			//更新历史信息,QStringList中包含每行信息，每行信息中的数据使用 ',' 风格
	virtual void SkipCurrentPage();										//跳转到当前页面
	virtual bool GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal);//获取有修改的数据

Q_SIGNALS:
	void SigSwitchSection(int nIndex, QString qstrHistoryFilePath);		//切换不同历史信息
	void SigCleanHistoryFile(QString qstrHistoryFilePath);				//清除历史文件
};

