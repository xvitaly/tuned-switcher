/**
 * SPDX-FileCopyrightText: 2021-2023 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/** @file app/mainwindow/mainwindow.h
 * This file contains MainWindow class structure.
*/

#include <QMainWindow>

#include "notificationsmanager/notificationsmanager.h"
#include "tunedmanager/tunedmanager.h"

/**
 * UI namespace.
*/
namespace Ui
{
    /**
     * GUI application form elements.
    */
    class MainWindow;
}

/**
 * Class for working with the GUI application.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * Main constructor of the MainWindow class.
     * @param parent Parent widget.
    */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * Destructor of the MainWindow class.
    */
    ~MainWindow();

protected slots:
    /**
     * Mouse move event slot (handler).
     * @param event Event object instance.
    */
    void mouseMoveEvent(QMouseEvent*);

    /**
     * Mouse button press event slot (handler).
     * @param event Event object instance.
    */
    void mousePressEvent(QMouseEvent*);

    /**
     * Mouse button release event slot (handler).
     * @param event Event object instance.
    */
    void mouseReleaseEvent(QMouseEvent*);

    /**
     * Form close event slot (handler).
     * @param event Event object instance.
    */
    void closeEvent(QCloseEvent*);

    /**
     * Key pressed event slot (handler).
     * @param event Event object instance.
    */
    void keyPressEvent(QKeyEvent*);

private slots:
    /**
     * "Profile selected" event slot (handler).
    */
    void on_ProfileSelector_activated(const QString&);

    /**
     * Button "Cancel" clicked event slot (handler).
    */
    void on_ButtonCancel_clicked();

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
     * Get available Tuned profiles for internal usage.
    */
    void getTunedProfiles();

    /**
     * Load form settings: position and size.
    */
    void loadSettings();

    /**
     * Set custom form style: remove border, apply gradients, etc.
    */
    void setFormStyle();

    /**
     * Get the active Tuned profile and set it on form.
    */
    void updateProfile();

    /**
     * Stores the GUI application form instance.
    */
    Ui::MainWindow *ui;

    /**
     * Stores pointer to the NotificationsManager class instance.
    */
    NotificationsManager *notifications;

    /**
     * Stores pointer to the TunedManager class instance.
    */
    TunedManager *tunedManager;

    /**
     * Stores the list of available Tuned profiles.
    */
    QStringList availableProfiles;

    /**
     * Stores the last mouse position.
    */
    QPoint mLastMousePosition;

    /**
     * Stores the form moving state.
    */
    bool mMoving;
};

#endif // MAINWINDOW_H
