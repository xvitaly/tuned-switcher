/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef PORTALTYPES_H
#define PORTALTYPES_H

/**
 * @file portaltypes/portaltypes.h
 * Contains definitions of special structures for working with portals.
*/

#include <QDBusArgument>
#include <QMetaType>
#include <QObject>
#include <QVariantMap>

struct QRequestResponse
{
    unsigned int Code;
    QVariantMap Data;
    QRequestResponse() : Code(), Data() {}
    friend QDBusArgument& operator <<(QDBusArgument&, const QRequestResponse&);
    friend const QDBusArgument& operator >>(const QDBusArgument&, QRequestResponse&);
};
Q_DECLARE_METATYPE(QRequestResponse)

#endif // PORTALTYPES_H
