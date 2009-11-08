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

#include <QPainter>

#include <QDebug>

MandelbrotWidget::MandelbrotWidget(QWidget *parent)
	: QWidget(parent), m_img(0, 0, QImage::Format_RGB32)
{
	m_threadCount = 0;
	m_threadProgress = NULL;
	setMinimumSize(128, 128);
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
	m_img = QImage(width, height, QImage::Format_RGB32);
}


void MandelbrotWidget::setThreadCount(int threadCount)
{
	stopRendering();
	m_threadCount = threadCount;
	initThreads();
}


void MandelbrotWidget::stopRendering()
{
	if (m_threadProgress != NULL) {
		for (int i = 0; i < m_threadCount; ++i) {
			m_threadProgress[i] = 0;
		}
	}
	update();
}


void MandelbrotWidget::startRendering()
{
	Q_ASSERT(m_threadCount > 0);
	stopRendering();

	/*foreach (RenderThread *thread, m_renderThreads) {
		thread->startRendering(QRect(0, 0, 256, 256));
	}*/
	m_renderThreads[0]->startRendering(QRect(0, 0, 512, 512));
	m_renderThreads[1]->startRendering(QRect(512, 0, 512, 512));
	m_renderThreads[2]->startRendering(QRect(0, 512, 512, 512));
	m_renderThreads[3]->startRendering(QRect(512, 512, 512, 512));
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
	QString text = "Thread";
	QFontMetrics metrics = painter.fontMetrics();
	int width = metrics.width(text) * 4;
	int height = metrics.height() + 8;
	int fullProg = 0;
	for (int i = 0; i < m_threadCount; ++i) {
		QString infoText = text + QString(" %1: %2%").arg(i + 1).arg(m_threadProgress[i] / 10);
		QRect region = QRect(2, i * (height + 2) + 2, width, height);
		drawProgressBar(region, m_threadProgress[i], infoText, painter);
		fullProg += m_threadProgress[i];
	}
	QRect region = QRect(5, this->height() - height - 5, this->width() - 10, height);
	drawProgressBar(region, fullProg / 4, "Overall Progress", painter);
}


void MandelbrotWidget::drawProgressBar(const QRect &rect, int progress, const QString &text, QPainter &painter)
{
	static const QBrush progressBox = QColor(32, 32, 32, 127);
	static const QBrush progressBar = QColor(0, 0, 0, 127);
	static const QBrush progressAct = QColor(255, 128, 0);

	QRect progressReg = QRect(rect.left() + 5, rect.bottom() - 8, rect.width() - 10, 5);
	QSize progressSize(progressReg.width() * progress / 1000, 5);

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
		delete thread;
	}
	m_renderThreads.clear();

	m_threadProgress = new int[m_threadCount];
	for (int i = 0; i < m_threadCount; ++i) {
		RenderThread *thread = new RenderThread(i, m_left, m_top, m_width, m_height, m_img.size());
		connect(thread, SIGNAL(imageRendered(const QImage &, const QPoint &)), SLOT(drawImage(const QImage &, const QPoint &)));
		connect(thread, SIGNAL(progressChanged(int, int, int)), SLOT(updateThreadProgress(int, int, int)));
		m_renderThreads.append(thread);
	}
}


void MandelbrotWidget::updateThreadProgress(int id, int value, int maxValue)
{
	m_threadProgress[id] = value * 1000 / maxValue;
	update();
}


void MandelbrotWidget::drawImage(const QImage &image, const QPoint &point)
{
	QPainter painter(&m_img);
	qDebug() << image.size();
	QImage ni(256, 256, QImage::Format_ARGB32);
	QPainter ptr(&ni);
	ptr.fillRect(0, 0, 256, 256, Qt::white);
	ptr.end();
	painter.drawImage(point, ni);
	painter.drawImage(point, image);
	update();
}

