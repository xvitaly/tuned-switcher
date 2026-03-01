/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef DUMMYSERVICE_H
#define DUMMYSERVICE_H

/**
 * @file dummyservice/dummyservice.h
 * Contains the DummyService class definition.
*/

#include <QObject>

#include "servicemanager/servicemanager.h"

/**
 * Stub class with methods used when the service control
 * feature is disabled.
*/
class DummyService : public ServiceManager
{
    Q_OBJECT
public:
    /**
     * Main constructor of the DummyService class.
     * @param parent Parent.
    */
    explicit DummyService(QObject* parent = nullptr);

    /**
     * Destructor of the DummyService class.
    */
    ~DummyService() override = default;

    /**
     * Check whether the service control feature is supported.
     * @returns Whether the service control feature is supported.
     * @retval true The service control feature is supported.
     * @retval false The service control feature is not supported.
    */
    bool IsSupported() const override;

    /**
     * Check whether the Tuned service is running.
     * @returns Whether the Tuned sevice is running.
     * @retval true The Tuned service is running.
     * @retval false The Tuned servic is not running.
    */
    bool IsRunning() const override;

    /**
     * Start the Tuned service.
     * @returns Result of the requested operation.
     * @retval true The Tuned service was successfully started.
     * @retval false An error occurred when trying to start the Tuned service.
    */
    bool Start() const override;

    /**
     * Stop the Tuned service.
     * @returns Result of the requested operation.
     * @retval true The Tuned service was successfully stopped.
     * @retval false An error occurred when trying to stop the Tuned service.
    */
    bool Stop() const override;
};

#endif // DUMMYSERVICE_H
