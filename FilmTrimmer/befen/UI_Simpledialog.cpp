#include "UI_Simpledialog.h"

SimPleDialog::SimPleDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	initConnect();
}

SimPleDialog::~SimPleDialog()
{

}

void SimPleDialog::SetShow(QStringList Name, QVector<ST_CHANGE_POINT> &Point)
{
	m_QvPoint = &Point;
	for (int i = 0; i < Name.length(); i++)
	{
		QLabel *temp = new QLabel(Name.at(i));
		QLineEdit *tempE = new QLineEdit();
		m_QVQlabel.push_back(temp);
		m_QVQlineEdit.push_back(tempE);
	}
	initQlableAndQlinedit();
	this->exec();
	return ;
}

void SimPleDialog::SlotOkButtonClicked()
{
	//暂时不判断输入的数据
	/*for (int i = 0; i < m_QVQlineEdit.length(); i++)
	{
		(m_QvPoint->data()+i)->dlData = m_QVQlineEdit.at(i)->text().toDouble();
	}*/
	accept();
}

void SimPleDialog::initQlableAndQlinedit()
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

void SimPleDialog::initConnect()
{
	connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(SlotOkButtonClicked()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(SlotCancelButtonClicked()));
}

void SimPleDialog::SlotCancelButtonClicked()
{
	
}
