/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file dummyservice/dummyservice.cpp
 * Contains the DummyService class implementation.
*/

#include <QLoggingCategory>
#include <QObject>

#include "dummyservice/dummyservice.h"
#include "logcategories/logcategories.h"

DummyService::DummyService(QObject* parent) : ServiceManager(parent)
{
}

bool DummyService::IsSupported() const
{
    return false;
}

bool DummyService::IsRunning() const
{
    qCWarning(LogCategories::Service) << "Failed to get the Tuned service state due to disabled service control feature!";
    return false;
}

bool DummyService::Start() const
{
    qCWarning(LogCategories::Service) << "Failed to start the Tuned service due to disabled service control feature!";
    return false;
}

bool DummyService::Stop() const
{
    qCWarning(LogCategories::Service) << "Failed to stop the Tuned service due to disabled service control feature!";
    return false;
}
