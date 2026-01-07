/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file about/about.cpp
 * Contains the About class implementation.
*/

#include <QByteArray>
#include <QDialog>
#include <QIcon>
#include <QPixmap>
#include <QSize>
#include <QString>
#include <QStringLiteral>
#include <QWidget>

#include "about/about.h"
#include "appconstants/appconstants.h"
#include "guihelpers/guihelpers.h"
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
        setSavedFormPosition();
    else
        setDefaultFormPosition();
}

void About::saveFormSettings()
{
    if (settings -> GetGeometrySavingEnabled())
        settings -> SetAboutGeometry(saveGeometry());
}

void About::setDefaultFormPosition()
{
    setGeometry(GuiHelpers::GetDefaultFormPosition(window()));
}

void About::setSavedFormPosition()
{
    const QByteArray savedGeometry = settings -> GetAboutGeometry();
    if (GuiHelpers::CheckGeometryValid(savedGeometry))
        restoreGeometry(savedGeometry);
    else
        setDefaultFormPosition();
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
    ui -> AppCopyright -> setText(AppConstants::ProductCopyright);
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
