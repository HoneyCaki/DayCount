#pragma once

#include <QWidget>
#include "ui_positionSettings.h"
#include <qevent.h>
#include "DayCount.h"
#include <qlabel.h>
class positionSettings : public QWidget
{
	Q_OBJECT

public:
	positionSettings(QWidget *parent = Q_NULLPTR);
	~positionSettings();
	QLabel* cDay = new QLabel(this);
	QLabel* tDay = new QLabel(this);
	QLabel* dayTip = new QLabel(this);
	QLabel* day = new QLabel(this);
	QLabel* tip = new QLabel(this);
protected:
	void paintEvent(QPaintEvent* e);
private:
	Ui::positionSettings ui;
	bool eventFilter(QObject* obj, QEvent* event);
};
