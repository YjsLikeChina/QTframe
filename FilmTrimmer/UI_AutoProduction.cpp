#include "UI_AutoProduction.h"
#include <QCoreApplication>
#define ROWWIDTH	271
#define ROWHEIGHT	40

UI_AutoProduction::UI_AutoProduction(QWidget* parent /*= Q_NULLPTR*/)
	:QWidget(parent),UI_InterfaceBase(parent)
{
	ui.setupUi(this);
	initVal();
	initUI();
	initConnect();
	//��Controller
	m_pCtrlAutoProduction = new CTRL_AutoProduction;
	m_pCtrlAutoProduction->SetUIInterface(this);
}

UI_AutoProduction::~UI_AutoProduction()
{
	delete m_Painter;
	m_Painter = NULL;
	delete m_pWorkSpeedInputDlg;
}

void UI_AutoProduction::initConnect()
{
	connect(ui.TRW_ModuleTree, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(SlotItemChanged(QTreeWidgetItem*, int)));
	connect(ui.PB_RunDirection, SIGNAL(clicked()), this, SLOT(SlotRunDirection()));
	connect(ui.PB_OnloadDirection, SIGNAL(clicked()), this, SLOT(SlotOnloadDirection()));

	connect(ui.PB_SendloadFW, SIGNAL(pressed()), this, SLOT(SlotOnloadClockwiseP()));
	connect(ui.PB_SendloadFW, SIGNAL(released()), this, SLOT(SlotOnloadClockwiseR()));

	connect(ui.PB_SendloadRE, SIGNAL(pressed()), this, SLOT(SlotOnloadAnticlockwiseP()));
	connect(ui.PB_SendloadRE, SIGNAL(released()), this, SLOT(SlotOnloadAnticlockwiseR()));

	connect(ui.PB_MainAxisFW, SIGNAL(pressed()), this, SLOT(SlotMainAxisClockwiseP()));
	connect(ui.PB_MainAxisFW, SIGNAL(released()), this, SLOT(SlotMainAxisClockwiseR()));

	connect(ui.PB_MainAxisRE, SIGNAL(pressed()), this, SLOT(SlotMainAxisAnticlockwiseP()));
	connect(ui.PB_MainAxisRE, SIGNAL(released()), this, SLOT(SlotMainAxisAnticlockwiseR()));

	connect(ui.PB_RecvloadFW, SIGNAL(pressed()), this, SLOT(SlotRecvClockwiseP()));
	connect(ui.PB_RecvloadFW, SIGNAL(released()), this, SLOT(SlotRecvClockwiseR()));

	connect(ui.PB_RecvloadRE, SIGNAL(pressed()), this, SLOT(SlotRecvAnticlockwiseP()));
	connect(ui.PB_RecvloadRE, SIGNAL(released()), this, SLOT(SlotRecvAnticlockwiseR()));

	//����¼�����
	ui.LB_DataListShow->installEventFilter(this);
	ui.label_MainAxis->installEventFilter(this);
	ui.label_Laser1->installEventFilter(this);
	ui.label_Laser2->installEventFilter(this);
}

