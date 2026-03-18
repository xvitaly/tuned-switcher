/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
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
#include "debugsettings/debugsettings.h"
#include "mainwindow/mainwindow.h"
#include "translationmanager/translationmanager.h"
#include "trayicon/trayicon.h"

/**
 * The main entry point.
 * @param argc Command-line arguments count.
 * @param argv Command-line arguments array.
*/
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName(AppConstants::ProductNameInternal());
    QApplication::setApplicationVersion(AppConstants::ProductVersionInternal());
    QApplication::setDesktopFileName(AppConstants::LauncherName());
    QApplication::setOrganizationName(AppConstants::ProductCompanyInternal());
    QApplication::setOrganizationDomain(AppConstants::DomainSchemeName());

    TranslationManager translator;
    if (translator.IsQtTranslatorAvailable())
        app.installTranslator(translator.GetQtTranslator());
    if (translator.IsAppTranslatorAvailable())
        app.installTranslator(translator.GetAppTranslator());

    if (QSystemTrayIcon::isSystemTrayAvailable() && !DebugSettings::IsWidgetRequired())
    {
        TrayIcon trayIcon;
        trayIcon.Show();
        return app.exec();
    }
    else
    {
        MainWindow mainWindow;
        mainWindow.show();
        return app.exec();
    }
}
