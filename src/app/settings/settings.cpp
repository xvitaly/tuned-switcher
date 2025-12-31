/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file settings/settings.cpp
 * Contains the Settings class implementation.
*/

#include <QByteArray>
#include <QDialog>
#include <QWidget>

#include "guihelpers/guihelpers.h"
#include "settings/settings.h"
#include "settingsmanager/settingsmanager.h"

#include "ui_settings.h"

Settings::Settings(QWidget* parent) : QDialog(parent), ui(new Ui::Settings)
{
    ui -> setupUi(this);
    initializeSettings();
    loadFormSettings();
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

void Settings::loadFormSettings()
{
    if (settings -> GetGeometrySavingEnabled())
        setSavedFormPosition();
    else
        setDefaultFormPosition();
}

void Settings::loadSettings()
{
    ui -> SaveFormGeometry -> setChecked(settings -> GetGeometrySavingEnabled());
    ui -> SaveFormState -> setChecked(settings -> GetStateSavingEnabled());
    ui -> EnableSound -> setChecked(settings -> GetSoundEnabled());
}

void Settings::saveFormSettings()
{
    if (settings -> GetGeometrySavingEnabled())
    {
        settings -> SetSettingsGeometry(saveGeometry());
        settings -> Save();
    }
}

void Settings::saveSettings()
{
    settings -> SetGeometrySavingEnabled(ui -> SaveFormGeometry -> isChecked());
    settings -> SetStateSavingEnabled(ui -> SaveFormState -> isChecked());
    settings -> SetSoundEnabled(ui -> EnableSound -> isChecked());
    settings -> Save();
}

void Settings::setDefaultFormPosition()
{
    move(GuiHelpers::GetDefaultFormPosition(window()));
}

void Settings::setSavedFormPosition()
{
    const QByteArray savedGeometry = settings -> GetSettingsGeometry();
    if (GuiHelpers::CheckGeometryValid(savedGeometry))
        restoreGeometry(savedGeometry);
    else
        setDefaultFormPosition();
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
    saveFormSettings();
}

void Settings::settingsRejectedEvent()
{
    saveFormSettings();
}
