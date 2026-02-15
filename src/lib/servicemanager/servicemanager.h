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

#include <QObject>

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
};

#endif // SERVICEMANAGER_H
