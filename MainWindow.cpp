/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.cpp
 *
 *        Version:  1.0
 *        Created:  09.11.2009 14:02:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "MainWindow.h"
#include "MandelbrotWidget.h"
#include "SettingsWidget.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle("Mandelbrot");
	m_mandelbrot = new MandelbrotWidget(this);
	setCentralWidget(m_mandelbrot);

	m_settings = new SettingsWidget(m_mandelbrot);
	addDockWidget(Qt::LeftDockWidgetArea, m_settings);
}


MainWindow::~MainWindow()
{
	delete m_mandelbrot;
}

