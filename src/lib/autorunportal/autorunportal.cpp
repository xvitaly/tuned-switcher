/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file autorunportal/autorunportal.cpp
 * Contains the AutorunPortal class implementation.
*/

#include <QChar>
#include <QDBusInterface>
#include <QDBusMetaType>
#include <QDBusReply>
#include <QList>
#include <QLoggingCategory>
#include <QMetaType>
#include <QObject>
#include <QString>
#include <QStringLiteral>
#include <QVariant>
#include <QVariantMap>

#include "appconstants/appconstants.h"
#include "autorunportal/autorunportal.h"
#include "logcategories/logcategories.h"
#include "portaltypes/portaltypes.h"

AutorunPortal::AutorunPortal(QObject* parent) : AutorunManager(parent)
{
    if (DBusInstance.isConnected())
    {
        qRegisterMetaType<QRequestResponse>();
        qDBusRegisterMetaType<QRequestResponse>();
    }
}

bool AutorunPortal::IsEnabled() const
{
    return false;
}

bool AutorunPortal::IsSupported() const
{
    return true;
}

bool AutorunPortal::Enable() const
{
    return RunDBusRequestMethod(true);
}

bool AutorunPortal::Disable() const
{
    return RunDBusRequestMethod(false);
}

QString AutorunPortal::CreateHandleToken() const
{
    return PortalBusRequestPath.arg(PortalBusPath, DBusInstance.baseService().remove(QChar(':')).replace(QChar('.'), QChar('_')), AppConstants::ProductNameInternal);
}

QString AutorunPortal::CreateReasonString(const bool autostart) const
{
    return QStringLiteral("%1 the autorun feature for the %2").arg(autostart ? QStringLiteral("Enable") : QStringLiteral("Disable"), AppConstants::ProductName);
}

const QVariantMap AutorunPortal::CreateOptionsStructure(const bool autostart) const
{
    QVariantMap result;
    result[QStringLiteral("handle_token")] = CreateHandleToken();
    result[QStringLiteral("reason")] = CreateReasonString(autostart);
    result[QStringLiteral("autostart")] = autostart;
    result[QStringLiteral("dbus-activatable")] = false;
    return result;
}

const QList<QVariant> AutorunPortal::CreateRequestStructure(const bool autostart) const
{
    QList<QVariant> result;
    result << QString();
    result << CreateOptionsStructure(autostart);
    return result;
}

bool AutorunPortal::RunDBusRequestMethod(const bool autostart) const
{
    QDBusInterface DBusInterface(PortalBusName, PortalBusPath, PortalBusInterface, DBusInstance);
    QDBusReply<QRequestResponse> DBusReply = DBusInterface.callWithArgumentList(QDBus::AutoDetect, PortalBusMethodNameRequestBackground, CreateRequestStructure(autostart));
    if (!DBusReply.isValid())
        qCWarning(LogCategories::Autorun) << "Failed to configure the autorun feature using portal due to an error:" << DBusReply.error();
    return DBusReply.isValid() && DBusReply.value();
}

void AutorunPortal::RequestResponseEvent(unsigned int response, const QVariantMap& results) const
{
    //
}
