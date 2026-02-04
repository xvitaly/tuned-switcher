/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file portalrequest/portalrequest.cpp
 * Contains the PortalRequest class implementation.
*/

#include <QDBusInterface>
#include <QDBusReply>
#include <QList>
#include <QLoggingCategory>
#include <QObject>
#include <QRandomGenerator>
#include <QString>
#include <QStringLiteral>
#include <QVariant>
#include <QVariantMap>

#include "logcategories/logcategories.h"
#include "portalrequest/portalrequest.h"

PortalRequest::PortalRequest(QObject* parent) : QObject(parent)
{
}

QString PortalRequest::CreateHandleToken() const
{
    return QStringLiteral("u%1").arg(QRandomGenerator::global() -> generate());
}

QString PortalRequest::CreateReasonString() const
{
    return QStringLiteral("Configure the autorun feature using portal");
}

const QVariantMap PortalRequest::CreateOptionsStructure(const bool autostart) const
{
    QVariantMap result;
    result[QStringLiteral("handle_token")] = CreateHandleToken();
    result[QStringLiteral("reason")] = CreateReasonString();
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
    QDBusInterface DBusInterface(PortalBusName, PortalBusPath, PortalBusBackgroundInterface, DBusInstance);
    QDBusReply<QDBusObjectPath> DBusReply = DBusInterface.callWithArgumentList(QDBus::AutoDetect, PortalBusMethodNameRequestBackground, CreateRequestStructure(autostart));
    const bool DBusResult = DBusReply.isValid();
    if (!DBusResult)
    {
        qCWarning(LogCategories::Autorun) << "Failed to configure the autorun feature using portal due to an error:" << DBusReply.error();
        RequestResponseError();
    }
    else
    {
        DBusInstance.connect(QString(), DBusReply.value().path(), PortalBusRequestInterface, PortalBusSignalNameResponse, this, SLOT(RequestResponseEvent(unsigned int, const QVariantMap)));
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
    if (!ResponseResults.contains(PortalBusFieldNameAutostart))
        return BackgroundResult::Unknown;
    return ResponseResults[PortalBusFieldNameAutostart].toBool() ? BackgroundResult::Enabled : BackgroundResult::Disabled;
}

PortalRequest::BackgroundResult PortalRequest::GetResult() const
{
    if (!ResponseFinished || ResponseResults.isEmpty())
        return BackgroundResult::NotFinished;
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
