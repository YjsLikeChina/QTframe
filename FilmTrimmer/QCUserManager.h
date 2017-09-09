#ifndef QCUSERMANAGER_H
#define QCUSERMANAGER_H
#include "UserManager.h"
#include <QObject>

class QCUserManager : public QObject
{
	Q_OBJECT

public:
	QCUserManager(QObject *parent);
	~QCUserManager();

public:
	void AddUser(QString UserName, CString strPassword, enum USER_TYPE eType);
	void DeleteUser(QString UserName);
	void ChangePassword(QString UserName, QString Password);
	void ChangeUserName(QString OldName, QString NewName);
	void ChangeUserType(QString UserName, enum USER_TYPE);
	void DeleteUsdrPassword(QString UserName);
	QStringList Login();//返回权限和用户名,用户名在前，权限在后
	void Logout();

	BOOL ReadUserListFromFile(CList<CUser, CUser&> *m_pList);
	BOOL WriteUserListToFile(CList<CUser, CUser&> *m_pList);
private:
	CUserManager*  m_CUSerManager;   //被封装的用户管理指针
public:
	static QCUserManager* GetQcUserManagerP();
};
#define USERMANAGER (*QCUserManager::GetQcUserManagerP())
#endif // QCUSERMANAGER_H
