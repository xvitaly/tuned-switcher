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
#include <QVariant>

#include "settingsmanager/settingsmanager.h"

bool SettingsManager::GetGeometrySavingEnabled() const
{
    return settings -> value(GeometrySavingEnabledName, true).toBool();
}

void SettingsManager::SetGeometrySavingEnabled(const bool value)
{
    settings -> setValue(GeometrySavingEnabledName, value);
}

bool SettingsManager::GetStateSavingEnabled() const
{
    return settings -> value(StateSavingEnabledName, true).toBool();
}

void SettingsManager::SetStateSavingEnabled(const bool value)
{
    settings -> setValue(StateSavingEnabledName, value);
}

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

QByteArray SettingsManager::GetSettingsGeometry() const
{
    return settings -> value(SettingsGeometryName).toByteArray();
}

void SettingsManager::SetSettingsGeometry(const QByteArray& value)
{
    settings -> setValue(SettingsGeometryName, value);
}

QByteArray SettingsManager::GetAboutGeometry() const
{
    return settings -> value(AboutGeometryName).toByteArray();
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
