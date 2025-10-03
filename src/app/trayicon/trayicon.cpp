/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file trayicon/trayicon.cpp
 * Contains the TrayIcon class implementation.
*/

#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QIcon>
#include <QMenu>
#include <QString>
#include <QStringLiteral>
#include <QSystemTrayIcon>
#include <QThread>
#include <QTimer>
#include <QWidget>

#include "appconstants/appconstants.h"
#include "notificationsmanager/notificationsmanager.h"
#include "settingsmanager/settingsmanager.h"
#include "trayicon/trayicon.h"
#include "tunedmanager/tunedmanager.h"
#include "tunedtypes/tunedtypes.h"

TrayIcon::TrayIcon(QWidget* parent) : QWidget(parent)
{
    initializeSettings();
    initializeNotifications();
    initializeTuned();
    checkTunedRunning();
    setTrayIcon();
    markCurrentProfile();
    markAutoProfileMode();
    subscribeToEvents();
}

void TrayIcon::initializeSettings()
{
    settings = new SettingsManager(this);
}

void TrayIcon::initializeNotifications()
{
    notifications = new NotificationsManager(this);
    notifications -> SetNotificationSoundMode(settings -> GetSoundEnabled());
}

void TrayIcon::initializeTuned()
{
    tunedManager = new TunedManager(this);
}

void TrayIcon::tryToStartTuned()
{
    if (tunedManager -> Start())
    {
        // Sleep to allow Tuned service to be initialized correctly.
        QThread::sleep(AppConstants::SleepTime);
    }
    else
    {
        notifications -> ShowNotification(tr("Startup error"), tr("Cannot start Tuned service via D-Bus call. Terminating."));
        exitApplication();
    }
}

void TrayIcon::checkTunedRunning()
{
    if (!(tunedManager -> IsOperational() && tunedManager -> IsRunning()))
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
    trayIcon -> setIcon(QIcon::fromTheme(AppConstants::DomainSchemeName, QIcon(QStringLiteral(":/icons/fallback.png"))));
    trayIcon -> setContextMenu(createTrayIconMenu());
    trayIcon -> setToolTip(AppConstants::ProductName);
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

void TrayIcon::setAutoProfileMode(const bool autoMode)
{
    QAction* autoProfile = tunedProfiles[autoProfileActionName];
    if (autoProfile)
    {
        autoProfile -> setChecked(autoMode);
        autoProfile -> setDisabled(autoMode);
    }
}

void TrayIcon::markAutoProfileMode()
{
    setAutoProfileMode(tunedManager -> IsProfileModeAuto());
}

void TrayIcon::exitApplication()
{
    QTimer::singleShot(AppConstants::TimerDelay, qApp, SLOT(quit()));
}

void TrayIcon::profileChangedEvent(const QString& profile, const bool result, const QString& message)
{
    if (result)
    {
        QAction* profileAction = tunedProfiles[profile];
        const bool autoMode = tunedManager -> IsProfileModeAuto();
        if (profileAction)
        {
            profileAction -> setChecked(true);
            if (autoMode)
                notifications -> ShowNotification(tr("Profile auto-selected"), tr("The active profile was automatically switched to <b>%1</b>.").arg(profile));
            else
                notifications -> ShowNotification(tr("Profile switched"), tr("The active profile was switched to <b>%1</b>.").arg(profile));
        }
        setAutoProfileMode(autoMode);
    }
    else
    {
        notifications -> ShowNotification(tr("Profile switch error"), message);
    }
}

QMenu* TrayIcon::createSettingsSubmenu(QWidget* parent)
{
    QMenu* trayIconSettings = new QMenu(parent);
    trayIconSettings -> setTitle(tr("Settings"));

    QAction* serviceAction = new QAction(tr("Enable profiles"), trayIconSettings);
    serviceAction -> setCheckable(true);
    serviceAction -> setChecked(tunedManager -> IsOperational());

    connect(serviceAction, SIGNAL(triggered(bool)), this, SLOT(serviceEnabledEvent(const bool)));
    trayIconSettings -> addAction(serviceAction);
    return trayIconSettings;
}

QMenu* TrayIcon::createProfilesSubmenu(QWidget* parent)
{
    QMenu* trayIconProfiles = new QMenu(parent);
    trayIconProfiles -> setTitle(tr("Active profile"));
    QActionGroup* trayIconGroup = new QActionGroup(trayIconProfiles);
    trayIconGroup -> setExclusive(true);

    for (const QString& profile : tunedManager -> GetAvailableProfiles())
    {
        QAction* profileAction = new QAction(profile, trayIconGroup);
        profileAction -> setData(profile);
        profileAction -> setCheckable(true);
        tunedProfiles.insert(profile, profileAction);
    }

    connect(trayIconGroup, SIGNAL(triggered(QAction*)), this, SLOT(profileSelectedEvent(QAction*)));
    trayIconProfiles -> addActions(trayIconGroup -> actions());
    return trayIconProfiles;
}

QMenu* TrayIcon::createTrayIconMenu()
{
    // Creating QMenu object...
    QMenu* trayIconMenu = new QMenu(this);

    // Setting actions and slots...
    QAction* quitAction = new QAction(tr("Quit"), trayIconMenu);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(exitEvent()));

    // Setting system tray's icon menu...
    QAction* autoProfile = new QAction(tr("Auto-select profile"), trayIconMenu);
    autoProfile -> setCheckable(true);
    tunedProfiles.insert(autoProfileActionName, autoProfile);
    connect(autoProfile, SIGNAL(triggered(bool)), this, SLOT(profileAutoSelectedEvent(const bool)));

    trayIconMenu -> addAction(autoProfile);
    trayIconMenu -> addSeparator();
    trayIconMenu -> addMenu(createSettingsSubmenu(trayIconMenu));
    trayIconMenu -> addMenu(createProfilesSubmenu(trayIconMenu));
    trayIconMenu -> addSeparator();
    trayIconMenu -> addAction(quitAction);
    return trayIconMenu;
}

void TrayIcon::profileAutoSelectedEvent(const bool autoMode)
{
    if (autoMode)
    {
        const QTunedResult result = tunedManager -> SetProfileModeAuto();
        if (!result.Success)
        {
            setAutoProfileMode(false);
            notifications -> ShowNotification(tr("Profile auto-selection error"), tr("Failed to enable profile auto-selection: %1").arg(result.Message));
        }
    }
}

void TrayIcon::profileSelectedEvent(QAction* action)
{
    const QTunedResult result = tunedManager -> SetActiveProfile(action -> data().toString());
    if (!result.Success)
    {
        notifications -> ShowNotification(tr("Profile switch error"), tr("Failed to switch the active profile: %1").arg(result.Message));
    }
}

void TrayIcon::serviceEnabledEvent(const bool mode)
{
    if (mode)
        tunedManager -> Enable();
    else
        tunedManager -> Disable();
}

void TrayIcon::exitEvent()
{
    qApp -> quit();
}
