/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file autorunfile/autorunfile.cpp
 * Contains the AutorunFile class implementation.
*/

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QStandardPaths>
#include <QString>
#include <QStringLiteral>
#include <QTextStream>

#include "appconstants/appconstants.h"
#include "autorunfile/autorunfile.h"

AutorunFile::AutorunFile(QObject* parent) : AutorunManager(parent)
{
    AutorunDirectoryName = GetAutorunDirectoryName();
    AutorunFileName = GetAutorunFileName();
}

QString AutorunFile::GetAutorunDirectoryName() const
{
    return QStringLiteral("%1/autostart").arg(
        QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation));
}

QString AutorunFile::GetAutorunFileName() const
{
    return QStringLiteral("%1/autostart/%2.desktop").arg(
        QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation),
        AppConstants::LauncherName());
}

QString AutorunFile::GetExecutablePath() const
{
    return !QStandardPaths::findExecutable(AppConstants::ProductNameInternal()).isEmpty() ? AppConstants::ProductNameInternal() : QCoreApplication::applicationFilePath();
}

void AutorunFile::CreateAutorunDirectory() const
{
    const QDir directory(AutorunDirectoryName);
    if (!directory.exists())
        directory.mkpath(QStringLiteral("."));
}

QString AutorunFile::GenerateAutorunFile() const
{
    QFile autorun(QStringLiteral(":/assets/autorun.desktop"));
    if (!autorun.open(QFile::ReadOnly | QFile::Text))
        return QString();
    QTextStream af(&autorun);
    return af.readAll().arg(AppConstants::ProductName(),
                            AppConstants::ProductDescription(),
                            AppConstants::DomainSchemeName(),
                            GetExecutablePath());
}

void AutorunFile::WriteAutorunFile(const QString& value) const
{
    QFile autorun(AutorunFileName);
    if (!value.isEmpty() && autorun.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream af(&autorun);
        af << value;
    }
}

bool AutorunFile::IsEnabled() const
{
    return QFile::exists(AutorunFileName);
}

bool AutorunFile::IsSupported() const
{
    return true;
}

bool AutorunFile::Enable() const
{
    if (!IsEnabled())
    {
        CreateAutorunDirectory();
        WriteAutorunFile(GenerateAutorunFile());
        return IsEnabled();
    }
    return false;
}

bool AutorunFile::Disable() const
{
    if (IsEnabled())
    {
        QFile::remove(AutorunFileName);
        return !IsEnabled();
    }
    return false;
}
