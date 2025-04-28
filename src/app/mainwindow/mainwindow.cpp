/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file mainwindow/mainwindow.cpp
 * Contains the MainWindow class implementation.
*/

#include <QGraphicsDropShadowEffect>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QThread>
#include <QSettings>
#include <QWidget>
#include <QMainWindow>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QFlags>
#include <QStringLiteral>
#include <QString>
#include <QTimer>
#include <QIcon>

#include "appconstants/appconstants.h"
#include "mainwindow/mainwindow.h"
#include "notificationsmanager/notificationsmanager.h"
#include "tunedmanager/tunedmanager.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    loadSettings();
    setFormStyle();
    setFormEvents();
    initializeNotifications();
    initializeTuned();
    checkTunedRunning();
    getTunedProfiles();
    markCurrentProfile();
    markAutoProfileMode();
    subscribeToEvents();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete notifications;
    delete tunedManager;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (event -> button() == Qt::LeftButton)
    {
        mMoving = true;
        mLastMousePosition = event -> pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (event -> buttons().testFlag(Qt::LeftButton) && mMoving)
    {
        move(pos() + (event -> pos() - mLastMousePosition));
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event -> button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event -> key())
    {
        case Qt::Key_Escape:
            close();
            break;
        default:
            QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::initializeNotifications()
{
    notifications = new NotificationsManager(this);
}

void MainWindow::initializeTuned()
{
    tunedManager = new TunedManager(this);
}

void MainWindow::setFormEvents()
{
    connect(ui -> AutoSelect, SIGNAL(clicked(bool)), this, SLOT(profileAutoSelectedEvent(const bool)));
    connect(ui -> CloseForm, SIGNAL(clicked()), this, SLOT(closeFormEvent()));
    connect(ui -> ProfileSelector, SIGNAL(textActivated(QString)), this, SLOT(profileSelectedEvent(const QString&)));
}

void MainWindow::tryToStartTuned()
{
    if (tunedManager -> Start())
    {
        // Sleep to allow Tuned service to be initialized correctly.
        QThread::sleep(AppConstants::SleepTime);
    }
    else
    {
        QMessageBox::critical(this, AppConstants::ProductName, tr("Cannot start Tuned service via D-Bus call. Terminating."));
        exitApplication();
    }
}

void MainWindow::checkTunedRunning()
{
    if (!tunedManager -> IsRunning())
    {
        if (QMessageBox::question(this, AppConstants::ProductName, tr("Tuned service is not running. Do you want to start it now?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
            tryToStartTuned();
        else
            exitApplication();
    }
}

void MainWindow::getTunedProfiles()
{
    availableProfiles = tunedManager -> GetAvailableProfiles();
}

void MainWindow::subscribeToEvents()
{
    connect(tunedManager, SIGNAL(ProfileChangedSignal(const QString&, const bool, const QString&)), this, SLOT(profileChangedEvent(const QString&, const bool, const QString&)));
}

void MainWindow::loadSettings()
{
    QSettings settings;
    settings.beginGroup("widget");
    restoreGeometry(settings.value(QStringLiteral("geometry")).toByteArray());
    restoreState(settings.value(QStringLiteral("windowState")).toByteArray());
    settings.endGroup();
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.beginGroup("widget");
    settings.setValue(QStringLiteral("geometry"), saveGeometry());
    settings.setValue(QStringLiteral("windowState"), saveState());
    settings.endGroup();
    settings.sync();
}

void MainWindow::setFormStyle()
{
    // Setting form style...
    setWindowIcon(QIcon::fromTheme(AppConstants::DomainSchemeName, QIcon(QStringLiteral(":/icons/fallback.png"))));
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // Adding shadows for widgets...
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect -> setBlurRadius(9.0);
    shadowEffect -> setColor(QColor(0, 0, 0, 160));
    shadowEffect -> setOffset(4.0);
    ui -> WidgetMain -> setGraphicsEffect(shadowEffect);
}

void MainWindow::setAutoProfileMode(bool mode)
{
    ui -> AutoSelect -> setChecked(mode);
    ui -> AutoSelect -> setDisabled(mode);
}

void MainWindow::markCurrentProfile()
{
    if (availableProfiles.count() > 0)
    {
        ui -> ProfileSelector -> addItems(availableProfiles);
        ui -> ProfileSelector -> setCurrentText(tunedManager -> GetActiveProfile());
    }
}

void MainWindow::markAutoProfileMode()
{
    setAutoProfileMode(tunedManager -> IsProfileModeAuto());
}

void MainWindow::exitApplication()
{
    QTimer::singleShot(AppConstants::TimerDelay, qApp, SLOT(quit()));
}

void MainWindow::profileChangedEvent(const QString& profile, const bool result, const QString& message)
{
    if (result)
    {
        bool autoMode = tunedManager -> IsProfileModeAuto();
        if (ui -> ProfileSelector -> findText(profile) > 0)
        {
            ui -> ProfileSelector -> setCurrentText(profile);
            if (autoMode)
                notifications -> ShowNotification(tr("Profile auto-selected"), tr("The active profile was automatically switched to <b>%1</b>.").arg(profile));
            else
                notifications -> ShowNotification(tr("Profile switched"), tr("The active profile was switched to <b>%1</b>.").arg(profile));
        }
        setAutoProfileMode(autoMode);
    }
    else
    {
        notifications -> ShowNotification(tr("Profile switch error"), tr("Failed to switch the active profile: %1").arg(message));
    }
}

void MainWindow::profileSelectedEvent(const QString &profile)
{
    QTunedResult result = tunedManager -> SetActiveProfile(profile);
    if (!result.Success)
    {
        notifications -> ShowNotification(tr("Profile switch error"), tr("Failed to switch the active profile: %1").arg(result.Message));
    }
}

void MainWindow::closeFormEvent()
{
    close();
}

void MainWindow::profileAutoSelectedEvent(const bool modeAuto)
{
    if (modeAuto)
    {
        QTunedResult result = tunedManager -> SetProfileModeAuto();
        if (!result.Success)
        {
            setAutoProfileMode(false);
            notifications -> ShowNotification(tr("Profile auto-selection error"), tr("Failed to enable profile auto-selection: %1").arg(result.Message));
        }
    }
}
