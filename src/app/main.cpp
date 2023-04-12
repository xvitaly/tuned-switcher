/**
 * SPDX-FileCopyrightText: 2021-2023 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/** @file app/main.cpp
 * This file contains the main entry point implementation
 * of the application.
*/

#include <QApplication>

#include "trayicon/trayicon.h"
#include "translationmanager/translationmanager.h"
#include "mainwindow/mainwindow.h"

/**
 * The main entry point.
 * @param argc Command-line arguments count.
 * @param argv Command-line arguments array.
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setDesktopFileName(AppConstants::LauncherName);

    TranslationManager *translator = new TranslationManager();
    a.installTranslator(translator -> GetQtTranslator());
    a.installTranslator(translator -> GetAppTranslator());

    if (QSystemTrayIcon::isSystemTrayAvailable() && !qEnvironmentVariableIsSet("TUNED_SWITCHER_FORCE_GUI"))
    {
        TrayIcon *trayIcon = new TrayIcon();
        trayIcon -> Show();
    }
    else
    {
        MainWindow *w = new MainWindow();
        w -> show();
    }

    return a.exec();
}
