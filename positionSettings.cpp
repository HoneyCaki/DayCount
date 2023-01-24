#ifdef Q_OS_WIN
#pragma execution_character_set("utf-8")   //解决 VS编译器下中文乱码
#endif

#include "positionSettings.h"
#include <qsettings.h>
#include <qdebug.h>
#include <qpainter.h>
#include <QMessageBox.h>
#include <QtWidgets/qstyleoption.h>

int tipFontSize, tipFontBoldLevel,
dayFontSize, dayFontBoldLevel,
cDayFontSize, cDayFontBoldLevel,
tDayFontSize, tDayFontBoldLevel;

int cDayPosX, cDayPosY, 
	tDayPosX, tDayPosY, 
	dayPosX, dayPosY, 
	tipPosX, tipPosY, 
	dayTipPosX, dayTipPosY;

QString imgPTH; // image Path
int count_ = 0;
positionSettings::positionSettings(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setAttribute(Qt::WA_QuitOnClose, false);
	this->setWindowIcon(QIcon(":/imgs/images/programICO.png"));
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	this->setWindowTitle(QStringLiteral("文字位置调整 [关闭则自动保存]"));
	if (count_ > 0)
		count_ = 0;
	QString imagePath, imagePath2, imagePath3, imagePath4,
		tipWord, targetDate,
		tipFontColor,
		dayFontColor, dayText,
		cDayFontColor, cDayText,
		tDayFontColor, tDayText;
	int days;
	DayCount dc;
	
	QSettings* config = new QSettings("./config/config.ini", QSettings::IniFormat);
	
	                  //----------------获取图像地址-----------------------
	QString pathStr = "#centralWidget{background-image: url(";
	if (config->value("Background/Image_Path").toString() == "")
	{
		imagePath = ".background-img/error.png";
	}
	else {
		imagePath = config->value("Background/Image_Path").toString();
	}
	imgPTH = imagePath;

	tipWord = config->value("Tip_Word").toString();
	targetDate = config->value("Target_Date").toString();

	tipFontColor = config->value("Tip_Font/Font_Color").toString();
	tipFontSize = config->value("Tip_Font/Font_Size").toInt();
	tipFontBoldLevel = config->value("Tip_Font/Font_BoldLevel").toInt();

	dayFontColor = config->value("Day_Font/Font_Color").toString();
	dayFontSize = config->value("Day_Font/Font_Size").toInt();
	dayFontBoldLevel = config->value("Day_Font/Font_BoldLevel").toInt();

	cDayFontColor = config->value("Current_Date_Font/Font_Color").toString();
	cDayFontSize = config->value("Current_Date_Font/Font_Size").toInt();
	cDayFontBoldLevel = config->value("Current_Date_Font/Font_BoldLevel").toInt();

	tDayFontColor = config->value("Target_Date_Font/Font_Color").toString();
	tDayFontSize = config->value("Target_Date_Font/Font_Size").toInt();
	tDayFontBoldLevel = config->value("Target_Date_Font/Font_BoldLevel").toInt();

				//----------------------坐标-----------------------
	tDayPosX = config->value("Control_Position/Target_Day_Position_X").toInt();
	tDayPosY = config->value("Control_Position/Target_Day_Position_Y").toInt();

	tipPosX = config->value("Control_Position/Tip_Text_Position_X").toInt();
	tipPosY = config->value("Control_Position/Tip_Text_Position_Y").toInt();

	dayPosX = config->value("Control_Position/Day_Position_X").toInt();
	dayPosY = config->value("Control_Position/Day_Position_Y").toInt();

	cDayPosX = config->value("Control_Position/Current_Day_Position_X").toInt();
	cDayPosY = config->value("Control_Position/Current_Day_Position_Y").toInt();

	dayTipPosX = config->value("Control_Position/Day_Text_Position_X").toInt();
	dayTipPosY = config->value("Control_Position/Day_Text_Position_Y").toInt();

				//------------------字体样式----------------------
	QPalette tipColor, dayColor, tarDayColor, curDayColor;
	tipColor.setColor(QPalette::WindowText, QColor(dc.tipR, dc.tipG, dc.tipB));
	dayColor.setColor(QPalette::WindowText, QColor(dc.dayR, dc.dayG, dc.dayB));
	curDayColor.setColor(QPalette::WindowText, QColor(dc.cDayR, dc.cDayG, dc.cDayB));
	tarDayColor.setColor(QPalette::WindowText, QColor(dc.tDayR, dc.tDayG, dc.tDayB));

	day->setFont(QFont(config->value("Day_Font/Font_Style").toString(), 
						config->value("Day_Font/Font_Size").toInt(), 
						config->value("Day_Font/Font_BoldLevel").toInt()));
	day->setPalette(dayColor);

	cDay->setFont(QFont(config->value("Current_Date_Font/Font_Style").toString(),
						config->value("Current_Date_Font/Font_Size").toInt(),
						config->value("Current_Date_Font/Font_BoldLevel").toInt()));
	cDay->setPalette(curDayColor);

	tDay->setFont(QFont(config->value("Target_Date_Font/Font_Style").toString(),
						config->value("Target_Date_Font/Font_Size").toInt(),
						config->value("Target_Date_Font/Font_BoldLevel").toInt()));
	tDay->setPalette(tarDayColor);

	tip->setFont(QFont(config->value("Tip_Font/Font_Style").toString(),
						config->value("Tip_Font/Font_Size").toInt(),
						config->value("Tip_Font/Font_BoldLevel").toInt()));
	tip->setPalette(tipColor);

	dayTip->setFont(QFont(config->value("Day_Font/Font_Style").toString(),
						config->value("Tip_Font/Font_Size").toInt(),
						config->value("Tip_Font/Font_BoldLevel").toInt()));
	dayTip->setPalette(tipColor);

	           //----------------------移动label到指定位置并显示----------------------

	cDay->setText(dc.currentTime); 
	tDay->setText(dc.targetDateTime.toString("yyyy-MM-dd"));
	day->setText(QString::number(dc.days));
	dayTip->setText(dc.dayText);
	tip->setText(tipWord);
			//--------------------------位置----------------------------
	tip->move(config->value("Control_Position/Tip_Text_Position_X").toInt(),
				config->value("Control_Position/Tip_Text_Position_Y").toInt());

	cDay->move(config->value("Control_Position/Current_Day_Position_X").toInt(),
				config->value("Control_Position/Current_Day_Position_Y").toInt());

	tDay->move(config->value("Control_Position/Target_Day_Position_X").toInt(),
				config->value("Control_Position/Target_Day_Position_Y").toInt());

	day->move(config->value("Control_Position/Day_Position_X").toInt(),
				config->value("Control_Position/Day_Position_Y").toInt());

	dayTip->move(config->value("Control_Position/Day_Text_Position_X").toInt(),
		config->value("Control_Position/Day_Text_Position_Y").toInt());

	cDay,tDay,day,dayTip,tip->show();

	delete config;

					 //----------------------安装事件过滤器-------------------------
	day->installEventFilter(this);
	cDay->installEventFilter(this);
	tDay->installEventFilter(this);
	tip->installEventFilter(this);
	dayTip->installEventFilter(this);
	this->installEventFilter(this);

}


