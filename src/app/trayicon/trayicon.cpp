/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/** @file app/trayicon/trayicon.cpp
 * This file contains implementation of the TrayIcon class.
*/

#include "trayicon.h"

TrayIcon::TrayIcon(QWidget *parent) : QWidget(parent)
{
    initializeNotifications();
    initializeTuned();
    checkTunedRunning();
    setTrayIcon();
    markCurrentProfile();
    markAutoProfileMode();
    subscribeToEvents();
}

TrayIcon::~TrayIcon()
{
    delete notifications;
    delete tunedManager;
}

void TrayIcon::initializeNotifications()
{
    notifications = new NotificationsManager(this);
}

void TrayIcon::initializeTuned()
{
    tunedManager = new TunedManager(this);
}

void TrayIcon::tryToStartTuned()
{
    if (tunedManager -> StartTuned())
        QThread::sleep(AppConstants::SleepTime);
    else
        exit(EXIT_FAILURE);
}

void TrayIcon::checkTunedRunning()
{
    if (!tunedManager -> IsTunedRunning())
        tryToStartTuned();
}

void TrayIcon::Show()
{
    // Showing icon...
    trayIcon -> show();
}

void TrayIcon::setTrayIcon()
{
    // Setting tray icon...
    trayIcon = new QSystemTrayIcon(this);
    trayIcon -> setIcon(QIcon::fromTheme(AppConstants::DomainSchemeName, QIcon(":/icons/fallback.png")));
    trayIcon -> setContextMenu(createTrayIconMenu());
    trayIcon -> setToolTip(tr("Tuned profile switcher"));
}

void TrayIcon::subscribeToEvents()
{
    connect(tunedManager, SIGNAL(ProfileChangedSignal(const QString&, const bool, const QString&)), this, SLOT(profileChangedEvent(const QString&, const bool, const QString&)));
}

void TrayIcon::markCurrentProfile()
{
    QAction* profileAction = tunedProfiles[tunedManager -> GetActiveProfile()];
    if (profileAction) profileAction -> setChecked(true);
}

void TrayIcon::markAutoProfileMode()
{
    bool modeAuto = tunedManager -> IsProfileModeAuto();
    autoProfile -> setChecked(modeAuto);
    if (modeAuto) autoProfile -> setDisabled(true);
}

void TrayIcon::profileChangedEvent(const QString& profile, const bool result, const QString& message)
{
    if (result)
    {
        QAction* profileAction = tunedProfiles[profile];
        if (profileAction)
        {
            profileAction -> setChecked(true);
            trayIcon -> showMessage(tr("Profile switched"), tr("The active profile was switched to %1.").arg(profile), QSystemTrayIcon::Information);
        }
    }
    else
    {
        trayIcon -> showMessage(tr("Profile switch error"), message, QSystemTrayIcon::Critical);
    }
}

QMenu* TrayIcon::createProfilesSubmenu()
{
    QMenu *trayIconProfiles = new QMenu(this);
    QActionGroup *trayIcontGroup = new QActionGroup(trayIconProfiles);
    const QStringList availableProfiles = tunedManager -> GetAvailableProfiles();

    trayIconProfiles -> setTitle(tr("Profiles"));
    trayIcontGroup -> setExclusive(true);

    for(int i = 0; i < availableProfiles.size(); i++)
    {
        QAction* profileAction = new QAction(availableProfiles[i], this);
        profileAction -> setData(availableProfiles[i]);
        profileAction -> setCheckable(true);
        trayIcontGroup -> addAction(profileAction);
        tunedProfiles.insert(availableProfiles[i], profileAction);
    }

    connect(trayIcontGroup, SIGNAL(triggered(QAction*)), this, SLOT(profileSelectedEvent(QAction*)));
    trayIconProfiles -> addActions(trayIcontGroup -> actions());
    return trayIconProfiles;
}

QMenu* TrayIcon::createTrayIconMenu()
{
    // Creating QMenu object...
    QMenu *trayIconMenu = new QMenu(this);

    // Setting actions and slots...
    QAction *quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(exitEvent()));

    // Setting system tray's icon menu...
    autoProfile = new QAction(tr("Auto-select profile"), this);
    autoProfile -> setCheckable(true);
    connect(autoProfile, SIGNAL(triggered(bool)), this, SLOT(profileAutoSelectedEvent(bool)));

    trayIconMenu -> addAction(autoProfile);
    trayIconMenu -> addSeparator();
    trayIconMenu -> addMenu(createProfilesSubmenu());
    trayIconMenu -> addSeparator();
    trayIconMenu -> addAction(quitAction);
    return trayIconMenu;
}

void TrayIcon::profileAutoSelectedEvent(bool modeAuto)
{
    if (modeAuto)
    {
        QTunedResult result = tunedManager -> SetProfileModeAuto();
        if (result.Success)
            autoProfile -> setDisabled(true);
        else
            trayIcon -> showMessage(tr("Auto profile"), tr("Failed set auto-select profile: %1").arg(result.Message), QSystemTrayIcon::Critical);
    }
}

void TrayIcon::profileSelectedEvent(QAction* action)
{
    QTunedResult result = tunedManager -> SetActiveProfile(action -> data().toString());
    if (result.Success)
    {
        autoProfile -> setChecked(false);
        autoProfile -> setDisabled(false);
    }
    else
    {
        trayIcon -> showMessage(tr("Switch profile"), tr("Failed to switch profile: %1").arg(result.Message), QSystemTrayIcon::Critical);
    }
}

void TrayIcon::exitEvent()
{
    QApplication::exit(0);
}
