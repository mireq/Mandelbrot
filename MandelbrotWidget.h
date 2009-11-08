/*
 * =====================================================================================
 *
 *       Filename:  MandelbrotWidget.h
 *
 *        Version:  1.0
 *        Created:  07.11.2009 23:37:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  MANDELBROTWIDGET_H
#define  MANDELBROTWIDGET_H

#include <QWidget>

class MandelbrotWidget : public QWidget
{
Q_OBJECT
public:
	MandelbrotWidget(QWidget *parent = 0);
	~MandelbrotWidget();
protected:
	virtual void paintEvent(QPaintEvent *event);
private:
	void drawThreadBars(QPainter &painter);
	void drawProgressBar(const QRect &rect, int progress, const QString &text, QPainter &painter);
private:
	int *m_threadProgress;
	int m_threads;
	QPixmap m_pix;
};

#endif   /* ----- #ifndef MANDELBROTWIDGET_H  ----- */

