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

#include <QDBusConnection>
#include <QList>
#include <QObject>
#include <QString>
#include <QStringLiteral>
#include <QVariant>
#include <QVariantMap>

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
    /**
     * Stores the desktop portal DBus interface name.
    */
    const QString PortalBusName = QStringLiteral("org.freedesktop.portal.Desktop");

    /**
     * Stores the desktop portal DBus object path.
    */
    const QString PortalBusPath = QStringLiteral("/org/freedesktop/portal/desktop");

    /**
     * Stores the desktop portal DBus request interface.
    */
    const QString PortalBusRequestPath = QStringLiteral("{1}/request/{2}/{3}");

    /**
     * Stores the desktop portal DBus interface.
    */
    const QString PortalBusInterface = QStringLiteral("org.freedesktop.portal.Background");

    /**
     * Stores the desktop portal DBus RequestBackground method name.
    */
    const QString PortalBusMethodNameRequestBackground = QStringLiteral("RequestBackground");

    /**
     * Stores DBus instance.
    */
    QDBusConnection DBusInstance = QDBusConnection::sessionBus();

    /**
     * Constructs and returns special DBus object path for the
     * request interface.
     * @returns Fully-qualified DBus object path.
    */
    const QString CreateHandleToken() const;

    /**
     * Constructs and returns special Options structure for
     * the desktop portal service.
     * @param reason Reason of the requested operation.
     * @param autostart New autorun status.
     * @returns Options structure for the desktop portal service.
    */
    const QVariantMap CreateOptionsStructure(const QString&, const bool) const;

    const QList<QVariant> CreateRequestStructure(const QString&, const bool) const;
};

#endif // AUTORUNPORTAL_H
