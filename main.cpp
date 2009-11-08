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
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>

#include <gmpxx.h>
#include "MandelbrotWorker.h"
#include "MandelbrotWidget.h"
#include "UltraMath.h"


#define LEFT -0.746191
#define TOP -0.111974
#define WIDTH 0.00005
#define HEIGHT 0.00005

/*
class Label : public QLabel
{
protected:
	void mouseReleaseEvent ( QMouseEvent * event ) {
		double x = event->x();
		double y = event->y();
		double w = 256;
		double h = 256;
		double left = LEFT;
		double top  = TOP;
		double width = WIDTH;
		double height = HEIGHT;

		qDebug() << (x / w) * width + left << (y / h) * height + top;
	}
};*/


int main(int argc, char *argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);
	mpf_set_default_prec(6);
	QApplication app(argc, argv);
	MandelbrotWidget w;
	w.show();
	//MandelbrotWorker w;
	//QImage image = w.render(LEFT, TOP, WIDTH, HEIGHT, QRect(0, 0, 256, 256), QSize(256, 256));
	//Label label;
	//label.setPixmap(QPixmap::fromImage(image));
	//label.show();
	return app.exec();
}

