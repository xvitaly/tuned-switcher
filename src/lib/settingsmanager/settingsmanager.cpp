/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file settingsmanager/settingsmanager.cpp
 * Contains the SettingsManager class implementation.
*/

#include <QByteArray>
#include <QGuiApplication>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QStringLiteral>
#include <QVariant>

#include "autorunmanager/autorunmanager.h"
#include "settingsmanager/settingsmanager.h"

bool SettingsManager::IsGeometrySavingSupported() const
{
    return !IsWayland;
}

bool SettingsManager::GetGeometrySavingEnabled() const
{
    return IsGeometrySavingSupported() && Settings -> value(GeometrySavingEnabledName, true).toBool();
}

void SettingsManager::SetGeometrySavingEnabled(const bool value)
{
    if (value != GetGeometrySavingEnabled())
        Settings -> setValue(GeometrySavingEnabledName, value);
}

QByteArray SettingsManager::GetWidgetGeometry() const
{
    return Settings -> value(WidgetGeometryName).toByteArray();
}

void SettingsManager::SetWidgetGeometry(const QByteArray& value)
{
    Settings -> setValue(WidgetGeometryName, value);
}

QByteArray SettingsManager::GetSettingsGeometry() const
{
    return Settings -> value(SettingsGeometryName).toByteArray();
}

void SettingsManager::SetSettingsGeometry(const QByteArray& value)
{
    Settings -> setValue(SettingsGeometryName, value);
}

QByteArray SettingsManager::GetAboutGeometry() const
{
    return Settings -> value(AboutGeometryName).toByteArray();
}

void SettingsManager::SetAboutGeometry(const QByteArray& value)
{
    Settings -> setValue(AboutGeometryName, value);
}

bool SettingsManager::GetSoundEnabled() const
{
    return Settings -> value(SoundEnabledName, true).toBool();
}

void SettingsManager::SetSoundEnabled(const bool value)
{
    if (value != GetSoundEnabled())
        Settings -> setValue(SoundEnabledName, value);
}

bool SettingsManager::IsAutorunSupported() const
{
    return autorun -> IsSupported();
}

bool SettingsManager::GetAutorunEnabled() const
{
    return autorun -> IsEnabled() || Settings -> value(AutorunEnabledName, false).toBool();
}

void SettingsManager::SetAutorunEnabled(const bool value) const
{
    if (value == GetAutorunEnabled())
        return;
    if (value ? autorun -> Enable() : autorun -> Disable())
        Settings -> setValue(AutorunEnabledName, value);
}

void SettingsManager::Reset() const
{
    Settings -> clear();
}

void SettingsManager::ResetGeometry() const
{
    Settings -> remove(AboutGeometryName);
    Settings -> remove(SettingsGeometryName);
    Settings -> remove(WidgetGeometryName);
}

SettingsManager::SettingsManager(QObject* parent) : QObject(parent)
{
    Settings = new QSettings(this);
    autorun = AutorunManager::Create(this);
    IsWayland = QGuiApplication::platformName() == QStringLiteral("wayland");
}
