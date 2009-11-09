/*
 * =====================================================================================
 *
 *       Filename:  MandelbrotWorker.h
 *     __  ___             __    ____            __ _      __         __
 *    /  |/  /__ ____  ___/ /__ / / /  _______  / /| | /| / /__  ____/ /_____ ____
 *   / /|_/ / _ `/ _ \/ _  / -_) / _ \/ __/ _ \/ __/ |/ |/ / _ \/ __/  '_/ -_) __/
 *  /_/  /_/\_,_/_//_/\_,_/\__/_/_.__/_/  \___/\__/|__/|__/\___/_/ /_/\_\\__/_/
 *
 *        Version:  1.0
 *        Created:  07.11.2009 12:26:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  MANDELBROTWORKER_H
#define  MANDELBROTWORKER_H

#include <QImage>
#include <QThread>


class RenderThread;

template <typename NumberT>
class MandelbrotWorker
{
public:
	MandelbrotWorker(RenderThread *callback);
	QImage render(const QRect &rect, bool &stop);
	void setRegion(NumberT left, NumberT top, NumberT width, NumberT height);
	void setSize(const QSize &size);
private:
	enum { ColormapSize = 512 };
	enum { MaxIterations = 1024 };
	static uint m_colormap[];
	static bool m_colormapInitialized;

	NumberT m_left;
	NumberT m_top;
	NumberT m_width;
	NumberT m_height;
	QSize m_size;
	RenderThread *m_callback;
};

// Šablóna - je nutná implementácia
#include "MandelbrotWorker.cpp"

#endif   /* ----- #ifndef MANDELBROTWORKER_H  ----- */

