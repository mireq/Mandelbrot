/*
 * =====================================================================================
 *
 *       Filename:  MandelbrotWidget.cpp
 *
 *        Version:  1.0
 *        Created:  07.11.2009 23:38:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "MandelbrotWidget.h"

#include "RenderThread.h"

#include <QPainter>
#include <QTimer>

MandelbrotWidget::MandelbrotWidget(QWidget *parent)
	: QWidget(parent),
	m_segmentsRendered(-1),
	m_img(0, 0, QImage::Format_RGB32),
	m_useGmp(false),
	m_running(false)
{
	m_updateTimer = new QTimer(this);
	m_updateTimer->setSingleShot(true);
	connect(m_updateTimer, SIGNAL(timeout()), SLOT(update()));
	m_threadCount = 0;
	m_threadProgress = NULL;
	setMinimumSize(480, 480);
}


MandelbrotWidget::~MandelbrotWidget()
{
	if (m_threadProgress != NULL) {
		delete[] m_threadProgress;
		m_threadProgress = NULL;
	}
}


void MandelbrotWidget::setRegion(double left, double top, double width, double height)
{
	Q_ASSERT(width > 0);
	Q_ASSERT(height > 0);

	m_left   = left;
	m_top    = top;
	m_width  = width;
	m_height = height;
}


void MandelbrotWidget::setRenderingSize(int width, int height)
{
	Q_ASSERT(width > 0);
	Q_ASSERT(height > 0);

	stopRendering();
	m_img = QImage(width, height, QImage::Format_RGB32);
	m_renderingSize = QSize(width, height);
	setMinimumSize(width, height);
}


void MandelbrotWidget::setThreadCount(int threadCount)
{
	Q_ASSERT(threadCount > 0);

	stopRendering();
	m_threadCount = threadCount;
	initThreads();
}


void MandelbrotWidget::setSegmentSize(int width, int height)
{
	stopRendering();
	m_segmentSize = QSize(width, height);
}


void MandelbrotWidget::setMaxIterations(int iterations)
{
	Q_ASSERT(iterations > 0);
	m_maxIterations = iterations;
}


void MandelbrotWidget::setGmp(bool useGmp)
{
	stopRendering();
	m_useGmp = useGmp;
}


void MandelbrotWidget::stopRendering()
{
	foreach (RenderThread *thread, m_renderThreads) {
		if (thread->isRunning()) {
			thread->stop();
			thread->wait();
		}
	}
	if (m_threadProgress != NULL) {
		for (int i = 0; i < m_threadCount; ++i) {
			m_threadProgress[i] = -1;
		}
	}
	m_workunits.clear();
	m_segmentsRendered = -1;
	m_segments = 0;
	if (m_running) {
		m_running = false;
		emit renderingStopped();
	}
	update();
}


void MandelbrotWidget::startRendering()
{
	Q_ASSERT(m_threadCount > 0);
	Q_ASSERT(m_segmentSize.isValid());
	stopRendering();
	if (!m_running) {
		m_running = true;
		emit renderingStarted();
	}

	// Vyčistenie plochy
	QPainter painter(&m_img);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, m_img.width(), m_img.height());

	initThreads();

	int segmentsWidth = (m_renderingSize.width() + m_segmentSize.width() - 1) / m_segmentSize.width();
	int segmentsHeight = (m_renderingSize.height() + m_segmentSize.height() - 1) / m_segmentSize.height();
	m_segments = segmentsWidth * segmentsHeight;
	m_segmentsRendered = 0;
	for (int y = 0; y < segmentsHeight; ++y) {
		for (int x = 0; x < segmentsWidth; ++x) {
			int px = x * m_segmentSize.width();
			int py = y * m_segmentSize.height();
			int w = m_segmentSize.width();
			int h = m_segmentSize.height();
			if (px + w > m_renderingSize.width()) {
				w = m_renderingSize.width() - px;
			}
			if (py + h > m_renderingSize.height()) {
				h = m_renderingSize.height() - py;
			}
			m_workunits.append(QRect(px, py, w, h));
		}
	}

	for (int thread = 0; thread < m_threadCount; ++thread) {
		startNextWorkunit();
	}
}


void MandelbrotWidget::paintEvent(QPaintEvent * /*event*/)
{
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, width(), height());
	painter.drawImage(0, 0, m_img);
	drawThreadBars(painter);
}


