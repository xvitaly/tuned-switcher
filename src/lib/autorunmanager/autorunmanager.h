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
#include <QStringLiteral>

class AutorunManager : public QObject
{
    Q_OBJECT
public:
    /**
     * Main constructor of the AutorunManager class.
     * @param parent Parent.
    */
    explicit AutorunManager(QObject* parent = nullptr);

    /**
     * Get whether the autorun feature is enabled.
     * @returns Whether the autorun feature is enabled.
    */
    bool IsEnabled();

    /**
     * Enable the autorun feature.
    */
    void Enable();

    /**
     * Disable the autorun feature.
    */
    void Disable();
private:
    /**
     * Get autorun directory path.
     * @returns Fully-qualified autorun directory path.
    */
    QString GetAutorunDirectoryName() const;

    /**
     * Get autorun file name.
     * @returns Fully-qualified autorun file name.
    */
    QString GetAutorunFileName() const;

    /**
     * Generate autorun file contents.
     * @returns Autorun file contents.
    */
    QString GenerateAutorunFile() const;

    /**
     * Write autorun file to disk.
     * @param value Autorun file contents.
    */
    void WriteAutorunFile(const QString&) const;

    /**
     * Stores full path to the autorun directory.
    */
    QString AutorunDirectoryName;

    /**
     * Stores full path to the autorun file.
    */
    QString AutorunFileName;

    /**
     * Stores the path to the autorun directory.
    */
    const QString AutorunDirectoryPath = QStringLiteral("%1/.config/autostart");

    /**
     * Stores the autorun file path.
    */
    const QString AutorunFilePath = QStringLiteral("%1/.config/autostart/%2.desktop");
};

#endif // AUTORUNMANAGER_H
