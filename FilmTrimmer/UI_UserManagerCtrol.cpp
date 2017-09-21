#include "UI_UserManagerCtrol.h"
#include "QCUserManager.h"
#include "QComboBox"
#include "UI_MessageBox.h"
#define  PlistCuser(x) (*((QList<CUser>*)x))
QList<CUser> * QLCuser;
UI_UserManagerCtrol::UI_UserManagerCtrol(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	initVal();
	initUi();
	initConnect();
	ui.OldPassword->installEventFilter(this);
	ui.PasswordOne->installEventFilter(this);
	ui.PasswordTwo->installEventFilter(this);
}

UI_UserManagerCtrol::~UI_UserManagerCtrol()
{

}

void UI_UserManagerCtrol::SlotSave()
{
	QString Success(QString::fromLocal8Bit("�޷�����,���޸��"));
	if (ui.OldPassword->isEnabled())
	{
		QString OldPassWord = ui.OldPassword->text();
		if (OldPassWord.length() <= 0)
		{
			MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("����������룡�����벻��Ϊ��"), 1);
			return;
		}
		if (!USERMANAGER.CheckPassword(OldPassWord))
		{
			MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("�����������������"), 1);
			ui.OldPassword->setText("");
			ui.PasswordOne->setText("");
			ui.PasswordTwo->setText("");
			return;
		}
		QString PasswordOne = ui.PasswordOne->text();
		QString PasswordTwo = ui.PasswordTwo->text();
		if (PasswordOne.length() <= 0)
		{
			MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("�����������룡�����벻��Ϊ��"), 1);
			return;
		}
		if (PasswordTwo.length() <= 0 || PasswordOne != PasswordTwo)
		{
			MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("�����������벻һ�£����������룡"), 1);
			ui.PasswordTwo->setText("");
			return;
		}
		if (!USERMANAGER.ChangePassword(USERMANAGER.m_CurUserName, OldPassWord, PasswordOne))
		{
			MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("�����޸�ʧ�ܣ�"), 1);
			return;
		}
		if (ui.NoAdminUserList->rowCount() != PlistCuser(m_UserList).length() - 1)
		{
			MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("�����û�������������ƥ�䣬����ϵ����Ա!"), 1);
			return;
		}
		
		Success.clear();
		Success += QString::fromLocal8Bit("���뱣��ɹ�");
	}	
	if (ContrlUser) {
		if (Success == QString::fromLocal8Bit("�޷�����,���޸��"))
			Success.clear();
		for (int i = 0, j = 0; i < ui.NoAdminUserList->rowCount();j++, i++)
		{
			if (PlistCuser(m_UserList).at(j).m_strName == USERMANAGER.m_CurUserName.toStdWString().data())
			{
				j++;
				continue;
			}
			QString username = ui.NoAdminUserList->item(i, 0)->text();
			QComboBox *Ctemp = (QComboBox*)ui.NoAdminUserList->cellWidget(i, 1);
			int Type = Ctemp->currentIndex();
			USER_TYPE UserType;
			switch (Type)
			{
			case 0:UserType = (USER_TYPE)1; break;
			case 1:UserType = (USER_TYPE)2; break;
			case 2:UserType = (USER_TYPE)4; break;
			default:
				break;
			}
			PlistCuser(m_UserList)[j].m_strName = username.toStdWString().c_str();
			PlistCuser(m_UserList)[j].m_eType = (int)UserType;
		}
		if (USERMANAGER.WriteUserListToFile(&PlistCuser(m_UserList)))
			Success += QString::fromLocal8Bit("\n�û���Ϣ����ɹ�");
		else
			Success += QString::fromLocal8Bit("\n�û���Ϣ����ʧ��");
	}
	MESSAGEBOX.SlotNewMessAgeBoxData(Success, 1);
	initUi();
}

void UI_UserManagerCtrol::SlotDec()
{
	if (ui.NoAdminUserList->rowCount() <= 0)
	{
		MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("��ǰû���û��ɲ���!"), 1);
		return;
	}
	if (ui.NoAdminUserList->currentRow() < 0)
	{
		MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("��ѡ��Ҫɾ�����û�!"), 1);
		return;
	}
	EN_Resoult Resoult = MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("ȷ��ɾ�����û���?\nע�⣡�˲��������棡"),0,0,true ,TWOBUTTON);
	if (Resoult == CANCEL)
		return;
	int CurItem = ui.NoAdminUserList->currentRow();
	QString username = ui.NoAdminUserList->item(CurItem, 0)->text();
	USERMANAGER.DeleteUser(username);
	ui.NoAdminUserList->removeRow(CurItem);
	PlistCuser(m_UserList).removeAt(CurItem);
}

void UI_UserManagerCtrol::SlotAdd()
{
	ui.NoAdminUserList->insertRow(ui.NoAdminUserList->rowCount());
	int Count = ui.NoAdminUserList->rowCount();
	QTableWidgetItem *Item = new QTableWidgetItem;
	Item->setText(QString::fromLocal8Bit("δ����"));
	ui.NoAdminUserList->setItem(Count - 1, 0, Item);
	QComboBox *QCtemp = new QComboBox;
	QStringList Strlist;
	Strlist << QString::fromLocal8Bit("����Ա") << QString::fromLocal8Bit("����ʦ") << QString::fromLocal8Bit("����Ա");
	QCtemp->addItems(Strlist);
	QCtemp->setCurrentIndex(2);
	ui.NoAdminUserList->setCellWidget(Count - 1, 1, QCtemp);
	Item = new QTableWidgetItem;
	Item->setText("123456");
	Item->setFlags(Qt::ItemIsSelectable);
	ui.NoAdminUserList->setItem(Count - 1, 2, Item);
	CUser CUserTemp;
	CUserTemp.m_strName = L"δ����";
	CUserTemp.m_eType = 1;
	CUserTemp.m_strPassword = USERMANAGER.EncryptPassWord("123456");
	PlistCuser(m_UserList).push_back(CUserTemp);
}

