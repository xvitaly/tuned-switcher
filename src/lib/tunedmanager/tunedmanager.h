/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef TUNEDMANAGER_H
#define TUNEDMANAGER_H

/** @file lib/tunedmanager/tunedmanager.h
 * This file contains TunedManager class structure.
*/

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusMetaType>
#include <QObject>

#include "tunedtypes/tunedtypes.h"

/**
 * Class for working with the Tuned service.
*/
class TunedManager : public QObject
{
    Q_OBJECT
public:
    /**
     * Main constructor of the TunedManager class.
     * @param parent Parent.
    */
    explicit TunedManager(QObject *parent = nullptr);

    /**
     * Get active Tuned profile.
     * @returns Active Tuned profile.
    */
    QString GetActiveProfile();

    /**
     * Get the list of available Tuned profiles.
     * @returns Available Tuned profiles.
    */
    QStringList GetAvailableProfiles();

    /**
     * Get the list of available Tuned profiles with additional
     * useful information like profile descriptions.
     * @returns Available Tuned profiles.
    */
    QTunedProfileList GetAvailableProfiles2();

    /**
     * Get current Tuned mode: manual or auto.
     * @returns Current Tuned mode.
    */
    QTunedProfileMode GetProfileMode();

    /**
     * Check if the Tuned is working in automatic mode.
     * @returns Automatic mode on/off.
     * @retval true Tuned is working in automatic mode.
     * @retval false Tuned is working in manual mode.
    */
    bool IsProfileModeAuto();

    /**
     * Switch Tuned to automatic mode.
     * @returns Result of current operation.
    */
    QTunedResult SetProfileModeAuto();

    /**
     * Switch Tuned to the the specified profile.
     * @param Profile New Tuned profile name.
     * @returns Result of current operation.
    */
    QTunedResult SetActiveProfile(const QString&);

    /**
     * Check if the Tuned service is running.
     * @returns If the Tuned sevice is running.
     * @retval true Tuned is running.
     * @retval false Tuned is not running.
    */
    bool IsTunedRunning();

    /**
     * Start the Tuned service.
     * @returns Result of current operation.
     * @retval true Tuned was successfully started.
     * @retval false An error occured when trying to start Tuned.
    */
    bool StartTuned();

    /**
     * Stop the Tuned service.
     * @returns Result of current operation.
     * @retval true Tuned was successfully stopped.
     * @retval false An error occured when trying to stop Tuned.
    */
    bool StopTuned();
private:
    /**
     * Stores the Tuned DBus interface name.
    */
    const QString TunedBusName = "com.redhat.tuned";

    /**
     * Stores the Tuned DBus object path.
    */
    const QString TunedBusPath = "/Tuned";

    /**
     * Stores the Tuned DBus interface.
    */
    const QString TunedBusInterface = "com.redhat.tuned.control";

    /**
     * Stores the Tuned DBus ActiveProfile method name.
    */
    const QString TunedBusMethodNameActiveProfile = "active_profile";

    /**
     * Stores the Tuned DBus AvailableProfiles method name.
    */
    const QString TunedBusMethodNameProfiles = "profiles";

    /**
     * Stores the Tuned DBus SwitchProfile method name.
    */
    const QString TunedBusMethodNameSwitchProfile = "switch_profile";

    /**
     * Stores the Tuned DBus SetProfileMode method name.
    */
    const QString TunedBusMethodNameProfileMode = "profile_mode";

    /**
     * Stores the Tuned DBus AutoProfile method name.
    */
    const QString TunedBusMethodNameAutoProfile = "auto_profile";

    /**
     * Stores the Tuned DBus ProfileChanged signal name.
    */
    const QString TunedBusSignalNameProfileChanged = "profile_changed";

    /**
     * Stores the Tuned DBus AvailableProfiles2 method name.
    */
    const QString TunedBusMethodNameProfiles2 = "profiles2";

    /**
     * Stores the Systemd DBus interface name.
    */
    const QString SystemdBusName = "org.freedesktop.systemd1";

    /**
     * Stores the Systemd DBus object path.
    */
    const QString SystemdBusPath = "/org/freedesktop/systemd1";

    /**
     * Stores the Systemd DBus interface.
    */
    const QString SystemdBusInterface = "org.freedesktop.systemd1.Manager";

    /**
     * Stores the Systemd DBus MethodNameStart method name.
    */
    const QString SystemdBusMethodNameStart = "StartUnit";

    /**
     * Stores the Systemd DBus MethodNameStop method name.
    */
    const QString SystemdBusMethodNameStop = "StopUnit";

    /**
     * Stores the Tuned Systemd service name.
    */
    const QString SystemdTunedServiceName = "tuned.service";

    /**
     * Stores the Systemd start/stop service mode.
    */
    const QString SystemdTunedServiceMode = "replace";

    /**
     * Stores DBus instance.
    */
    const QDBusConnection DBusInstance = QDBusConnection::systemBus();
private slots:
    /**
     * Tuned profile changed event slot.
     * @param NewProfile Recently switched profile name.
     * @param SwitchResult Switch result: true - success; false - failure.
     * @param ResultMessage Result message (OK on success).
    */
    void ProfileChangedEvent(const QString&, const bool, const QString&);
signals:
    /**
     * Tuned profile changed event signal.
    */
    void ProfileChangedSignal(const QString&, const bool, const QString&);
};

#endif // TUNEDMANAGER_H