void UI_AutoProduction::initUI()
{
	QStringList qslHead;
	qslHead << QString::fromLocal8Bit("ģ����") << QString::fromLocal8Bit("ֵ");
	ui.TRW_ModuleTree->setHeaderLabels(qslHead);
	ui.TRW_ModuleTree->setColumnWidth(0, 140);
	//ui.LCD_OnloadDiameter->setDigitCount(6);
	//ui.LCD_OnloadDiameter->setSmallDecimalPoint(true);
	//ui.LCD_OnloadTension->setDigitCount(6);
	//ui.LCD_OnloadTension->setSmallDecimalPoint(true);
	//ui.LCD_RecvDiameter->setDigitCount(6);
	//ui.LCD_RecvDiameter->setSmallDecimalPoint(true);
	//ui.LCD_RecvTension->setDigitCount(6);
	//ui.LCD_RecvTension->setSmallDecimalPoint(true);
	//ui.LCD_WorkSpeedShow->setDigitCount(6);
	//ui.LCD_WorkSpeedShow->setSmallDecimalPoint(true);
	//���ñ���
	QString qstrIconFile = QCoreApplication::applicationDirPath();
	QString qstrIconPath = qstrIconFile + "/Image/Background.png";
	ui.LB_Background1->setPixmap(QPixmap(qstrIconPath));
	ui.LB_Background1->setScaledContents(true);
	ui.LB_Background1->setVisible(false);
	//�б�����
	ui.TRW_ModuleTree->setVisible(false);
	qstrIconPath = qstrIconFile + "/Image/Slide2.png";
	m_qPixmapOtherDataShow.load(qstrIconPath);
	qstrIconPath = qstrIconFile + "/Image/Slide.png";
	m_qPixmapOtherDataHide.load(qstrIconPath);
	ui.LB_DataListShow->setPixmap(m_qPixmapOtherDataShow);
	ui.LB_DataListShow->setScaledContents(true);
	ui.LB_DataListShow->setStyleSheet("background: transparent;");
	ui.LB_Info->setVisible(false);

	//ui.TRW_ModuleTree->setStyleSheet("QTreeWiget::item {border: 1px solid #d9d9d9;border-top-color: transparent;border-bottom-color: transparent;}");

	//�������
	qstrIconPath = qstrIconFile + "/Image/LaserStepDelete.png"; 
	ui.PB_CleanYield->setIcon(QIcon(qstrIconPath));
	ui.PB_CleanYield->setIconSize(QSize(25, 25)); // border-style: outset;
	ui.PB_CleanYield->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white;border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	//���ذ�ť
	ui.Btn_Put->setVisible(false);
	ui.Btn_Get->setVisible(false);

	//�������з���ť
	qstrIconPath = qstrIconFile + "/Image/OnloadDirectionA.png";
	m_qIconOnloadDirFW.addFile(qstrIconPath);
	qstrIconPath = qstrIconFile + "/Image/OnloadDirectionB.png";
	m_qIconOnloadDirRE.addFile(qstrIconPath);
	ui.PB_OnloadDirection->setIcon(m_qIconOnloadDirFW);
	ui.PB_OnloadDirection->setIconSize(QSize(30, 30));
	ui.PB_OnloadDirection->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	//���÷ž���ť
	qstrIconPath = qstrIconFile + "/Image/RunDirB.png";
	m_qIconRunDirFW.addFile(qstrIconPath);
	qstrIconPath = qstrIconFile + "/Image/RunDirF.png";
	m_qIconRunDirRE.addFile(qstrIconPath);
	ui.PB_RunDirection->setIcon(m_qIconRunDirFW);
	ui.PB_RunDirection->setIconSize(QSize(30, 30));
	ui.PB_RunDirection->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white;border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	//�����շž���ǣ��ͼ��
	qstrIconPath = qstrIconFile + "/Image/OnloadDirectionA.png"; //�ž���ת 
	ui.PB_SendloadFW->setIcon(QIcon(qstrIconPath));
	ui.PB_SendloadFW->setIconSize(QSize(25, 25));
	ui.PB_SendloadFW->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/OnloadDirectionB.png"; //�ž�ת
	ui.PB_SendloadRE->setIcon(QIcon(qstrIconPath));
	ui.PB_SendloadRE->setIconSize(QSize(25, 25));
	ui.PB_SendloadRE->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/OnloadDirectionA.png"; //��ǣ����ת 
	ui.PB_MainAxisFW->setIcon(QIcon(qstrIconPath));
	ui.PB_MainAxisFW->setIconSize(QSize(25, 25));
	ui.PB_MainAxisFW->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/OnloadDirectionB.png"; //��ǣ����ת
	ui.PB_MainAxisRE->setIcon(QIcon(qstrIconPath));
	ui.PB_MainAxisRE->setIconSize(QSize(25, 25));
	ui.PB_MainAxisRE->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white;border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/OnloadDirectionA.png"; //�վ���ת 
	ui.PB_RecvloadFW->setIcon(QIcon(qstrIconPath));
	ui.PB_RecvloadFW->setIconSize(QSize(25, 25));
	ui.PB_RecvloadFW->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	qstrIconPath = qstrIconFile + "/Image/OnloadDirectionB.png"; //�վ�ת
	ui.PB_RecvloadRE->setIcon(QIcon(qstrIconPath));
	ui.PB_RecvloadRE->setIconSize(QSize(25, 25));
	ui.PB_RecvloadRE->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	//����ͼ���趨
	qstrIconPath = qstrIconFile + "/Image/LaserNoEnable.png";
	m_qPixmapLaserStatusNoEnable.load(qstrIconPath);
	qstrIconPath = qstrIconFile + "/Image/LaserEnable.png";
	m_qPixmapLaserStatusEnableNoConnect.load(qstrIconPath);
	qstrIconPath = qstrIconFile + "/Image/LaserReady.png";
	m_qPixmapLaserStatusConnectNoRun.load(qstrIconPath);
	qstrIconPath = qstrIconFile + "/Image/LaserRun.png";
	m_qPixmapLaserStatusRun.load(qstrIconPath);

	m_cstrFilmTrimmerCfgPath = qstrIconFile.toStdWString().data();
	m_cstrFilmTrimmerCfgPath += _T("/System/FilmTrimmer.cfg");
}

