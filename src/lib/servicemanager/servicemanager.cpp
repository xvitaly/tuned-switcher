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
#include "systemdservice/systemdservice.h"

ServiceManager* ServiceManager::Create(QObject* parent)
{
    return new SystemdService(parent);
}

ServiceManager::ServiceManager(QObject* parent) : QObject(parent)
{
}
