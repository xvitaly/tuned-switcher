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
#include <QDir>
#include <QFile>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QStringLiteral>
#include <QTextStream>
#include <QVariant>

#include "appconstants/appconstants.h"
#include "settingsmanager/settingsmanager.h"

bool SettingsManager::GetGeometrySavingEnabled() const
{
    return settings -> value(GeometrySavingEnabledName, true).toBool();
}

void SettingsManager::SetGeometrySavingEnabled(const bool value)
{
    settings -> setValue(GeometrySavingEnabledName, value);
}

QByteArray SettingsManager::GetWidgetGeometry() const
{
    return settings -> value(WidgetGeometryName).toByteArray();
}

void SettingsManager::SetWidgetGeometry(const QByteArray& value)
{
    settings -> setValue(WidgetGeometryName, value);
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

void SettingsManager::SetAboutGeometry(const QByteArray& value)
{
    settings -> setValue(AboutGeometryName, value);
}

bool SettingsManager::GetSoundEnabled() const
{
    return settings -> value(SoundEnabledName, true).toBool();
}

void SettingsManager::SetSoundEnabled(const bool value)
{
    settings -> setValue(SoundEnabledName, value);
}

QString SettingsManager::GetAutorunFileName() const
{
    return AutorunFilePath.arg(QDir::homePath(), AppConstants::LauncherName);
}

bool SettingsManager::GetAutorunEnabled() const
{
    return QFile::exists(GetAutorunFileName());
}

QString SettingsManager::GenerateAutorunFile() const
{
    QFile autorun(QStringLiteral(":/assets/autorun.desktop"));
    if (!autorun.open(QFile::ReadOnly | QFile::Text))
        return QString();
    QTextStream af(&autorun);
    return af.readAll().arg(AppConstants::ProductName,
                            AppConstants::ProductDescription,
                            AppConstants::DomainSchemeName,
                            AppConstants::ProductNameInternal);
}

SettingsManager::SettingsManager(QObject* parent) : QObject(parent)
{
    settings = new QSettings(this);
}
