/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file servicemanager/servicemanager.cpp
 * Contains the ServiceManager class implementation.
*/

#include <QObject>

#include "servicemanager/servicemanager.h"

ServiceManager::ServiceManager(QObject* parent) : QObject(parent)
{
}

bool ServiceManager::IsRunning() const
{
    return false;
}

bool ServiceManager::Start() const
{
    return false;
}

bool ServiceManager::Stop() const
{
    return false;
}
