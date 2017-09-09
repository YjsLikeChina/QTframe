#include "UI_AutoProduction.h"

#define ROWWIDTH	271
#define ROWHEIGHT	40

UI_AutoProduction::UI_AutoProduction()
{
	ui.setupUi(this);
	initVal();
	initUI();
	initConnect();
}


UI_AutoProduction::~UI_AutoProduction()
{
}

void UI_AutoProduction::initConnect()
{
	connect(ui.TRW_ModuleTree, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(SlotItemChanged(QTreeWidgetItem*, int)));
	connect(ui.TRW_ModuleTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(SlotItemDoubleClicked(QTreeWidgetItem*, int)));
}

void UI_AutoProduction::initUI()
{
	QStringList qslHead;
	qslHead << QString::fromLocal8Bit("模组名") << QString::fromLocal8Bit("值");
	ui.TRW_ModuleTree->setHeaderLabels(qslHead);
	ui.TRW_ModuleTree->setColumnWidth(0, 170);
	ui.lcdNumber->setDigitCount(6);
	ui.lcdNumber->setSmallDecimalPoint(true);
	ui.lcdNumber_2->setDigitCount(6);
	ui.lcdNumber_2->setSmallDecimalPoint(true);
	ui.lcdNumber_3->setDigitCount(6);
	ui.lcdNumber_3->setSmallDecimalPoint(true);
	ui.lcdNumber_4->setDigitCount(6);
	ui.lcdNumber_4->setSmallDecimalPoint(true);
	ui.lcdNumber_5->setDigitCount(6);
	ui.lcdNumber_5->setSmallDecimalPoint(true);
	//设置背景
	QString qstrIconFile = QCoreApplication::applicationDirPath();
	QString qstrIconPath = qstrIconFile + "/Image/Diaphaneity2.png";
	//ui.LB_Background1->setScaledContents(true);
	//ui.LB_Background1->setPixmap(QPixmap(qstrIconPath));
	//ui.LB_Background2->setScaledContents(true);
	//ui.LB_Background2->setPixmap(QPixmap(qstrIconPath));
}

