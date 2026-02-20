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
     * Create an instance of the ServiceManager class. Factory method.
     * @param parent Parent.
     * @returns Instance of the ServiceManager class.
    */
    static ServiceManager* Create(QObject* parent = nullptr);

    /**
     * Destructor of the ServiceManager class.
    */
    virtual ~ServiceManager() = default;

    /**
     * Get whether the service control feature is supported on running platform.
     * @returns Whether the service control feature is supported on running platform.
     * @retval true The service control feature is supported on running platform.
     * @retval false The service control feature is not supported on running platform.
    */
    virtual bool IsSupported() const;

    /**
     * Check if the Tuned service is running.
     * @returns If the Tuned sevice is running.
     * @retval true Tuned is running.
     * @retval false Tuned is not running.
    */
    virtual bool IsRunning() const;

    /**
     * Start the Tuned service.
     * @returns Result of current operation.
     * @retval true Tuned was successfully started.
     * @retval false An error occurred when trying to start the Tuned service.
    */
    virtual bool Start() const;

    /**
     * Stop the Tuned service.
     * @returns Result of current operation.
     * @retval true Tuned was successfully stopped.
     * @retval false An error occurred when trying to stop the Tuned service.
    */
    virtual bool Stop() const;
protected:
    /**
     * Main constructor of the ServiceManager class.
     * Cannot be called directly. A special factory method Create()
     * should be used instead.
     * @param parent Parent.
    */
    explicit ServiceManager(QObject* parent = nullptr);
};

#endif // SERVICEMANAGER_H
