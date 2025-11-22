/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file settings/settings.cpp
 * Contains the Settings class implementation.
*/

#include "settings/settings.h"

#include "ui_settings.h"

Settings::Settings(QWidget* parent) : QDialog(parent), ui(new Ui::Settings)
{
    ui -> setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}
