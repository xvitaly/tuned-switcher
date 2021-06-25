/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef APPSTRINGS_H
#define APPSTRINGS_H

/** @file appconstants/appconstants.h
 * This file contains AppConstants namespace.
*/

#include <QString>

/**
 * Namespace for working with various constants used in project.
*/
namespace AppConstants {
    /**
     * Stores application company name.
     * Used as settings directory name.
    */
    const QString ProductCompany = QStringLiteral("EasyCoding");

    /**
     * Stores application public name.
     * Used as public name in different dialogs.
    */
    const QString ProductName = QStringLiteral("Tuned Switcher");

    /**
     * Stores application internal name (for the settings project name).
     * Used as settings project name.
    */
    const QString ProductNameInternal = QStringLiteral(QT_STRINGIFY(TS_PROJECT_NAME));

    /**
     * Stores application launcher (.desktop) file name.
    */
    const QString LauncherName = QStringLiteral(QT_STRINGIFY(TS_LAUNCHER_NAME));

    /**
     * Stores application reverse domain scheme name.
    */
    const QString DomainSchemeName = QStringLiteral(QT_STRINGIFY(TS_SCHEME_NAME));

    /**
     * Stores data root directory installation prefix.
    */
    const QString DataRootPrefix = QStringLiteral(QT_STRINGIFY(TS_DATAROOT_PREFIX)"/");

    /**
     * Stores default application sleep time before trying to
     * fetch available Tuned profiles.
    */
    const int SleepTime = 2;
}

#endif // APPSTRINGS_H
