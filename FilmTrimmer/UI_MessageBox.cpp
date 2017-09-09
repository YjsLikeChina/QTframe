#include "UI_MessageBox.h"
#include "BaseDataType.h"

UI_MessageBox* UI_MessageBox::m_pInstanceObj = NULL;
UI_MessageBox* UI_MessageBox::GetInstanceObj()
{
	if (NULL == m_pInstanceObj)
		m_pInstanceObj = new UI_MessageBox;

	return m_pInstanceObj;
}

UI_MessageBox::UI_MessageBox()
{
	ui.setupUi(this);
	initVal();
	initUI();
	initConnect();
}


UI_MessageBox::~UI_MessageBox()
{
	delete m_pTimeout;
}


EN_Resoult UI_MessageBox::Domodel(const QString qstrInfo,int Time, DOMODELTYPE DoModelType)
{
	ui.PB_OK->setVisible(true);
	ui.NeverJump->setVisible(true);
	ui.PB_Cancel->setVisible(true);
	if (DoModelType == THREEBUTTON)
	{
		ui.PB_OK->setGeometry(20, 195, 110, 45);
		ui.PB_OK->setText(QString::fromLocal8Bit("保存"));
		ui.NeverJump->setGeometry(145, 195, 110, 45);
		ui.NeverJump->setText(QString::fromLocal8Bit("不保存"));
		ui.PB_Cancel->setGeometry(270, 195, 110, 45);
		ui.PB_Cancel->setText(QString::fromLocal8Bit("取消"));
		ui.LB_MessageInfo->setText(qstrInfo);
	}
	else if(DoModelType == TWOBUTTON)
	{
		ui.NeverJump->setVisible(false);
		ui.PB_OK->setText(QString::fromLocal8Bit("确定"));
		ui.PB_OK->setGeometry(50, 195, 110, 45);
		ui.PB_Cancel->setGeometry(240, 195, 110, 45);
		if (Time != 0)
		{
			m_pTimeout->start(Time);
		}
		ui.LB_MessageInfo->setText(qstrInfo);
	}
	else if (DoModelType = NOBUTTON)
	{
		ui.PB_OK->setVisible(false);
		ui.NeverJump->setVisible(false);
		ui.PB_Cancel->setVisible(false);
	}
	exec();
	return m_bResult;
}




void UI_MessageBox::NoDomodel(const QString qstrInfo, unsigned int nChokeTime /*= 2000*/)
{
	ui.PB_Cancel->setVisible(false);
	ui.NeverJump->setVisible(false);
	ui.PB_OK->setVisible(true);
	ui.PB_OK->setGeometry(145, 195, 110, 45);
	ui.LB_MessageInfo->setText(qstrInfo);
	show();
	m_pTimeout->start(nChokeTime);
}



EN_Resoult UI_MessageBox::NewMessage(ST_MessageBoxData data)
{
	EN_Resoult resoult = EN_Resoult::NORESOULT;
	if (m_CurStatius == NOMESSAGE)
	{
		switch (data.model)
		{
		case 0: m_CurStatius = DOMODEL; resoult = Domodel(data.message, data.time,data.DoModelType); break;
		case 1:  m_CurStatius = NODOMODEL; NoDomodel(data.message, data.time); break;
		default:
			break;
		}
	}
	return resoult;
}

void UI_MessageBox::initConnect()
{
	connect(ui.PB_OK, SIGNAL(clicked()), this, SLOT(SlotOk()));
	connect(ui.PB_Cancel, SIGNAL(clicked()), this, SLOT(SlotCancel()));
	connect(ui.NeverJump, SIGNAL(clicked()), this, SLOT(SlotNever()));
	connect(m_pTimeout, SIGNAL(timeout()), this, SLOT(SlotTimeout()));
	connect(this, SIGNAL(SigNalMessAgeBoxData(QString, int, int, bool, DOMODELTYPE)), this, SLOT(SlotNewMessAgeBoxData1(QString, int, int, bool, DOMODELTYPE)), Qt::QueuedConnection);
	connect(this, SIGNAL(SigNalCloseMessageBox()), this, SLOT(SlotCloseDomodel()), Qt::QueuedConnection);
}

void UI_MessageBox::initVal()
{
	m_bResult = NORESOULT;
	m_pTimeout = new QTimer;
	ui.LB_MessageInfo->setWordWrap(true);
	ui.LB_MessageInfo->setAlignment(Qt::AlignTop | Qt::AlignCenter);
	qRegisterMetaType<DOMODELTYPE>("DOMODELTYPE");
	//m_pCtrlMessageBox = MESSAGEBOX.GetInstanceObj();
}