void UI_AutoProduction::initVal()
{
	m_bAutoUpdateLock = false;
	m_pCtrlAutoProduction = NULL;
	m_pWorkSpeedInputDlg = new UI_WorkSpeedInputDlg;
	m_nLastSetWorkSpeed = ReadIntFromFile(_T("Ĭ�ϲ���"),_T("�����ٶ�����"),20, m_cstrFilmTrimmerCfgPath);

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
	//m_Painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));//���û�ˢ��ʽ 
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
	if (!Release)
	{
		m_Curtension = m_PuCurtension;
		m_Mintension = m_PuMintension;
		m_Maxtension = m_PuMaxtension;
	}
	if (m_Curtension >= m_Mintension&&m_Curtension <= m_Maxtension)
	{
		double bad = m_Maxtension - m_Mintension;
		double rangle = m_Maxtension + m_Mintension;
		double rangleaver = rangle / 2;
		double badvalue = m_Curtension - rangleaver;
		if(bad!=0&&badvalue!=0)
			angle = badvalue / (bad / 2) * 60;
	}
	else if (m_Curtension < m_Mintension)
		angle = -60.0;
	else
		angle = 60.0;
	m_Painter->translate(Pie1.x() + r / 2.0, Pie1.y() + r / 2.0);
	m_Painter->rotate(angle);
	m_Painter->drawLine(0, 0, 0, 10 - r / 2);
	m_Painter->resetTransform();
}
void UI_AutoProduction::PaintConnectLine()
{
	if(m_isOneTwo)
		m_Painter->drawLine(ui.label->x() + ui.label->width(), ui.label->y() + ui.label->height() / 2.0, ui.label_9->x(), ui.label_9->y() + ui.label_9->height() / 2.0);
	else
		m_Painter->drawLine(ui.label_17->x(), ui.label_17->y() + ui.label_17->height() / 2.0, ui.label_9->x(), ui.label_9->y() + ui.label_9->height() / 2.0);
	m_Painter->drawLine(ui.label_9->x() + ui.label_9->width() / 2.0, ui.label_9->y(), ui.label_12->x() + ui.label_12->width() - 2, ui.label_12->y());

	m_Painter->drawLine(ui.label_12->x() + ui.label_12->width() - 2, ui.label_12->y() + ui.label_12->height() - 2, ui.label_7->x(), ui.label_7->y() + ui.label_7->height() / 2.0);

	m_Painter->drawLine(ui.label_7->x() + ui.label_7->width()/2, ui.label_7->y() + ui.label_7->height(), ui.label_11->x() + ui.label_11->width() / 2, ui.label_11->y());

	m_Painter->drawLine(ui.label_11->x() + ui.label_11->width(), ui.label_11->y() + ui.label_11->height() / 2.0, ui.label_8->x() + ui.label_8->width() / 2, ui.label_8->y());

	m_Painter->drawLine(ui.label_8->x() + ui.label_8->width() / 2.0, ui.label_8->y() + ui.label_8->height(), ui.label_MainAxis->x() + ui.label_MainAxis->width() / 2.0, ui.label_MainAxis->y() + ui.label_MainAxis->height());

	m_Painter->drawLine(ui.label_MainAxis->x() + ui.label_MainAxis->width(), ui.label_MainAxis->y() + ui.label_MainAxis->height() / 2.0, ui.label_10->x(), ui.label_10->y() + ui.label_10->height() / 2.0);

	if(m_PuisOneTwo)
		m_Painter->drawLine(ui.label_10->x() + ui.label_10->width(), ui.label_10->y() + ui.label_10->height() / 2.0, ui.label_3->x(), ui.label_3->y() + ui.label_3->height() / 2.0);
	else
		m_Painter->drawLine(ui.label_10->x() + ui.label_10->width(), ui.label_10->y() + ui.label_10->height() / 2.0, ui.label_18->x(), ui.label_18->y() + ui.label_18->height() / 2.0);
}

