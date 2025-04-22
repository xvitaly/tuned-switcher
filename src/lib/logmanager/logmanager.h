/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef LOGMANAGER_H
#define LOGMANAGER_H

/**
 * @file logmanager/logmanager.h
 * Contains the LogManager namespace definition.
*/

#include <QLoggingCategory>

/**
 * Namespace with methods for working with custom
 * logging categories.
*/
namespace LogManager
{
    /**
     * Get the logging category for DBus related messages.
    */
    Q_DECLARE_LOGGING_CATEGORY(DBus)
}

#endif // LOGMANAGER_H
