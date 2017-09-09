#include "UI_InterfaceBase.h"
#include <QFont>

UI_InterfaceBase::UI_InterfaceBase(QWidget* parent)
{
	m_pQObject = parent;
}

UI_InterfaceBase::~UI_InterfaceBase()
{
}

bool UI_InterfaceBase::AutoUpdateData(QList<ST_UPDATEDATA> qliAutoInfo)
{
	return true;
}

bool UI_InterfaceBase::AutoUpdateData(int nIndex, QStringList qstrListInfo)
{
	return true;
}

bool UI_InterfaceBase::AutoUpdateData(const QString qstrAlarmInfo)
{
	return true;
}

bool UI_InterfaceBase::insertModule(QVector<ST_MODULE>*)
{
	return true;
}

void UI_InterfaceBase::SkipCurrentPage()
{

}

bool UI_InterfaceBase::GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal)
{
	return true;
}

bool UI_InterfaceBase::SaveParamer()
{
	return true;
}

UI_LineEdit::UI_LineEdit(int i, int j, QWidget* parent /*= Q_NULLPTR*/)
	:nModuleNum(i),nChildNum(j), QLineEdit(parent)
{
	initUI();
}

UI_LineEdit::UI_LineEdit(QWidget* parent /*= Q_NULLPTR*/)
	:QLineEdit(parent)
{
	nModuleNum = 0;
	nChildNum = 0;
	initUI();
}

UI_LineEdit::~UI_LineEdit()
{

}

void UI_LineEdit::initUI()
{
	QFont font(QString::fromLocal8Bit("Î¢ÈíÑÅºÚ"),10);
	this->setFont(font);
	QRegExp regx("([0-9]{0,4}[.][0-9]{0,4})|([0-9]{0,4})");
	QValidator *validator = new QRegExpValidator(regx, this);
	this->setValidator(validator);
	this->setContextMenuPolicy(Qt::NoContextMenu);
	this->setMaximumHeight(28);
	this->setMaximumWidth(100);
	this->setStyleSheet("background-color:rgb(13,74,185); color:white;border: 1px groove white;");
}

void UI_LineEdit::SetStyleSheet(QFont qfont, QRegExp regx)
{
	this->setFont(qfont);
	QValidator *validator = new QRegExpValidator(regx, this);
	this->setValidator(validator);
}
