#include "UI_MachineErrorList.h"
#include <direct.h>

#define WIDGETDEFULTHIGH	81	//窗口默认高度
#define COLUMNHIGH			25	//每一行的高度
#define ROWWIDTH			493	//行宽
#define WIDGET_POINT_CX		280	//cx
#define WIDGET_POINT_CY		40	//cy
#define PB_POINT_CX			196
#define PB_POINT_CY			40

UI_MachineErrorList::UI_MachineErrorList(QWidget* parent /*= Q_NULLPTR*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | f);
	setGeometry(WIDGET_POINT_CX, WIDGET_POINT_CY, ROWWIDTH, WIDGETDEFULTHIGH);
	initUI();
	initVal();
	initConnect();
}

UI_MachineErrorList::~UI_MachineErrorList()
{
	delete m_pTimer;
}

void UI_MachineErrorList::ShowWidget(QString strParam)
{
	if (!m_pTimer->isActive())
		m_pTimer->start(300);
	int nNum = 0;
	if (m_strLastErrorList == strParam)
	{
		show();
	}
	else
	{
		m_strLastErrorList = strParam;
		m_strlistInfo.clear();
		m_strlistInfo = m_strLastErrorList.split(",");
		m_strlistInfo.removeLast();
		ui.LW_ErrorInfo->addItems(m_strlistInfo);
		nNum = m_strlistInfo.length();
		show();
	}
	if (0 != nNum)
	{
		if (nNum > 15)
			nNum = 15;
		//动态设置列表高度
		setGeometry(WIDGET_POINT_CX, WIDGET_POINT_CY, ROWWIDTH, WIDGETDEFULTHIGH + (nNum - 1) * COLUMNHIGH); //窗口大小
		ui.LB_Background->setGeometry(0, 0, ROWWIDTH, WIDGETDEFULTHIGH + (nNum - 1) * COLUMNHIGH);//背景大小
		ui.LW_ErrorInfo->setGeometry(1,0,ROWWIDTH-2, nNum * COLUMNHIGH);//设置列表高度
		ui.PB_CloseButton->move(PB_POINT_CX,PB_POINT_CY + (nNum - 1) * COLUMNHIGH);//按钮位置
	}
}

bool UI_MachineErrorList::CloseWidget()
{
	if (this->isVisible())
	{
		this->SlotCloseBtn();
	}
	return true;
}

void UI_MachineErrorList::initVal()
{
	m_pTimer = new QTimer;
	m_strlistInfo.clear();
	m_strLastErrorList = "";
}

void UI_MachineErrorList::initUI()
{
	char* pBuffer = NULL;
	if(NULL == (pBuffer = _getcwd(NULL,0)))
	{
		perror("_getcwd error");
	}

	QString strIcon = QString::fromLocal8Bit(pBuffer);
	strIcon += "/Image/Cancel.png";
	ui.PB_CloseButton->setIcon(QIcon(strIcon));
	ui.PB_CloseButton->setIconSize(QSize(30, 30));
	ui.PB_CloseButton->setStyleSheet("QPushButton{background-color:white;color: rgb(1,81,152); border-radius: 10px; border: 1px groove gray; border-style: outset;}"
		"QPushButton:pressed{background-color:blue;color: white; border-style: inset; }");

	ui.LB_Background->setStyleSheet("background-image: url(:/FilmTrimmer/Image/Background.png)");
	ui.LW_ErrorInfo->setStyleSheet("background-image: url(:/FilmTrimmer/Image/Background.png)");
}

void UI_MachineErrorList::initConnect()
{
	connect(ui.PB_CloseButton, SIGNAL(clicked()), this, SLOT(SlotCloseBtn()));
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(SlotTimeOut()));
}

void UI_MachineErrorList::SlotCloseBtn()
{
	m_pTimer->stop();
	this->close();
}

void UI_MachineErrorList::SlotTimeOut()
{
	if (!this->isActiveWindow())
	{
		SlotCloseBtn();
	}
}
