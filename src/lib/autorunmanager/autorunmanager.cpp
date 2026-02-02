/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file autorunmanager/autorunmanager.cpp
 * Contains the AutorunManager class implementation.
*/

#include <QFile>
#include <QString>
#include <QStringLiteral>

#include "autorunfile/autorunfile.h"
#include "autorunmanager/autorunmanager.h"
#include "autorunportal/autorunportal.h"

AutorunManager* AutorunManager::Create(QObject* parent)
{
    if (!CheckSandbox())
        return new AutorunFile(parent);
    else
        return new AutorunPortal(parent);
}

AutorunManager::AutorunManager(QObject* parent) : QObject(parent)
{
}

bool AutorunManager::CheckSandbox()
{
    return QFile::exists(QStringLiteral("/.flatpak-info"));
}
