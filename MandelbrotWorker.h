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

#include "UltraMath.h"

class MandelbrotWorker
{
public:
	MandelbrotWorker();
	QImage render(bignum left, bignum top, bignum width, bignum height, const QRect &rect, const QSize &size);
private:
	enum { ColormapSize = 512 };
	uint m_colormap[ColormapSize];
};

#endif   /* ----- #ifndef MANDELBROTWORKER_H  ----- */

