#ifndef UI_SIMPLEDIALOG_H
#define UI_SIMPLEDIALOG_H

#include <QDialog>
#include "ui_UI_Simpledialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QVector>
#include <QMap>
#include "BaseDataType.h"
class UI_Simpledialog : public QDialog
{
	Q_OBJECT

public:
	UI_Simpledialog(QWidget *parent = 0);
	~UI_Simpledialog();

	void SetShow(QStringList Name, QVector<ST_CHANGE_POINT> &Point);
	QVector<QLabel*> m_QVQlabel;
	QVector<QLineEdit*> m_QVQlineEdit;
	QVector<ST_CHANGE_POINT>* m_QvPoint;
private:
	Ui::SimPleDialog ui;
	void initQlableAndQlinedit();
	void initConnect();
protected Q_SLOTS:
	void SlotOkButtonClicked();
	void SlotCancelButtonClicked();
};

#endif // UI_SIMPLEDIALOG_H
