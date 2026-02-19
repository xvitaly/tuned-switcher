/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef SYSTEMDSERVICE_H
#define SYSTEMDSERVICE_H

/**
 * @file systemdservice/systemdservice.h
 * Contains the SystemdService class definition.
*/

#include <QDBusConnection>
#include <QObject>
#include <QString>
#include <QStringLiteral>

#include "servicemanager/servicemanager.h"

/**
 * Class for working with the systemd service manager.
*/
class SystemdService : public ServiceManager
{
    Q_OBJECT
public:
    /**
     * Main constructor of the SystemdService class.
     * @param parent Parent.
    */
    explicit SystemdService(QObject* parent = nullptr);
};

#endif // SYSTEMDSERVICE_H
