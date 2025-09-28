/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file settingsmanager/settingsmanager.cpp
 * Contains the SettingsManager class implementation.
*/

#include <QByteArray>
#include <QObject>
#include <QSettings>

#include "settingsmanager/settingsmanager.h"

QByteArray SettingsManager::GetWidgetGeometry() const
{
    return settings -> value(WidgetGeometryName).toByteArray();
}

void SettingsManager::SetWidgetGeometry(const QByteArray& value)
{
    settings -> setValue(WidgetGeometryName, value);
}

QByteArray SettingsManager::GetWidgetState() const
{
    return settings -> value(WidgetStateName).toByteArray();
}

void SettingsManager::SetWidgetState(const QByteArray& value)
{
    settings -> setValue(WidgetStateName, value);
}

bool SettingsManager::GetSoundEnabled() const
{
    return settings -> value(SoundEnabledName, true).toBool();
}

void SettingsManager::SetSoundEnabled(const bool value)
{
    settings -> setValue(SoundEnabledName, value);
}

void SettingsManager::Save()
{
    settings -> sync();
}

SettingsManager::SettingsManager(QObject* parent) : QObject(parent)
{
    settings = new QSettings(this);
}
