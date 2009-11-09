/*
 * =====================================================================================
 *
 *       Filename:  MandelbrotWidget.h
 *     __  ___             __    ____            __ _      ___    __         __
 *    /  |/  /__ ____  ___/ /__ / / /  _______  / /| | /| / (_)__/ /__ ____ / /_
 *   / /|_/ / _ `/ _ \/ _  / -_) / _ \/ __/ _ \/ __/ |/ |/ / / _  / _ `/ -_) __/
 *  /_/  /_/\_,_/_//_/\_,_/\__/_/_.__/_/  \___/\__/|__/|__/_/\_,_/\_, /\__/\__/
 *                                                               /___/
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
#include <QVector>

class RenderThread;
class QTimer;

class MandelbrotWidget : public QWidget
{
Q_OBJECT
public:
	MandelbrotWidget(QWidget *parent = 0);
	~MandelbrotWidget();
	void setRegion(double left, double top, double width, double height);
	void setRenderingSize(int width, int height);
	void setThreadCount(int threadCount);
	void setSegmentSize(int width, int height);
	void setGmp(bool useGmp);
	void stopRendering();
	void startRendering();
signals:
	void renderingStarted();
	void renderingStopped();
protected:
	virtual void paintEvent(QPaintEvent *event);
private:
	void drawThreadBars(QPainter &painter);
	void drawProgressBar(const QRect &rect, int progress, const QString &text, QPainter &painter);
	void initThreads();
private slots:
	void imageRendered(int id, const QImage &image, const QPoint &point);
	void updateThreadProgress(int id, int value, int maxValue);
	void startNextWorkunit();
private:
	enum {ProgressSteps = 1000};
	int m_segments;
	int m_segmentsRendered;
	int *m_threadProgress;
	int m_threadCount;
	QImage m_img;
	QSize m_renderingSize;
	QSize m_segmentSize;
	bool m_useGmp;
	QTimer *m_updateTimer;

	QVector<RenderThread *> m_renderThreads;
	QList<int> m_freeThreads;
	QList<QRect> m_workunits;

	double m_left;
	double m_top;
	double m_width;
	double m_height;

	bool m_running;
};

#endif   /* ----- #ifndef MANDELBROTWIDGET_H  ----- */

