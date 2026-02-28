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

#ifdef WITH_SYSTEMD
#include "systemdservice/systemdservice.h"
#else
#include "dummyservice/dummyservice.h"
#endif

ServiceManager* ServiceManager::Create(QObject* parent)
{
#ifdef WITH_SYSTEMD
    return new SystemdService(parent);
#else
    return new DummyService(parent);
#endif
}

ServiceManager::ServiceManager(QObject* parent) : QObject(parent)
{
}
