#pragma once
#include <QObject>
#include "CTRL_Base.h"
#include "QDir"
#include <QDateTime>
class CTRL_ProductEditor : public CTRL_Base 
{


public:
	CTRL_ProductEditor(QObject * parent= Q_NULLPTR);
	~CTRL_ProductEditor();

private:
	QString m_qstrCfgPath;						//程序文件路径
	QString m_qstrCurFileName;					//当前产品文件名
	CString m_cstrFilmTrimmerPath;
	QDateTime  LastUpdateTime;					//上次上传的文件的修改时间
	bool m_bfirstStart = true;

private:
	void InitVal();
	void InitConnect();
public:
	bool SaveProducteData(QVector<ST_CHANGE_POINT> VeChangePoint,QVector<double> LaserStepInfo,QStringList FileNewAndOldName,QString LaserFileName); //保存参数
	bool ChangeCurproduct(QString ProductFileName); //设置当前产品
	bool CopyPackage(QString qstrPkgName,QString& qstrNewPkgName);			//产品复制,返回值为真时,产品列表添加新的产品名
	bool DeletePackage(QString qstrPkgName);		//删除产品,弹出提示，选择为真时就删除产品
	bool NewPackage(QVector<ST_CHANGE_POINT> VeChangePoint, QVector<double> LaserStepInfo, QString FileName, QString LaserFileName);//新建产品,返回值为真时,(参数为新的产品的产品名)产品列表添加新的产品名
	bool SwitchPackage(QVector<ST_CHANGE_POINT> &Data,QString& LaserFileName, QString qstrPkgName);		//产品信息查看	
	bool SetLaserData(int nCard, double dlLaserPower, double dlLaserpFreq);	//设置激光参数(快捷)
};
