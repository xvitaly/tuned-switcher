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
     * Destructor of the ServiceManager class.
    */
    virtual ~ServiceManager() = default;

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
};

#endif // SERVICEMANAGER_H
