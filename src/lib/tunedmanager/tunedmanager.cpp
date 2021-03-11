/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "tunedmanager.h"

QString TunedManager::GetActiveProfile()
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<QString> DBusReply = DBusInterface.call(TunedBusMethodNameActiveProfile);
    return DBusReply.value();
}

QStringList TunedManager::GetAvailableProfiles()
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<QStringList> DBusReply = DBusInterface.call(TunedBusMethodNameProfiles);
    return DBusReply.value();
}

QTunedProfileMode TunedManager::GetProfileMode()
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<QTunedProfileMode> DBusReply = DBusInterface.call(TunedBusMethodNameProfileMode);
    return DBusReply.value();
}

bool TunedManager::IsProfileModeAuto()
{
    const QTunedProfileMode ProfileMode = GetProfileMode();
    return ProfileMode.Mode == "auto";
}

QTunedResult TunedManager::SetProfileModeAuto()
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<QTunedResult> DBusReply = DBusInterface.call(TunedBusMethodNameAutoProfile);
    return DBusReply.isValid() ? DBusReply.value() : QTunedResult(false, DBusReply.error().message());
}

QTunedResult TunedManager::SetActiveProfile(const QString& Profile)
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<QTunedResult> DBusReply = DBusInterface.call(TunedBusMethodNameSwitchProfile, Profile);
    return DBusReply.isValid() ? DBusReply.value() : QTunedResult(false, DBusReply.error().message());
}

QTunedProfileList TunedManager::GetAvailableProfiles2()
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    QDBusReply<QTunedProfileList> DBusReply = DBusInterface.call(TunedBusMethodNameProfiles2);
    return DBusReply.value();
}

bool TunedManager::IsTunedRunning()
{
    QDBusInterface DBusInterface(TunedBusName, TunedBusPath, TunedBusInterface, DBusInstance);
    return DBusInterface.isValid();
}

bool TunedManager::StartTuned()
{
    QDBusInterface DBusInterface(SystemdBusName, SystemdBusPath, SystemdBusInterface, DBusInstance);
    QDBusReply<void> DBusReply = DBusInterface.call(SystemdBusMethodNameStart, SystemdTunedServiceName, SystemdTunedServiceMode);
    return DBusReply.isValid();
}

bool TunedManager::StopTuned()
{
    QDBusInterface DBusInterface(SystemdBusName, SystemdBusPath, SystemdBusInterface, DBusInstance);
    QDBusReply<void> DBusReply = DBusInterface.call(SystemdBusMethodNameStop, SystemdTunedServiceName, SystemdTunedServiceMode);
    return DBusReply.isValid();
}

void TunedManager::ProfileChangedEvent(const QString& NewProfile, const bool SwitchResult, const QString& ResultMessage)
{
    emit ProfileChangedSignal(NewProfile, SwitchResult, ResultMessage);
}

TunedManager::TunedManager(QObject *parent) : QObject(parent)
{
    if (DBusInstance.isConnected())
    {
        qRegisterMetaType<QTunedProfile>("QTunedProfile");
        qDBusRegisterMetaType<QTunedProfile>();
        qRegisterMetaType<QTunedProfileList>("QTunedProfileList");
        qDBusRegisterMetaType<QTunedProfileList>();
        qRegisterMetaType<QTunedProfileMode>("QTunedProfileMode");
        qDBusRegisterMetaType<QTunedProfileMode>();
        qRegisterMetaType<QTunedResult>("QTunedResult");
        qDBusRegisterMetaType<QTunedResult>();
        QDBusConnection::systemBus().connect(TunedBusName, TunedBusPath, TunedBusInterface, TunedBusSignalNameProfileChanged, this, SLOT(ProfileChangedEvent(const QString&, const bool, const QString&)));
    }
}
