#include "settings.h"
#include <qsettings.h>
#include <qtextcodec.h>
#include <qpropertyanimation.h>
#include <QFileDialog.h>
#include <qdebug.h>
#include <qmessagebox.h>

#ifdef Q_OS_WIN
#pragma execution_character_set("utf-8")   //解决 VS编译器下中文乱码
#endif

	QSettings* configIni = new QSettings("./config/config.ini", QSettings::IniFormat);

	QString bgImg;
	QString backgroundPth, tipWord, targetDate,
		tipFontColor, tipFontSize, tipFontStyle, tipFontBoldLevel,
		dayFontColor, dayFontSize, dayFontStyle, dayFontBoldLevel,
		curDayFontColor, curDayFontSize, curDayFontStyle, curDayFontBoldLevel,
		tarDayFontColor, tarDayFontSize, tarDayFontStyle, tarDayFontBoldLevel;
	bool isRecPosition;

settings::settings(QWidget *parent)
	: QWidget(parent)
{

	ui.setupUi(this);
	this->setAttribute(Qt::WA_QuitOnClose, false);
	this->setWindowIcon(QIcon(":/imgs/images/programICO.png"));
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint); //设置不可被移动
	this->setWindowTitle("设置");
	launchAnimation(); //启动动画
	//位置设置按钮
	connect(ui.posSettingsBtn, &QPushButton::clicked, this, [=]() 
		{
			QMessageBox::warning(this, "注意", "直接拖动字体即可设置位置，点击关闭即可保存");
			positionSettings* posSet = new positionSettings;
			posSet->show();
		});

	connect(ui.selectImageBtn, &QPushButton::clicked, this, [=]() {
		bgImg = QFileDialog::getOpenFileName(this, QStringLiteral("Select background image"), "C:", QStringLiteral("Picture(*png *jpg *jpeg)"));
		});
	configIni->setIniCodec(QTextCodec::codecForName("GB2312")); //设置ini字符集，避免中文出错

	//预设
	ui.tipWord->setText(configIni->value("Tip_Word").toString());
	QString date = configIni->value("Target_Date").toString();
	QStringList list = date.split("-");
	int year = list[0].toInt();
	int moon = list[1].toInt();
	int day = list[2].toInt();
	ui.targetDate->setDate(QDate(year,moon,day));
	ui.isRecPosition->setChecked(configIni->value("RecordPosition").toBool());

	ui.tipFontColor->setText(configIni->value("Tip_Font/Font_Color").toString());
	ui.tipFontSize->setValue(configIni->value("Tip_Font/Font_Size").toInt());
	ui.tipFontStyle->setCurrentText(configIni->value("Tip_Font/Font_Style").toString());
	ui.tipFontBoldLevel->setValue(configIni->value("Tip_Font/Font_BoldLevel").toInt());

	ui.dayFontColor->setText(configIni->value("Day_Font/Font_Color").toString());
	ui.dayFontSize->setValue(configIni->value("Day_Font/Font_Size").toInt());
	ui.dayFontStyle->setCurrentText(configIni->value("Day_Font/Font_Style").toString());
	ui.dayFontBoldLevel->setValue(configIni->value("Day_Font/Font_BoldLevel").toInt());

	ui.curDayFontColor->setText(configIni->value("Current_Date_Font/Font_Color").toString());
	ui.curDayFontSize->setValue(configIni->value("Current_Date_Font/Font_Size").toInt());
	ui.curDayFontStyle->setCurrentText(configIni->value("Current_Date_Font/Font_Style").toString());
	ui.curDayFontBoldLevel->setValue(configIni->value("Current_Date_Font/Font_BoldLevel").toInt());

	ui.tarDayFontColor->setText(configIni->value("Target_Date_Font/Font_Color").toString());
	ui.tarDayFontSize->setValue(configIni->value("Target_Date_Font/Font_Size").toInt());
	ui.tarDayFontStyle->setCurrentText(configIni->value("Target_Date_Font/Font_Style").toString());
	ui.tarDayFontBoldLevel->setValue(configIni->value("Target_Date_Font/Font_BoldLevel").toInt());

	//应用设置
	connect(ui.applyBtn, &QPushButton::clicked, this, [=]() 
		{
			if (bgImg == "") {
				//backgroundPth = "./background-img/error.png";
				backgroundPth = configIni->value("Background/Image_Path").toString();
			}
			else {
				backgroundPth = bgImg;
			}
			
			isRecPosition = ui.isRecPosition->isChecked();
			tipWord = ui.tipWord->text();
			targetDate = ui.targetDate->text().replace("/", "-");
			
			tipFontColor = ui.tipFontColor->text();
			tipFontSize = ui.tipFontSize->text();
			tipFontStyle = ui.tipFontStyle->currentText();
			tipFontBoldLevel = ui.tipFontBoldLevel->text();

			dayFontColor = ui.dayFontColor->text();
			dayFontSize = ui.dayFontSize->text();
			dayFontStyle = ui.dayFontStyle->currentText();
			dayFontBoldLevel = ui.dayFontBoldLevel->text();

			curDayFontColor = ui.curDayFontColor->text();
			curDayFontSize = ui.curDayFontSize->text();
			curDayFontStyle = ui.curDayFontStyle->currentText();
			curDayFontBoldLevel = ui.curDayFontBoldLevel->text();

			tarDayFontColor = ui.tarDayFontColor->text();
			tarDayFontSize = ui.tarDayFontSize->text();
			tarDayFontStyle = ui.tarDayFontStyle->currentText();
			tarDayFontBoldLevel = ui.tarDayFontBoldLevel->text();

			configIni->setValue("Background/Image_Path", backgroundPth);
			configIni->setValue("Tip_Word", tipWord);
			configIni->setValue("Target_Date", targetDate);
			configIni->setValue("RecordPosition", isRecPosition);

			configIni->setValue("Tip_Font/Font_Color", tipFontColor);
			configIni->setValue("Tip_Font/Font_Size", tipFontSize);
			configIni->setValue("Tip_Font/Font_Style", tipFontStyle);
			configIni->setValue("Day_Font/Font_BoldLevel", tipFontBoldLevel);

			configIni->setValue("Day_Font/Font_Color", dayFontColor);
			configIni->setValue("Day_Font/Font_Size", dayFontSize);
			configIni->setValue("Day_Font/Font_Style", dayFontStyle);
			configIni->setValue("Day_Font/Font_BoldLevel", dayFontBoldLevel);

			configIni->setValue("Current_Date_Font/Font_Color", curDayFontColor);
			configIni->setValue("Current_Date_Font/Font_Size", curDayFontSize);
			configIni->setValue("Current_Date_Font/Font_Style", curDayFontStyle);
			configIni->setValue("Current_Date_Font/Font_BoldLevel", curDayFontBoldLevel);

			configIni->setValue("Target_Date_Font/Font_Color", tarDayFontColor);
			configIni->setValue("Target_Date_Font/Font_Size", tarDayFontSize);
			configIni->setValue("Target_Date_Font/Font_Style", tarDayFontStyle);
			configIni->setValue("Target_Date_Font/Font_BoldLevel", tarDayFontBoldLevel);
			// --------------------保存成功消息框-----------------
			QMessageBox::information(this, "信息", "保存成功，重启以应用设置");
		});
	//取消设置
	connect(ui.cancelBtn, &QPushButton::clicked, this, [=]()
		{
			QPropertyAnimation* pAnimation = new QPropertyAnimation(this, "windowOpacity");
			pAnimation->setDuration(1000);
			pAnimation->setKeyValueAt(1, 1);
			pAnimation->setKeyValueAt(0, 0);
			pAnimation->setKeyValueAt(0, 1);
			pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
			this->close();
		});
}

settings::~settings()
{
}

void settings::launchAnimation()
{
	QPropertyAnimation* pAnimation = new QPropertyAnimation(this, "windowOpacity");
	pAnimation->setDuration(400);
	pAnimation->setKeyValueAt(0, 1);
	pAnimation->setKeyValueAt(0, 0);
	pAnimation->setKeyValueAt(1, 1);
	pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}