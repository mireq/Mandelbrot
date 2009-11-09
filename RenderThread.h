/*
 * =====================================================================================
 *
 *       Filename:  RenderThread.h
 *     ___              __       ________                   __
 *    / _ \___ ___  ___/ /__ ___/_  __/ /  _______ ___ ____/ /
 *   / , _/ -_) _ \/ _  / -_) __// / / _ \/ __/ -_) _ `/ _  /
 *  /_/|_|\__/_//_/\_,_/\__/_/  /_/ /_//_/_/  \__/\_,_/\_,_/
 *
 *        Version:  1.0
 *        Created:  08.11.2009 12:54:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  RENDERTHREAD_H
#define  RENDERTHREAD_H

#include <QThread>
#include <QImage>
#include <QSemaphore>
#include <QMutex>

#include "UltraMath.h"

template <typename NumberT> class MandelbrotWorker;

class RenderThread: public QThread
{
Q_OBJECT
public:
	enum WorkerType {
		Double = 0,
		Bignum = 1
	};
	RenderThread(int id, double left, double top, double width, double height, const QSize &size, WorkerType type);
	~RenderThread();
	void startRendering(const QRect &region);
	void stop();
signals:
	void imageRendered(int id, const QImage &image, const QPoint &region);
	void progressChanged(int id, int value, int maxValue);
protected:
	virtual void run();
private:
	void progressCallback();
	MandelbrotWorker<double> *m_doubleWorker;
	MandelbrotWorker<bignum> *m_bignumWorker;

	int m_id;
	double m_left;
	double m_top;
	double m_width;
	double m_height;
	QSize m_size;
	QRect m_renderRegion;
	QSemaphore m_renderLock;
	QMutex m_threadFree;

	int m_rownum;
	int m_maxRownum;
	bool m_stop;

	template<typename NumberT>
	friend class MandelbrotWorker;
};

#endif   /* ----- #ifndef RENDERTHREAD_H  ----- */

