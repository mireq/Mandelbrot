/*
 * =====================================================================================
 *
 *       Filename:  SettingsWidget.h
 *     ____    __  __  _             _      ___    __         __
 *    / __/__ / /_/ /_(_)__  ___ ___| | /| / (_)__/ /__ ____ / /_
 *   _\ \/ -_) __/ __/ / _ \/ _ `(_-< |/ |/ / / _  / _ `/ -_) __/
 *  /___/\__/\__/\__/_/_//_/\_, /___/__/|__/_/\_,_/\_, /\__/\__/
 *                         /___/                  /___/
 *        Version:  1.0
 *        Created:  09.11.2009 14:21:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  SETTINGSWIDGET_H
#define  SETTINGSWIDGET_H

#include <QDockWidget>

class QLabel;
class QPushButton;
class QTime;
class QDoubleSpinBox;
class QSpinBox;
class MandelbrotWidget;

class SettingsWidget: public QDockWidget
{
Q_OBJECT
public:
	enum RenderingState {
		Finished = 0,
		Running = 1
	};
	SettingsWidget(MandelbrotWidget *mandelbrot, QWidget *parent = 0);
	~SettingsWidget();
	void setState(RenderingState state);
private slots:
	void start();
	void stop();
	void setRunningState();
	void setStoppedState();
private:
	enum {SpinBoxDecimals = 8};

	QPushButton *m_startBtn;
	QPushButton *m_stopBtn;
	MandelbrotWidget *m_mandelbrot;
	QLabel *m_timeLabel;
	QTime *m_renderTimer;
	bool m_started;

	QDoubleSpinBox *m_leftSpinBox;
	QDoubleSpinBox *m_topSpinBox;
	QDoubleSpinBox *m_widthSpinBox;
	QDoubleSpinBox *m_heightSpinBox;
	QSpinBox *m_renderWidthSpinBox;
	QSpinBox *m_renderHeightSpinBox;
	QSpinBox *m_threadSpinBox;
	QSpinBox *m_segmentWidthSpinBox;
	QSpinBox *m_segmentHeightSpinBox;
	QPushButton *m_useGmp;

	static const double m_defaultLeft;
	static const double m_defaultTop;
	static const double m_defaultWidth;
	static const double m_defaultHeight;
	static const int m_defaultRenderWidth;
	static const int m_defaultRenderHeight;
	static const int m_defaultThreadCount;
	static const int m_defaultSegmentWidth;
	static const int m_defaultSegmentHeight;
};

#endif   /* ----- #ifndef SETTINGSWIDGET_H  ----- */

