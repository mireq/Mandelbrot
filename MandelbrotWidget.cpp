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

MandelbrotWidget::MandelbrotWidget(QWidget *parent)
	: QWidget(parent)
{
	m_threads = 4;
	m_threadProgress = new int[m_threads];
	
	m_threadProgress[0] = 100;
	m_threadProgress[1] = 300;
	m_threadProgress[2] = 500;
	m_threadProgress[3] = 900;

	m_pix = QPixmap("/home/mirec/hnusnyprogram.png");
}


MandelbrotWidget::~MandelbrotWidget()
{
	delete[] m_threadProgress;
}


void MandelbrotWidget::paintEvent(QPaintEvent * /*event*/)
{
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, width(), height());
	painter.drawPixmap(0, 0, m_pix);
	drawThreadBars(painter);
}


void MandelbrotWidget::drawThreadBars(QPainter &painter)
{
	QString text = "Thread";
	QFontMetrics metrics = painter.fontMetrics();
	int width = metrics.width(text) * 4;
	int height = metrics.height() + 8;
	for (int i = 0; i < m_threads; ++i) {
		QString infoText = text + QString(" %1: %2%").arg(i + 1).arg(m_threadProgress[i] / 10);
		QRect region = QRect(2, i * (height + 2) + 2, width, height);
		drawProgressBar(region, m_threadProgress[i], infoText, painter);
	}
	QRect region = QRect(5, this->height() - height - 5, this->width() - 10, height);
	drawProgressBar(region, 500, "Overall Progress", painter);
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
