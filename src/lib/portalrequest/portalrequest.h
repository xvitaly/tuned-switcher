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
     * Runs the Request method and returns the result.
     * @param autostart New autorun status.
     * @returns Result of the operation.
     * @retval true The requested operation completed successfully.
     * @retval false An error occurred when trying to perform the requested operation.
    */
    bool RequestBackground(const bool);

    /**
     * Returns the result of the asynchronous operation.
     * @returns Result of the asynchronous operation.
    */
    BackgroundResult GetResult() const;
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
     * Response received event slot.
     * @param response Response code: 0 - success; 1 - cancelled; 2 - timeout.
     * @param results Results data.
    */
    void RequestResponseEvent(unsigned int, const QVariantMap&);
signals:
    /**
     * Asynchronous request completed signal.
    */
    void finished();
};

#endif // PORTALREQUEST_H
