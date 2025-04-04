/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file tunedtypes/tunedtypes.cpp
 * This file contains implementation of special structures
 * for use in other classes.
*/

#include "tunedtypes/tunedtypes.h"

QDBusArgument& operator <<(QDBusArgument& argument, const QTunedProfile& profile)
{
    argument.beginStructure();
    argument << profile.Name;
    argument << profile.Description;
    argument.endStructure();

    return argument;
}

const QDBusArgument& operator >>(const QDBusArgument& argument, QTunedProfile& profile)
{
    argument.beginStructure();
    argument >> profile.Name;
    argument >> profile.Description;
    argument.endStructure();

    return argument;
}

QDBusArgument& operator <<(QDBusArgument& argument, const QTunedProfileMode& mode)
{
    argument.beginStructure();
    argument << mode.Mode;
    argument << mode.Reason;
    argument.endStructure();

    return argument;
}

const QDBusArgument& operator >>(const QDBusArgument& argument, QTunedProfileMode& mode)
{
    argument.beginStructure();
    argument >> mode.Mode;
    argument >> mode.Reason;
    argument.endStructure();

    return argument;
}

QDBusArgument& operator <<(QDBusArgument& argument, const QTunedResult& result)
{
    argument.beginStructure();
    argument << result.Success;
    argument << result.Message;
    argument.endStructure();

    return argument;
}

const QDBusArgument& operator >>(const QDBusArgument& argument, QTunedResult& result)
{
    argument.beginStructure();
    argument >> result.Success;
    argument >> result.Message;
    argument.endStructure();

    return argument;
}
