/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/** @file lib/notificationsmanager/notificationsmanager.cpp
 * This file contains implementation of the NotificationsManager class.
*/

#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusMetaType>
#include <QIcon>

#include "appconstants/appconstants.h"
#include "notificationsmanager/notificationsmanager.h"
#include "notificationsmanager/dbusconverters.h"

void NotificationsManager::GetCapabilities()
{
    QDBusInterface DBusInterface(NotifyBusName, NotifyBusPath, NotifyBusInterface, DBusInstance);
    QDBusReply<QStringList> DBusReply = DBusInterface.call(NotifyBusMethodNameCapabilities);
    IsMarkupSupported = DBusReply.value().contains("body-markup");
    IsImagesSupported = DBusReply.value().contains("body-images");
}

const QImage NotificationsManager::GetNotificationImage(const int size = 128) const
{
    QIcon icon = QIcon::fromTheme(AppConstants::DomainSchemeName, QIcon(":/icons/fallback.png"));
    QPixmap pixmap = icon.pixmap(icon.actualSize(QSize(size, size)));
    return pixmap.toImage();
}

const QVariantMap NotificationsManager::CreateHintsStructure()
{
    QVariantMap result;
    if (IsImagesSupported) result["image-data"] = GetNotificationImage();
    result["sound-name"] = "message-new-instant";
    result["desktop-entry"] = AppConstants::DomainSchemeName;
    return result;
}

const QList<QVariant> NotificationsManager::CreateArgListStructure(const QString& title, const QString& message)
{
    QList<QVariant> result;
    result << AppConstants::ProductName;
    result << static_cast<uint>(0);
    result << "";
    result << title;
    result << (IsMarkupSupported ? message : QString(message).remove(QRegExp("<\\/?[bi]>", Qt::CaseInsensitive)));
    result << QStringList();
    result << CreateHintsStructure();
    result << static_cast<int>(5000);
    return result;
}

bool NotificationsManager::ShowNotification(const QString& title, const QString& message)
{
    QDBusInterface DBusInterface(NotifyBusName, NotifyBusPath, NotifyBusInterface, DBusInstance);
    QDBusReply<void> DBusReply = DBusInterface.callWithArgumentList(QDBus::AutoDetect, NotifyBusMethodNameNotify, CreateArgListStructure(title, message));
    return DBusReply.isValid();
}

NotificationsManager::NotificationsManager(QObject *parent) : QObject(parent)
{
    if (DBusInstance.isConnected())
    {
        qDBusRegisterMetaType<QImage>();
        GetCapabilities();
    }
}
