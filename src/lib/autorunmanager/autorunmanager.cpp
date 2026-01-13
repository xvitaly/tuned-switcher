/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file autorunmanager/autorunmanager.cpp
 * Contains the AutorunManager class implementation.
*/

#include <QDir>
#include <QFile>
#include <QString>
#include <QStringLiteral>
#include <QTextStream>

#include "appconstants/appconstants.h"
#include "autorunmanager/autorunmanager.h"

AutorunManager::AutorunManager(QObject* parent) : QObject(parent)
{
    AutorunDirectoryName = GetAutorunDirectoryName();
    AutorunFileName = GetAutorunFileName();
    AutorunSupported = !CheckSandbox();
}

QString AutorunManager::GetAutorunDirectoryName() const
{
    return AutorunDirectoryPath.arg(QDir::homePath());
}

QString AutorunManager::GetAutorunFileName() const
{
    return AutorunFilePath.arg(QDir::homePath(), AppConstants::LauncherName);
}

void AutorunManager::CreateAutorunDirectory() const
{
    const QDir directory(AutorunDirectoryName);
    if (!directory.exists())
        directory.mkpath(QStringLiteral("."));
}

QString AutorunManager::GenerateAutorunFile() const
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

void AutorunManager::WriteAutorunFile(const QString& value) const
{
    QFile autorun(AutorunFileName);
    if (value.isEmpty() || !autorun.open(QFile::WriteOnly | QFile::Text))
        return;
    QTextStream af(&autorun);
    af << value;
}

bool AutorunManager::CheckSandbox() const
{
    return QFile::exists(QStringLiteral("/.flatpak-info"));
}

bool AutorunManager::IsEnabled()
{
    return QFile::exists(AutorunFileName);
}

bool AutorunManager::IsSupported()
{
    return AutorunSupported;
}

void AutorunManager::Enable()
{
    if (!IsEnabled())
        WriteAutorunFile(GenerateAutorunFile());
}

void AutorunManager::Disable()
{
    if (IsEnabled())
        QFile::remove(AutorunFileName);
}