void UI_UserManagerCtrol::SlotCancel()
{
	this->close();
}

void UI_UserManagerCtrol::SlotPasswordClicked()
{
	ui.PasswordOne->setEnabled(true);
	ui.PasswordTwo->setEnabled(true);
	ui.OldPassword->setEnabled(true);
}

void UI_UserManagerCtrol::SlotShowUserContrl()
{
	if (USERMANAGER.m_CurUSER_TYPEName == QString::fromLocal8Bit("����Ա"))
	{
		ContrlUser = true;
		ui.NoAdminUserList->setVisible(true);
		ui.Add->setVisible(true);
		ui.Dec->setVisible(true);
	}
	else
		MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("Ȩ�޲���"), 1);
}

void UI_UserManagerCtrol::Dialog_show()
{
	USERMANAGER.Login();
	USERMANAGER.LogOut();
	if (USERMANAGER.m_CurUserName == "Operator")
	{
		MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("�޷�������\nĬ�ϲ���Ա�޴˹���!"), 1);
		return;
	}
	initUi();
	this->show();
}

void UI_UserManagerCtrol::initVal()
{
	QLCuser = new QList<CUser>;
	m_UserList = QLCuser;
	QRegExp rx("^[A-Za-z0-9]+$ ");
	QRegExpValidator *peng = new QRegExpValidator(rx, ui.OldPassword);
	ui.OldPassword->setValidator(peng);
	peng = new QRegExpValidator(rx, ui.PasswordOne);
	ui.PasswordOne->setValidator(peng);
	peng = new QRegExpValidator(rx, ui.PasswordTwo);
	ui.PasswordTwo->setValidator(peng);
	USERMANAGER.ReadUserListFromFile(&PlistCuser(m_UserList));
}

void UI_UserManagerCtrol::initUi()
{
	ContrlUser = false;
	ui.PasswordOne->setEnabled(false);
	ui.PasswordTwo->setEnabled(false);
	ui.OldPassword->setEnabled(false);
	ui.UserName->setEnabled(false);
	ui.NoAdminUserList->setVisible(false);
	ui.Add->setVisible(false);
	ui.Dec->setVisible(false);

	ui.PasswordOne->setText("");
	ui.PasswordTwo->setText("");
	ui.OldPassword->setText("");
	ui.UserName->setText(USERMANAGER.m_CurUserName);
	ui.Authority->setText(USERMANAGER.m_CurUSER_TYPEName);
	ui.NoAdminUserList->setRowCount(0);
	for (int i =0,j=0; i < PlistCuser(m_UserList).length(); i++)
	{
		if (PlistCuser(m_UserList).at(i).m_strName == USERMANAGER.m_CurUserName.toStdWString().data())
		{
			j = i;
			continue;
		}
		ui.NoAdminUserList->setRowCount(j+1);
		QTableWidgetItem *Item = new QTableWidgetItem;
		CString CStrtemp = PlistCuser(m_UserList).at(i).m_strName; //��ȡ����
		Item->setText(QString::fromStdWString(CStrtemp.GetBuffer()));
		ui.NoAdminUserList->setItem(j, 0, Item);
		QComboBox *QCtemp = new QComboBox;
		QStringList Strlist;
		Strlist << QString::fromLocal8Bit("����Ա") << QString::fromLocal8Bit("����ʦ") << QString::fromLocal8Bit("����Ա");
		QCtemp->addItems(Strlist);
		QCtemp->setCurrentText(USERMANAGER.GetTypeName((USER_TYPE)PlistCuser(m_UserList).at(i).m_eType));//��ȡ����
		ui.NoAdminUserList->setCellWidget(j, 1, QCtemp);
		Item = new QTableWidgetItem;
		Item->setText("***********");
		Item->setFlags(Qt::ItemIsSelectable);
		ui.NoAdminUserList->setItem(j, 2, Item);
		j++;
	}
}

void UI_UserManagerCtrol::initConnect()
{
	connect(ui.Save, SIGNAL(clicked()), this, SLOT(SlotSave()));
	connect(ui.Cancel, SIGNAL(clicked()), this, SLOT(SlotCancel()));
	connect(ui.Add, SIGNAL(clicked()), this, SLOT(SlotAdd()));
	connect(ui.Dec, SIGNAL(clicked()), this, SLOT(SlotDec()));
	connect(ui.UserContrlButton, SIGNAL(clicked()), this, SLOT(SlotShowUserContrl()));
}

bool UI_UserManagerCtrol::eventFilter(QObject* obj, QEvent *event)
{
	if (obj == ui.PasswordOne || obj == ui.PasswordTwo || obj == ui.OldPassword)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			SlotPasswordClicked();
		}
	}
	return QDialog::eventFilter(obj, event);
}
