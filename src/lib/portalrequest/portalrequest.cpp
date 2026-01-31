/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file portalrequest/portalrequest.cpp
 * Contains the PortalRequest class implementation.
*/

#include <QChar>
#include <QDBusInterface>
#include <QDBusMetaType>
#include <QDBusReply>
#include <QEventLoop>
#include <QList>
#include <QLoggingCategory>
#include <QMetaType>
#include <QObject>
#include <QRandomGenerator>
#include <QString>
#include <QStringLiteral>
#include <QVariant>
#include <QVariantMap>

#include "appconstants/appconstants.h"
#include "logcategories/logcategories.h"
#include "portalrequest/portalrequest.h"

PortalRequest::PortalRequest(QObject* parent) : QObject(parent)
{}

QString PortalRequest::CreateHandleToken() const
{
    return QStringLiteral("u%1").arg(QRandomGenerator::global() -> generate());
}

QString PortalRequest::CreateReasonString(const bool autostart) const
{
    return QStringLiteral("%1 the autorun feature for the %2").arg(autostart ? QStringLiteral("Enable") : QStringLiteral("Disable"), AppConstants::ProductName);
}

const QVariantMap PortalRequest::CreateOptionsStructure(const bool autostart) const
{
    QVariantMap result;
    result[QStringLiteral("handle_token")] = CreateHandleToken();
    result[QStringLiteral("reason")] = CreateReasonString(autostart);
    result[QStringLiteral("autostart")] = autostart;
    result[QStringLiteral("dbus-activatable")] = false;
    return result;
}

const QList<QVariant> PortalRequest::CreateRequestStructure(const bool autostart) const
{
    QList<QVariant> result;
    result << QString();
    result << CreateOptionsStructure(autostart);
    return result;
}

bool PortalRequest::RequestBackground(const bool autostart)
{
    QDBusInterface DBusInterface(PortalBusName, PortalBusPath, PortalBusInterface, DBusInstance);
    QDBusReply<QDBusObjectPath> DBusReply = DBusInterface.callWithArgumentList(QDBus::AutoDetect, PortalBusMethodNameRequestBackground, CreateRequestStructure(autostart));
    const bool DBusResult = DBusReply.isValid();
    if (!DBusResult)
    {
        qCWarning(LogCategories::Autorun) << "Failed to configure the autorun feature using portal due to an error:" << DBusReply.error();
        RequestResponseError();
    }
    else
    {
        DBusInstance.connect(QString(), DBusReply.value().path(), QStringLiteral("org.freedesktop.portal.Request"), QStringLiteral("Response"), this, SLOT(RequestResponseEvent(unsigned int, const QVariantMap)));
    }
    return DBusResult;
}

void PortalRequest::RequestResponseEvent(unsigned int response, const QVariantMap& results)
{
    ResponseFinished = true;
    ResponseCode = response;
    ResponseResults = results;
    emit finished();
}

void PortalRequest::RequestResponseError()
{
    ResponseFinished = false;
    ResponseCode = 255UL;
    ResponseResults = QVariantMap();
    emit finished();
}

PortalRequest::BackgroundResult PortalRequest::ExtractAutostartValue() const
{
    const QString Key = QStringLiteral("autostart");
    if (!ResponseResults.contains(Key)) return BackgroundResult::Unknown;
    return ResponseResults[Key].toBool() ? BackgroundResult::Enabled : BackgroundResult::Disabled;
}

PortalRequest::BackgroundResult PortalRequest::GetResult() const
{
    if (!ResponseFinished || ResponseResults.isEmpty()) return BackgroundResult::NotFinished;
    switch (ResponseCode)
    {
        case 0UL:
            return ExtractAutostartValue();
        case 1UL:
            return BackgroundResult::Cancelled;
        case 2UL:
            return BackgroundResult::Timeout;
        default:
            return BackgroundResult::Unknown;
    }
}
