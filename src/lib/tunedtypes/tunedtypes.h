/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef TUNEDTYPES_H
#define TUNEDTYPES_H

/** @file lib/tunedtypes/tunedtypes.h
 * This file contains special structures for use in other classes.
*/

#include <QDBusArgument>
#include <QObject>

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
    */
    friend QDBusArgument &operator<<(QDBusArgument &argument, const QTunedProfile &arg);

    /**
     * Operator >> of the QTunedProfile structure.
    */
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, QTunedProfile &arg);
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
    */
    friend QDBusArgument &operator<<(QDBusArgument &argument, const QTunedProfileMode &arg);

    /**
     * Operator >> of the QTunedProfileMode structure.
    */
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, QTunedProfileMode &arg);
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
    */
    friend QDBusArgument &operator<<(QDBusArgument &argument, const QTunedResult &arg);

    /**
     * Operator >> of the QTunedResult structure.
    */
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, QTunedResult &arg);
};
Q_DECLARE_METATYPE(QTunedResult)

#endif // TUNEDTYPES_H
