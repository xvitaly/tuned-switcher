/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef AUTORUNFILE_H
#define AUTORUNFILE_H

/**
 * @file autorunfile/autorunfile.h
 * Contains the AutorunFile class definition.
*/

#include <QObject>
#include <QString>

#include "autorunmanager/autorunmanager.h"

/**
 * Class for working with standard autorun files.
*/
class AutorunFile : public AutorunManager
{
    Q_OBJECT
public:
    /**
     * Main constructor of the AutorunFile class.
     * @param parent Parent.
    */
    explicit AutorunFile(QObject* parent = nullptr);

    /**
     * Destructor of the AutorunFile class.
    */
    ~AutorunFile() = default;

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
private:
    /**
     * Get the fully-qualified autorun directory path.
     * @returns Fully-qualified autorun directory path.
    */
    QString GetAutorunDirectoryName() const;

    /**
     * Get the fully-qualified autorun file name.
     * @returns Fully-qualified autorun file name.
    */
    QString GetAutorunFileName() const;

    /**
     * Create the autorun directory if it doesn't exists.
    */
    void CreateAutorunDirectory() const;

    /**
     * Generate the autorun file contents using stored template.
     * @returns Autorun file contents.
    */
    QString GenerateAutorunFile() const;

    /**
     * Write the autorun file contents to disk.
     * @param value Autorun file contents.
    */
    void WriteAutorunFile(const QString&) const;

    /**
     * Stores the full path to the autorun directory.
    */
    QString AutorunDirectoryName;

    /**
     * Stores the full path to the autorun file.
    */
    QString AutorunFileName;
};

#endif // AUTORUNFILE_H
