/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file tunedmanager/tunedmanager.cpp
 * Contains the TunedManager class implementation.
*/

#include <QDBusConnection>
#include <QDBusError>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusMetaType>
#include <QDBusObjectPath>
#include <QDBusReply>
#include <QDBusVariant>
#include <QLoggingCategory>
#include <QMetaType>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "logcategories/logcategories.h"
#include "tunedmanager/tunedmanager.h"
#include "tunedtypes/tunedtypes.h"

QString TunedManager::GetActiveProfile() const
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<QString> DBusReply = DBusInterface.call(TunedBusMethodNameActiveProfile);
    if (!DBusReply.isValid())
        qCWarning(LogCategories::DBus) << "Failed to get the active Tuned profile due to an error:" << DBusReply.error();
    return DBusReply.value();
}

QStringList TunedManager::GetAvailableProfiles() const
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<QStringList> DBusReply = DBusInterface.call(TunedBusMethodNameProfiles);
    if (!DBusReply.isValid())
        qCWarning(LogCategories::DBus) << "Failed to get the available Tuned profiles due to an error:" << DBusReply.error();
    return DBusReply.value();
}

QTunedProfileMode TunedManager::GetProfileMode() const
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<QTunedProfileMode> DBusReply = DBusInterface.call(TunedBusMethodNameProfileMode);
    if (!DBusReply.isValid())
        qCWarning(LogCategories::DBus) << "Failed get current Tuned mode due to an error:" << DBusReply.error();
    return DBusReply.value();
}

bool TunedManager::IsProfileModeAuto() const
{
    const QTunedProfileMode ProfileMode = GetProfileMode();
    return ProfileMode.Mode == TunedBusValueAutoProfile;
}

QTunedResult TunedManager::SetProfileModeAuto() const
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<QTunedResult> DBusReply = DBusInterface.call(TunedBusMethodNameAutoProfile);
    return DBusReply.isValid() ? DBusReply.value() : QTunedResult(false, DBusReply.error().message());
}

QTunedResult TunedManager::SetActiveProfile(const QString& Profile) const
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<QTunedResult> DBusReply = DBusInterface.call(TunedBusMethodNameSwitchProfile, Profile);
    return DBusReply.isValid() ? DBusReply.value() : QTunedResult(false, DBusReply.error().message());
}

QTunedProfileList TunedManager::GetAvailableProfiles2() const
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<QTunedProfileList> DBusReply = DBusInterface.call(TunedBusMethodNameProfiles2);
    if (!DBusReply.isValid())
        qCWarning(LogCategories::DBus) << "Failed to get the available Tuned profiles with their descriptions due to an error:" << DBusReply.error();
    return DBusReply.value();
}

bool TunedManager::IsOperational() const
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<bool> DBusReply = DBusInterface.call(TunedBusMethodNameIsRunning);
    if (!DBusReply.isValid())
        qCWarning(LogCategories::DBus) << "Failed to determine if the Tuned service is running due to an error:" << DBusReply.error();
    return DBusReply.value();
}

QString TunedManager::GetServiceState(const QString& BusPath) const
{
    QDBusInterface DBusInterface(SystemdBusName, BusPath, DBusPropertyInterface, DBusInstance);
    QDBusReply<QDBusVariant> DBusReply = DBusInterface.call(DBusPropertyMethodNameGet, SystemdBusInterfaceUnit, SystemdBusPropertyNameActiveState);
    if (!DBusReply.isValid())
        qCWarning(LogCategories::DBus) << "Failed to get the Tuned service state due to an error:" << DBusReply.error();
    return DBusReply.value().variant().toString();
}

bool TunedManager::IsRunning() const
{
    QDBusInterface DBusInterface(SystemdBusName, SystemdBusPath, SystemdBusInterfaceManager, DBusInstance);
    QDBusReply<QDBusObjectPath> DBusReply = DBusInterface.call(SystemdBusMethodNameGetUnit, SystemdTunedServiceName);
    if (!DBusReply.isValid())
        qCWarning(LogCategories::DBus) << "Failed to get the Tuned service DBus path due to an error:" << DBusReply.error();
    return GetServiceState(DBusReply.value().path()) == SystemdBusValueServiceActive;
}

