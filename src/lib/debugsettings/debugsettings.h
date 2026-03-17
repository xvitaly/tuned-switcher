/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef DEBUGSETTINGS_H
#define DEBUGSETTINGS_H

/**
 * @file debugsettings/debugsettings.h
 * Contains the DebugSettings namespace definition.
*/

/**
 * Namespace with static methods for working with debug settings.
*/
namespace DebugSettings
{
    /**
     * Get whether the systemd integration is disabled.
     * @returns Whether the systemd integration is disabled.
    */
    bool IsSystemdIntegrationDisabled();
}

#endif // DEBUGSETTINGS_H
