/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef LOGCATEGORIES_HPP
#define LOGCATEGORIES_HPP

/**
 * @file logcategories/logcategories.hpp
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

#endif // LOGCATEGORIES_HPP
