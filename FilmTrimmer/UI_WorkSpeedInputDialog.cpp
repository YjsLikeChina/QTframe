#include "UI_WorkSpeedInputDialog.h"
#include <direct.h>

UI_WorkSpeedInputDlg::UI_WorkSpeedInputDlg(QDialog* parent /*= Q_NULLPTR*/)
	:QDialog(parent)
{
	ui.setupUi(this);
	initVal();
	initUI();
	initConnect();
}

UI_WorkSpeedInputDlg::~UI_WorkSpeedInputDlg()
{
}

int UI_WorkSpeedInputDlg::DoModal(int nCurSpeed)
{
	ui.LE_WorkSpeedInput->setText(QString::number(nCurSpeed));
	exec();
	if (m_bFlag)
		return ui.LE_WorkSpeedInput->text().toInt();
	else
		return -1;
}

void UI_WorkSpeedInputDlg::initVal()
{
	m_bFlag = false;
}

void UI_WorkSpeedInputDlg::initUI()
{
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);

	char* pBuffer = NULL;
	if (NULL == (pBuffer = _getcwd(NULL, 0)))
	{
		perror("_getcwd error");
	}

	QString strIcon = QString::fromLocal8Bit(pBuffer);
	strIcon += "/Image/OK.png";
	ui.PB_OK->setIcon(QIcon(strIcon));
	ui.PB_OK->setIconSize(QSize(28,28));
	ui.PB_OK->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white; border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	strIcon = QString::fromLocal8Bit(pBuffer);
	strIcon += "/Image/Cancel.png";
	ui.PB_Cancel->setIcon(QIcon(strIcon));
	ui.PB_Cancel->setIconSize(QSize(28, 28));
	ui.PB_Cancel->setStyleSheet(
		"QPushButton{background:rgb(1,172,179);color: white;border-radius: 10px;}"
		"QPushButton:pressed{background:blue;color: white; border: 1px groove rgb(0,136,255); border-style: inset; }"
		);

	strIcon = QString::fromLocal8Bit(pBuffer);
	strIcon += "/Image/Background.png";
	ui.LB_Background->setScaledContents(true);
	ui.LB_Background->setPixmap(QPixmap(strIcon));

	ui.LE_WorkSpeedInput->setStyleSheet("background-color:rgb(13,74,185)");
	QRegExp regx("([0-9]{0,2})");
	QValidator *validator = new QRegExpValidator(regx, ui.LE_WorkSpeedInput);
	ui.LE_WorkSpeedInput->setValidator(validator);

}

void UI_WorkSpeedInputDlg::initConnect()
{
	connect(ui.PB_OK, SIGNAL(clicked()), this, SLOT(SlotOK()));
	connect(ui.PB_Cancel, SIGNAL(clicked()), this, SLOT(SlotCancel()));
}

void UI_WorkSpeedInputDlg::SlotOK()
{
	m_bFlag = true;
	close();
}

void UI_WorkSpeedInputDlg::SlotCancel()
{
	m_bFlag = false;
	close();
}