bool UI_AutoProduction::eventFilter(QObject *obj, QEvent *ev)
{
	if (obj == ui.LB_DataListShow)
	{
		if (ev->type() == QEvent::MouseButtonPress)
		{
			DataListShowClick();
			return true;
		}
		else
		{
			return false;
		}
			
	}
	else if (obj == ui.label_Laser1)
	{
		if (ev->type() == QEvent::MouseButtonPress)
		{
			emit SigSetLaserParam(0);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (obj == ui.label_Laser2)
	{
		if (ev->type() == QEvent::MouseButtonPress)
		{
			emit SigSetLaserParam(1);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (obj == ui.label_MainAxis)
	{
		if (ev->type() == QEvent::MouseButtonPress)
		{
			SlotSetWorkSpeed();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return UI_AutoProduction::eventFilter(obj, ev);
	}
}

void UI_AutoProduction::DataListShowClick()
{
	if (ui.TRW_ModuleTree->isVisible())
	{
		ui.TRW_ModuleTree->setVisible(false);
		ui.LB_Background1->setVisible(false);
		ui.LB_Info->setVisible(false);
		ui.LB_DataListShow->setPixmap(m_qPixmapOtherDataShow);
		ui.LB_DataListShow->move(QPoint(932, 320));
	}
	else
	{
		ui.LB_Background1->setVisible(true);
		ui.TRW_ModuleTree->setVisible(true);
		ui.LB_Info->setVisible(true);
		ui.LB_DataListShow->setPixmap(m_qPixmapOtherDataHide);
		ui.LB_DataListShow->move(QPoint(670, 320));
	}
}

void UI_AutoProduction::SlotSetWorkSpeed()
{

	int nSetWorkSpeed = m_pWorkSpeedInputDlg->DoModal(m_nLastSetWorkSpeed);
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : %1]_{[����:���ù����ٶ�,�ٶ�Ϊ��%2]").arg(__func__).arg(nSetWorkSpeed));
	if (m_pCtrlAutoProduction->SetWorkSpeed(nSetWorkSpeed))
	{
		m_nLastSetWorkSpeed = nSetWorkSpeed;
	}

}

void UI_AutoProduction::paintEvent(QPaintEvent* ev)
{
	//ui.TRW_ModuleTree->setVisible(false);
	m_Painter = new QPainter(this);
	QPen *qpen = new QPen;
	qpen->setColor(Qt::red);
	qpen->setWidth(2);
	m_Painter->setPen(*qpen);//���û�����ʽ 
	m_Painter->setRenderHint(QPainter::Antialiasing, true);
	PaintConnectLine();
	PaintElectronicMeter((ui.label_9->x() + ui.label_9->width() / 2.0) - 75, ui.label_9->y() - 80, 150);
	PaintElectronicMeter((ui.label_10->x() + ui.label_10->width() / 2.0) - 75, ui.label_10->y() - 80, 150, false);
}

bool UI_AutoProduction::GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal)
{
	qVecModifyVal = m_qVecModifyVal;
	return true;
}

bool UI_AutoProduction::insertModule(QVector<ST_MODULE>* pQVector)
{
	int nParentLength = pQVector->length(); //ģ�����
	for (int i = 0; i < nParentLength; i++)
	{
		ST_MODULEITEM _moduleItem;
		if (i == 0)
		{
			continue;
		}
		
		QTreeWidgetItem* DataModule = new QTreeWidgetItem(ui.TRW_ModuleTree, QStringList(pQVector->at(i).ModuleName));
		_moduleItem.ParentModuleItem = DataModule;
		DataModule->setSizeHint(0, QSize(ROWWIDTH, ROWHEIGHT));

		int nChildLength = pQVector->at(i).m_nModuleLength();
		for (int j = 0; j < nChildLength; j++) //����
		{
			QTreeWidgetItem* ChildModule = new QTreeWidgetItem(DataModule, QStringList(pQVector->at(i).Value_.at(j).Function_name));
			ChildModule->setSizeHint(0,QSize(ROWWIDTH, ROWHEIGHT));
			QString strVal;
			if (pQVector->at(i).Value_.at(j).Vel_Type == _INT)
				strVal = QString::number(pQVector->at(i).Value_.at(j).Vel);
			else
				strVal = QString::number(pQVector->at(i).Value_.at(j).Vel, 'g', 8);

			{
				UI_LineEdit* UserLineEdit = new UI_LineEdit(i,j,ui.TRW_ModuleTree);
				UserLineEdit->setReadOnly(true);
				ui.TRW_ModuleTree->setItemWidget(ChildModule, 1, UserLineEdit);
			}

			_moduleItem.ChildModuleItems.push_back(ChildModule);
		}
		m_ModuleVector.push_back(_moduleItem);
	}
	//m_nModuleNum = m_ModuleVector.length();
	return true;
}

bool UI_AutoProduction::AutoUpdateData(QList<ST_UPDATEDATA> AutoUpdateVal)
{
	if (m_bAutoUpdateLock)
		return false;
	m_bAutoUpdateLock = true;
	int nLength = AutoUpdateVal.length()- 2;//�������Ϊ2
	int nModuleItem = -1, nChildItem = -1;
	int nLaser1Step = 0, nLaser2Step = 0, nLaser1CurYield = 0, nLaser2CurYield = 0, nLaser1SumYield = 0, nLaser2SumYield = 0;
	for (int i = 0; i < nLength; i++)
	{
		//��ȡ��������
		QString qstrVal = QString::number(AutoUpdateVal.at(i).dlData, 'g');
		if (i < 11)
		{
			switch (i)
			{
			case 0: //�ž��
				{
					ui.LCD_OnloadDiameter->setText(qstrVal);
				}
				break;
			case 1: //�ž�����
				{
					ui.LCD_OnloadTension->setText(qstrVal);
				}
				break;
			case 2: //�ž��
				{
					ui.LCD_RecvDiameter->setText(qstrVal);
				}
				break;
			case 3: //�ž�����
				{
					ui.LCD_RecvTension->setText(qstrVal);
				}
				break;
			case 4: //�����ٶ�
				{
					ui.LCD_WorkSpeedShow->setText(qstrVal);
				}
			case 5: //����1����
				{
					nLaser1Step = (int)qstrVal.toDouble();
					ui.LB_Laser1Step->setText(QString::number(nLaser1Step));
				}
				break;
			case 6: //����2����
				{
					nLaser2Step = (int)qstrVal.toDouble();
					ui.LB_Laser2Step->setText(QString::number(nLaser2Step));
				}
				break;
			case 7:	//����1�������
				{
					nLaser1CurYield = (int)qstrVal.toDouble();
					ui.LB_Laser1CurYield->setText(QString::number(nLaser1CurYield));
				}
				break;
			case 8:	//����2�������
				{
					nLaser2CurYield = (int)qstrVal.toDouble();
					ui.LB_Laser2CurYield->setText(QString::number(nLaser2CurYield));
				}
				break;
			case 9:	//����1�ܲ���
				{
					nLaser1SumYield = (int)qstrVal.toDouble();
					ui.LB_Laser1SumYield->setText(QString::number(nLaser1SumYield));
				}
				break;
			case 10://����2�ܲ���
				{
					nLaser2SumYield = (int)qstrVal.toDouble();
					ui.LB_Laser2SumYield->setText(QString::number(nLaser2SumYield));
				}
			break;
			default:
				break;
			}
		}
		else
		{
			nModuleItem = AutoUpdateVal.at(i).nModuleItem - 1; //��ȥĬ��ģ��
			nChildItem = AutoUpdateVal.at(i).nChildItem;

			//���ҵ��޸ĵ�Item
			if (m_ModuleVector.length() == 0)
			{
				m_bAutoUpdateLock = false;
				return false;
			}
			QTreeWidgetItem* DataItem = m_ModuleVector.at(nModuleItem).ChildModuleItems.at(nChildItem);//
			UI_LineEdit* DataLineEdit = (UI_LineEdit*)ui.TRW_ModuleTree->itemWidget(DataItem, 1);
			DataLineEdit->setText(qstrVal);
		}
	}
	//���ü��⵱���ܲ����Լ��ܲ���
	ui.LB_LaserCurSumYield->setText(QString::number(nLaser1CurYield + nLaser2CurYield));
	ui.LB_LaserSumYield->setText(QString::number(nLaser1SumYield + nLaser2SumYield));
	//���ü���״̬
	for (int i = 0; i < 2; i++)
	{
		int nLaserStatus = (int)AutoUpdateVal.at(nLength + i).dlData;
		if (i == 0) //����1
		{
			if (-1 == nLaserStatus)
			{
				ui.label_Laser1->setPixmap(m_qPixmapLaserStatusNoEnable);
			}
			else if (1 == nLaserStatus)
			{
				ui.label_Laser1->setPixmap(m_qPixmapLaserStatusEnableNoConnect);
			}
			else if (2 == nLaserStatus)
			{
				ui.label_Laser1->setPixmap(m_qPixmapLaserStatusConnectNoRun);
			}
			else if(nLaserStatus > 2)
			{
				ui.label_Laser1->setPixmap(m_qPixmapLaserStatusRun);
			}
		}
		else
		{
			if (-1 == nLaserStatus)
			{
				ui.label_Laser2->setPixmap(m_qPixmapLaserStatusNoEnable);
			}
			else if (1 == nLaserStatus)
			{
				ui.label_Laser2->setPixmap(m_qPixmapLaserStatusEnableNoConnect);
			}
			else if (2 == nLaserStatus)
			{
				ui.label_Laser2->setPixmap(m_qPixmapLaserStatusConnectNoRun);
			}
			else if(nLaserStatus > 2)
			{
				ui.label_Laser2->setPixmap(m_qPixmapLaserStatusRun);
			}
		}
	}
	m_bAutoUpdateLock = false;
	update();
	return true;
}

void UI_AutoProduction::SkipCurrentPage()
{
	m_qVecModifyVal.clear();
	//��ȡ��ǰҳ���ֵ
}

void UI_AutoProduction::SetDefault(double MaxRe, double MinRe, double MaxPu, double MinPu, bool isOneTwo,  bool PuisOneTwo)
{
	m_ReMaxtension = MaxRe;
	m_ReMintension = MinRe;
	m_PuMaxtension = MaxPu;
	m_PuMintension = MinPu;
	m_isOneTwo = isOneTwo;
	m_PuisOneTwo = PuisOneTwo;
}

void UI_AutoProduction::SetButtonAttribute(bool bFlag)
{
	if (bFlag)
	{
		ui.PB_SendloadFW->setVisible(true);
		ui.PB_SendloadRE->setVisible(true);
		ui.PB_MainAxisFW->setVisible(true);
		ui.PB_MainAxisRE->setVisible(true);
		ui.PB_RecvloadFW->setVisible(true);
		ui.PB_RecvloadRE->setVisible(true);
		ui.PB_RunDirection->setVisible(true);
		ui.PB_OnloadDirection->setVisible(true);
	}
	else
	{
		ui.PB_SendloadFW->setVisible(false);
		ui.PB_SendloadRE->setVisible(false);
		ui.PB_MainAxisFW->setVisible(false);
		ui.PB_MainAxisRE->setVisible(false);
		ui.PB_RecvloadFW->setVisible(false);
		ui.PB_RecvloadRE->setVisible(false);
		ui.PB_RunDirection->setVisible(false);
		ui.PB_OnloadDirection->setVisible(false);
	}
}

bool UI_AutoProduction::SaveParamer()
{
	return true;
}

void UI_AutoProduction::SlotItemChanged(QTreeWidgetItem *item, int column)
{
	QTreeWidgetItem* CurItemParent = item->parent();
	if (CurItemParent == NULL)
		return;
	int nModuleNum = ui.TRW_ModuleTree->indexOfTopLevelItem(CurItemParent);
	int nChildNum = CurItemParent->indexOfChild(item);
	double dlData = item->text(1).toDouble();

	ST_CHANGE_POINT temp;
	temp.dlData = dlData;
	temp.nChildNum = nChildNum;
	temp.nModuleNum = nModuleNum;
	m_qVecModifyVal.push_back(temp);
}

void UI_AutoProduction::SlotRunDirection()
{
	bool bRes = m_pCtrlAutoProduction->SetMachineRunDir();
	QString Dir;
	if (bRes)
	{
		Dir = QString::fromLocal8Bit("��������");
		ui.PB_RunDirection->setIcon(m_qIconRunDirFW);
	}
	else
	{
		Dir = QString::fromLocal8Bit("��������");
		ui.PB_RunDirection->setIcon(m_qIconRunDirRE);
	}
	ui.PB_RunDirection->setText(Dir);
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : SlotRunDirection]_����:�������з���Ϊ%1").arg(Dir));
	emit SigMachineRunDir(bRes);
}

void UI_AutoProduction::SlotOnloadDirection()
{
	bool bRes = m_pCtrlAutoProduction->SetMachineOnloadDir();
	if (bRes)
	{
		ui.PB_OnloadDirection->setText(QString::fromLocal8Bit("˳ʱ��ž�"));
		ui.PB_OnloadDirection->setIcon(m_qIconOnloadDirFW);
		LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : SlotOnloadDirection]_����:���÷ž���Ϊ%1").arg(ui.PB_OnloadDirection->text()));
	}
	else
	{
		ui.PB_OnloadDirection->setText(QString::fromLocal8Bit("��ʱ��ž�"));
		ui.PB_OnloadDirection->setIcon(m_qIconOnloadDirRE);
		LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : SlotOnloadDirection]_����:���÷ž�Ϊ%1").arg(ui.PB_OnloadDirection->text()));
	}
	
}

void UI_AutoProduction::SlotOnloadClockwiseP()
{
	m_pCtrlAutoProduction->SetOnloadClockwise(true);
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : SlotOnloadDirection]_����:�ž���ת(��ѹ)"));
}

