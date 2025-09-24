/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

/**
 * @file settingsmanager/settingsmanager.h
 * Contains the SettingsManager class definition.
*/

#include <QObject>

/**
 * Class for working with program settings.
*/
class SettingsManager : public QObject
{
    Q_OBJECT
public:
    /**
     * Main constructor of the SettingsManager class.
     * @param parent Parent.
    */
    explicit SettingsManager(QObject* parent = nullptr);
};

#endif // SETTINGSMANAGER_H