void UI_MessageBox::initUI()
{
	QString strIconFile = QCoreApplication::applicationDirPath();
	QString strIconPath = strIconFile + "/Image/Background.png";
	ui.LB_Background1->setScaledContents(true);
	ui.LB_Background1->setPixmap(QPixmap(strIconPath));

	strIconPath = strIconFile + "/Image/Diaphaneity2.png";
	ui.LB_MessageInfo->setScaledContents(true);
	ui.LB_MessageInfo->setPixmap(QPixmap(strIconPath));

	strIconPath = strIconFile + "/Image/OK.png";
	ui.PB_OK->setIcon(QIcon(strIconPath));
	ui.PB_OK->setIconSize(QSize(30, 25));
	ui.PB_OK->setStyleSheet("QPushButton{background-color:white;color: rgb(1,81,152); border-radius: 10px; border: 1px groove gray; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border-style: inset; }");

	strIconPath = strIconFile + "/Image/Cancel.png";
	ui.PB_Cancel->setIcon(QIcon(strIconPath));
	ui.PB_Cancel->setIconSize(QSize(30, 25));
	ui.PB_Cancel->setStyleSheet("QPushButton{background-color:white;color: rgb(1,81,152); border-radius: 10px; border: 1px groove gray; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border-style: inset; }");

	ui.NeverJump->setIcon(QIcon(strIconPath));
	ui.NeverJump->setIconSize(QSize(30, 25));
	ui.NeverJump->setStyleSheet("QPushButton{background-color:white;color: rgb(1,81,152); border-radius: 10px; border: 1px groove gray; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border-style: inset; }");
	this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

bool UI_MessageBox::isOhterMessageData()
{
	bool isNext = false;
	if (m_STMessAgeData.length()  > 0) //判断是否还有数据
		isNext = true;
	return isNext;
}

void UI_MessageBox::SlotOk()
{
	m_bResult = EN_Resoult::OK;
	SlotCloseDomodel();
}

void UI_MessageBox::SlotCancel()
{
	m_bResult = EN_Resoult::CANCEL;
	SlotCloseDomodel();
}

void UI_MessageBox::SlotNever()
{
	m_bResult = EN_Resoult::COMPEL;
	SlotCloseDomodel();
}

void UI_MessageBox::SlotTimeout()
{
	m_bResult = EN_Resoult::NORESOULT;
	SlotCloseDomodel();
}

void UI_MessageBox::SlotCloseDomodel()
{
	if (m_CurStatius == NOMESSAGE)
		return;
	m_pTimeout->stop();
	m_STMessAgeData.removeAt(CurMessageDataNumber);
	accept();
	int m_OldStatius = m_CurStatius;
	m_CurStatius = NOMESSAGE;
	if(isOhterMessageData() && m_CurStatius != (int)DOMODEL)
		NewMessage(m_STMessAgeData.at(CurMessageDataNumber));
}

EN_Resoult UI_MessageBox::SlotNewMessAgeBoxData(QString message, int model, int time, bool precedence, DOMODELTYPE DomodelType)
{

	int a = m_CurStatius;
	ST_MessageBoxData temp;
	temp.message = message;
	temp.model = model;
	temp.time = time;
	temp.DoModelType = DomodelType;
	if (precedence)
	{
		if (m_CurStatius != NOMESSAGE)
		{
			m_STMessAgeData.insert(1, temp);
			m_pTimeout->stop();
			m_STMessAgeData.removeAt(CurMessageDataNumber);
			accept();
			m_CurStatius = NOMESSAGE;
		}
		else
			m_STMessAgeData.push_back(temp);
	}
	else
		m_STMessAgeData.push_back(temp);
	return NewMessage(temp);
}

void UI_MessageBox::SlotNewMessAgeBoxData1(QString message, int model, int time /*= 2000*/, bool precedence /*= false*/, DOMODELTYPE DomodelType /*= TWOBUTTON*/)
{
	int a = m_CurStatius;
	ST_MessageBoxData temp;
	temp.message = message;
	temp.model = model;
	temp.time = time;
	temp.DoModelType = DomodelType;
	if (precedence)
	{
		if (m_CurStatius != NOMESSAGE)
		{
			m_STMessAgeData.insert(1, temp);
			m_pTimeout->stop();
			m_STMessAgeData.removeAt(CurMessageDataNumber);
			accept();
			m_CurStatius = NOMESSAGE;
		}
		else
			m_STMessAgeData.push_back(temp);
	}
	else
		m_STMessAgeData.push_back(temp);
	NewMessage(temp);
	return;
}

