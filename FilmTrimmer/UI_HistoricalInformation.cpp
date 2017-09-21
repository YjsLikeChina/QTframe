#include "UI_HistoricalInformation.h"
#include <QFile>
#include <QTextStream>
#include "UI_MessageBox.h"
#include "LogManager.h"
UI_HistoricalInformation::UI_HistoricalInformation(QWidget* parent /*= Q_NULLPTR*/)
	:QWidget(parent),UI_InterfaceBase(parent)
{
	ui.setupUi(this);
	initVal();
	initUI();
	initConnect();
}

UI_HistoricalInformation::~UI_HistoricalInformation()
{
}

void UI_HistoricalInformation::initVal()
{
	m_strIconFile = QCoreApplication::applicationDirPath();
	m_nLastIndex = -1;
	m_bAutoUpdateLock = false;
}

void UI_HistoricalInformation::initUI()
{
	QString qstrIconPath = m_strIconFile + "/Image/Diaphaneity2.png";
	ui.LB_Background1->setScaledContents(true);
	ui.LB_Background1->setPixmap(QPixmap(qstrIconPath));
	ui.LB_Background2->setScaledContents(true);
	ui.LB_Background2->setPixmap(QPixmap(qstrIconPath));

	qstrIconPath = m_strIconFile + "/Image/LaserStepDelete.png";
	ui.PB_CleanHistoryFile->setIcon(QIcon(qstrIconPath));
	ui.PB_CleanHistoryFile->setIconSize(QSize(28, 28));
	ui.PB_CleanHistoryFile->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	ui.PB_AlarmScreen->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	ui.TW_HistoryInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽
	ui.TW_HistoryInfo->verticalHeader()->setDefaultSectionSize(35); //设置行高
	ui.TW_HistoryInfo->verticalHeader()->setVisible(false); //设置垂直头不可见
	ui.TW_HistoryInfo->setSelectionMode(QAbstractItemView::SingleSelection); //只能单选
	ui.TW_HistoryInfo->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
	ui.TW_HistoryInfo->horizontalHeader()->setFixedHeight(38); //设置表头的高度
	ui.TW_HistoryInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.TW_HistoryInfo->setStyleSheet("selection-background-color:lightblue; gridline-color:white;"); //设置选中背景色
	ui.TW_HistoryInfo->setFocusPolicy(Qt::NoFocus);
}

void UI_HistoricalInformation::initConnect()
{
	connect(ui.CB_HistoryInfoSel, SIGNAL(activated(int)), this, SLOT(SlotSwitchSection(int)));
	connect(ui.PB_CleanHistoryFile, SIGNAL(clicked()), this, SLOT(SlotCleanHistoryFile()));
}

void UI_HistoricalInformation::SlotSwitchSection(int nIndex)
{
	if (m_nLastIndex == nIndex)
		return;
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_{[操作:选择切换不同页面历史数据,切换页面为:%2").arg(__func__).arg(nIndex));
	m_nLastIndex = nIndex;
	QStringList qslHead = m_qMapHistoryInfoHead.value(nIndex);
	if (qslHead.isEmpty())
		return;
	//清除所有
	ui.TW_HistoryInfo->setRowCount(0);
	//设置列头
	ui.TW_HistoryInfo->setColumnCount(qslHead.length());
	ui.TW_HistoryInfo->setHorizontalHeaderLabels(qslHead);

	//进行数据更新
	if(!m_qMapIsAutoUpdata.value(nIndex))//不需要自动更新的
	{
		QFile file(m_qMapHistoryInfoPath.value(nIndex));
		if (!file.open(QIODevice::ReadOnly))
		{
			MESSAGEBOX.SlotNewMessAgeBoxData(QString::fromLocal8Bit("打开历史文件失败"),NODOMODEL);
			LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_操作:切换页面失败,打开历史文件失败,切换页面为:%2").arg(__func__).arg(nIndex));
			return;
		}

		QTextStream* FileInfoStream = new QTextStream(&file);//文本流  
		QStringList qslFileInfo = FileInfoStream->readAll().split("\n");//每行以\n区分
		ui.TW_HistoryInfo->setRowCount(0);
		ui.TW_HistoryInfo->clearContents();
		for (int i = qslFileInfo.count() - 1, nItem = 0; i >= 0; i--, nItem++)
		{
			ui.TW_HistoryInfo->insertRow(nItem);
			QStringList tempbar = qslFileInfo.at(i).split(",");//一行中的单元格以，区分
			for (int j = 0; j <= tempbar.size() - 1; j++)
			{
				QString strinfo = tempbar[j];
				ui.TW_HistoryInfo->setItem(nItem, j, new QTableWidgetItem(strinfo));
				this->show();
			}
		}
		ui.TW_HistoryInfo->removeRow(0);

		file.close();//操作完成后记得关闭文件 
	}
}

void UI_HistoricalInformation::SlotCleanHistoryFile()
{
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[层次: UI层]_[函数名 : %1]_{[操作:清除历史文件").arg(__func__));
	emit SigCleanHistoryFile(m_qMapHistoryInfoPath.value(m_nLastIndex));
}

bool UI_HistoricalInformation::insertModule(QVector<ST_MODULE>* cfgModuleInfo)
{
	int nLength = cfgModuleInfo->length();
	for (int i = 0; i < nLength; i++)
	{
		ui.CB_HistoryInfoSel->addItem(cfgModuleInfo->at(i).ModuleName);
		int ItemHeadNum = cfgModuleInfo->at(i).m_nModuleLength();
		QStringList qslHead;
		qslHead.clear();
		for (int j = 0; j < ItemHeadNum; j++)
		{
			if (j == 0)
				m_qMapHistoryInfoPath.insert(i, cfgModuleInfo->at(i).Value_.at(j).Function_name);
			else
				qslHead << cfgModuleInfo->at(i).Value_.at(j).Function_name;
		}
		if (AUTOUPDATA == cfgModuleInfo->at(i).Value_.at(0).OtherAttribute)
		{
			m_qMapIsAutoUpdata.insert(i, true);
		}
		else
		{
			m_qMapIsAutoUpdata.insert(i, false);
		}
		m_qMapHistoryInfoHead.insert(i, qslHead);
		
	}
	return true;
}

bool UI_HistoricalInformation::AutoUpdateData(int nIndex, QStringList qstrListInfo)
{
	if (m_bAutoUpdateLock)
		return false;
	m_bAutoUpdateLock = true;
	if (nIndex != m_nLastIndex)
	{
		return false;
	}
	int nHeadLength = m_qMapHistoryInfoHead.value(nIndex).length();
	//解析字符串
	int nDataCount = qstrListInfo.length();
	for (int i = 0; i < nDataCount; i++)
	{
		QStringList qstrSingInfo = qstrListInfo.at(i).split(",");
		if(qstrSingInfo.length() < nHeadLength)
			break;
		ui.TW_HistoryInfo->insertRow(i); //插入一行
		for (int j = 0; j < nHeadLength; j++)
		{
			ui.TW_HistoryInfo->item(i, j)->setText(qstrSingInfo.at(j));
		}
	}
	m_bAutoUpdateLock = false;
	return true;
}

void UI_HistoricalInformation::SkipCurrentPage()
{
	SlotSwitchSection(0);
}

bool UI_HistoricalInformation::GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal)
{
	return true;
}