void UI_AutoProduction::initVal()
{
	m_Painter = new QPainter;
	m_bAutoUpdateLock = false;
}
void UI_AutoProduction::PaintElectronicMeter(double x, double y, double r, bool Release)
{
	double bad_value = r / 4;
	QRectF Pie1, Pie2, Pie3;
	Pie1.setX(x); Pie1.setY(y);
	Pie1.setWidth(r); Pie1.setHeight(r);
	Pie2.setX(x + bad_value / 2);
	Pie2.setY(y + bad_value / 2);
	Pie2.setWidth(r - bad_value); Pie2.setHeight(r - bad_value);
	Pie3.setX(x + 3 * bad_value / 2);
	Pie3.setY(y + 3 * bad_value / 2);
	Pie3.setWidth(r - 3 * bad_value); Pie3.setHeight(r - 3 * bad_value);
	m_Painter->setPen(Qt::NoPen);
	//ui.label_15
	//m_Painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));//设置画刷形式 
	m_Painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));//
	m_Painter->drawPie(Pie1, 480, 320);
	m_Painter->drawPie(Pie1, 2080, 320);

	m_Painter->setBrush(QBrush(Qt::yellow, Qt::SolidPattern));//
	m_Painter->drawPie(Pie1, 800, 320);
	m_Painter->drawPie(Pie1, 1760, 320);

	m_Painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));//
	m_Painter->drawPie(Pie1, 1120, 640);

	m_Painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));//
	m_Painter->drawPie(Pie2, 480, 1920);

	m_Painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));//
	m_Painter->drawPie(Pie3, 480, 1920);


	m_Painter->setPen(Qt::SolidLine);
	m_Painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));//
	double angle = 0;
	double m_Curtension = m_ReCurtension;
	double m_Mintension = m_ReMintension;
	double m_Maxtension = m_ReMaxtension;
	if (Release)
	{
		 m_Curtension = m_PuCurtension;
		 m_Mintension = m_PuMintension;
		 m_Maxtension = m_PuMaxtension;
		 ui.lcdNumber_5->display(m_Curtension);
	}
	else 
	{
		ui.lcdNumber_4->display(m_Curtension);
	}
	if (m_Curtension >= m_Mintension&&m_Curtension <= m_Maxtension)
	{
		double bad = m_Maxtension - m_Mintension;
		double rangle = m_Maxtension + m_Mintension;
		double rangleaver = rangle / 2;
		double badvalue = m_Curtension - rangleaver;
		angle = badvalue / (bad / 2) * 60;
	}
	else
		angle = -60.0;
	m_Painter->translate(Pie1.x() + r / 2.0, Pie1.y() + r / 2.0);
	m_Painter->rotate(angle);
	m_Painter->drawLine(0, 0, 0, 10 - r / 2);
	m_Painter->resetTransform();
}
void UI_AutoProduction::PaintConnectLine()
{
	m_Painter->drawLine(ui.label->x() + ui.label->width(), ui.label->y() + ui.label->height() / 2.0, ui.label_9->x(), ui.label_9->y() + ui.label_9->height() / 2.0);

	m_Painter->drawLine(ui.label_9->x() + ui.label_9->width() / 2.0, ui.label_9->y(), ui.label_12->x() + ui.label_12->width() - 2, ui.label_12->y());

	m_Painter->drawLine(ui.label_12->x() + ui.label_12->width() - 2, ui.label_12->y() + ui.label_12->height() - 2, ui.label_7->x(), ui.label_7->y() + ui.label_7->height() / 2.0);

	m_Painter->drawLine(ui.label_7->x() + ui.label_7->width(), ui.label_7->y() + ui.label_7->height() / 2.0, ui.label_11->x() + ui.label_11->width() / 2, ui.label_11->y());

	m_Painter->drawLine(ui.label_11->x() + ui.label_11->width(), ui.label_11->y() + ui.label_11->height() / 2.0, ui.label_8->x() + ui.label_8->width() / 2, ui.label_8->y());

	m_Painter->drawLine(ui.label_8->x() + ui.label_8->width() / 2.0, ui.label_8->y() + ui.label_8->height(), ui.label_4->x() + ui.label_4->width() / 2.0, ui.label_4->y() + ui.label_4->height());

	m_Painter->drawLine(ui.label_4->x() + ui.label_4->width(), ui.label_4->y() + ui.label_4->height() / 2.0, ui.label_10->x(), ui.label_10->y() + ui.label_10->height() / 2.0);

	m_Painter->drawLine(ui.label_10->x() + ui.label_10->width(), ui.label_10->y() + ui.label_10->height() / 2.0, ui.label_3->x(), ui.label_3->y() + ui.label_3->height() / 2.0);
}
void UI_AutoProduction::paintEvent(QPaintEvent*)
{
	ui.TRW_ModuleTree->setVisible(false);
	//QRect chidUi;
	//	chidUi = ui.TRW_ModuleTree->geometry();
	//if(!ui.TRW_ModuleTree->isVisible())
	//	chidUi.setWidth(124);
	//QRect UIre = this->geometry();
	//QRectF myuir;
	//myuir.setX(0);
	//myuir.setY(0);
	//myuir.setWidth(UIre.width() - chidUi.width());
	//myuir.setHeight(chidUi.height());
	//double bad_value = myuir.width() / 4.0;
	//double badyvalue = myuir.height() / 3.0;
	//m_Painter = new QPainter(this);
	//m_Painter->setPen(QPen(Qt::red));//设置画笔形式 
	//m_Painter->setRenderHint(QPainter::Antialiasing, true);
	//PaintConnectLine();
	//m_Painter->translate(0, chidUi.y());
	//for (int i = 0; i < 3; i++)
	//{
	//	//m_Painter->drawLine(bad_value + i*bad_value, 0, bad_value + i*bad_value, myuir.height());
	//	switch (i)
	//	{
	//	case 0: {
	//		double r = bad_value;
	//		double x = bad_value / 2;
	//		double y = (badyvalue - bad_value) / 2 + badyvalue;
	//		PaintElectronicMeter(x, y, 150);
	//		m_Painter->translate(0, chidUi.y());
	//		x = x + 2 * bad_value;
	//		PaintElectronicMeter(x, y, 180);
	//		m_Painter->translate(0, chidUi.y());
	//	}break;
	//	case 100: {
	//		m_Painter->drawEllipse(0, badyvalue + badyvalue*i, bad_value, badyvalue);
	//		m_Painter->drawEllipse(0 +3*bad_value, badyvalue + badyvalue*i, bad_value, badyvalue);
	//	} break;
	//	default:
	//		break;
	//	}
	//}
	m_Painter = new QPainter(this);
	QPen *qpen = new QPen;
	qpen->setColor(Qt::red);
	qpen->setWidth(2);
	m_Painter->setPen(*qpen);//设置画笔形式 
	m_Painter->setRenderHint(QPainter::Antialiasing, true);

	PaintConnectLine();
	PaintElectronicMeter((ui.label_9->x() + ui.label_9->width() / 2.0) - 75, ui.label_9->y() - 80, 150);
	PaintElectronicMeter((ui.label_10->x() + ui.label_10->width() / 2.0) - 75, ui.label_10->y() - 80, 150,false);
}


bool UI_AutoProduction::GetModifyParam(QMap<QString, QString>& mapModifyVal)
{
	mapModifyVal = m_mapModifyVal;
	return true;
}

