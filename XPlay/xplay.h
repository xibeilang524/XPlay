
#ifndef XPLAY_H
#define XPLAY_H

#include <QWidget>
#include "ui_xplay.h"

class XPlay : public QWidget
{
	Q_OBJECT

public:
	XPlay(QWidget *parent = 0);
	~XPlay();
	void resizeEvent(QResizeEvent *e);
	void timerEvent(QTimerEvent *e);
	void openFile(QString name);

public slots:
	void open();
	void play();
	void sliderPress();
	void sliderRelease();

private:
	Ui::XPlayClass ui;

};

#endif // XPLAY_H