positionSettings::~positionSettings()
{
}
				//----------------背景图预览--------------------
void positionSettings::paintEvent(QPaintEvent* e)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), QPixmap(imgPTH), QRect());
}
	
               //-----------事件过滤---------------------
bool positionSettings::eventFilter(QObject* obj, QEvent* event)
{
	QMouseEvent* e = static_cast<QMouseEvent*>(event);
	const QPointF windowPT = e->windowPos();
	QPoint cDayPos, tDayPos, tipPos, dayTipP, dayPos;
	//以下是各个控件鼠标拖动事件
	if (obj == cDay)
	{
		if (event->type() == QEvent::MouseMove) {
			cDayPos = windowPT.toPoint();
			cDay->move(cDayPos);
			return true;
		}
		return false;
	}
	else if (obj == tDay)
	{
		if (event->type() == QEvent::MouseMove) {
			tDayPos = windowPT.toPoint();
			tDay->move(tDayPos);
			return true;
		}
		return false;
	}
	else if (obj == day)
	{
		if (event->type() == QEvent::MouseMove)
		{
			dayPos = windowPT.toPoint();
			day->move(dayPos);
			return true;
		}
		return false;
	}
	else if (obj == dayTip)
	{
		dayTip->setMouseTracking(false);
		if (event->type() == QEvent::MouseMove)
		{
			dayTipP = windowPT.toPoint();
			dayTip->move(dayTipP);
			return true;
		}
		return false;
	}
	else if (obj == tip)
	{
		if (event->type() == QEvent::MouseMove)
		{
				tipPos = windowPT.toPoint();
				tip->move(tipPos);
				return true;
		}
		return false;
	}
	//关闭窗口时自动保存 （确保只执行一次）
	
	if ((event->type() == QEvent::Hide) && (count_ == 0)) 
	{
		QSettings* configIni = new QSettings("./config/config.ini", QSettings::IniFormat);
		//存储在配置文件
		configIni->setValue("Control_Position/Tip_Text_Position_X", tip->pos().x());
		configIni->setValue("Control_Position/Tip_Text_Position_Y", tip->pos().y());

		configIni->setValue("Control_Position/Day_Position_X", day->pos().x());
		configIni->setValue("Control_Position/Day_Position_Y", day->pos().y());

		configIni->setValue("Control_Position/Current_Day_Position_X", cDay->pos().x());
		configIni->setValue("Control_Position/Current_Day_Position_Y", cDay->pos().y());

		configIni->setValue("Control_Position/Target_Day_Position_X", tDay->pos().x());
		configIni->setValue("Control_Position/Target_Day_Position_Y", tDay->pos().y());

		configIni->setValue("Control_Position/Day_Text_Position_X", dayTip->pos().x());
		configIni->setValue("Control_Position/Day_Text_Position_Y", dayTip->pos().y());
		delete configIni;

		QMessageBox::information(this, QStringLiteral("信息"), QStringLiteral("保存成功，重启以应用设置"));
		count_++;
	}
	return QWidget::eventFilter(obj, event);
}