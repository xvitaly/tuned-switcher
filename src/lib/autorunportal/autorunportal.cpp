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
#include <QObject>
#include <QString>
#include <QStringLiteral>
#include <QVariantMap>

#include "appconstants/appconstants.h"
#include "autorunportal/autorunportal.h"

AutorunPortal::AutorunPortal(QObject* parent) : AutorunManager(parent)
{}

bool AutorunPortal::IsEnabled() const
{
    return false;
}

bool AutorunPortal::IsSupported() const
{
    return false;
}

void AutorunPortal::Enable() const
{
}

void AutorunPortal::Disable() const
{
}

const QString AutorunPortal::CreateHandleToken() const
{
    return PortalBusRequestPath.arg(PortalBusPath, DBusInstance.baseService().remove(QChar(':')).replace(QChar('.'), QChar('_')), AppConstants::ProductNameInternal);
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
