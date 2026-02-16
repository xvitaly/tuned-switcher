/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

/**
 * @file servicemanager/servicemanager.h
 * Contains the ServiceManager class definition.
*/

#include <QDBusConnection>
#include <QObject>
#include <QString>
#include <QStringLiteral>

/**
 * Class for working with the system service manager.
*/
class ServiceManager : public QObject
{
    Q_OBJECT
public:
    /**
     * Main constructor of the ServiceManager class.
     * @param parent Parent.
    */
    explicit ServiceManager(QObject* parent = nullptr);

    /**
     * Check if the Tuned service is running.
     * @returns If the Tuned sevice is running.
     * @retval true Tuned is running.
     * @retval false Tuned is not running.
    */
    bool IsRunning() const;

    /**
     * Start the Tuned service.
     * @returns Result of current operation.
     * @retval true Tuned was successfully started.
     * @retval false An error occurred when trying to start the Tuned service.
    */
    bool Start() const;

    /**
     * Stop the Tuned service.
     * @returns Result of current operation.
     * @retval true Tuned was successfully stopped.
     * @retval false An error occurred when trying to stop the Tuned service.
    */
    bool Stop() const;
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

#endif // SERVICEMANAGER_H
