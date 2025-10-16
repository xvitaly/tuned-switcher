/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef TUNEDTYPES_H
#define TUNEDTYPES_H

/**
 * @file tunedtypes/tunedtypes.h
 * Contains definitions of special structures for use in other classes.
*/

#include <QDBusArgument>
#include <QList>
#include <QMetaType>
#include <QObject>
#include <QString>

/**
 * Structure for working with a single Tuned profile entry.
*/
struct QTunedProfile
{
    /**
     * Tuned profile name.
    */
    QString Name;

    /**
     * Tuned profile description.
    */
    QString Description;

    /**
     * Constructor of the QTunedProfile structure.
    */
    QTunedProfile() : Name(), Description() {}

    /**
     * Operator << of the QTunedProfile structure.
     * @param argument Instance of the QDBusArgument class.
     * @param profile Instance of the QTunedProfile class.
    */
    friend QDBusArgument& operator <<(QDBusArgument&, const QTunedProfile&);

    /**
     * Operator >> of the QTunedProfile structure.
     * @param argument Instance of the QDBusArgument class.
     * @param profile Instance of the QTunedProfile class.
    */
    friend const QDBusArgument& operator >>(const QDBusArgument&, QTunedProfile&);
};
Q_DECLARE_METATYPE(QTunedProfile)

/**
 * List of the QTunedProfile elements.
*/
typedef QList<QTunedProfile> QTunedProfileList;
Q_DECLARE_METATYPE(QTunedProfileList)

/**
 * Structure for working Tuned profile modes.
*/
struct QTunedProfileMode
{
    /**
     * Tuned profile mode.
    */
    QString Mode;

    /**
     * Tuned profile mode switch reason.
    */
    QString Reason;

    /**
     * Constructor of the QTunedProfileMode structure.
    */
    QTunedProfileMode() : Mode(), Reason() {}

    /**
     * Operator << of the QTunedProfileMode structure.
     * @param argument Instance of the QDBusArgument class.
     * @param mode Instance of the QTunedProfileMode class.
    */
    friend QDBusArgument& operator <<(QDBusArgument&, const QTunedProfileMode&);

    /**
     * Operator >> of the QTunedProfileMode structure.
     * @param argument Instance of the QDBusArgument class.
     * @param mode Instance of the QTunedProfileMode class.
    */
    friend const QDBusArgument& operator >>(const QDBusArgument&, QTunedProfileMode&);
};
Q_DECLARE_METATYPE(QTunedProfileMode)

/**
 * Structure for working with the return values of the Tuned methods.
*/
struct QTunedResult
{
    /**
     * Method result.
    */
    bool Success;

    /**
     * Result message.
    */
    QString Message;

    /**
     * Constructor of the QTunedResult structure.
    */
    QTunedResult() : Success(false), Message() {}

    /**
     * Alternative constructor of the QTunedResult structure.
    */
    QTunedResult(bool success, QString message) : Success(success), Message(message) {}

    /**
     * QTunedResult check operator.
    */
    operator bool() const { return Success; }

    /**
     * Operator << of the QTunedResult structure.
     * @param argument Instance of the QDBusArgument class.
     * @param result Instance of the QTunedResult class.
    */
    friend QDBusArgument& operator <<(QDBusArgument&, const QTunedResult&);

    /**
     * Operator >> of the QTunedResult structure.
     * @param argument Instance of the QDBusArgument class.
     * @param result Instance of the QTunedResult class.
    */
    friend const QDBusArgument& operator >>(const QDBusArgument&, QTunedResult&);
};
Q_DECLARE_METATYPE(QTunedResult)

#endif // TUNEDTYPES_H
