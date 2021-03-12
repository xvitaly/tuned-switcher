/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef TRAYICON_H
#define TRAYICON_H

#include <QApplication>
#include <QActionGroup>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QThread>
#include <QWidget>

#include "tunedmanager/tunedmanager.h"

class TrayIcon : public QWidget
{
    Q_OBJECT
public:
    explicit TrayIcon(QWidget *parent = nullptr);
    ~TrayIcon();
    void Show();
private slots:
    void profileSelectedEvent(QAction*);
    void profileAutoSelectedEvent(bool);
    void profileChangedEvent(const QString&, const bool, const QString&);
    void exitEvent();
private:
    void initializeTuned();
    void tryToStartTuned();
    void checkTunedRunning();
    void setTrayIcon();
    void markCurrentProfile();
    void markAutoProfileMode();
    void subscribeToEvents();
    QMenu* createProfilesSubmenu();
    QMenu* createTrayIconMenu();
    QSystemTrayIcon *trayIcon;
    TunedManager *tunedManager;
    QHash<QString, QAction*> tunedProfiles;
    QAction* autoProfile;
};

#endif // TRAYICON_H