void UI_AutoProduction::SlotOnloadClockwiseR()
{
	m_pCtrlAutoProduction->SetOnloadClockwise(false);
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : SlotOnloadDirection]_����:�ž���ת(�ͷ�)"));
}

void UI_AutoProduction::SlotOnloadAnticlockwiseP()
{
	m_pCtrlAutoProduction->SetOnloadAnticlockwise(true);
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : SlotOnloadDirection]_����:�ž���ת"));
}

void UI_AutoProduction::SlotOnloadAnticlockwiseR()
{
	m_pCtrlAutoProduction->SetOnloadAnticlockwise(false);
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : SlotOnloadDirection]_����:���÷ž���"));
}

void UI_AutoProduction::SlotMainAxisClockwiseP()
{
	m_pCtrlAutoProduction->SetMainAxisClockwise(true);
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : SlotOnloadDirection]_����:��ǣ����ת"));
}

void UI_AutoProduction::SlotMainAxisClockwiseR()
{
	m_pCtrlAutoProduction->SetMainAxisClockwise(false);
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : SlotMainAxisClockwiseR]_����:��ǣ����ת"));
}

void UI_AutoProduction::SlotMainAxisAnticlockwiseP()
{
	m_pCtrlAutoProduction->SetMainAxisAnticlockwise(true);
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : SlotMainAxisAnticlockwiseP]_����:��ǣ����ת"));
}

void UI_AutoProduction::SlotMainAxisAnticlockwiseR()
{
	m_pCtrlAutoProduction->SetMainAxisAnticlockwise(false);
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : SlotMainAxisAnticlockwiseR]_����:��ǣ����ת"));
}

void UI_AutoProduction::SlotRecvClockwiseP()
{
	m_pCtrlAutoProduction->SetRecvClockwise(true);
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : SlotRecvClockwiseP]_����:�վ���ת"));
}

void UI_AutoProduction::SlotRecvClockwiseR()
{
	m_pCtrlAutoProduction->SetRecvClockwise(false);
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : %1]_����:�վ�ת").arg(__func__));
}

void UI_AutoProduction::SlotRecvAnticlockwiseP()
{
	m_pCtrlAutoProduction->SetRecvAnticlockwise(true);
	LOGSTR.WriteLogQstring(3, QString::fromLocal8Bit("[���: UI��]_[������ : %1]_����:�վ�ת").arg(__func__));
}

void UI_AutoProduction::SlotRecvAnticlockwiseR()
{
	m_pCtrlAutoProduction->SetRecvAnticlockwise(false);
}
