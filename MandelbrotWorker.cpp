/*
 * =====================================================================================
 *
 *       Filename:  MandelbrotWorker.cpp
 *
 *        Version:  1.0
 *        Created:  07.11.2009 12:26:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "MandelbrotWorker.h"

#include <QDebug>

MandelbrotWorker::MandelbrotWorker()
{
	for (int i = 0; i < ColormapSize; ++i) {
		//m_colormap[i] = qRgb(255, 255, 255);
		int r = (512 - i) / 2;
		int g = (i);
		int b = i / 2;
		if (g > 256) {
			g -= g % 256;
		}
		m_colormap[i] = qRgb(r, g, b);
	}
}

QImage MandelbrotWorker::render(bignum left, bignum top, bignum width, bignum height)
{
	int sizeX = 1024;
	int sizeY = 1024;
	bignum sizeDX = sizeX;
	bignum sizeDY = sizeY;
	QImage image(QSize(sizeX, sizeY), QImage::Format_RGB32);

	for (int py = 0; py < sizeY; ++py) {
		qDebug() << py;
		bignum y0 = (bignum(py) / sizeDY) * height + top;
		for (int px = 0; px < sizeX; ++px) {
			bignum x0 = (bignum(px) / sizeDX) * width + left;
			bignum x = 0;
			bignum y = 0;
		
			int iteration = 0;
			int maxIteration = 1024;

			bignum pow2x = x*x;
			bignum pow2y = y*y;
		
			while (pow2x + pow2y < 4.0 && iteration < maxIteration) {
				bignum xTemp = pow2x - pow2y + x0;
				y = 2*x*y + y0;
				x = xTemp;
				iteration++;
				pow2x = x*x;
				pow2y = y*y;
			}
		
			if (iteration == maxIteration) {
				image.setPixel(px, py, 0x00000000);
			}
			else {
				image.setPixel(px, py, m_colormap[iteration / 2]);
			}
		}
	}

	return image;
}