void MandelbrotWidget::drawThreadBars(QPainter &painter)
{
	QString text = tr("Thread");
	QFontMetrics metrics = painter.fontMetrics();
	int width = metrics.width(text) * 4;
	int height = metrics.height() + 8;
	long fullProg = 0;
	for (int i = 0; i < m_threadCount; ++i) {
		if (m_threadProgress[i] < 0) {
			continue;
		}
		QString infoText = text + QString(" %1: %2%").arg(i + 1).arg(m_threadProgress[i] / 10);
		QRect region = QRect(2, i * (height + 2) + 2, width, height);
		drawProgressBar(region, m_threadProgress[i], infoText, painter);
		fullProg += m_threadProgress[i];
	}

	if (m_segmentsRendered < 0 || m_segments == 0) {
		return;
	}
	QRect region = QRect(5, this->height() - height - 5, this->width() - 10, height);
	int progress = 0;
	if (m_segments > 0) {
		progress = int((long(ProgressSteps) * long(m_segmentsRendered) + long(fullProg)) / long(m_segments));
	}
	drawProgressBar(region, progress, tr("Overall Progress"), painter);
}


void MandelbrotWidget::drawProgressBar(const QRect &rect, int progress, const QString &text, QPainter &painter)
{
	static const QBrush progressBox = QColor(32, 32, 32, 127);
	static const QBrush progressBar = QColor(0, 0, 0, 127);
	static const QBrush progressAct = QColor(255, 128, 0);

	QRect progressReg = QRect(rect.left() + 5, rect.bottom() - 8, rect.width() - 10, 5);
	QSize progressSize(progressReg.width() * progress / ProgressSteps, 5);

	painter.setPen(Qt::NoPen);
	painter.setBrush(progressBox);
	painter.drawRect(rect);
	painter.setBrush(progressBar);
	painter.drawRect(progressReg);
	painter.setBrush(progressAct);
	painter.drawRect(QRect(progressReg.topLeft(), progressSize));
	painter.setPen(Qt::white);
	painter.drawText(rect, Qt::AlignHCenter, text);
}


void MandelbrotWidget::initThreads()
{
	if (m_threadProgress != NULL) {
		delete[] m_threadProgress;
		m_threadProgress = NULL;
	}

	foreach (RenderThread *thread, m_renderThreads) {
		if (thread->isRunning()) {
			thread->stop();
			thread->wait();
		}
		delete thread;
	}
	m_renderThreads.clear();
	m_freeThreads.clear();
	m_segments = 0;
	m_segmentsRendered = 0;

	m_threadProgress = new int[m_threadCount];
	for (int i = 0; i < m_threadCount; ++i) {
		RenderThread *thread;
		if (m_useGmp) {
			thread = new RenderThread(i, m_left, m_top, m_width, m_height, m_renderingSize, m_maxIterations, RenderThread::Bignum);
		}
		else {
			thread = new RenderThread(i, m_left, m_top, m_width, m_height, m_renderingSize, m_maxIterations, RenderThread::Double);
		}
		connect(thread, SIGNAL(imageRendered(int, const QImage &, const QPoint &)), SLOT(imageRendered(int, const QImage &, const QPoint &)));
		connect(thread, SIGNAL(progressChanged(int, int, int)), SLOT(updateThreadProgress(int, int, int)));
		m_renderThreads.append(thread);
		m_freeThreads.append(i);
		m_threadProgress[i] = -1;
		thread->start();
	}
}


void MandelbrotWidget::updateThreadProgress(int id, int value, int maxValue)
{
	m_threadProgress[id] = value * ProgressSteps / maxValue;
	if (!m_updateTimer->isActive()) {
		m_updateTimer->start(100);
	}
}


void MandelbrotWidget::startNextWorkunit()
{
	if (m_workunits.empty()) {
		if (m_segmentsRendered == m_segments) {
			if (m_running) {
				m_running = false;
				m_segmentsRendered = -1;
				emit renderingStopped();
			}
		}
		return;
	}
	if (m_freeThreads.empty()) {
		return;
	}
	int threadId = m_freeThreads.takeFirst();
	m_renderThreads[threadId]->startRendering(m_workunits.takeFirst());
}


void MandelbrotWidget::imageRendered(int id, const QImage &image, const QPoint &point)
{
	QPainter painter(&m_img);
	painter.drawImage(point, image);
	update();

	m_freeThreads.append(id);
	m_segmentsRendered++;
	if (m_workunits.empty()) {
		m_renderThreads[id]->stop();
		m_threadProgress[id] = -1;
	}
	else {
		m_threadProgress[id] = 0;
	}
	startNextWorkunit();
}

