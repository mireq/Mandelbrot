/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *        Version:  1.0
 *        Created:  07.11.2009 12:13:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include <QApplication>

#include "MandelbrotWidget.h"
#include "UltraMath.h"

#define LEFT -0.746191
#define TOP -0.111974
#define WIDTH 0.00005
#define HEIGHT 0.00005

int main(int argc, char *argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);
	mpf_set_default_prec(512);
	QApplication app(argc, argv);
	MandelbrotWidget w;
	w.setRegion(LEFT, TOP, WIDTH, HEIGHT);
	w.setRenderingSize(1024, 1024);
	w.setThreadCount(4);
	w.setSegmentSize(256, 256);
	w.show();
	w.startRendering();
	return app.exec();
}

