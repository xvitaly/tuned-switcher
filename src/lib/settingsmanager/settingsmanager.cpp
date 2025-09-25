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
#include <QStringLiteral>

#include "settingsmanager/settingsmanager.h"

QByteArray SettingsManager::GetGeometry() const
{
    return settings -> value(QStringLiteral("widget/geometry")).toByteArray();
}

void SettingsManager::SetGeometry(const QByteArray value)
{
    settings -> setValue(QStringLiteral("widget/geometry"), value);
}

QByteArray SettingsManager::GetWindowState() const
{
    return settings -> value(QStringLiteral("widget/windowState")).toByteArray();
}

void SettingsManager::SetWindowState(const QByteArray value)
{
    settings -> setValue(QStringLiteral("widget/windowState"), value);
}

bool SettingsManager::GetSoundEnabled() const
{
    return settings -> value(QStringLiteral("widget/soundEnabled"), true).toBool();
}

void SettingsManager::SetSoundEnabled(const bool value)
{
    settings -> setValue(QStringLiteral("widget/soundEnabled"), value);
}

void SettingsManager::Save()
{
    settings -> sync();
}

SettingsManager::SettingsManager(QObject* parent) : QObject(parent)
{
    settings = new QSettings(this);
}
