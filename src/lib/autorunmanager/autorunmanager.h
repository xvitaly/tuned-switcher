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
#include <QString>

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
    static AutorunManager* Create(QObject*);

    /**
     * Main constructor of the AutorunManager class.
     * @param parent Parent.
    */
    explicit AutorunManager(QObject* parent = nullptr);

    /**
     * Destructor of the AutorunManager class.
    */
    virtual ~AutorunManager();

    /**
     * Get whether the autorun feature is enabled.
     * @returns Whether the autorun feature is enabled.
    */
    virtual bool IsEnabled() const = 0;

    /**
     * Get whether the autorun feature is supported on running platform.
     * @returns Whether the autorun feature is supported.
    */
    virtual bool IsSupported() const;

    /**
     * Enable the autorun feature.
    */
    virtual void Enable() const = 0;

    /**
     * Disable the autorun feature.
    */
    virtual void Disable() const = 0;
private:
    /**
     * Check whether the application is running in a sandbox.
     * @returns Whether the application is running in a sandbox.
    */
    static bool CheckSandbox();
};

#endif // AUTORUNMANAGER_H
