/*
 * =====================================================================================
 *
 *       Filename:  SettingsWidget.cpp
 *
 *        Version:  1.0
 *        Created:  09.11.2009 14:21:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "SettingsWidget.h"
#include "MandelbrotWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTime>
#include <QGroupBox>
#include <QFormLayout>
#include <QDoubleSpinBox>


const double SettingsWidget::m_defaultLeft       = -0.746191;
const double SettingsWidget::m_defaultTop        = -0.111974;
const double SettingsWidget::m_defaultWidth      = 0.00005;
const double SettingsWidget::m_defaultHeight     = 0.00005;
const int SettingsWidget::m_defaultRenderWidth   = 512;
const int SettingsWidget::m_defaultRenderHeight  = 512;
const int SettingsWidget::m_defaultThreadCount   = 4;
const int SettingsWidget::m_defaultSegmentWidth  = 64;
const int SettingsWidget::m_defaultSegmentHeight = 64;

SettingsWidget::SettingsWidget(MandelbrotWidget *mandelbrot, QWidget *parent)
	: QDockWidget(parent),
	m_mandelbrot(mandelbrot),
	m_started(false)
{
	setWindowTitle(tr("Settings"));

	m_renderTimer = new QTime;

	QVBoxLayout *layout = new QVBoxLayout;
	QWidget *widget = new QWidget(this);
	widget->setLayout(layout);
	setWidget(widget);

	QGroupBox *areaGroupBox = new QGroupBox(tr("Area"));
	QGroupBox *outputGroupBox = new QGroupBox(tr("Output settings"));
	QGroupBox *threadsGroupBox = new QGroupBox(tr("Threads"));
	QGroupBox *iterationsGroupBox = new QGroupBox(tr("Iterations"));
	layout->addWidget(areaGroupBox);
	layout->addWidget(outputGroupBox);
	layout->addWidget(threadsGroupBox);
	layout->addWidget(iterationsGroupBox);

	m_leftSpinBox = new QDoubleSpinBox;
	m_leftSpinBox->setDecimals(SpinBoxDecimals);
	m_leftSpinBox->setRange(-10, 10);
	m_leftSpinBox->setValue(m_defaultLeft);
	m_topSpinBox = new QDoubleSpinBox;
	m_topSpinBox->setDecimals(SpinBoxDecimals);
	m_topSpinBox->setRange(-10, 10);
	m_topSpinBox->setValue(m_defaultTop);
	m_widthSpinBox = new QDoubleSpinBox;
	m_widthSpinBox->setDecimals(SpinBoxDecimals);
	m_widthSpinBox->setRange(0.00000001, 10);
	m_widthSpinBox->setValue(m_defaultWidth);
	m_heightSpinBox = new QDoubleSpinBox;
	m_heightSpinBox->setDecimals(SpinBoxDecimals);
	m_heightSpinBox->setRange(0.00000001, 10);
	m_heightSpinBox->setValue(m_defaultHeight);

	QFormLayout *areaLayout = new QFormLayout;
	areaGroupBox->setLayout(areaLayout);
	areaLayout->addRow(tr("&Left"), m_leftSpinBox);
	areaLayout->addRow(tr("&Top"), m_topSpinBox);
	areaLayout->addRow(tr("&Width"), m_widthSpinBox);
	areaLayout->addRow(tr("&Height"), m_heightSpinBox);

	m_renderWidthSpinBox = new QSpinBox;
	m_renderWidthSpinBox->setRange(1, 8192);
	m_renderWidthSpinBox->setValue(m_defaultRenderWidth);
	m_renderHeightSpinBox = new QSpinBox;
	m_renderHeightSpinBox->setRange(1, 8192);
	m_renderHeightSpinBox->setValue(m_defaultRenderHeight);

	QFormLayout *outputLayout = new QFormLayout;
	outputGroupBox->setLayout(outputLayout);
	outputLayout->addRow(tr("W&idth"), m_renderWidthSpinBox);
	outputLayout->addRow(tr("H&eight"), m_renderHeightSpinBox);

	m_threadSpinBox = new QSpinBox;
	m_threadSpinBox->setRange(1, 255);
	m_threadSpinBox->setValue(m_defaultThreadCount);
	m_segmentWidthSpinBox = new QSpinBox;
	m_segmentWidthSpinBox->setRange(1, 8192);
	m_segmentWidthSpinBox->setValue(m_defaultSegmentWidth);
	m_segmentHeightSpinBox = new QSpinBox;
	m_segmentHeightSpinBox->setRange(1, 8192);
	m_segmentHeightSpinBox->setValue(m_defaultSegmentHeight);

	QFormLayout *threadsLayout = new QFormLayout;
	threadsGroupBox->setLayout(threadsLayout);
	threadsLayout->addRow(tr("&Number of threads"), m_threadSpinBox);
	threadsLayout->addRow(tr("&Segment width"), m_segmentWidthSpinBox);
	threadsLayout->addRow(tr("Se&gment height"), m_segmentHeightSpinBox);

	m_iterationsSpinBox = new QSpinBox;
	m_iterationsSpinBox->setRange(1, 8192);
	m_iterationsSpinBox->setValue(1000);

	QFormLayout *iterationsLayout = new QFormLayout;
	iterationsGroupBox->setLayout(iterationsLayout);
	iterationsLayout->addRow(tr("&Max iterations"), m_iterationsSpinBox);

	m_useGmp = new QPushButton(tr("&Use GMP"));
	m_useGmp->setCheckable(true);
	m_useGmp->setChecked(true);
	layout->addWidget(m_useGmp);

	layout->addStretch();

	m_timeLabel = new QLabel;
	m_timeLabel->setFrameShape(QFrame::StyledPanel);
	m_timeLabel->setFrameShadow(QFrame::Plain);
	layout->addWidget(m_timeLabel);

	QHBoxLayout *btnLayout = new QHBoxLayout();
	layout->addLayout(btnLayout);
	m_startBtn = new QPushButton(tr("Start"));
	m_stopBtn = new QPushButton(tr("Stop"));
	btnLayout->addWidget(m_startBtn);
	btnLayout->addWidget(m_stopBtn);

	connect(m_startBtn, SIGNAL(clicked()), SLOT(start()));
	connect(m_stopBtn, SIGNAL(clicked()), SLOT(stop()));
	connect(m_mandelbrot, SIGNAL(renderingStarted()), SLOT(setRunningState()));
	connect(m_mandelbrot, SIGNAL(renderingStopped()), SLOT(setStoppedState()));

	setState(Finished);
}


SettingsWidget::~SettingsWidget()
{
	delete m_renderTimer;
}


void SettingsWidget::setState(RenderingState state)
{
	switch (state)
	{
		case Running:
			m_startBtn->setEnabled(false);
			m_stopBtn->setEnabled(true);
			m_renderTimer->start();
			break;
		case Finished:
			m_startBtn->setEnabled(true);
			m_stopBtn->setEnabled(false);
			if (m_started) {
				m_timeLabel->setText(QString("<b>%1</b> ms").arg(m_renderTimer->elapsed()));
			}
			m_started = false;
			break;
	}
}


void SettingsWidget::start()
{
	m_started = true;

	m_mandelbrot->setRegion(m_leftSpinBox->value(), m_topSpinBox->value(), m_widthSpinBox->value(), m_heightSpinBox->value());
	m_mandelbrot->setRenderingSize(m_renderWidthSpinBox->value(), m_renderHeightSpinBox->value());
	m_mandelbrot->setThreadCount(m_threadSpinBox->value());
	m_mandelbrot->setSegmentSize(m_segmentWidthSpinBox->value(), m_segmentHeightSpinBox->value());
	m_mandelbrot->setMaxIterations(m_iterationsSpinBox->value());
	m_mandelbrot->setGmp(m_useGmp->isChecked());

	m_startBtn->setEnabled(false);
	m_mandelbrot->startRendering();
}


void SettingsWidget::stop()
{
	m_stopBtn->setEnabled(false);
	m_mandelbrot->stopRendering();
}


void SettingsWidget::setRunningState()
{
	setState(Running);
}


void SettingsWidget::setStoppedState()
{
	setState(Finished);
}


