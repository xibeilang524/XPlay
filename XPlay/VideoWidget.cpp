#include "VideoWidget.h"
#include <QPainter>
#include "XFFmpeg.h"
#include "XVideoThread.h"

VideoWidget::VideoWidget(QWidget *p)
    : QOpenGLWidget(p)
{
	startTimer(20);
	XVideoThread::Get()->start();
}


VideoWidget::~VideoWidget()
{
}

void VideoWidget::paintEvent(QPaintEvent *e)
{
	static QImage *image = NULL;
	static int w = 0;
	static int h = 0;

	if (w != width() || h != height())
	{
        if(image)
		{
			delete image->bits();
			delete image;
			image = NULL;
		}
	}

	if (image == NULL)
	{
        uchar *buf = new uchar[width()*height()*4];
		image = new QImage(buf, width(), height(), QImage::Format_ARGB32);
	}

	XFFmpeg::Get()->ToRGB((char*)image->bits(), width(), height());
	QPainter painter;
	painter.begin(this);
	painter.drawImage(QPoint(0, 0), *image);
	painter.end();
}

void VideoWidget::timerEvent(QTimerEvent *e)
{
	this->update();
}
