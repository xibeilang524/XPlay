
#ifndef XSLIDER_H
#define XSLIDER_H

#include <qslider.h>

class XSlider:public QSlider
{
	Q_OBJECT
public:
	XSlider(QWidget*p=NULL);
	~XSlider();

	void mousePressEvent(QMouseEvent *e);
};

#endif

