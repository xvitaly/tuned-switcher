/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef LOGCATEGORIES_H
#define LOGCATEGORIES_H

/**
 * @file logcategories/logcategories.h
 * Contains the LogCategories namespace definition.
*/

#include <QLoggingCategory>

/**
 * Namespace with methods for working with custom
 * logging categories.
*/
namespace LogCategories
{
    /**
     * Get the logging category for DBus related messages.
    */
    Q_DECLARE_LOGGING_CATEGORY(DBus)
}

#endif // LOGCATEGORIES_H
