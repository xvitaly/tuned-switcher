/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file logmanager/logmanager.cpp
 * Contains the LogManager namespace implementation.
*/

#include <QLoggingCategory>

#include "logmanager/logmanager.h"

namespace LogManager
{
    Q_LOGGING_CATEGORY(DBus, "tuned-switcher.dbus")
}
