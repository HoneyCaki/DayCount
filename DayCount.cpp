/**
* Program Name: DayCount 倒数日
* Version: 1.0
* Author: 茶姬不是受i
* Bilibili Link: https://space.bilibili.com/524676261
* Notice: 该程序为个人练手项目，现已开源至github供各位交流借鉴学习，若要改码发布，
*         请注明原作者和原链接，谢绝售卖程序。
* Tips: · 程序目前已知bug较多，部分交互对用户使用不友好，不建议日常使用
*		· 程序在某些情况下存在性能问题，详情在README.md
*		· 程序更新周期较长（学生党）
*		· 代码中部分功能实现比较下饭
*/


#ifdef Q_OS_WIN
#pragma execution_character_set("utf-8")   //解决中文乱码
#endif

#include "DayCount.h"
#include <qdebug.h>
#include <qdatetime.h>
#include <qsettings.h>
#include <qdir.h>
#include <qtextcodec.h>
#include <qscreen.h>
#include <qpainter.h>
#include <qsystemtrayicon.h>
#include <qaction.h>
#include <qmenu.h>

QString inifilePath = "./config/config.ini"; //默认配置文件位置

QString imagePath;

int count = 0;

bool mouseEnter;

DayCount::DayCount(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//---------属性---------
	this->setAttribute(Qt::WA_TranslucentBackground);
	this->setAttribute(Qt::WA_QuitOnClose, true);//当关闭主窗口时其它窗口一起关闭
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
	//-------------------------
	QString // 注：tar / cur = target / current
		tipWord, targetDate,
		tipFontColor, tipFontStyle,
		dayFontColor, dayFontStyle,
		curDayFontColor, curDayFontStyle,
		tarDayFontColor, tarDayFontStyle;
		
	int tipFontSize, tipFontBoldLevel,
		dayFontSize, dayFontBoldLevel,
		curDayFontSize, curDayFontBoldLevel,
		tarDayFontSize, tarDayFontBoldLevel;

	dayText = ui.dayText->text();
	//获取窗口长高
	int width = this->geometry().width();
	int height = this->geometry().height();
	//按钮尺寸
	int btnW = 32;
	int btnH = 32;
	ui.statusBar->hide();
	//-------------------软件托盘----------------------
	QSystemTrayIcon* tray = new QSystemTrayIcon(this);
	tray->setIcon(QIcon(":/imgs/images/programICO.png"));
	tray->setToolTip("Day Count \n v1.0");
	QAction* actSettings = new QAction(QStringLiteral("设置"), this);
	QAction* actExit = new QAction(QStringLiteral("退出程序"), this);

	//托盘右键[设置]选项
	connect(actSettings, &QAction::triggered, [this] 
		{
		settings* set = new settings;
		set->show(); //弹出设置窗口
		}); 

	//退出
	connect(actExit, &QAction::triggered, [this] {
		this->close();
		}); 

	//添加菜单
	QMenu* m = new QMenu(this);
	m->addAction(actSettings);
	m->addAction(actExit);
	tray->setContextMenu(m);
	//托盘事件：当双击托盘图标，弹出设置界面
	connect(tray, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason action) 
		{
			switch (action) {
			case QSystemTrayIcon::DoubleClick:
				settings* set = new settings;
				set->show();
			}
		});
	tray->show();
	//触发右下角消息框提示，停留时间为1s
	tray->showMessage(QStringLiteral("已放入托盘"),QStringLiteral("双击显示设置界面，右键查看更多选项"),QSystemTrayIcon::Information,1000);
	

	//----程序启动动画----
	QPropertyAnimation* pAnimation = new QPropertyAnimation(this, "windowOpacity");
	pAnimation->setDuration(1000); //时间
	pAnimation->setKeyValueAt(0, 1);
	pAnimation->setKeyValueAt(0, 0);
	pAnimation->setKeyValueAt(1, 1);
	pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
	
	//----设置自定义按钮属性----
	//关闭按钮
	closeButton->move(QPoint(width / 2 - btnW, height-btnH)); //位置
	closeButton->setFixedSize(QSize(btnW,btnH)); //大小 32x32
	closeButton->setFlat(true);
	closeButton->setStyleSheet("QPushButton{border-image: url(:imgs/images/close.png);}"
		"QPushButton:pressed{border-image: url(:imgs/images/Pressed_close.png);}");
	closeButton->raise(); 
	closeButton->hide(); 
	//设置按钮
	settingsButton->move(QPoint(width / 2 -1, height - btnH)); //位置
	settingsButton->setFixedSize(QSize(btnW, btnH)); //大小 32x32
	settingsButton->setFlat(true);
	settingsButton->setStyleSheet("QPushButton{border-image: url(:imgs/images/settings.png);}"
		"QPushButton:pressed{border-image: url(:imgs/images/Pressed_settings.png);}");
	settingsButton->raise();
	settingsButton->hide();
	

	//---------配置文件---------

	QSettings* configIni = new QSettings(inifilePath, QSettings::IniFormat);
	configIni->setIniCodec(QTextCodec::codecForName("GB2312")); //设置ini字符集，避免中文出错

	//程序位置
	int posX = configIni->value("Position_X").toInt();
	int posY = configIni->value("Position_Y").toInt();
	//记录位置
	if (configIni->value("RecordPosition").toBool()) 
	{
		this->move(QPoint(posX, posY));
	}
	
	//-------文件操作-------
	QString configDir = "./config/"; //默认路径
	QString backGroundImagesDir = "./background-img/"; //默认路径
	QDir dir;
	if (!dir.exists(configDir))
	{
		//如果文件夹不存在，则创建
		bool res = dir.mkdir(configDir);
		if (!res) //文件夹生成失败
			qDebug() << "[149] ERROR: Profile directory generation failed.";
	}
	if (!dir.exists(backGroundImagesDir))
	{
		//如果文件夹不存在，则创建
		bool res = dir.mkdir(backGroundImagesDir);
		if (!res) //文件夹生成失败
			qDebug() << "[156] ERROR: Background images directory generation failed.";
	}

	QFile iniFile("./config/config.ini");
	if (!dir.exists("./config/config.ini"))
	{
		//如果配置文件不存在，则创建
		bool success = iniFile.open(QIODevice::WriteOnly);
		if(!success)
			qDebug() << "[165] ERROR: Background images directory generation failed.";
	}


	//-------背景图片获取-------
	//若配置文件路径为空，则处理为一个错误的贴图
	if (configIni->value("Background/Image_Path").toString() == "") 
	{
		imagePath = ".background-img/error.png";
	}
	else { //获取图片地址
		imagePath = configIni->value("Background/Image_Path").toString();
	}

	//从配置文件中读取对应的值并存储到变量中
	tipWord = configIni->value("Tip_Word").toString();
	targetDate = configIni->value("Target_Date").toString();
	
	tipFontColor = configIni->value("Tip_Font/Font_Color").toString();
	tipFontSize = configIni->value("Tip_Font/Font_Size").toInt();
	tipFontStyle = configIni->value("Tip_Font/Font_Style").toString();
	tipFontBoldLevel = configIni->value("Tip_Font/Font_BoldLevel").toInt();

	dayFontColor = configIni->value("Day_Font/Font_Color").toString();
	dayFontSize = configIni->value("Day_Font/Font_Size").toInt();
	dayFontStyle = configIni->value("Day_Font/Font_Style").toString();
	dayFontBoldLevel = configIni->value("Day_Font/Font_BoldLevel").toInt();

	curDayFontColor = configIni->value("Current_Date_Font/Font_Color").toString();
	curDayFontSize = configIni->value("Current_Date_Font/Font_Size").toInt();
	curDayFontStyle = configIni->value("Current_Date_Font/Font_Style").toString();
	curDayFontBoldLevel = configIni->value("Current_Date_Font/Font_BoldLevel").toInt();

	tarDayFontColor = configIni->value("Target_Date_Font/Font_Color").toString(); 
	tarDayFontSize = configIni->value("Target_Date_Font/Font_Size").toInt();
	tarDayFontStyle = configIni->value("Target_Date_Font/Font_Style").toString();
	tarDayFontBoldLevel = configIni->value("Target_Date_Font/Font_BoldLevel").toInt();
	delete configIni;

	//-------日期获取与计算-------
	QDate date;
	QDateTime dt;
	dt.setDate(date.currentDate());
	//当前日期
	currentTime = dt.toString("yyyy-MM-dd");
	QDateTime currentDateTime = QDateTime::fromString(currentTime, "yyyy-MM-dd");
	//目标日期
	targetDateTime = QDateTime::fromString(targetDate, "yyyy-MM-dd");
	//日期差值
	days = currentDateTime.daysTo(targetDateTime);
	//**字体颜色**
	//以下代码片段简介：通过用户给定的xxx,xxx,xxx颜色字符串值，通过split函数进行拆分，
	//				 并将各个RGB值存储到QStringList中
	//更新：			 后面考虑改为色板调整，以下代码片段仅供参考
	QStringList tipColor_ = tipFontColor.split(",");
	QStringList dayColor_ = dayFontColor.split(",");
	QStringList curDayColor_ = curDayFontColor.split(",");
	QStringList tarDayColor_ = tarDayFontColor.split(",");
	tipR = tipColor_[0].toInt(); dayR = dayColor_[0].toInt(); cDayR = curDayColor_[0].toInt(); tDayR = tarDayColor_[0].toInt();
	tipG = tipColor_[1].toInt(); dayG = dayColor_[1].toInt(); cDayG = curDayColor_[1].toInt(); tDayG = tarDayColor_[1].toInt();
	tipB = tipColor_[2].toInt(); dayB = dayColor_[2].toInt(); cDayB = curDayColor_[2].toInt(); tDayB = tarDayColor_[2].toInt();
	
	QPalette tipColor,dayColor,tarDayColor,curDayColor;
	tipColor.setColor(QPalette::WindowText, QColor(tipR, tipG, tipB));
	dayColor.setColor(QPalette::WindowText, QColor(dayR, dayG, dayB));
	curDayColor.setColor(QPalette::WindowText, QColor(cDayR, cDayG, cDayB));
	tarDayColor.setColor(QPalette::WindowText, QColor(tDayR, tDayG, tDayB));


	//-------控件属性设置（设置字体样式和文本信息）-------
	ui.days->setText(QString::number(days));
	ui.days->setFont(QFont(dayFontStyle,dayFontSize,dayFontBoldLevel));
	ui.days->setPalette(dayColor);
	ui.currentDate->setText(currentTime.append(QStringLiteral(" ———— "))); //xxxx.xx.xx ———— ...
	ui.currentDate->setFont(QFont(curDayFontStyle, curDayFontSize, curDayFontBoldLevel));
	ui.currentDate->setPalette(curDayColor);
	ui.targetDate->setText(targetDate);
	ui.targetDate->setFont(QFont(tarDayFontStyle, tarDayFontSize, tarDayFontBoldLevel));
	ui.targetDate->setPalette(tarDayColor);
	ui.tipText->setText(tipWord);
	ui.tipText->setFont(QFont(tipFontStyle, tipFontSize, tipFontBoldLevel));
	ui.tipText->setPalette(tipColor);
	ui.dayText->setFont(QFont(dayFontStyle, dayFontSize, dayFontBoldLevel));
	ui.dayText->setPalette(dayColor);


	//------关闭按钮功能-------
	connect(closeButton, &QPushButton::clicked, this, [=]()
		{
			QPropertyAnimation* pAnimation = new QPropertyAnimation(this, "windowOpacity");
			pAnimation->setDuration(1000);
			pAnimation->setKeyValueAt(1, 1);
			pAnimation->setKeyValueAt(0, 0);
			pAnimation->setKeyValueAt(0, 1);
			pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
			close();
		}
	);
	//-------设置按钮功能-------
	connect(settingsButton, &QPushButton::clicked, this, [=]() 
		{
			settings *set = new settings;
			set->show();
		});
}

