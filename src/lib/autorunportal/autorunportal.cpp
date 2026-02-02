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
    return ChangeAutorunState(true, PortalRequest::BackgroundResult::Enabled);
}

bool AutorunPortal::Disable() const
{
    return ChangeAutorunState(false, PortalRequest::BackgroundResult::Disabled);
}

bool AutorunPortal::ChangeAutorunState(const bool value, const PortalRequest::BackgroundResult result) const
{
    PortalRequest portal;
    QEventLoop loop;
    QTimer timer;

    timer.setSingleShot(true);
    if (!portal.RequestBackground(value))
        return false;

    connect(&portal, &PortalRequest::finished, &loop, &QEventLoop::quit);
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);

    timer.start(10000);
    loop.exec();

    return timer.isActive() ? portal.GetResult() == result : false;
}
