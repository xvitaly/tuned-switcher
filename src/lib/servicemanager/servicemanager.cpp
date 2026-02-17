/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file servicemanager/servicemanager.cpp
 * Contains the ServiceManager class implementation.
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
#include "servicemanager/servicemanager.h"

ServiceManager::ServiceManager(QObject* parent) : QObject(parent)
{
}

QString ServiceManager::GetServiceState(const QString& BusPath) const
{
    QDBusInterface DBusInterface(SystemdBusName, BusPath, DBusPropertyInterface, DBusInstance);
    QDBusReply<QDBusVariant> DBusReply = DBusInterface.call(DBusPropertyMethodNameGet, SystemdBusInterfaceUnit, SystemdBusPropertyNameActiveState);
    if (!DBusReply.isValid())
        qCWarning(LogCategories::Service) << "Failed to get the Tuned service state due to an error:" << DBusReply.error();
    return DBusReply.value().variant().toString();
}

bool ServiceManager::IsRunning() const
{
    QDBusInterface DBusInterface(SystemdBusName, SystemdBusPath, SystemdBusInterfaceManager, DBusInstance);
    QDBusReply<QDBusObjectPath> DBusReply = DBusInterface.call(SystemdBusMethodNameGetUnit, SystemdTunedServiceName);
    if (!DBusReply.isValid())
        qCWarning(LogCategories::Service) << "Failed to get the Tuned service DBus path due to an error:" << DBusReply.error();
    return GetServiceState(DBusReply.value().path()) == SystemdBusValueServiceActive;
}

bool ServiceManager::Start() const
{
    QDBusMessage DBusMessage = QDBusMessage::createMethodCall(SystemdBusName, SystemdBusPath, SystemdBusInterfaceManager, SystemdBusMethodNameStart);
    DBusMessage.setInteractiveAuthorizationAllowed(true);
    DBusMessage.setArguments({SystemdTunedServiceName, SystemdTunedServiceMode});
    QDBusMessage DBusReply = DBusInstance.call(DBusMessage, QDBus::Block);
    bool DbusResult = !(DBusReply.type() == QDBusMessage::ErrorMessage);
    if (!DbusResult)
        qCWarning(LogCategories::Service) << "Failed to start the Tuned service due to an error:" << DBusReply.errorMessage();
    return DbusResult;
}

bool ServiceManager::Stop() const
{
    QDBusMessage DBusMessage = QDBusMessage::createMethodCall(SystemdBusName, SystemdBusPath, SystemdBusInterfaceManager, SystemdBusMethodNameStop);
    DBusMessage.setInteractiveAuthorizationAllowed(true);
    DBusMessage.setArguments({SystemdTunedServiceName, SystemdTunedServiceMode});
    QDBusMessage DBusReply = DBusInstance.call(DBusMessage, QDBus::Block);
    bool DbusResult = !(DBusReply.type() == QDBusMessage::ErrorMessage);
    if (!DbusResult)
        qCWarning(LogCategories::Service) << "Failed to stop the Tuned service due to an error:" << DBusReply.errorMessage();
    return DbusResult;
}