bool TunedManager::Start() const
{
    QDBusMessage DBusMessage = QDBusMessage::createMethodCall(SystemdBusName, SystemdBusPath, SystemdBusInterfaceManager, SystemdBusMethodNameStart);
    DBusMessage.setInteractiveAuthorizationAllowed(true);
    DBusMessage.setArguments({SystemdTunedServiceName, SystemdTunedServiceMode});
    QDBusMessage DBusReply = DBusInstance.call(DBusMessage, QDBus::Block);
    bool DbusResult = !(DBusReply.type() == QDBusMessage::ErrorMessage);
    if (!DbusResult)
        qCWarning(LogCategories::DBus) << "Failed to start the Tuned service due to an error:" << DBusReply.errorMessage();
    return DbusResult;
}

bool TunedManager::Stop() const
{
    QDBusMessage DBusMessage = QDBusMessage::createMethodCall(SystemdBusName, SystemdBusPath, SystemdBusInterfaceManager, SystemdBusMethodNameStop);
    DBusMessage.setInteractiveAuthorizationAllowed(true);
    DBusMessage.setArguments({SystemdTunedServiceName, SystemdTunedServiceMode});
    QDBusMessage DBusReply = DBusInstance.call(DBusMessage, QDBus::Block);
    bool DbusResult = !(DBusReply.type() == QDBusMessage::ErrorMessage);
    if (!DbusResult)
        qCWarning(LogCategories::DBus) << "Failed to stop the Tuned service due to an error:" << DBusReply.errorMessage();
    return DbusResult;
}

bool TunedManager::Enable() const
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<bool> DBusReply = DBusInterface.call(TunedBusMethodNameStart);
    if (!DBusReply.isValid())
        qCWarning(LogCategories::DBus) << "Failed to enable the Tuned service due to an error:" << DBusReply.error();
    return DBusReply.value();
}

bool TunedManager::Disable() const
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<bool> DBusReply = DBusInterface.call(TunedBusMethodNameStop);
    if (!DBusReply.isValid())
        qCWarning(LogCategories::DBus) << "Failed to disable the Tuned service due to an error:" << DBusReply.error();
    return DBusReply.value();
}

bool TunedManager::Reload() const
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<bool> DBusReply = DBusInterface.call(TunedBusMethodNameReload);
    if (!DBusReply.isValid())
        qCWarning(LogCategories::DBus) << "Failed to reload the Tuned service configuration due to an error:" << DBusReply.error();
    return DBusReply.value();
}

bool TunedManager::Shutdown() const
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<bool> DBusReply = DBusInterface.call(TunedBusMethodNameDisable);
    if (!DBusReply.isValid())
        qCWarning(LogCategories::DBus) << "Failed to shut down the Tuned service and disable configurations due to an error:" << DBusReply.error();
    return DBusReply.value();
}

bool TunedManager::RunServiceMethod(const ServiceMethod method) const
{
    switch (method)
    {
        case ServiceMethod::MethodEnable:
            return Enable();
        case ServiceMethod::MethodDisable:
            return Disable();
        case ServiceMethod::MethodReload:
            return Reload();
        case ServiceMethod::MethodShutdown:
            return Shutdown();
        default:
            return false;
    }
}

void TunedManager::ProfileChangedEvent(const QString& NewProfile, const bool SwitchResult, const QString& ResultMessage)
{
    emit ProfileChangedSignal(NewProfile, SwitchResult, ResultMessage);
}

TunedManager::TunedManager(QObject* parent) : QObject(parent)
{
    if (DBusInstance.isConnected())
    {
        qRegisterMetaType<QTunedProfile>();
        qDBusRegisterMetaType<QTunedProfile>();
        qRegisterMetaType<QTunedProfileList>();
        qDBusRegisterMetaType<QTunedProfileList>();
        qRegisterMetaType<QTunedProfileMode>();
        qDBusRegisterMetaType<QTunedProfileMode>();
        qRegisterMetaType<QTunedResult>();
        qDBusRegisterMetaType<QTunedResult>();
        DBusInstance.connect(TunedBusName, TunedBusPath, TunedBusInterface, TunedBusSignalNameProfileChanged, this, SLOT(ProfileChangedEvent(const QString&, const bool, const QString&)));
    }
}
