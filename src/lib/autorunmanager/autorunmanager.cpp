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

AutorunManager* AutorunManager::Create(QObject* parent)
{
    return new AutorunFile(parent);
}

AutorunManager::AutorunManager(QObject* parent) : QObject(parent)
{}

AutorunManager::~AutorunManager()
{}

bool AutorunManager::CheckSandbox()
{
    return QFile::exists(QStringLiteral("/.flatpak-info"));
}

bool AutorunManager::IsSupported() const
{
    return false;
}
