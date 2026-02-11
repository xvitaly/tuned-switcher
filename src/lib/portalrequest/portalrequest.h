/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef PORTALREQUEST_H
#define PORTALREQUEST_H

/**
 * @file portalrequest/portalrequest.h
 * Contains the PortalRequest class definition.
*/

#include <QDBusConnection>
#include <QList>
#include <QObject>
#include <QString>
#include <QStringLiteral>
#include <QVariant>
#include <QVariantMap>

/**
 * Class for working with portals.
*/
class PortalRequest : public QObject
{
    Q_OBJECT
public:
    /**
     * Main constructor of the PortalRequest class.
     * @param parent Parent.
    */
    explicit PortalRequest(QObject* parent = nullptr);

    /**
     * Enum with IDs of result codes, used by various methods.
    */
    enum class BackgroundResult { Disabled, Enabled, Cancelled, Timeout, Unknown, NotFinished };
    Q_ENUM(BackgroundResult)

    /**
     * Runs the RequestBackground method and returns the DBus method call status.
     * The GetResult() method should be called after receiving the finished()
     * signal to obtain the result.
     * @param autostart New autorun status.
     * @returns DBus method call status.
     * @retval true The requested method was called successfully.
     * @retval false An error occurred when trying to call the the requested method.
    */
    bool RequestBackground(const bool);

    /**
     * Returns the result of the asynchronous operation.
     * @returns Result of the asynchronous operation.
    */
    BackgroundResult GetResult() const;

    /**
     * Returns version of the PortalRequest portal as an unsigned integer.
     * @returns Version of the PortalRequest portal, or 0 if an error occurs.
    */
    unsigned int GetVersion() const;
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
     * Stores the desktop portal Background DBus interface.
    */
    const QString PortalBusBackgroundInterface = QStringLiteral("org.freedesktop.portal.Background");

    /**
     * Stores the desktop portal Request DBus interface.
    */
    const QString PortalBusRequestInterface = QStringLiteral("org.freedesktop.portal.Request");

    /**
     * Stores the desktop portal DBus RequestBackground method name.
    */
    const QString PortalBusMethodNameRequestBackground = QStringLiteral("RequestBackground");

    /**
     * Stores the desktop portal DBus Response signal name.
    */
    const QString PortalBusSignalNameResponse = QStringLiteral("Response");

    /**
     * Stores the desktop portal DBus Autostart field name.
    */
    const QString PortalBusFieldNameAutostart = QStringLiteral("autostart");

    /**
     * Stores the desktop portal DBus Version property name.
    */
    const QString PortalBusPropertyNameVersion = QStringLiteral("version");

    /**
     * Stores the Systemd Properties DBus interface.
    */
    const QString DBusPropertyInterface = QStringLiteral("org.freedesktop.DBus.Properties");

    /**
     * Stores the Systemd DBus GetProperty method name.
    */
    const QString DBusPropertyMethodNameGet = QStringLiteral("Get");

    /**
     * Stores the status of the asynchronous operation.
    */
    bool ResponseFinished = false;

    /**
     * Stores the response code after running the asynchronous operation.
    */
    unsigned long ResponseCode = 255UL;

    /**
     * Stores the response results after running the asynchronous operation.
    */
    QVariantMap ResponseResults;

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
    QString CreateReasonString() const;

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
     * Extracts and returns the result of the asynchronous operation.
     * @returns Result of the asynchronous operation.
    */
    PortalRequest::BackgroundResult ExtractAutostartValue() const;

    /**
     * Sets error values to various private fields and calls finished() slot.
    */
    void RequestResponseError();
private slots:
    /**
     * Response received event slot. Sets received values to various
     * private fields and calls finished() slot.
     * @param response Response code: 0 - success; 1 - cancelled; 2 - timeout.
     * @param results Results data.
    */
    void RequestResponseEvent(const unsigned int, const QVariantMap&);
signals:
    /**
     * Asynchronous request completed signal.
    */
    void finished();
};

#endif // PORTALREQUEST_H
