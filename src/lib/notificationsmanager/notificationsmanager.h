/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef NOTIFICATIONSMANAGER_H
#define NOTIFICATIONSMANAGER_H

/** @file lib/notificationsmanager/notificationsmanager.h
 * This file contains NotificationsManager class structure.
*/

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusMetaType>
#include <QIcon>
#include <QObject>

#include "appconstants/appconstants.h"

/**
 * Class for working with native DBus notifications.
*/
class NotificationsManager : public QObject
{
    Q_OBJECT
public:
    /**
     * Main constructor of the NotificationsManager class.
     * @param parent Parent.
    */
    explicit NotificationsManager(QObject *parent = nullptr);

    /**
     * Main constructor of the NotificationsManager class.
     * @param title Notification title.
     * @param message Notification message.
    */
    bool Show(const QString&, const QString&);
private:
    /**
     * Stores the Notifications DBus interface name.
    */
    const QString NotifyBusName = QStringLiteral("org.freedesktop.Notifications");

    /**
     * Stores the Notifications DBus object path.
    */
    const QString NotifyBusPath = QStringLiteral("/org/freedesktop/Notifications");

    /**
     * Stores the Notifications DBus interface.
    */
    const QString NotifyBusInterface = QStringLiteral("org.freedesktop.Notifications");

    /**
     * Stores the Notifications DBus GetCapabilities method name.
    */
    const QString NotifyBusMethodNameCapabilities = QStringLiteral("GetCapabilities");

    /**
     * Stores the Notifications DBus Notify method name.
    */
    const QString NotifyBusMethodNameNotify = QStringLiteral("Notify");

    /**
     * Stores DBus instance.
    */
    const QDBusConnection DBusInstance = QDBusConnection::sessionBus();

    /**
     * Stores the list of available notifications capabilities.
    */
    QStringList Capabilities;

    /**
     * Gets information about available notifications capabilities and
     * stores it in a private field.
    */
    void GetCapabilities();

    /**
     * Check if the Notifications service supports basic HTML markup.
     * @returns If the Notifications service supports basic HTML markup.
     * @retval true HTML markup is supported.
     * @retval false HTML markup is not supported.
    */
    bool IsMarkupSupported();

    /**
     * Check if the Notifications service supports images.
     * @returns If the Notifications service supports images.
     * @retval true Images is supported.
     * @retval false Images is not supported.
    */
    bool IsImagesSupported();

    /**
     * Gets a default image for the Notifications service.
     * @param size Desired image size.
     * @returns Image for the Notifications service.
    */
    QImage GetNotificationImage(const int) const;

    /**
     * Constructs and returns special Hints structure for the
     * Notifications service.
     * @returns Hints structure for the Notifications service.
    */
    QVariantMap CreateHintsStructure();

    /**
     * Constructs and returns special ArgumentsList structure for
     * the Notifications service.
     * @returns ArgumentsList structure for the Notifications service.
    */
    QList<QVariant> CreateArgListStructure(const QString&, const QString&);
};

#endif // NOTIFICATIONSMANAGER_H
