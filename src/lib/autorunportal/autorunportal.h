/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef AUTORUNPORTAL_H
#define AUTORUNPORTAL_H

/**
 * @file autorunportal/autorunportal.h
 * Contains the AutorunPortal class definition.
*/

#include <QObject>

#include "autorunmanager/autorunmanager.h"

/**
 * Class for working with autorun configurations using portals.
*/
class AutorunPortal : public AutorunManager
{
    Q_OBJECT
public:
    /**
     * Main constructor of the AutorunPortal class.
     * @param parent Parent.
    */
    explicit AutorunPortal(QObject* parent = nullptr);

    /**
     * Destructor of the AutorunPortal class.
    */
    ~AutorunPortal() = default;

    /**
     * Get whether the autorun feature is enabled.
     * @returns Whether the autorun feature is enabled.
     * @retval true The autorun feature is enabled.
     * @retval false The autorun feature is not enabled.
    */
    bool IsEnabled() const override;

    /**
     * Get whether the autorun feature is supported on running platform.
     * @returns Whether the autorun feature is supported on running platform.
     * @retval true The autorun feature is supported on running platform.
     * @retval false The autorun feature is not supported on running platform.
    */
    bool IsSupported() const override;

    /**
     * Enable the autorun feature.
     * @returns Result of the requested operation.
     * @retval true The requested operation completed successfully.
     * @retval false An error occurred when trying to perform the requested operation.
    */
    bool Enable() const override;

    /**
     * Disable the autorun feature.
     * @returns Result of the requested operation.
     * @retval true The requested operation completed successfully.
     * @retval false An error occurred when trying to perform the requested operation.
    */
    bool Disable() const override;
};

#endif // AUTORUNPORTAL_H
