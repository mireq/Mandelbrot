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
#include "RenderThread.h"


template <typename NumberT>
uint MandelbrotWorker<NumberT>::m_colormap[MandelbrotWorker::ColormapSize];
template <typename NumberT>
bool MandelbrotWorker<NumberT>::m_colormapInitialized = false;


template <typename NumberT>
MandelbrotWorker<NumberT>::MandelbrotWorker(RenderThread *callback)
{
	// Inicializácia farebnej mapy
	if (!m_colormapInitialized) {
		for (int i = 0; i < ColormapSize; ++i) {
			int r = (512 - i) / 2;
			int g = (i);
			int b = i / 2;
			if (g > 256) {
				g -= g % 256;
			}
			m_colormap[i] = qRgb(r, g, b);
		}
		m_colormapInitialized = true;
	}

	m_callback = callback;
}


template <typename NumberT>
QImage MandelbrotWorker<NumberT>::render(const QRect &rect, bool &stop)
{
	NumberT sizeDX = m_size.width();
	NumberT sizeDY = m_size.height();

	QImage image(rect.size(), QImage::Format_RGB32);

	for (int py = rect.y(); py <= rect.bottom(); ++py) {
		// Zastavenie výpočtu pri požiadavke užívateľa
		if (stop) {
			return image;
		}

		// Signalizujeme výpočeť ďalšieho riadku
		if (m_callback != NULL) {
			m_callback->progressCallback();
		}

		// Prepočet z pixelov na mierku množiny
		NumberT y0 = (NumberT(py) / sizeDY) * m_height + m_top;
		for (int px = rect.x(); px <= rect.right(); ++px) {
			NumberT x0 = (NumberT(px) / sizeDX) * m_width + m_left;

			NumberT x = 0;
			NumberT y = 0;
		
			int iteration = 0;
			int maxIteration = MaxIterations;

			NumberT pow2x = x*x;
			NumberT pow2y = y*y;
		
			while (pow2x + pow2y < NumberT(4.0) && iteration < maxIteration) {
				NumberT xTemp = pow2x - pow2y + x0;
				y = NumberT(2)*x*y + y0;
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


template <typename NumberT>
void MandelbrotWorker<NumberT>::setRegion(NumberT left, NumberT top, NumberT width, NumberT height)
{
	m_left   = left;
	m_top    = top;
	m_width  = width;
	m_height = height;
}


template <typename NumberT>
void MandelbrotWorker<NumberT>::setSize(const QSize &size)
{
	m_size = size;
}


