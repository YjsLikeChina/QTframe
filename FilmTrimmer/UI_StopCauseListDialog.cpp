#include "UI_StopCauseListDialog.h"
#include "DP_FileOperator.h"
#include <QFileInfo>
#include "UI_MessageBox.h"
#include <QLayout>

UI_StopCauseListDialog::UI_StopCauseListDialog()
{
	ui.setupUi(this);
	InitVal();
	InitUI();
	InitConnect();
	SetStopButton(m_qslStopCause1, m_qslStopCause2, m_qslStopCause3, m_qslStopCause4, m_qslStopCause5);
}

UI_StopCauseListDialog::~UI_StopCauseListDialog()
{
	delete m_pStopList1ButtonGroup;
	delete m_pStopList2ButtonGroup;
	delete m_pStopList3ButtonGroup;
	delete m_pStopList4ButtonGroup;
	delete m_pStopList5ButtonGroup;
}

void UI_StopCauseListDialog::InitUI()
{
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	ui.LW_StopCauseList1->setStyleSheet("background:transparent;");
	ui.LW_StopCauseList2->setStyleSheet("background:transparent;");
	ui.LW_StopCauseList3->setStyleSheet("background:transparent;");
	ui.LW_StopCauseList4->setStyleSheet("background:transparent;");
	ui.LW_StopCauseList5->setStyleSheet("background:transparent;");
}

void UI_StopCauseListDialog::InitVal()
{
	m_pStopList1ButtonGroup = new QButtonGroup;
	m_pStopList2ButtonGroup = new QButtonGroup;
	m_pStopList3ButtonGroup = new QButtonGroup;
	m_pStopList4ButtonGroup = new QButtonGroup;
	m_pStopList5ButtonGroup = new QButtonGroup;

	//获取配置文件信息
	QString qstrPath = QCoreApplication::applicationDirPath();
	qstrPath += QString::fromLocal8Bit("/System/StopCause.cfg");
	QFileInfo isOpen(qstrPath);
	if (!isOpen.exists())
	{
		isOpen.refresh();
		QFile temp(qstrPath);
		bool tqc = temp.open(QIODevice::WriteOnly);
		temp.close();
		return;
	}
	CString cslList[5];
	CString cstrPath = qstrPath.toStdWString().data();
	for (int i = 0; i < 5; i++)
	{
		CString strDefault;
		strDefault.Format(_T("%d"), i + 1);
		CString value = ReadStringFromFile("Head", strDefault, "NOFOUND", cstrPath);
		if (value == "NOFOUND")
			break;
		cslList[i] = value;
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; ; j++)
		{
			CString cstrKey;
			cstrKey.Format(_T("%d"), j + 1);
			CString strChlidName = ReadStringFromFile(cslList[i], cstrKey, _T("NOFOUND"), cstrPath);
			if (strChlidName == _T("NOFOUND"))
				break;
			QString qstrStopCause = QString::fromStdWString(strChlidName.GetBuffer());
			strChlidName.ReleaseBuffer();
			switch (i)
			{
			case 0:
				m_qslStopCause1 << qstrStopCause;
				break;
			case 1:
				m_qslStopCause2 << qstrStopCause;
				break;
			case 2:
				m_qslStopCause3 << qstrStopCause;
				break;
			case 3:
				m_qslStopCause4 << qstrStopCause;
				break;
			case 4:
				m_qslStopCause5 << qstrStopCause;
				break;
			default:
				break;
			}
		}
	}
}

void UI_StopCauseListDialog::InitConnect()
{
	connect(m_pStopList1ButtonGroup, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(SlotButtonGroup1Click(QAbstractButton*)));
	connect(m_pStopList2ButtonGroup, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(SlotButtonGroup2Click(QAbstractButton*)));
	connect(m_pStopList3ButtonGroup, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(SlotButtonGroup3Click(QAbstractButton*)));
	connect(m_pStopList4ButtonGroup, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(SlotButtonGroup4Click(QAbstractButton*)));
	connect(m_pStopList5ButtonGroup, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(SlotButtonGroup5Click(QAbstractButton*)));
}

