#include "xplay.h"
#include <QtWidgets/QApplication>
#include "XFFmpeg.h"
#include <QAudioOutput>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	XPlay w;
	w.show();
	return a.exec();
}
