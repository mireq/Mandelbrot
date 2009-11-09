/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.h
 *     __  ___     _    _      ___         __
 *    /  |/  /__ _(_)__| | /| / (_)__  ___/ /__ _    __
 *   / /|_/ / _ `/ / _ \ |/ |/ / / _ \/ _  / _ \ |/|/ /
 *  /_/  /_/\_,_/_/_//_/__/|__/_/_//_/\_,_/\___/__,__/
 *
 *        Version:  1.0
 *        Created:  09.11.2009 14:02:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  MAINWINDOW_H
#define  MAINWINDOW_H

#include <QMainWindow>

class MandelbrotWidget;
class SettingsWidget;

class MainWindow: public QMainWindow
{
Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
private:
	MandelbrotWidget *m_mandelbrot;
	SettingsWidget *m_settings;
};

#endif   /* ----- #ifndef MAINWINDOW_H  ----- */

