/*
 * =====================================================================================
 *
 *       Filename:  RenderThread.cpp
 *
 *        Version:  1.0
 *        Created:  08.11.2009 12:54:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "RenderThread.h"
#include "MandelbrotWorker.h"

#include <QImage>
#include <QPixmap>

RenderThread::RenderThread(int id, double left, double top, double width, double height, const QSize &size, int maxIterations, WorkerType type)
	: QThread(),
	m_doubleWorker(NULL),
	m_bignumWorker(NULL),
	m_id(id),
	m_left(left),
	m_top(top),
	m_width(width),
	m_height(height),
	m_size(size),
	m_renderLock(0),
	m_maxIterations(maxIterations),
	m_rownum(0),
	m_maxRownum(0),
	m_stop(false)
{
	if (type == Double) {
		m_doubleWorker = new MandelbrotWorker<double>(this);
		m_doubleWorker->setRegion(left, top, width, height);
		m_doubleWorker->setSize(size);
		m_doubleWorker->setMaxIterations(m_maxIterations);
	}
	else {
		m_bignumWorker = new MandelbrotWorker<bignum>(this);
		m_bignumWorker->setRegion(left, top, width, height);
		m_bignumWorker->setSize(size);
		m_bignumWorker->setMaxIterations(m_maxIterations);
	}
}


RenderThread::~RenderThread()
{
	if (m_doubleWorker != NULL) {
		delete m_doubleWorker;
		m_doubleWorker = NULL;
	}
	else {
		delete m_bignumWorker;
		m_bignumWorker = NULL;
	}
}


void RenderThread::startRendering(const QRect &region)
{
	m_threadFree.lock();
	m_renderRegion = region;
	m_maxRownum = region.height();
	m_renderLock.release();
}


void RenderThread::stop()
{
	m_stop = true;
	// Podstrčenie nevalidných dát pre ukončenie vlákna
	startRendering(QRect());
}


void RenderThread::run()
{
	//std::binder1st<std::mem_fun1_t<void, RenderThread, int> >callback = std::bind1st(std::mem_fun(&RenderThread::progressCallback), this);
	forever {
		// Čakanie na dáta
		m_renderLock.acquire();
		if (!m_renderRegion.isValid()) {
			m_threadFree.unlock();
			return;
		}
		m_rownum = 0;
		QImage img;
		//QImage img = m_doubleWorker->render(m_renderRegion, m_stop);
		if (m_doubleWorker != NULL) {
			img = m_doubleWorker->render(m_renderRegion, m_stop);
		}
		else {
			img = m_bignumWorker->render(m_renderRegion, m_stop);
		}
		emit imageRendered(m_id, img, m_renderRegion.topLeft());
		m_threadFree.unlock();
	}
}


void RenderThread::progressCallback()
{
	m_rownum++;
	emit progressChanged(m_id, m_rownum, m_maxRownum);
}

