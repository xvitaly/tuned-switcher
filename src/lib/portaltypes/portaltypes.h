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

/**
 * Structure for working with the portal request responses.
*/
struct QRequestResponse
{
    /**
     * Response code: 0 - success; 1 - cancelled; 2 - timeout.
    */
    unsigned int Code;

    /**
     * Results data.
    */
    QVariantMap Data;

    /**
     * Constructor of the QRequestResponse structure.
    */
    QRequestResponse() : Code(), Data() {}

    /**
     * Operator << of the QRequestResponse structure.
     * @param argument Instance of the QDBusArgument class.
     * @param profile Instance of the QRequestResponse class.
    */
    friend QDBusArgument& operator <<(QDBusArgument&, const QRequestResponse&);

    /**
     * Operator >> of the QRequestResponse structure.
     * @param argument Instance of the QDBusArgument class.
     * @param profile Instance of the QRequestResponse class.
    */
    friend const QDBusArgument& operator >>(const QDBusArgument&, QRequestResponse&);
};
Q_DECLARE_METATYPE(QRequestResponse)

#endif // PORTALTYPES_H
