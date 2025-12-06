/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file settings/settings.cpp
 * Contains the Settings class implementation.
*/

#include <QDialog>

#include "settingsmanager/settingsmanager.h"
#include "settings/settings.h"

#include "ui_settings.h"

Settings::Settings(QWidget* parent) : QDialog(parent), ui(new Ui::Settings)
{
    ui -> setupUi(this);
    initializeSettings();
    loadSettings();
    setFormStyle();
    setFormEvents();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::initializeSettings()
{
    settings = new SettingsManager(this);
}

void Settings::loadSettings()
{
    ui -> SaveFormGeometry -> setChecked(settings -> GetWidgetGeometryEnabled());
    ui -> SaveFormState -> setChecked(settings -> GetWidgetStateEnabled());
    ui -> EnableSound -> setChecked(settings -> GetSoundEnabled());
}

void Settings::saveSettings()
{
    settings -> SetWidgetGeometryEnabled(ui -> SaveFormGeometry -> isChecked());
    settings -> SetWidgetStateEnabled(ui -> SaveFormState -> isChecked());
    settings -> SetSoundEnabled(ui -> EnableSound -> isChecked());
    settings -> Save();
}

void Settings::setFormStyle()
{
    setFixedSize(width(), height());
}

void Settings::setFormEvents()
{
    connect(this, &QDialog::accepted, this, &Settings::settingsAcceptedEvent);
    connect(this, &QDialog::rejected, this, &Settings::settingsRejectedEvent);
}

void Settings::settingsAcceptedEvent()
{
    saveSettings();
    this -> close();
}

void Settings::settingsRejectedEvent()
{
    this -> close();
}
