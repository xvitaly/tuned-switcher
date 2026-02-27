/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef AUTORUNMANAGER_H
#define AUTORUNMANAGER_H

/**
 * @file autorunmanager/autorunmanager.h
 * Contains the AutorunManager class definition.
*/

#include <QObject>

/**
 * Abstract class for working with autorun configurations.
*/
class AutorunManager : public QObject
{
    Q_OBJECT
public:
    /**
     * Create an instance of the AutorunManager class. Factory method.
     * @param parent Parent.
     * @returns Instance of the AutorunManager class.
    */
    static AutorunManager* Create(QObject* parent = nullptr);

    /**
     * Destructor of the AutorunManager class.
    */
    virtual ~AutorunManager() = default;

    /**
     * Check whether the autorun feature is enabled.
     * @returns Whether the autorun feature is enabled.
     * @retval true The autorun feature is enabled.
     * @retval false The autorun feature is not enabled.
    */
    virtual bool IsEnabled() const = 0;

    /**
     * Check whether the autorun feature is supported on running platform.
     * @returns Whether the autorun feature is supported on running platform.
     * @retval true The autorun feature is supported on running platform.
     * @retval false The autorun feature is not supported on running platform.
    */
    virtual bool IsSupported() const = 0;

    /**
     * Enable the autorun feature.
     * @returns Result of the requested operation.
     * @retval true The requested operation completed successfully.
     * @retval false An error occurred when trying to perform the requested operation.
    */
    virtual bool Enable() const = 0;

    /**
     * Disable the autorun feature.
     * @returns Result of the requested operation.
     * @retval true The requested operation completed successfully.
     * @retval false An error occurred when trying to perform the requested operation.
    */
    virtual bool Disable() const = 0;

protected:
    /**
     * Main constructor of the AutorunManager class.
     * Cannot be called directly. A special factory method Create()
     * should be used instead.
     * @param parent Parent.
    */
    explicit AutorunManager(QObject* parent = nullptr);

private:
    /**
     * Check whether the application is running in a sandbox.
     * @returns Whether the application is running in a sandbox.
    */
    static bool CheckSandbox();
};

#endif // AUTORUNMANAGER_H
