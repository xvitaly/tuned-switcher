/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file about/about.cpp
 * Contains the About class implementation.
*/

#include <QDialog>
#include <QWidget>

#include "about/about.h"
#include "settingsmanager/settingsmanager.h"

#include "ui_about.h"

About::About(QWidget* parent) : QDialog(parent), ui(new Ui::About)
{
    ui -> setupUi(this);
    initializeSettings();
    loadFormSettings();
    setFormStyle();
}

About::~About()
{
    delete ui;
}

void About::initializeSettings()
{
    settings = new SettingsManager(this);
}

void About::loadFormSettings()
{
    if (settings -> GetGeometrySavingEnabled())
        restoreGeometry(settings -> GetAboutGeometry());
}

void About::saveFormSettings()
{
    if (settings -> GetGeometrySavingEnabled())
    {
        settings -> SetAboutGeometry(saveGeometry());
        settings -> Save();
    }
}

void About::setFormStyle()
{
    setFixedSize(width(), height());
}

void About::formClosedEvent()
{
    saveFormSettings();
}
