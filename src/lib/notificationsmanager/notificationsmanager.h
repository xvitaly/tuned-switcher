/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef NOTIFICATIONSMANAGER_H
#define NOTIFICATIONSMANAGER_H

/**
 * @file notificationsmanager/notificationsmanager.h
 * Contains the NotificationsManager class definition.
*/

#include <QDBusConnection>
#include <QImage>
#include <QList>
#include <QObject>
#include <QString>
#include <QStringLiteral>
#include <QVariant>
#include <QVariantMap>

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
    explicit NotificationsManager(QObject* parent = nullptr);

    /**
     * Shows DBus notification with specified title and message.
     * @param title Notification title.
     * @param message Notification message.
     * @returns Result of the operation.
     * @retval true The requested operation completed successfully.
     * @retval false An error occurred when trying to perform the requested operation.
    */
    bool ShowNotification(const QString&, const QString&) const;

    /**
     * Sets the notification sound mode: loud or silent.
     * @param mode Notification mode: true - loud, false - silent.
    */
    void SetNotificationSoundMode(const bool);
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
    QDBusConnection DBusInstance = QDBusConnection::sessionBus();

    /**
     * Stores if the notification sound is enabled.
    */
    bool IsSoundEnabled = true;

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
     * @param size Desired image size. Default - 128 px.
     * @returns Image for the Notifications service.
    */
    const QImage GetNotificationImage(const int size = 128) const;

    /**
     * Formats a message for the Notifications service based on
     * supported features.
     * @param message Source string.
     * @returns Formatted string for the Notifications service.
    */
    const QString FormatNotificationMessage(const QString&) const;

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
