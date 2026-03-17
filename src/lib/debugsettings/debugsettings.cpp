/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file debugsettings/debugsettings.cpp
 * Contains the DebugSettings namespace implementation.
*/

#include <QtGlobal>

#include "appconstants/appconstants.h"
#include "debugsettings/debugsettings.h"

bool DebugSettings::IsSystemdIntegrationDisabled()
{
    return qEnvironmentVariableIsSet(AppConstants::EnvNameSystemd());
}
