/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file logcategories/logcategories.cpp
 * Contains the LogCategories namespace implementation.
*/

#include <QLoggingCategory>

#include "appconstants/appconstants.h"
#include "logcategories/logcategories.h"

namespace LogCategories
{
    Q_LOGGING_CATEGORY(DBus, AppConstants::CategoryNameDbus)
}
