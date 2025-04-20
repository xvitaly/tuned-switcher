/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file main.cpp
 * Contains the main entry point implementation.
*/

#include <QApplication>
#include <QSystemTrayIcon>

#include "appconstants/appconstants.h"
#include "mainwindow/mainwindow.h"
#include "translationmanager/translationmanager.h"
#include "trayicon/trayicon.h"

/**
 * The main entry point.
 * @param argc Command-line arguments count.
 * @param argv Command-line arguments array.
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName(AppConstants::ProductNameInternal);
    QApplication::setApplicationVersion(AppConstants::ProductVersion);
    QApplication::setDesktopFileName(AppConstants::LauncherName);
    QApplication::setOrganizationName(AppConstants::ProductCompany);
    QApplication::setOrganizationDomain(AppConstants::DomainSchemeName);

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