void UI_StopCauseListDialog::SlotButtonGroup1Click(QAbstractButton *button)
{
	My_PushButton* pResultButton = (My_PushButton*)button;
	m_nSelStopCode = pResultButton->m_dwStopCord;
	m_qstrStopCause = pResultButton->text();
	close();
}

void UI_StopCauseListDialog::SlotButtonGroup2Click(QAbstractButton *button)
{
	My_PushButton* pResultButton = (My_PushButton*)button;
	m_nSelStopCode = pResultButton->m_dwStopCord;
	m_qstrStopCause = pResultButton->text();
	close();
}

void UI_StopCauseListDialog::SlotButtonGroup3Click(QAbstractButton *button)
{
	My_PushButton* pResultButton = (My_PushButton*)button;
	m_nSelStopCode = pResultButton->m_dwStopCord;
	m_qstrStopCause = pResultButton->text();
	close();
}

void UI_StopCauseListDialog::SlotButtonGroup4Click(QAbstractButton *button)
{
	My_PushButton* pResultButton = (My_PushButton*)button;
	m_nSelStopCode = pResultButton->m_dwStopCord;
	m_qstrStopCause = pResultButton->text();
	close();
}

void UI_StopCauseListDialog::SlotButtonGroup5Click(QAbstractButton *button)
{
	My_PushButton* pResultButton = (My_PushButton*)button;
	m_nSelStopCode = pResultButton->m_dwStopCord;
	m_qstrStopCause = pResultButton->text();
	close();
}

