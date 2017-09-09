#include "UI_InterfaceBase.h"

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

void UI_InterfaceBase::temp22()
{

}
