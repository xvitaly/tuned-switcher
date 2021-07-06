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
#include <QObject>

class NotificationsManager : public QObject
{
    Q_OBJECT
public:
    explicit NotificationsManager(QObject *parent = nullptr);
    bool IsMarkupSupported();
    bool IsImagesSupported();

private:
    const QString NotifyBusName = QStringLiteral("org.freedesktop.Notifications");
    const QString NotifyBusPath = QStringLiteral("/org/freedesktop/Notifications");
    const QString NotifyBusInterface = QStringLiteral("org.freedesktop.Notifications");
    const QString NotifyBusMethodNameCapabilities = QStringLiteral("GetCapabilities");
    const QDBusConnection DBusInstance = QDBusConnection::sessionBus();
    QStringList Capabilities;
    void GetCapabilities();
};

#endif // NOTIFICATIONSMANAGER_H
