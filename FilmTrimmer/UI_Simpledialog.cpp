#include "UI_Simpledialog.h"
#include "UI_InterfaceBase.h"

UI_Simpledialog::UI_Simpledialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	QString strIconFile = QCoreApplication::applicationDirPath();
	QString strIconPath = strIconFile + "/Image/OK.png";
	ui.PB_OK->setIcon(QIcon(strIconPath));
	ui.PB_OK->setIconSize(QSize(30, 25));
	ui.PB_OK->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	strIconPath = strIconFile + "/Image/Cancel.png";
	ui.PB_Cancel->setIcon(QIcon(strIconPath));
	ui.PB_Cancel->setIconSize(QSize(30, 25));
	ui.PB_Cancel->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white;border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);
	initConnect();
}

UI_Simpledialog::~UI_Simpledialog()
{

}

void UI_Simpledialog::SetShow(QStringList Name, QVector<ST_CHANGE_POINT> &Point)
{
	m_QvPoint = &Point;
	for (int i = 0; i < Name.length(); i++)
	{
		QLabel *temp = new QLabel(Name.at(i));
		QFont qFont(QString::fromLocal8Bit("微软雅黑"), 10);
		temp->setFont(qFont);
		temp->setStyleSheet("background: transparent;color: white;");
		UI_LineEdit *tempE = new UI_LineEdit();
		m_QVQlabel.push_back(temp);
		m_QVQlineEdit.push_back(tempE);
	}
	initQlableAndQlinedit();
	this->exec();
	for (int i = 0; i < Name.length(); i++)
	{
		ui.gridLayout->removeWidget(m_QVQlabel.at(i));
		delete (*(m_QVQlabel.data() + i));
		ui.gridLayout->removeWidget(m_QVQlineEdit.at(i));
		delete (*(m_QVQlineEdit.data() + i));
	}
	//QLayoutItem *child;
	//while ((child = ui.gridLayout->takeAt(0)) != 0)
	//{
	//	delete child;
	//	child = NULL;
	//}
	m_QVQlabel.clear();
	m_QVQlineEdit.clear();
	return ;
}

void UI_Simpledialog::SlotOkButtonClicked()
{
	//暂时不判断输入的数据
	for (int i = 0; i < m_QVQlineEdit.length(); i++)
	{
		ST_CHANGE_POINT stTmpData;
		stTmpData.dlData = m_QVQlineEdit.at(i)->text().toDouble();
		//(m_QvPoint->data() + i)->dlData = m_QVQlineEdit.at(i)->text().toDouble();
		m_QvPoint->push_back(stTmpData);
	}
	accept();
}

void UI_Simpledialog::initQlableAndQlinedit()
{
	if (m_QVQlabel.length() != m_QVQlineEdit.length())
		return;
	for (int i = 0; i < m_QVQlabel.length(); i++)
	{
		m_QVQlabel.at(i)->setMinimumSize(100, 40);
		m_QVQlineEdit.at(i)->setMinimumSize(200, 40);
		ui.gridLayout->setColumnStretch(1, 2);
		ui.gridLayout->addWidget(m_QVQlabel.at(i), i, 0);
		ui.gridLayout->addWidget(m_QVQlineEdit.at(i), i, 1);
	}
}

void UI_Simpledialog::initConnect()
{
	connect(ui.PB_OK,SIGNAL(clicked()),this,SLOT(SlotOkButtonClicked()));
	connect(ui.PB_Cancel, SIGNAL(clicked()), this, SLOT(SlotCancelButtonClicked()));
}

void UI_Simpledialog::SlotCancelButtonClicked()
{
	this->close();
}
