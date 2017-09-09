#include "UI_FloatingWindow.h"



UI_FloatingWindow::UI_FloatingWindow()
{
	ui.setupUi(this);
	m_bFloatWindowIsMove = false;
	m_bFirstPress = false;
}


UI_FloatingWindow::~UI_FloatingWindow()
{
}

void UI_FloatingWindow::SlotMachineStart()
{
	emit SigMachineStatusCtrl(MACHINE_START);
}

void UI_FloatingWindow::SlotMachineStop()
{
	emit SigMachineStatusCtrl(MACHINE_STOP);
}

void UI_FloatingWindow::SlotMachineReset()
{
	emit SigMachineStatusCtrl(MACHINE_RESET);
}

void UI_FloatingWindow::SlotMachineEStop()
{
	emit SigMachineStatusCtrl(MACHINE_ESTOP);
}

void UI_FloatingWindow::SlotRunSchema()
{
	emit SigMachineStatusCtrl(MACHINE_RUNSCHEMA);
}

void UI_FloatingWindow::SlotRunDirection()
{
	emit SigMachineStatusCtrl(MACHINE_RUNDIR);
}

void UI_FloatingWindow::SlotOnloadDirection()
{
	emit SigMachineStatusCtrl(MACHINE_ROLLDIR);
}

bool UI_FloatingWindow::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui.LB_Exit)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			setGeometry(-115, 385, 10, 305);
			m_bFloatWindowIsMove = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	return UI_FloatingWindow::eventFilter(watched, event);
}

void UI_FloatingWindow::mouseMoveEvent(QMouseEvent *ev)
{
	if ((ev->buttons() & Qt::LeftButton))
	{
		m_bFloatWindowIsMove = true;
		this->setGeometry(0, 385, ev->globalX(), 305);
	}
}

void UI_FloatingWindow::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_bFloatWindowIsMove)
	{
		m_bFloatWindowIsMove = false;
		if (geometry().width() > 100)
		{
			this->setGeometry(0, 385, 1024, 305);
		}
		else
		{
			setGeometry(-115, 385, 10, 305);
		}
		m_bFirstPress = true;
	}
}
