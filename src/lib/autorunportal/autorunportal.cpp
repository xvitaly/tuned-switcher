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
#include <QDBusMetaType>
#include <QList>
#include <QMetaType>
#include <QObject>
#include <QString>
#include <QStringLiteral>
#include <QVariant>
#include <QVariantMap>

#include "appconstants/appconstants.h"
#include "autorunportal/autorunportal.h"
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
    return false;
}

bool AutorunPortal::Enable() const
{
    return false;
}

bool AutorunPortal::Disable() const
{
    return false;
}

const QString AutorunPortal::CreateHandleToken() const
{
    return PortalBusRequestPath.arg(PortalBusPath, DBusInstance.baseService().remove(QChar(':')).replace(QChar('.'), QChar('_')), AppConstants::ProductNameInternal);
}

const QString AutorunPortal::CreateReasonString(const QString& query) const
{
    return QStringLiteral("{1} the autorun feature for the {2}").arg(query, AppConstants::ProductName);
}

const QVariantMap AutorunPortal::CreateOptionsStructure(const QString& reason, const bool autostart) const
{
    QVariantMap result;
    result[QStringLiteral("handle_token")] = CreateHandleToken();
    result[QStringLiteral("reason")] = reason;
    result[QStringLiteral("autostart")] = autostart;
    result[QStringLiteral("dbus-activatable")] = false;
    return result;
}

const QList<QVariant> AutorunPortal::CreateRequestStructure(const QString& reason, const bool autostart) const
{
    QList<QVariant> result;
    result << QString();
    result << CreateOptionsStructure(reason, autostart);
    return result;
}
