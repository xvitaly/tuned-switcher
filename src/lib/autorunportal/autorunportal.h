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
     * Stores the desktop portal DBus interface name.
    */
    const QString PortalBusName = QStringLiteral("org.freedesktop.portal.Desktop");

    /**
     * Stores the desktop portal DBus object path.
    */
    const QString PortalBusPath = QStringLiteral("/org/freedesktop/portal/desktop");

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
    QString CreateHandleToken() const;

    /**
     * Constructs and returns DBus activation reason for the
     * request interface.
     * @returns DBus activation reason.
    */
    QString CreateReasonString(const bool) const;

    /**
     * Constructs and returns special Options structure for
     * the desktop portal service.
     * @param autostart New autorun status.
     * @returns Options structure for the desktop portal service.
    */
    const QVariantMap CreateOptionsStructure(const bool) const;

    /**
     * Constructs and returns special Request structure for
     * the desktop portal service.
     * @param autostart New autorun status.
     * @returns Request structure for the desktop portal service.
    */
    const QList<QVariant> CreateRequestStructure(const bool) const;

    /**
     * Runs the Request method and returns the result.
     * @param autostart New autorun status.
     * @returns Result of the operation.
     * @retval true The requested operation completed successfully.
     * @retval false An error occurred when trying to perform the requested operation.
    */
    bool RunDBusRequestMethod(const bool) const;
private slots:
    /**
     * Response received event slot.
     * @param response Response code: 0 - success; 1 - cancelled; 2 - timeout..
     * @param results Results data.
    */
    void RequestResponseEvent(unsigned int, const QVariantMap&) const;
};

#endif // AUTORUNPORTAL_H
