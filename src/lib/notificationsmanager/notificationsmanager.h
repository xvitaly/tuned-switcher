/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef NOTIFICATIONSMANAGER_H
#define NOTIFICATIONSMANAGER_H

/** @file lib/notificationsmanager/notificationsmanager.h
 * This file contains NotificationsManager class structure.
*/

#include <QDBusInterface>
#include <QObject>

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
     * Shows DBus notification with specified title and message.
     * @param title Notification title.
     * @param message Notification message.
    */
    bool ShowNotification(const QString&, const QString&) const;
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
     * Stores information if the Notifications service supports basic
     * HTML markup.
    */
    bool IsMarkupSupported;

    /**
     * Stores information if the Notifications service supports images.
    */
    bool IsImagesSupported;

    /**
     * Gets information about available notifications capabilities and
     * stores it in a private field.
    */
    void GetCapabilities();

    /**
     * Gets a default image for the Notifications service.
     * @param size Desired image size.
     * @returns Image for the Notifications service.
    */
    const QImage GetNotificationImage(const int) const;

    /**
     * Constructs and returns special Hints structure for the
     * Notifications service.
     * @returns Hints structure for the Notifications service.
    */
    const QVariantMap CreateHintsStructure() const;

    /**
     * Constructs and returns special ArgumentsList structure for
     * the Notifications service.
     * @returns ArgumentsList structure for the Notifications service.
    */
    const QList<QVariant> CreateArgListStructure(const QString&, const QString&) const;
};

#endif // NOTIFICATIONSMANAGER_H
