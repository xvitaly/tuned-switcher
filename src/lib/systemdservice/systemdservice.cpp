/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file servicemanager/servicemanager.cpp
 * Contains the SystemdService class implementation.
*/

#include <QDBusError>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDBusReply>
#include <QDBusVariant>
#include <QList>
#include <QLoggingCategory>
#include <QObject>
#include <QVariant>

#include "logcategories/logcategories.h"
#include "systemdservice/systemdservice.h"

SystemdService::SystemdService(QObject* parent) : ServiceManager(parent)
{
}
