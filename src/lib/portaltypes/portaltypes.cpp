/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file portaltypes/portaltypes.cpp
 * Contains implementations of special structures for working with portals.
*/

#include <QDBusArgument>

#include "portaltypes/portaltypes.h"

QDBusArgument& operator <<(QDBusArgument& argument, const QRequestResponse& response)
{
    argument.beginStructure();
    argument << response.Code;
    argument << response.Data;
    argument.endStructure();

    return argument;
}

const QDBusArgument& operator >>(const QDBusArgument& argument, QRequestResponse& response)
{
    argument.beginStructure();
    argument >> response.Code;
    argument >> response.Data;
    argument.endStructure();

    return argument;
}
