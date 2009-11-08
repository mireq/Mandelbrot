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


MandelbrotWorker::MandelbrotWorker()
{
	for (int i = 0; i < ColormapSize; ++i) {
		int r = (512 - i) / 2;
		int g = (i);
		int b = i / 2;
		if (g > 256) {
			g -= g % 256;
		}
		m_colormap[i] = qRgb(r, g, b);
	}
}


QImage MandelbrotWorker::render(bignum left, bignum top, bignum width, bignum height, const QRect &rect, const QSize &size)
{
	bignum sizeDX = size.width();
	bignum sizeDY = size.height();
	QImage image(rect.size(), QImage::Format_RGB32);

	for (int py = rect.y(); py < rect.bottom(); ++py) {
		bignum y0 = (bignum(py) / sizeDY) * height + top;
		for (int px = rect.x(); px < rect.right(); ++px) {
			bignum x0 = (bignum(px) / sizeDX) * width + left;
			bignum x = 0;
			bignum y = 0;
		
			int iteration = 0;
			int maxIteration = 1024;

			bignum pow2x = x*x;
			bignum pow2y = y*y;
		
			while (pow2x + pow2y < bignum(4.0) && iteration < maxIteration) {
				bignum xTemp = pow2x - pow2y + x0;
				y = bignum(2)*x*y + y0;
				x = xTemp;
				iteration++;
				pow2x = x*x;
				pow2y = y*y;
			}
		
			if (iteration == maxIteration) {
				image.setPixel(px - rect.x(), py - rect.y(), 0x00000000);
			}
			else {
				image.setPixel(px - rect.x(), py - rect.y(), m_colormap[iteration / 2]);
			}
		}
	}

	return image;
}

