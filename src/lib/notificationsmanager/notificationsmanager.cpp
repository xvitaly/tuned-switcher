/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/** @file lib/notificationsmanager/notificationsmanager.cpp
 * This file contains implementation of the NotificationsManager class.
*/

#include "notificationsmanager.h"

void NotificationsManager::GetCapabilities()
{
    QDBusInterface DBusInterface(NotifyBusName, NotifyBusPath, NotifyBusInterface, DBusInstance);
    QDBusReply<QStringList> DBusReply = DBusInterface.call(NotifyBusMethodNameCapabilities);
    Capabilities = DBusReply.value();
}

bool NotificationsManager::IsMarkupSupported()
{
    return Capabilities.contains("body-markup");
}

bool NotificationsManager::IsImagesSupported()
{
    return Capabilities.contains("body-images");
}

NotificationsManager::NotificationsManager(QObject *parent) : QObject(parent)
{
    if (DBusInstance.isConnected())
    {
        qDBusRegisterMetaType<QImage>();
        GetCapabilities();
    }
}
