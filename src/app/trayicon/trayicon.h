/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef TRAYICON_H
#define TRAYICON_H

/** @file app/trayicon/trayicon.h
 * This file contains TrayIcon class structure.
*/

#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>

#include "appconstants/appconstants.h"
#include "notificationsmanager/notificationsmanager.h"
#include "tunedmanager/tunedmanager.h"

/**
 * Class for working with the Applet application.
*/
class TrayIcon : public QWidget
{
    Q_OBJECT
public:
    /**
     * Main constructor of the TrayIcon class.
     * @param parent Parent widget.
    */
    explicit TrayIcon(QWidget *parent = nullptr);

    /**
     * Destructor of the TrayIcon class.
    */
    ~TrayIcon();

    /**
     * Show the system tray icon.
    */
    void Show();
private slots:
    /**
     * "Tuned profile selected" event slot (handler).
     * @param action System tray menu action, caused this event.
    */
    void profileSelectedEvent(QAction*);

    /**
     * "Tuned auto-profile selected" event slot (handler).
     * @param modeAuto Auto-mode on or off.
    */
    void profileAutoSelectedEvent(bool);

    /**
     * "Tuned profile changed" DBus event slot (handler).
     * @param profile Recently switched profile name.
     * @param result Switch result: true - success; false - failure.
     * @param message Result message (OK on success).
    */
    void profileChangedEvent(const QString&, const bool, const QString&);

    /**
     * "Exit application" event slot (handler).
    */
    void exitEvent();
private:
    /**
     * Initialize the NotificationsManager class instance.
    */
    void initializeNotifications();

    /**
     * Initialize the TunedManager class instance.
    */
    void initializeTuned();

    /**
     * Try to start the Tuned service if not running.
    */
    void tryToStartTuned();

    /**
     * Check if the Tuned service is not running and
     * try to start it with DBus methods.
    */
    void checkTunedRunning();

    /**
     * Create an instance of the QSystemTrayIcon and set
     * its properties.
    */
    void setTrayIcon();

    /**
     * Get the active Tuned profile and mark it.
    */
    void markCurrentProfile();

    /**
     * Check if the automatic mode is enabled and mark the
     * special checkbox.
    */
    void markAutoProfileMode();

    /**
     * Subscribe to DBus events.
    */
    void subscribeToEvents();

    /**
     * Build and create submenu with the list of available
     * Tuned profiles.
     * @returns Pointer to the QMenu instance.
    */
    QMenu* createProfilesSubmenu();

    /**
     * Build and create menu for the system tray icon.
     * @returns Pointer to the QMenu instance.
    */
    QMenu* createTrayIconMenu();

    /**
     * Stores pointer to the QSystemTrayIcon class instance.
    */
    QSystemTrayIcon *trayIcon;

    /**
     * Stores pointer to the NotificationsManager class instance.
    */
    NotificationsManager *notifications;

    /**
     * Stores pointer to the TunedManager class instance.
    */
    TunedManager *tunedManager;

    /**
     * Stores special hash table with the Tuned profiles and
     * assigned QMenu elements.
    */
    QHash<QString, QAction*> tunedProfiles;

    /**
     * Stores pointer to the "Auto-profile" system menu entry.
    */
    QAction* autoProfile;
};

#endif // TRAYICON_H
