/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef TUNEDMANAGER_H
#define TUNEDMANAGER_H

/**
 * @file tunedmanager/tunedmanager.h
 * Contains the TunedManager class definition.
*/

#include <QDBusConnection>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QStringLiteral>

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
    explicit TunedManager(QObject* parent = nullptr);

    /**
     * Get active Tuned profile.
     * @returns Active Tuned profile.
    */
    QString GetActiveProfile() const;

    /**
     * Get the list of available Tuned profiles.
     * @returns Available Tuned profiles.
    */
    QStringList GetAvailableProfiles() const;

    /**
     * Get the list of available Tuned profiles with additional
     * useful information like profile descriptions.
     * @returns Available Tuned profiles.
    */
    QTunedProfileList GetAvailableProfiles2() const;

    /**
     * Get current Tuned mode: manual or auto.
     * @returns Current Tuned mode.
    */
    QTunedProfileMode GetProfileMode() const;

    /**
     * Check if the Tuned is working in automatic mode.
     * @returns Automatic mode on/off.
     * @retval true Tuned is working in automatic mode.
     * @retval false Tuned is working in manual mode.
    */
    bool IsProfileModeAuto() const;

    /**
     * Switch Tuned to automatic mode.
     * @returns Result of current operation.
    */
    QTunedResult SetProfileModeAuto() const;

    /**
     * Switch Tuned to the the specified profile.
     * @param Profile New Tuned profile name.
     * @returns Result of current operation.
    */
    QTunedResult SetActiveProfile(const QString&) const;

    /**
     * Check whether the Tuned service is operational.
     * @returns Whether the Tuned sevice is operational.
     * @retval true Tuned sevice is operational.
     * @retval false Tuned sevice is not operational.
    */
    bool IsOperational() const;

    /**
     * Check whether the Tuned is running a profile.
     * @returns Whether the Tuned is running a profile.
     * @retval true Tuned is running a profile.
     * @retval false Tuned is not running a profile.
    */
    bool IsRunning() const;

    /**
     * Enable the Tuned service.
     * @returns Result of current operation.
     * @retval true Tuned was successfully enabled.
     * @retval false An error occurred when trying to enable the Tuned service.
    */
    bool Enable() const;

    /**
     * Disable the Tuned service.
     * @returns Result of current operation.
     * @retval true Tuned was successfully disabled.
     * @retval false An error occurred when trying to disable the Tuned service.
    */
    bool Disable() const;

    /**
     * Reload the Tuned service configuration.
     * @returns Result of current operation.
     * @retval true Tuned service configuration was reloaded.
     * @retval false An error occurred when trying to reload the Tuned service configuration.
    */
    bool Reload() const;

    /**
     * Shutdown the Tuned service and disable all configurations.
     * @returns Result of current operation.
     * @retval true Tuned service configuration was shut down and configurations disabled.
     * @retval false An error occurred when trying to shut down the Tuned service and disable configurations.
    */
    bool Shutdown() const;

    /**
     * Enum with IDs of service methods, used by various methods.
    */
    enum class ServiceMethod { MethodEnable, MethodDisable, MethodReload, MethodShutdown };
    Q_ENUM(ServiceMethod)

    /**
     * Run the specified service control method.
     * @param method Service control method name.
     * @returns Result of the requested service control operation.
     * @retval true The requested service control operation completed successfully.
     * @retval false An error occurred when trying to perform the requested operation.
    */
    bool RunServiceMethod(const ServiceMethod) const;
private:
    /**
     * Stores the Tuned DBus interface name.
    */
    const QString TunedBusName = QStringLiteral("com.redhat.tuned");

    /**
     * Stores the Tuned DBus object path.
    */
    const QString TunedBusPath = QStringLiteral("/Tuned");

    /**
     * Stores the Tuned DBus interface.
    */
    const QString TunedBusInterface = QStringLiteral("com.redhat.tuned.control");

    /**
     * Stores the Tuned DBus ActiveProfile method name.
    */
    const QString TunedBusMethodNameActiveProfile = QStringLiteral("active_profile");

    /**
     * Stores the Tuned DBus AvailableProfiles method name.
    */
    const QString TunedBusMethodNameProfiles = QStringLiteral("profiles");

    /**
     * Stores the Tuned DBus SwitchProfile method name.
    */
    const QString TunedBusMethodNameSwitchProfile = QStringLiteral("switch_profile");

    /**
     * Stores the Tuned DBus SetProfileMode method name.
    */
    const QString TunedBusMethodNameProfileMode = QStringLiteral("profile_mode");

    /**
     * Stores the Tuned DBus AutoProfile method name.
    */
    const QString TunedBusMethodNameAutoProfile = QStringLiteral("auto_profile");

    /**
     * Stores the Tuned DBus ProfileChanged signal name.
    */
    const QString TunedBusSignalNameProfileChanged = QStringLiteral("profile_changed");

    /**
     * Stores the Tuned DBus AvailableProfiles2 method name.
    */
    const QString TunedBusMethodNameProfiles2 = QStringLiteral("profiles2");

    /**
     * Stores the Tuned DBus IsRunning method name.
    */
    const QString TunedBusMethodNameIsRunning = QStringLiteral("is_running");

    /**
     * Stores the Tuned DBus Start method name.
    */
    const QString TunedBusMethodNameStart = QStringLiteral("start");

    /**
     * Stores the Tuned DBus Stop method name.
    */
    const QString TunedBusMethodNameStop = QStringLiteral("stop");

    /**
     * Stores the Tuned DBus Reload method name.
    */
    const QString TunedBusMethodNameReload = QStringLiteral("reload");

    /**
     * Stores the Tuned DBus Disable method name.
    */
    const QString TunedBusMethodNameDisable = QStringLiteral("disable");

    /**
     * Stores the Tuned DBus AutoProfile value.
    */
    const QString TunedBusValueAutoProfile = QStringLiteral("auto");

    /**
     * Stores DBus instance.
    */
    QDBusConnection DBusInstance = QDBusConnection::systemBus();
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
