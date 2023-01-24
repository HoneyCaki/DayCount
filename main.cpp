
#include "DayCount.h"
#include <QtWidgets/QApplication>
#ifdef Q_OS_WIN
#pragma execution_character_set("utf-8")   //解决 VS编译器下中文乱码
#endif
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DayCount w;
	w.setFixedSize(QSize(483, 440));
	w.setMinimumSize(QSize(483, 440));
	w.setMaximumSize(QSize(483,440));
	w.setWindowTitle("倒数日");
	w.setWindowIcon(QIcon(":/imgs/images/programICO.png")); //程序图标
	
	w.show();
	return a.exec();
}
