/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef SYSTEMDSERVICE_H
#define SYSTEMDSERVICE_H

/**
 * @file systemdservice/systemdservice.h
 * Contains the SystemdService class definition.
*/

#include <QDBusConnection>
#include <QObject>
#include <QString>
#include <QStringLiteral>

#include "servicemanager/servicemanager.h"

/**
 * Class for working with the systemd service manager.
*/
class SystemdService : public ServiceManager
{
    Q_OBJECT
public:
    /**
     * Main constructor of the SystemdService class.
     * @param parent Parent.
    */
    explicit SystemdService(QObject* parent = nullptr);

    /**
     * Destructor of the SystemdService class.
    */
    ~SystemdService() override = default;

    /**
     * Check whether the service control feature is supported.
     * @returns Whether the service control feature is supported.
     * @retval true The service control feature is supported.
     * @retval false The service control feature is not supported.
    */
    bool IsSupported() const override;

    /**
     * Check whether the Tuned service is running using the DBus API.
     * @returns Whether the Tuned sevice is running.
     * @retval true The Tuned service is running.
     * @retval false The Tuned servic is not running.
    */
    bool IsRunning() const override;

    /**
     * Start the Tuned service using the DBus API.
     * @returns Result of the requested operation.
     * @retval true The Tuned service was successfully started.
     * @retval false An error occurred when trying to start the Tuned service.
    */
    bool Start() const override;

    /**
     * Stop the Tuned service using the DBus API.
     * @returns Result of the requested operation.
     * @retval true The Tuned service was successfully stopped.
     * @retval false An error occurred when trying to stop the Tuned service.
    */
    bool Stop() const override;

private:
    /**
     * Stores the Systemd DBus interface name.
    */
    const QString SystemdBusName = QStringLiteral("org.freedesktop.systemd1");

    /**
     * Stores the Systemd DBus object path.
    */
    const QString SystemdBusPath = QStringLiteral("/org/freedesktop/systemd1");

    /**
     * Stores the Systemd Manager DBus interface.
    */
    const QString SystemdBusInterfaceManager = QStringLiteral("org.freedesktop.systemd1.Manager");

    /**
     * Stores the Systemd Unit DBus interface.
    */
    const QString SystemdBusInterfaceUnit = QStringLiteral("org.freedesktop.systemd1.Unit");

    /**
     * Stores the Systemd DBus GetUnit method name.
    */
    const QString SystemdBusMethodNameGetUnit = QStringLiteral("GetUnit");

    /**
     * Stores the Systemd DBus MethodNameStart method name.
    */
    const QString SystemdBusMethodNameStart = QStringLiteral("StartUnit");

    /**
     * Stores the Systemd DBus MethodNameStop method name.
    */
    const QString SystemdBusMethodNameStop = QStringLiteral("StopUnit");

    /**
     * Stores the Systemd DBus ActiveState property name.
    */
    const QString SystemdBusPropertyNameActiveState = QStringLiteral("ActiveState");

    /**
     * Stores the Systemd DBus SystemState property name.
    */
    const QString SystemdBusPropertyNameSystemState = QStringLiteral("SystemState");

    /**
     * Stores the Tuned DBus ServiceActive value.
    */
    const QString SystemdBusValueServiceActive = QStringLiteral("active");

    /**
     * Stores the Tuned Systemd service name.
    */
    const QString SystemdTunedServiceName = QStringLiteral("tuned.service");

    /**
     * Stores the Systemd start/stop service mode.
    */
    const QString SystemdTunedServiceMode = QStringLiteral("replace");

    /**
     * Stores the Systemd Properties DBus interface.
    */
    const QString DBusPropertyInterface = QStringLiteral("org.freedesktop.DBus.Properties");

    /**
     * Stores the Systemd DBus GetProperty method name.
    */
    const QString DBusPropertyMethodNameGet = QStringLiteral("Get");

    /**
     * Stores DBus instance.
    */
    QDBusConnection DBusInstance = QDBusConnection::systemBus();

    /**
     * Get the state of the Tuned service.
     * @param BusPath DBus service object path.
     * @returns The state of the Tuned service, or an empty string if an error occurs.
    */
    QString GetServiceState(const QString&) const;
};

#endif // SYSTEMDSERVICE_H