bool UI_AutoProduction::insertModule(QVector<ST_MODULE>* pQVector)
{
	int nParentLength = pQVector->length(); //模组个数
	for (int i = 0; i < nParentLength; i++)
	{
		ST_MODULEITEM _moduleItem;
		
		QTreeWidgetItem* DataModule = new QTreeWidgetItem(ui.TRW_ModuleTree, QStringList(pQVector->at(i).ModuleName));
		_moduleItem.ParentModuleItem = DataModule;
		DataModule->setSizeHint(0, QSize(ROWWIDTH, ROWHEIGHT));

		int nChildLength = pQVector->at(i).m_nModuleLength();
		for (int j = 0; j < nChildLength; j++) //子项
		{
			QTreeWidgetItem* ChildModule = new QTreeWidgetItem(DataModule, QStringList(pQVector->at(i).Value_.at(j).Function_name));
			ChildModule->setSizeHint(0,QSize(ROWWIDTH, ROWHEIGHT));
			QString strVal;
			if (pQVector->at(i).Value_.at(j).Vel_Type == _INT)
				strVal = QString::number(pQVector->at(i).Value_.at(j).Vel);
			else
				strVal = QString::number(pQVector->at(i).Value_.at(j).Vel, 'g', 8);

			if (ENABLEEDIT == pQVector->at(i).Value_.at(j).OtherAttribute)
				ui.TRW_ModuleTree->openPersistentEditor(ChildModule, 1);
				//ChildModule->o//setFlags(ChildModule->flags() | Qt::ItemIsEditable);
			else
				ChildModule->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

			ChildModule->setData(1, Qt::DisplayRole, strVal);

			_moduleItem.ChildModuleItems.push_back(ChildModule);
		}
		m_ModuleVector.push_back(_moduleItem);
	}
	m_nModuleNum = m_ModuleVector.length();
	return true;
}

bool UI_AutoProduction::AutoUpdateData(QList<ST_UPDATEDATA> AutoUpdateVal)
{
	if (m_bAutoUpdateLock)
		return false;
	m_bAutoUpdateLock = true;
	int nLength = AutoUpdateVal.length();
	int nModuleItem = -1, nChildItem = -1;
	for (int i = 0; i < nLength; i++)
	{

		//获取更新数据
		QString qstrVal = QString::number(AutoUpdateVal.at(i).dlData, 'g');
		if (i < 5)
		{
			switch (i)
			{
			case 0: {
				m_ReRollingDiameter = qstrVal.toDouble();
			}break;
			case 1: {
				m_ReCurtension = qstrVal.toDouble();
			}break;
			case 2: {
				m_PuRollingDiameter = qstrVal.toDouble();
			}break;
			case 3: {
				m_PuRollingDiameter = qstrVal.toDouble();
			}break;
			case 4: {
				m_WorkSpeed = qstrVal.toDouble();
			}break;
			default:
				break;
			}
		
		}
		nModuleItem = AutoUpdateVal.at(i).nModuleItem;
		nChildItem = AutoUpdateVal.at(i).nChildItem;

		//查找到修改的Item
		m_ModuleVector.at(nModuleItem).ChildModuleItems.at(nChildItem)->setText(1, qstrVal);
	}
	m_bAutoUpdateLock = false;
	update();
	return true;
}

void UI_AutoProduction::SkipCurrentPage()
{
	m_mapModifyVal.clear();
	//获取当前页面的值

}

void UI_AutoProduction::SetDefault(double MaxRe, double MinRe, double MaxPu, double MinPu)
{
	m_ReMaxtension = MaxRe;
	m_ReMintension = MinRe;
	m_PuMaxtension = MaxPu;
	m_PuMintension = MinPu;
}

void UI_AutoProduction::SlotItemChanged(QTreeWidgetItem *item, int column)
{
	QString strModifyItem = item->text(0);

	if (m_mapModifyVal.find(strModifyItem) != m_mapModifyVal.end())
	{
		m_mapModifyVal.remove(strModifyItem);
	}
	QString strModifyVal = item->text(1);
	m_mapModifyVal.insert(strModifyItem, strModifyVal);

	if (m_LastDoubleChickItem == item) //暂时使用失去焦点，发送参数，后续添加按钮
	{
		QTreeWidgetItem* CurItemParent = item->parent();
		int nModuleNum = ui.TRW_ModuleTree->indexOfTopLevelItem(CurItemParent);
		int nChildNum = CurItemParent->indexOfChild(item);
		double dlData = item->text(1).toDouble();

		emit SigItemChanged(nModuleNum, nChildNum, dlData);
	}
}

void UI_AutoProduction::SlotItemDoubleClicked(QTreeWidgetItem *item, int column)
{
	m_LastDoubleChickItem = item;
}
