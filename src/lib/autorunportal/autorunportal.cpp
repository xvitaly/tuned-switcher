/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file autorunportal/autorunportal.cpp
 * Contains the AutorunPortal class implementation.
*/

#include <QEventLoop>
#include <QObject>
#include <QTimer>

#include "autorunportal/autorunportal.h"
#include "portalrequest/portalrequest.h"

AutorunPortal::AutorunPortal(QObject* parent) : AutorunManager(parent)
{
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
    return false;
}

bool AutorunPortal::Disable() const
{
    return false;
}

bool AutorunPortal::ChangeAutorunState(const bool value, const PortalRequest::BackgroundResult result) const
{
    PortalRequest portal;
    if (!portal.RequestBackground(value))
        return false;
    QEventLoop loop;
    connect(&portal, &PortalRequest::finished, &loop, &QEventLoop::quit);
    loop.exec();
    return portal.GetResult() == result;
}
