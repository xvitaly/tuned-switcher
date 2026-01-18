/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef AUTORUNFILE_H
#define AUTORUNFILE_H

/**
 * @file autorunfile/autorunfile.h
 * Contains the AutorunNative class definition.
*/

#include <QObject>

#include "autorunmanager/autorunmanager.h"

class AutorunFile : public AutorunManager
{
    Q_OBJECT
public:
    explicit AutorunFile(QObject* parent = nullptr);
};

#endif // AUTORUNFILE_H
