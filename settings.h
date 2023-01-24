#pragma once

#include <QWidget>
#include "ui_settings.h"
#include "positionSettings.h"
class settings : public QWidget
{
	Q_OBJECT

public:
	settings(QWidget *parent = Q_NULLPTR);
	~settings();
	void launchAnimation();
private:
	Ui::settings ui;
};
