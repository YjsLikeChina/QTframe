#include "QCUserManager.h"
#include "LogManager.h"
#include "QMap"
QCUserManager* QCUserManager::m_QCUserManager = NULL;
QCUserManager::QCUserManager(QObject *parent)
	: QObject(parent)
{
	initVal();
}

QCUserManager::~QCUserManager()
{
	delete m_CUSerManager;
}

bool QCUserManager::AddUser(QString UserName, QString strPassword, enum USER_TYPE eType)
{
	CString CUserName = UserName.toStdWString().data();
	CString CstrPassword = strPassword.toStdWString().data();
	return m_CUSerManager->AddUser(CUserName, CstrPassword, eType);
}

bool QCUserManager::DeleteUser(QString UserName)
{
	CString CUserName = UserName.toStdWString().data();
	CStringList CUserList;
	CUserList.AddTail(CUserName);
	return m_CUSerManager->DeleteUsers(CUserList);
}

bool QCUserManager::ChangePassword(QString UserName, QString PasswordOLD, QString PasswordNEW)
{
	CString CUserName = UserName.toStdWString().data();
	CString CstrPasswordOLD = PasswordOLD.toStdWString().data();
	CString CstrPasswordNew = PasswordNEW.toStdWString().data();
	return m_CUSerManager->ChangePassword(CUserName, CstrPasswordOLD, CstrPasswordNew);
}

bool QCUserManager::ChangeUserName(QString OldName, QString NewName)
{
	CString CUserNameOld = OldName.toStdWString().data();
	CString CUserNameNew = NewName.toStdWString().data();
	return m_CUSerManager->ChangeUserName(CUserNameOld, CUserNameNew);
}

bool QCUserManager::ChangeUserType(QString UserName, enum USER_TYPE Type)
{
	CString CUserName = UserName.toStdWString().data();
	return m_CUSerManager->ChangeType(CUserName, Type);
}

bool QCUserManager::DeleteUsdrPassword(QString UserName)
{
	CString CUserName = UserName.toStdWString().data();
	return m_CUSerManager->DeleteUserPassword(CUserName);
}

bool QCUserManager::CheckPassword(QString PassWord)
{
	bool resoult = ChangePassword(m_CurUserName, PassWord, PassWord);
	return resoult;
}

QStringList QCUserManager::Login()
{
	QStringList Resoult("error");
	BOOL Resoult_fuction = m_CUSerManager->Login(m_ParentWnd);
	if(Resoult_fuction)
	{ 
		Sleep(10);
		QString UserName = QString::fromWCharArray(m_CUSerManager->GetName());
		Resoult.clear();
		m_CurUserName = UserName;
		m_CurUSER_TYPE = m_CUSerManager->GetType();
		m_CurUSER_TYPEName = this->GetTypeName(m_CurUSER_TYPE);
		Resoult << UserName << m_CurUSER_TYPEName;
		LOGSTR.SetCurUserInfo(m_CurUserName.toStdWString().c_str(), m_CurUSER_TYPEName.toStdWString().c_str());
		emit NewLoginUser();
	}
	return Resoult;
}

bool QCUserManager::LogOut()
{
	m_CUSerManager->Logout();
	QString UserName = QString::fromWCharArray(m_CUSerManager->GetName());
	m_CurUserName = QString::fromLocal8Bit("未登录");
	m_CurUSER_TYPE = m_CUSerManager->GetType();
	m_CurUSER_TYPEName = QString::fromLocal8Bit("无权限");
	LOGSTR.SetCurUserInfo(m_CurUserName.toStdWString().c_str(), m_CurUSER_TYPEName.toStdWString().c_str());
	emit NewLoginUser();
	return true;
}
QString QCUserManager::GetTypeName(enum USER_TYPE eType)
{
	QString resoult;
	
	switch (eType)
	{
	case USER_OPERATOR:
		resoult = QString::fromLocal8Bit("操作员");
		break;
	case USER_MAINTENANCE:
		resoult = QString::fromLocal8Bit("工程师");
		break;
	case USER_ADMIN:
		resoult = QString::fromLocal8Bit("管理员");
		break;
	default:
		break;
	}
	return resoult;
}
BOOL QCUserManager::ReadUserListFromFile(QList<CUser> *m_QList)
{
	CList<CUser, CUser&> m_pList;
	if (!m_CUSerManager->ReadUserListFromFile(&m_pList))
		return false;
	m_QList->clear();
	for (POSITION i = m_pList.GetHeadPosition(); i != NULL;)
	{
		m_QList->push_back(m_pList.GetNext(i));
	}
	return true;
}

BOOL QCUserManager::WriteUserListToFile(QList<CUser> *m_QList)
{
	CList<CUser, CUser&> m_pList;
	for (int i = 0;i< m_QList->length(); i++)
	{
		CUser UserTemp = m_QList->at(i);
		m_pList.AddTail(UserTemp);
	}
	if (!m_CUSerManager->WriteUserListToFile(&m_pList))
		return false;
	return true;
}

CString QCUserManager::EncryptPassWord(CString SourcePassWord)
{
	return m_CUSerManager->EncryptPassword(SourcePassWord);
}

void QCUserManager::initVal()
{
	m_CUSerManager = new CUserManager;
}

QCUserManager*QCUserManager::GetQcUserManagerP()
{
	if (m_QCUserManager == NULL)
		m_QCUserManager = new QCUserManager;
	return m_QCUserManager;
}
