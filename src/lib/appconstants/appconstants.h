/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef APPSTRINGS_H
#define APPSTRINGS_H

/** @file appconstants/appconstants.h
 * This file contains AppConstants class structure.
*/

#include <QObject>

/**
 * Class for working with various constants used in project.
*/
class AppConstants : public QObject
{
    Q_OBJECT
public:
    /**
     * Stores application company name.
     * Used as settings directory name.
    */
    static const QString ProductCompany;

    /**
     * Stores application public name.
     * Used as public name in different dialogs.
    */
    static const QString ProductName;

    /**
     * Stores application internal name (for the settings project name).
     * Used as settings project name.
    */
    static const QString ProductNameInternal;

    /**
     * Stores application launcher (.desktop) file name.
    */
    static const QString LauncherName;

    /**
     * Stores application reverse domain scheme name.
    */
    static const QString DomainSchemeName;

    /**
     * Stores data root directory installation prefix.
    */
    static const QString DataRootPrefix;

    /**
     * Stores default application sleep time before trying to
     * fetch available Tuned profiles.
    */
    static const int SleepTime = 2;
};

#endif // APPSTRINGS_H
