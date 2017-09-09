#pragma once
#include <QObject>
#include <QVector>
#include <QMap>
#include "DP_FileOperator.h"
#include "BaseDataType.h"
#include <QTreeWidget>

class DP_CfgInterface : public QObject 
{
	Q_OBJECT
private:
	DP_CfgInterface(QObject * parent = Q_NULLPTR);

public:
	static DP_CfgInterface* GetInstanceObj();
	static	DP_CfgInterface* m_pInstanceObj;
	~DP_CfgInterface();
	bool initCfgValue(QVector<ST_MODULE>&, QString path); //第一个参数为模组信息，第二个参数为自动更新数据，第三个参数为自动配置文件路径
	//QVector<ST_MODULE> CfgValue;
	bool WriteValue(const QVector<ST_MODULE>* CfgValue, int nModuleItem, QString strCfgPath); //配置工具使用，一次性重新整个模组及所有子项
	bool WriteValue(const QMap<QString, QString>& ModifyVal, QString strKey,QString qstrCfgPath); //写入某个或某几个子项的值,strKey为配置文件中的key

	static bool JudgeDirIsExist(const QString qstrDir); //判断目录是否存在
	static bool JudgeFileIsExist(const QString qstrDir); //判断文件是否存在
	static bool CreateDir(const QString qstrDir); //创建目录
	static bool CreateFile(const QString qstrFilePath); //创建文件

	QString StringTranSlate(const CString &cstr);
	CString StringTranSlate(const QString &qstr);
	QString AddrTranSlate(QString Addr, EM_Type, bool Forward = true);
};

#define CFGINTERFACE (*DP_CfgInterface::GetInstanceObj()) //配置文件接口类