void DayCount::enterEvent(QEvent*)
{
	mouseEnter = true;
	closeButton->show();
	settingsButton->show();
}

//鼠标离开事件
void DayCount::leaveEvent(QEvent*)
{
	if (mouseEnter) 
	{
		//bug
		_sleep(500);
		closeButton->hide();
		settingsButton->hide();	
	}
}

//绘图事件
void DayCount::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), QPixmap(imagePath), QRect());

	//判断用户是否第一次打开移动控件界面，若是，则从配置文件直接读取各控件位置值
	//count初始值为0，触发此处代码片段后count值将+1，确保这里只能触发一次 ，否则可能导致性能问题
	if (count == 0) 
	{
		QSettings* configIni = new QSettings(inifilePath, QSettings::IniFormat);
		configIni->setIniCodec(QTextCodec::codecForName("GB2312")); //设置ini字符集，以免导致奇怪的乱码问题

		
		//-------------------先移动控件-------------------
		ui.tipText->move(configIni->value("Control_Position/Tip_Text_Position_X").toInt(),
							configIni->value("Control_Position/Tip_Text_Position_Y").toInt());
		
		ui.currentDate->move(configIni->value("Control_Position/Current_Day_Position_X").toInt(),
							configIni->value("Control_Position/Current_Day_Position_Y").toInt());

		ui.days->move(configIni->value("Control_Position/Day_Position_X").toInt(),
						configIni->value("Control_Position/Day_Position_Y").toInt());

		ui.targetDate->move(configIni->value("Control_Position/Target_Day_Position_X").toInt(),
							configIni->value("Control_Position/Target_Day_Position_Y").toInt());

		ui.dayText->move(configIni->value("Control_Position/Day_Text_Position_X").toInt(),
							configIni->value("Control_Position/Day_Text_Position_Y").toInt());

		//-------------------获取控件的位置-------------------
	
		cDayPos = QPoint(configIni->value("Control_Position/Current_Day_Position_X").toInt(),
						configIni->value("Control_Position/Current_Day_Position_Y").toInt());

		tDayPos = QPoint(configIni->value("Control_Position/Target_Day_Position_X").toInt(),
						configIni->value("Control_Position/Target_Day_Position_Y").toInt());
		 
		dayPos = QPoint(configIni->value("Control_Position/Day_Position_X").toInt(),
						configIni->value("Control_Position/Day_Position_Y").toInt());

		dayTipPos = QPoint(configIni->value("Control_Position/Day_Text_Position_X").toInt(),
						configIni->value("Control_Position/Day_Text_Position_Y").toInt());

		tipPos = QPoint(configIni->value("Control_Position/Tip_Text_Position_X").toInt(),
						configIni->value("Control_Position/Tip_Text_Position_Y").toInt());



		tDayPosX = ui.targetDate->pos().x();
		cDayPosX = ui.currentDate->pos().x();
		tipPosX = ui.tipText->pos().x();
		dayTipPosX = ui.dayText->pos().x();
		dayPosX = ui.days->pos().x();

		tDayPosY = ui.targetDate->pos().y();
		cDayPosY = ui.currentDate->pos().y();
		tipPosY = ui.tipText->pos().y();
		dayTipPosY = ui.dayText->pos().y();
		dayPosY = ui.days->pos().y();

		           //---------------存储在INI文件---------------------

		configIni->setValue("Control_Position/Tip_Text_Position_X", tipPosX);
		configIni->setValue("Control_Position/Tip_Text_Position_Y", tipPosY);

		configIni->setValue("Control_Position/Day_Position_X", dayPosX);
		configIni->setValue("Control_Position/Day_Position_Y", dayPosY);

		configIni->setValue("Control_Position/Current_Day_Position_X", cDayPosX);
		configIni->setValue("Control_Position/Current_Day_Position_Y", cDayPosY);

		configIni->setValue("Control_Position/Target_Day_Position_X", tDayPosX);
		configIni->setValue("Control_Position/Target_Day_Position_Y", tDayPosY);

		configIni->setValue("Control_Position/Day_Text_Position_X", dayTipPosX);
		configIni->setValue("Control_Position/Day_Text_Position_Y", dayTipPosY);
		count++;
	}
}

//鼠标按住事件
void DayCount::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_ptDragPosition = event->globalPos() - this->frameGeometry().topLeft();
		event->accept();
	}
}
//鼠标移动事件
void DayCount::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		move(event->globalPos() - m_ptDragPosition);
	}
}
//鼠标松开事件 
//当用户在松开鼠标左键时，记录下当前程序的所在位置并存储到配置文件中，以便下次打开程序恢复上一次的位置数据
void DayCount::mouseReleaseEvent(QMouseEvent* event)
{
	
	QSettings* config = new QSettings(inifilePath, QSettings::IniFormat);
	
	
	//若用户的设置中打开了“记录程序位置”选项，则进行赋值记录
	if (config->value("RecordPosition").toBool()) 
	{
		int posX = this->pos().x();
		int posY = this->pos().y();
		config->setValue("Position_X", posX);
		config->setValue("Position_Y", posY);
	}
}

