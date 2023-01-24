#pragma once
#include "settings.h"
#include <QtWidgets/QMainWindow>
#include "ui_DayCount.h"
#include <qevent.h>
#include <QPushButton.h>
#include <qpropertyanimation.h>
class DayCount : public QMainWindow
{
	Q_OBJECT

public:
	DayCount(QWidget *parent = Q_NULLPTR);
	QPushButton* closeButton = new QPushButton(this);
	QPushButton* settingsButton = new QPushButton(this);
	QPoint m_ptDragPosition;
	QPoint program_Pos;
	int days;
	QString dayText;
	QString currentTime;
	QPoint cDayPos, tDayPos, dayPos, dayTipPos, tipPos;
	int tipPosX, tipPosY, dayPosX, dayPosY, cDayPosX, cDayPosY, tDayPosX, tDayPosY, dayTipPosX, dayTipPosY;
	int tipR; int tDayR;
	int tipG; int tDayG;
	int tipB; int tDayB;
	int dayR;
	int dayG;
	int dayB;
	int cDayR;
	int cDayG;
	int cDayB;
	QDateTime targetDateTime;
	void paintEvent(QPaintEvent*e);
protected:
	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	
private:
	Ui::DayCountClass ui;
	
};
