#ifndef QCUSERMANAGER_H
#define QCUSERMANAGER_H
#include "UserManager.h"
#include <QObject>

class QCUserManager : public QObject
{
	Q_OBJECT

public:
	QCUserManager(QObject *parent = NULL);
	~QCUserManager();

public:
	bool AddUser(QString UserName, QString strPassword, enum USER_TYPE eType);
	bool DeleteUser(QString UserName);
	bool ChangePassword(QString UserName, QString PasswordOld,QString PasswordNEW);
	bool ChangeUserName(QString OldName, QString NewName);
	bool ChangeUserType(QString UserName, enum USER_TYPE);
	bool DeleteUsdrPassword(QString UserName);
	bool CheckPassword(QString PassWord);
	QStringList Login();//����Ȩ�޺��û���,�û�����ǰ��Ȩ���ں�
	bool LogOut();
	QString GetTypeName(USER_TYPE eType);
	BOOL ReadUserListFromFile(QList<CUser> *m_QList);
	BOOL WriteUserListToFile(QList<CUser> *m_QList);
	CString EncryptPassWord(CString SourcePassWord);
private:
	void initVal();


	CUserManager*  m_CUSerManager;   //��װ���û�����ָ��
	static QCUserManager*  m_QCUserManager; //����
public:
	static QCUserManager* GetQcUserManagerP();

	QString m_CurUserName;
	USER_TYPE m_CurUSER_TYPE;
	QString m_CurUSER_TYPEName;
	CWnd*	m_ParentWnd = NULL;
signals:
	void NewLoginUser();
};
#define USERMANAGER (*QCUserManager::GetQcUserManagerP())
#endif // QCUSERMANAGER_H
