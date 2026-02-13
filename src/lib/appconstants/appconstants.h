/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef APPSTRINGS_H
#define APPSTRINGS_H

/**
 * @file appconstants/appconstants.h
 * Contains the AppConstants namespace definition.
*/

#include <QString>

/**
 * Namespace for working with various constants used in project.
*/
namespace AppConstants {
    /**
     * Returns the application company public name.
     * Used as a public name in various dialogs.
     * @returns Application company public name.
    */
    QString ProductCompany();

    /**
     * Returns the application company internal name.
     * Used as a settings directory name.
     * @returns Application company internal name.
    */
    QString ProductCompanyInternal();

    /**
     * Returns the application copyright.
     * Used in various dialogs and messages.
     * @returns Application copyright.
    */
    QString ProductCopyright();

    /**
     * Returns the application description.
     * Used in various dialogs and messages.
     * @returns Application description.
    */
    QString ProductDescription();

    /**
     * Returns the application homepage URL.
     * Used in various dialogs and menu items.
     * @returns Application homepage URL.
    */
    QString ProductHomepage();

    /**
     * Returns the application public name.
     * Used as a public name in various dialogs.
     * @returns Application public name.
    */
    QString ProductName();

    /**
     * Returns the application internal name.
     * Used as a settings project name.
     * @returns Application internal name.
    */
    QString ProductNameInternal();

    /**
     * Returns the application version number as a string.
     * @returns Application version number.
    */
    QString ProductVersion();

    /**
     * Returns the application launcher file name without
     * the .desktop extension.
     * @returns Application launcher file name.
    */
    QString LauncherName();

    /**
     * Returns the application reverse domain scheme name.
     * @returns Application reverse domain scheme name.
    */
    QString DomainSchemeName();

    /**
     * Returns the data root directory installation prefix.
     * @returns Data root directory installation prefix.
    */
    QString DataRootPrefix();

    /**
     * Returns the default application sleep time before trying
     * to fetch the available performance profiles.
     * @returns Default application sleep time.
    */
    int SleepTime();

    /**
     * Returns the default timer delay in milliseconds before attempting
     * to shut down the application.
     * @returns Default timer delay.
    */
    int TimerDelay();

    /**
     * Returns the logging category name for DBus related messages.
     * @returns Logging category name for DBus related messages.
    */
    const char* CategoryNameDbus();

    /**
     * Returns the logging category name for autorun related messages.
     * @returns Logging category name for autorun related messages.
    */
    const char* CategoryNameAutorun();

    /**
     * Returns the environment variable name used to start the application
     * in GUI mode.
     * @returns Environment variable name for GUI mode.
    */
    const char* EnvNameGUI();
}

#endif // APPSTRINGS_H
