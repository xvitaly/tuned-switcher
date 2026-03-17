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

#include "debugsettings/debugsettings.h"
#include "dummyservice/dummyservice.h"
#include "servicemanager/servicemanager.h"
#include "systemdservice/systemdservice.h"

ServiceManager* ServiceManager::Create(QObject* parent)
{
    if (!DebugSettings::IsSystemdIntegrationDisabled())
        return new SystemdService(parent);
    else
        return new DummyService(parent);
}

ServiceManager::ServiceManager(QObject* parent) : QObject(parent)
{
}
