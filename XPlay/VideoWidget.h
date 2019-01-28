
#ifndef VIDEOWIDGET
#define VIDEOWIDGET

#include <QtWidgets/qwidget.h>
#include <QOpenGLWidget>

class VideoWidget : public QOpenGLWidget
{
public:
	VideoWidget(QWidget *p = NULL);
    virtual ~VideoWidget();

	void paintEvent(QPaintEvent *e);
	void timerEvent(QTimerEvent *e);

};

#endif



