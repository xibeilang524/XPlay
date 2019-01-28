#include "xplay.h"
#include <QFileDialog>
#include <QMessageBox>
#include "XFFmpeg.h"
#include "XAudioPlay.h"
#include <QDebug>

static bool isPressSlider = false;
static bool isPlay = true;

#define PAUSE "QPushButton\
{border-image:url\
(:/XPlay/Resources/pause_normal.png);}"

#define PLAY "QPushButton\
{border-image:url\
(:/XPlay/Resources/play_normal.png);}"

XPlay::XPlay(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	startTimer(40);
}

void XPlay::resizeEvent(QResizeEvent *e)
{
	ui.openGLWidget->resize(size());
	ui.playButton->move(this->width() / 2 + 50, this->height() - 80);
	ui.openButton->move(this->width() / 2 - 50, this->height() - 80);
	ui.playslider->move(25, this->height() - 120);
	ui.playslider->resize(this->width() - 50, ui.playslider->height());
	ui.playtime->move(25, ui.playButton->y());
	ui.sp->move(ui.playtime->x() + ui.playtime->width() + 5, ui.playtime->y());
	ui.totaltime->move(150, ui.playButton->y());
}

void XPlay::timerEvent(QTimerEvent *e)
{
    int min = (XFFmpeg::Get()->pts/1000)/60;
    int sec = (XFFmpeg::Get()->pts/1000) % 60;
	char buf[1024] = { 0 };
	sprintf(buf, "%03d:%02d", min, sec);
	ui.playtime->setText(buf);

	if (XFFmpeg::Get()->totalMs > 0)
	{
		float rate = (float)XFFmpeg::Get()->pts / (float)XFFmpeg::Get()->totalMs;
        if (!isPressSlider)
            ui.playslider->setValue(rate * 1000);
	}

}

void XPlay::sliderPress()
{
	isPressSlider = true;
}

void XPlay::sliderRelease()
{
	float pos = 0;
	pos = (float)ui.playslider->value() / (float)(ui.playslider->maximum() + 1);
    XFFmpeg::Get()->Seek(pos);
    isPressSlider = false;
}

void XPlay::play()
{
	isPlay = !isPlay;
	XFFmpeg::Get()->isPlay = isPlay;
	if (isPlay)
	{
		//pause
		ui.playButton->setStyleSheet(PAUSE);
	}
	else
	{
		ui.playButton->setStyleSheet(PLAY);
	}

}

void XPlay::openFile(QString name)
{
	if (name.isEmpty())
		return;
	this->setWindowTitle(name);
	int totalMs = XFFmpeg::Get()->Open(name.toLocal8Bit());
	if (totalMs <= 0)
	{
		QMessageBox::information(this, "err", "file open failed!");
		return;
	}
	XAudioPlay::Get()->sampleRate = XFFmpeg::Get()->sampleRate;
	XAudioPlay::Get()->channel = XFFmpeg::Get()->channel;
	XAudioPlay::Get()->sampleSize = 16;
	XAudioPlay::Get()->Start();
	char buf[1024] = { 0 };
    int min = (totalMs/1000)/60;
    int sec = (totalMs/1000)%60;
	sprintf(buf, "%03d:%02d", min, sec);
	ui.totaltime->setText(buf);
	isPlay = false;
	play();
}

void XPlay::open()
{
    QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择视频文件"));
	openFile(name);
}

XPlay::~XPlay()
{

}
