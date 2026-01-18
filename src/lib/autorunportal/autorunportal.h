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
     * Get whether the autorun feature is enabled.
     * @returns Whether the autorun feature is enabled.
    */
    bool IsEnabled() const override;

    /**
     * Get whether the autorun feature is supported on running platform.
     * @returns Whether the autorun feature is supported.
    */
    bool IsSupported() const override;

    /**
     * Enable the autorun feature.
    */
    void Enable() const override;

    /**
     * Disable the autorun feature.
    */
    void Disable() const override;
private:
};

#endif // AUTORUNPORTAL_H
