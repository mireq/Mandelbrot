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

#include <functional>
#include <algorithm>

#include <QImage>
#include <QPixmap>
#include <QLabel>

#include <QDebug>

RenderThread::RenderThread(int id, double left, double top, double width, double height, const QSize &size)
	: QThread(),
	m_id(id),
	m_left(left),
	m_top(top),
	m_width(width),
	m_height(height),
	m_size(size),
	m_rownum(0),
	m_maxRownum(0)
{
	m_doubleWorker = new MandelbrotWorker<double>(this);
	m_doubleWorker->setRegion(left, top, width, height);
	m_doubleWorker->setSize(size);
}


RenderThread::~RenderThread()
{
	delete m_doubleWorker;
}


void RenderThread::startRendering(const QRect &region, Priority priority)
{
	m_renderRegion = region;
	m_maxRownum = region.height();
	start(priority);
}


void RenderThread::run()
{
	//std::binder1st<std::mem_fun1_t<void, RenderThread, int> >callback = std::bind1st(std::mem_fun(&RenderThread::progressCallback), this);
	m_rownum = 0;
	QImage img = m_doubleWorker->render(m_renderRegion);
	emit imageRendered(img, m_renderRegion.topLeft());
}


void RenderThread::start(Priority priority)
{
	QThread::start(priority);
}


void RenderThread::progressCallback()
{
	m_rownum++;
	emit progressChanged(m_id, m_rownum, m_maxRownum);
}

