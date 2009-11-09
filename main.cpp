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
#include <QTranslator>
#include <QLocale>

#include "MainWindow.h"
#include "UltraMath.h"

int main(int argc, char *argv[])
{
	mpf_set_default_prec(512);
	QApplication app(argc, argv);

	QTranslator appTranslator;
	appTranslator.load(QString("mandelbrot_") + QLocale::system().name());
	app.installTranslator(&appTranslator);

	MainWindow win;
	win.show();
	return app.exec();
}

