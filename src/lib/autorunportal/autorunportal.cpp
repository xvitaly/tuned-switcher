/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file autorunportal/autorunportal.cpp
 * Contains the AutorunPortal class implementation.
*/

#include <QObject>

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
