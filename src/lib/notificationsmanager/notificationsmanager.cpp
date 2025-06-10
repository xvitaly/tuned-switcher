/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file notificationsmanager/notificationsmanager.cpp
 * Contains the NotificationsManager class implementation.
*/

#include <QDBusInterface>
#include <QDBusMetaType>
#include <QDBusReply>
#include <QIcon>
#include <QImage>
#include <QList>
#include <QMetaType>
#include <QObject>
#include <QPixmap>
#include <QRegularExpression>
#include <QString>
#include <QStringList>
#include <QStringLiteral>
#include <QVariant>
#include <QVariantMap>

#include "appconstants/appconstants.h"
#include "notificationsmanager/notificationsmanager.h"
#include "notificationsmanager/dbusconverters.h"

void NotificationsManager::GetCapabilities()
{
    QDBusInterface DBusInterface(NotifyBusName, NotifyBusPath, NotifyBusInterface, DBusInstance);
    QDBusReply<QStringList> DBusReply = DBusInterface.call(NotifyBusMethodNameCapabilities);
    IsMarkupSupported = DBusReply.value().contains(QStringLiteral("body-markup"));
    IsImagesSupported = DBusReply.value().contains(QStringLiteral("body-images"));
}

const QImage NotificationsManager::GetNotificationImage(const int size = 128) const
{
    QIcon icon = QIcon::fromTheme(AppConstants::DomainSchemeName, QIcon(QStringLiteral(":/icons/fallback.png")));
    QPixmap pixmap = icon.pixmap(icon.actualSize(QSize(size, size)));
    return pixmap.toImage();
}

const QString NotificationsManager::FormatNotificationMessage(const QString& message) const
{
    return IsMarkupSupported ? message : QString(message).remove(QRegularExpression(QStringLiteral("<\\/?[bi]>"), QRegularExpression::CaseInsensitiveOption));
}

const QVariantMap NotificationsManager::CreateHintsStructure() const
{
    QVariantMap result;
    if (IsImagesSupported) result[QStringLiteral("image-data")] = GetNotificationImage();
    result[QStringLiteral("sound-name")] = QStringLiteral("message-new-instant");
    result[QStringLiteral("desktop-entry")] = AppConstants::LauncherName;
    return result;
}

const QList<QVariant> NotificationsManager::CreateArgListStructure(const QString& title, const QString& message) const
{
    QList<QVariant> result;
    result << AppConstants::ProductName;
    result << static_cast<unsigned int>(0);
    result << QString();
    result << title;
    result << FormatNotificationMessage(message);
    result << QStringList();
    result << CreateHintsStructure();
    result << static_cast<int>(5000);
    return result;
}

bool NotificationsManager::ShowNotification(const QString& title, const QString& message) const
{
    QDBusInterface DBusInterface(NotifyBusName, NotifyBusPath, NotifyBusInterface, DBusInstance);
    QDBusReply<void> DBusReply = DBusInterface.callWithArgumentList(QDBus::AutoDetect, NotifyBusMethodNameNotify, CreateArgListStructure(title, message));
    return DBusReply.isValid();
}

NotificationsManager::NotificationsManager(QObject* parent) : QObject(parent)
{
    if (DBusInstance.isConnected())
    {
        qDBusRegisterMetaType<QImage>();
        GetCapabilities();
    }
}
