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


EN_Resoult UI_MessageBox::Domodel(const QString qstrInfo,int Time)
{
	ui.PB_OK->setVisible(true);
	ui.PB_OK->setGeometry(55, 190, 110, 45);
	ui.PB_Cancel->setGeometry(235, 190, 110, 45);
	if(Time == 0)
	{
		ui.PB_OK->setEnabled(false);
		ui.PB_Cancel->setEnabled(false);
	}
	else
	{
		ui.PB_OK->setEnabled(true);
		ui.PB_Cancel->setEnabled(true);
		m_pTimeout->start(Time);
	}
	ui.LB_MessageInfo->setText(qstrInfo);
	exec();
	return m_bResult;
}




void UI_MessageBox::NoDomodel(const QString qstrInfo, unsigned int nChokeTime /*= 2000*/)
{
	ui.PB_OK->setVisible(false);
	ui.PB_Cancel->setGeometry(140, 221, 190, 45);
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
		case 0: resoult = Domodel(data.message, data.time); m_CurStatius = DOMODEL; break;
		case 1: NoDomodel(data.message, data.time); m_CurStatius = NODOMODEL; break;
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
	connect(m_pTimeout, SIGNAL(timeout()), this, SLOT(SlotTimeout()));
	connect(this, SIGNAL(SigNalMessAgeBoxData(QString, int, int)),this, SLOT(SlotNewMessAgeBoxData(QString, int, int)));
	connect(this, SIGNAL(SigNalCloseMessageBox()), this, SLOT(SlotCloseDomodel()));
}

void UI_MessageBox::initVal()
{
	m_bResult = NORESOULT;
	m_pTimeout = new QTimer;
	ui.LB_MessageInfo->setWordWrap(true);
	ui.LB_MessageInfo->setAlignment(Qt::AlignTop | Qt::AlignCenter);
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

void UI_MessageBox::SlotTimeout()
{
	m_bResult = EN_Resoult::NORESOULT;
	SlotCloseDomodel();
}

void UI_MessageBox::SlotCloseDomodel()
{
	m_pTimeout->stop();
	bool isNext = false;
	if (m_STMessAgeData.length() - 1 > CurMessageDataNumber) //判断是否还有数据
		isNext = true;
	m_STMessAgeData.removeAt(CurMessageDataNumber);
	accept();
	m_CurStatius = NOMESSAGE;
	if(isNext)
		NewMessage(m_STMessAgeData.at(CurMessageDataNumber));
}

EN_Resoult UI_MessageBox::SlotNewMessAgeBoxData(QString message, int model, int time, bool precedence, bool streeButton)
{
	ST_MessageBoxData temp;
	temp.message = message;
	temp.model = model;
	temp.time = time;
	temp.streebutton = streeButton;
	if (precedence)
	{
		m_STMessAgeData.insert(CurMessageDataNumber, temp);
		if(m_CurStatius != NOMESSAGE)
			SlotCloseDomodel();
	}
	else
		m_STMessAgeData.push_back(temp);
	return NewMessage(temp);
}

