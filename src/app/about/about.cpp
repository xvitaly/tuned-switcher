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
#include <QIcon>
#include <QPixmap>
#include <QPoint>
#include <QScreen>
#include <QSize>
#include <QString>
#include <QStringLiteral>
#include <QWidget>

#include "about/about.h"
#include "appconstants/appconstants.h"
#include "settingsmanager/settingsmanager.h"

#include "ui_about.h"

About::About(QWidget* parent) : QDialog(parent), ui(new Ui::About)
{
    ui -> setupUi(this);
    initializeSettings();
    loadFormSettings();
    setFormStyle();
    setFormControls();
    setFormEvents();
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
    else
        setDefaultFormPosition();
}

void About::saveFormSettings()
{
    if (settings -> GetGeometrySavingEnabled())
    {
        settings -> SetAboutGeometry(saveGeometry());
        settings -> Save();
    }
}

void About::setDefaultFormPosition()
{
    move(screen() -> availableGeometry().center() - frameGeometry().center());
}

void About::setFormStyle()
{
    setFixedSize(width(), height());
}

void About::setFormControls()
{
    QIcon AppIcon = QIcon::fromTheme(AppConstants::DomainSchemeName, QIcon(QStringLiteral(":/icons/fallback.png")));
    ui -> AppIcon -> setPixmap(AppIcon.pixmap(AppIcon.actualSize(QSize(128, 128))));
    ui -> AppName -> setText(AppConstants::ProductName);
    ui -> AppVersion -> setText(tr("Version: %1").arg(AppConstants::ProductVersion));
    ui -> AppDeveloper -> setText(AppConstants::ProductCompany);
}

void About::setFormEvents()
{
    connect(this, &QDialog::accepted, this, &About::formClosedEvent);
    connect(this, &QDialog::rejected, this, &About::formClosedEvent);
}

void About::formClosedEvent()
{
    saveFormSettings();
}
