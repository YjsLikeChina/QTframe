#include "UI_UserManagerCtrol.h"
#include "QCUserManager.h"
UI_UserManagerCtrol::UI_UserManagerCtrol(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

UI_UserManagerCtrol::~UI_UserManagerCtrol()
{
	
}

void UI_UserManagerCtrol::SlotSave()
{
	
}

void UI_UserManagerCtrol::SlotDec()
{

}

void UI_UserManagerCtrol::SlodAdd()
{

}

void UI_UserManagerCtrol::SlotCancel()
{

}

void UI_UserManagerCtrol::SlotPasswordClicked()
{

}

void UI_UserManagerCtrol::initVal()
{
	CList<CUser, CUser&> *m_pList = NULL;
	USERMANAGER.GetQcUserManagerP->ReadUserListFromFile(m_pList);
	if (m_pList == NULL)
		return;
	for (POSITION i = m_pList->GetHeadPosition(); i!= NULL;)
	{
		CString UserName  = m_pList->GetNext(i).m_strName;
		USER_TYPE UserType = (USER_TYPE)m_pList->GetNext(i).m_eType;
		QString QUserName =QString::fromStdWString(UserName.GetBuffer());
		m_UserList.insert(QUserName, UserType);
	}
}

void UI_UserManagerCtrol::initUi()
{

}

void UI_UserManagerCtrol::initConnect()
{

}
