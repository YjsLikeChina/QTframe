#include "UI_Maintenance.h"
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>

UI_Maintenance::UI_Maintenance(QWidget* parent /*= Q_NULLPTR*/)
	:QDialog(parent),UI_InterfaceBase(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setModal(false);
	InitUI();
	InitConnect();
}

UI_Maintenance::~UI_Maintenance()
{
}

void UI_Maintenance::InitUI()
{
	QString qstrIconFile = QCoreApplication::applicationDirPath();
	QString qstrIconPath = qstrIconFile + "/Image/Maintenace_Picture.png";
	ui.LB_Background->setPixmap(QPixmap(qstrIconPath));
	ui.LB_Background->setScaledContents(true);

	qstrIconPath = qstrIconFile + "/Image/MaintenaceExit.png";
	ui.LB_Exit->setPixmap(QPixmap(qstrIconPath));
	ui.LB_Exit->setScaledContents(true);
}

void UI_Maintenance::InitConnect()
{
	ui.LB_Exit->installEventFilter(this);
}

bool UI_Maintenance::ExitMaintenance()
{
	close();
	emit SigExit();
	return true;
}


bool UI_Maintenance::eventFilter(QObject *obj, QEvent *ev)
{
	if (obj == ui.LB_Exit)
	{
		if (ev->type() == QEvent::MouseButtonPress)
		{
			ExitMaintenance();
			return true;
		}
		else
			return false;
	}
	else
	{
		return UI_Maintenance::eventFilter(obj, ev);
	}
}

bool UI_Maintenance::GetModifyParam(QVector<ST_CHANGE_POINT>& qVecModifyVal)
{
	return true;
}

void UI_Maintenance::SkipCurrentPage()
{
	show();
}