void UI_StopCauseListDialog::SetStopButton(QStringList qslStopCause1, QStringList qslStopCause2, QStringList qslStopCause3, QStringList qslStopCause4, QStringList qslStopCause5)
{
	//每一组最大长度
	int nMaxNum = -1;
	int nGroup1Num = qslStopCause1.length();
	nMaxNum = nGroup1Num;

	int nGroup2Num = qslStopCause2.length();
	if (nMaxNum < nGroup2Num)
		nMaxNum = nGroup2Num;

	int nGroup3Num = qslStopCause3.length();
	if (nMaxNum < nGroup3Num)
		nMaxNum = nGroup3Num;

	int nGroup4Num = qslStopCause4.length();
	if (nMaxNum < nGroup4Num)
		nMaxNum = nGroup4Num;

	int nGroup5Num = qslStopCause5.length();
	if (nMaxNum < nGroup5Num)
		nMaxNum = nGroup5Num;

	for (int i = 0; i < nMaxNum; i++)
	{
		//第一组
		if (i < nGroup1Num)
		{
			QString strStopCause = qslStopCause1.at(i);
			QString strText = strStopCause.split(",").at(0);
			int StopCord = strStopCause.split(",").at(1).toInt();
			My_PushButton* m_pMyButton = new My_PushButton(StopCord,ui.LW_StopCauseList1);
			m_pMyButton->setText(strText);
			m_pMyButton->setMinimumSize(QSize(100, 40));
			m_pMyButton->setMaximumSize(QSize(120, 45));
			m_pStopList1ButtonGroup->addButton(m_pMyButton, i);
			m_pMyButton->setGeometry(5, i * 75 + 15, 120, 45);

			//QListWidgetItem* addButtonItem = new QListWidgetItem;
			//addButtonItem->setSizeHint(QSize(125, 75));
			//ui.LW_StopCauseList1->addItem(addButtonItem);
			//ui.LW_StopCauseList1->setItemWidget(addButtonItem, m_pMyButton);
			//ui.LW_StopCauseList1->setEnabled(false);
		}
		//第二组
		if (i < nGroup2Num)
		{
			QString strStopCause = qslStopCause2.at(i);
			QString strText = strStopCause.split(",").at(0);
			int StopCord = strStopCause.split(",").at(1).toInt();
			My_PushButton* m_pMyButton = new My_PushButton(StopCord,ui.LW_StopCauseList2);
			m_pMyButton->setText(strText);
			m_pMyButton->setMinimumSize(QSize(100, 40));
			m_pMyButton->setMaximumSize(QSize(120, 45));
			m_pMyButton->setGeometry(5, i * 75 + 15, 120, 45);
			m_pStopList2ButtonGroup->addButton(m_pMyButton, i);

			//QListWidgetItem* addButtonItem = new QListWidgetItem;
			//addButtonItem->setSizeHint(QSize(131, 75));
			//ui.LW_StopCauseList2->addItem(addButtonItem);
			//ui.LW_StopCauseList2->setItemWidget(addButtonItem, m_pMyButton);
		}
		//第三组
		if (i < nGroup3Num)
		{
			QString strStopCause = qslStopCause3.at(i);
			QString strText = strStopCause.split(",").at(0);
			int StopCord = strStopCause.split(",").at(1).toInt();
			My_PushButton* m_pMyButton = new My_PushButton(StopCord,ui.LW_StopCauseList3);
			m_pMyButton->setText(strText);
			m_pMyButton->setMinimumSize(QSize(100, 40));
			m_pMyButton->setMaximumSize(QSize(120, 45));
			m_pStopList3ButtonGroup->addButton(m_pMyButton, i);
			m_pMyButton->setGeometry(5, i * 75 + 15, 120, 45);

			//QListWidgetItem* addButtonItem = new QListWidgetItem;
			//addButtonItem->setSizeHint(QSize(131, 75));
			//ui.LW_StopCauseList3->addItem(addButtonItem);
			//ui.LW_StopCauseList3->setItemWidget(addButtonItem, m_pMyButton);
		}
		//第四组
		if (i < nGroup1Num)
		{
			QString strStopCause = qslStopCause4.at(i);
			QString strText = strStopCause.split(",").at(0);
			int StopCord = strStopCause.split(",").at(1).toInt();
			My_PushButton* m_pMyButton = new My_PushButton(StopCord,ui.LW_StopCauseList4);
			m_pMyButton->setText(strText);
			m_pMyButton->setMinimumSize(QSize(100, 40));
			m_pMyButton->setMaximumSize(QSize(120, 45));
			m_pMyButton->setGeometry(5, i * 75 + 15, 120, 45);
			m_pStopList4ButtonGroup->addButton(m_pMyButton, i);

			//QListWidgetItem* addButtonItem = new QListWidgetItem;
			//addButtonItem->setSizeHint(QSize(131, 75));
			//ui.LW_StopCauseList4->addItem(addButtonItem);
			//ui.LW_StopCauseList4->setItemWidget(addButtonItem, m_pMyButton);
		}
		//第五组
		if (i < nGroup1Num)
		{
			QString strStopCause = qslStopCause5.at(i);
			QString strText = strStopCause.split(",").at(0);
			int StopCord = strStopCause.split(",").at(1).toInt();
			My_PushButton* m_pMyButton = new My_PushButton(StopCord,ui.LW_StopCauseList5);
			m_pMyButton->setText(strText);
			m_pMyButton->setMinimumSize(QSize(100, 40));
			m_pMyButton->setMaximumSize(QSize(120, 45));
			m_pMyButton->setGeometry(5, i * 75 + 15, 120, 45);
			m_pStopList5ButtonGroup->addButton(m_pMyButton, i);

			//QListWidgetItem* addButtonItem = new QListWidgetItem;
			//addButtonItem->setSizeHint(QSize(131, 75));
			//ui.LW_StopCauseList5->addItem(addButtonItem);
			//ui.LW_StopCauseList5->setItemWidget(addButtonItem, m_pMyButton);
		}
	}
}

void UI_StopCauseListDialog::SetAlarmInfo(QString strAlarmInfo)
{
	ui.TE_Alarm_Info->setText(strAlarmInfo);
}

bool UI_StopCauseListDialog::DoModel(int& nStopCard, QString& strStopCause)
{
Flag:
	exec();
	if (-1 == m_nSelStopCode)
	{
		MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("请选择一个停机原因"), DOMODEL, 0);
		goto Flag;
	}
	nStopCard = m_nSelStopCode;
	strStopCause = m_qstrStopCause;
	m_nSelStopCode = -1;
	m_qstrStopCause = "";
	return true;
}

/*自定义Button*/
My_PushButton::My_PushButton(int nStopCard, QWidget* parent /*= Q_NULLPTR*/)
	:m_dwStopCord(nStopCard),QPushButton(parent)
{
	QFont font(QString::fromLocal8Bit("微软雅黑"), 10);
	setFont(font);
	setStyleSheet("background-color: white;");
}

My_PushButton::~My_PushButton()
{

}
