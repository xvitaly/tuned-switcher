/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef TUNEDMANAGER_H
#define TUNEDMANAGER_H

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusMetaType>
#include <QObject>

#include "tunedtypes/tunedtypes.h"

class TunedManager : public QObject
{
    Q_OBJECT
public:
    explicit TunedManager(QObject *parent = nullptr);
    QString GetActiveProfile();
    QStringList GetAvailableProfiles();
    QTunedProfileList GetAvailableProfiles2();
    QTunedProfileMode GetProfileMode();
    bool IsProfileModeAuto();
    QTunedResult SetProfileModeAuto();
    QTunedResult SetActiveProfile(const QString&);
    bool IsTunedRunning();
    bool StartTuned();
    bool StopTuned();
    void ListenEvents();
private:
    const QString TunedBusName = "com.redhat.tuned";
    const QString TunedBusPath = "/Tuned";
    const QString TunedBusInterface = "com.redhat.tuned.control";
    const QString TunedBusMethodNameActiveProfile = "active_profile";
    const QString TunedBusMethodNameProfiles = "profiles";
    const QString TunedBusMethodNameSwitchProfile = "switch_profile";
    const QString TunedBusMethodNameProfileMode = "profile_mode";
    const QString TunedBusMethodNameAutoProfile = "auto_profile";
    const QString TunedBusSignalNameProfileChanged = "profile_changed";
    const QString TunedBusMethodNameProfiles2 = "profiles2";
    const QString SystemdBusName = "org.freedesktop.systemd1";
    const QString SystemdBusPath = "/org/freedesktop/systemd1";
    const QString SystemdBusInterface = "org.freedesktop.systemd1.Manager";
    const QString SystemdBusMethodNameStart = "StartUnit";
    const QString SystemdBusMethodNameStop = "StopUnit";
    const QString SystemdTunedServiceName = "tuned.service";
    const QString SystemdTunedServiceMode = "replace";
    const QDBusConnection DBusInstance = QDBusConnection::systemBus();
private slots:
    void ProfileChangedEvent(const QString&, const bool, const QString&);
signals:
    void ProfileChangedSignal(const QString&, const bool, const QString&);
};

#endif // TUNEDMANAGER_H
