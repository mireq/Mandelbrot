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
#include <QList>

#include "RenderThread.h"

class MandelbrotWidget : public QWidget
{
Q_OBJECT
public:
	MandelbrotWidget(QWidget *parent = 0);
	~MandelbrotWidget();
	void setRegion(double left, double top, double width, double height);
	void setRenderingSize(int width, int height);
	void setThreadCount(int threadCount);
	void stopRendering();
	void startRendering();
protected:
	virtual void paintEvent(QPaintEvent *event);
private:
	void drawThreadBars(QPainter &painter);
	void drawProgressBar(const QRect &rect, int progress, const QString &text, QPainter &painter);
	void initThreads();
private slots:
	void drawImage(const QImage &image, const QPoint &point);
	void updateThreadProgress(int id, int value, int maxValue);
private:
	int *m_threadProgress;
	int m_threadCount;
	QImage m_img;

	QList<RenderThread *> m_renderThreads;

	double m_left;
	double m_top;
	double m_width;
	double m_height;
};

#endif   /* ----- #ifndef MANDELBROTWIDGET_H  ----- */

