/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file mainwindow/mainwindow.cpp
 * Contains the MainWindow class implementation.
*/

#include <QAction>
#include <QApplication>
#include <QByteArray>
#include <QCheckBox>
#include <QCloseEvent>
#include <QComboBox>
#include <QDialog>
#include <QFlags>
#include <QGraphicsDropShadowEffect>
#include <QKeyEvent>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPushButton>
#include <QSettings>
#include <QString>
#include <QStringLiteral>
#include <QThread>
#include <QTimer>
#include <QWidget>

#include "about/about.h"
#include "appconstants/appconstants.h"
#include "guihelpers/guihelpers.h"
#include "mainwindow/mainwindow.h"
#include "notificationsmanager/notificationsmanager.h"
#include "servicemanager/servicemanager.h"
#include "settings/settings.h"
#include "settingsmanager/settingsmanager.h"
#include "tunedmanager/tunedmanager.h"
#include "tunedtypes/tunedtypes.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent), ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    initializeSettings();
    loadFormSettings();
    setFormStyle();
    setFormControls();
    setFormEvents();
    initializeNotifications();
    setNotificationsMode();
    initializeService();
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

void MainWindow::closeEvent(QCloseEvent* event)
{
    saveFormSettings();
    QWidget::closeEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event -> key())
    {
        case Qt::Key_Escape:
            close();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void MainWindow::initializeSettings()
{
    settings = new SettingsManager(this);
}

void MainWindow::initializeNotifications()
{
    notifications = new NotificationsManager(this);
}

void MainWindow::initializeService()
{
    serviceManager = new ServiceManager(this);
}

void MainWindow::initializeTuned()
{
    tunedManager = new TunedManager(this);
}

void MainWindow::setFormEvents()
{
    connect(ui -> AutoSelect, &QCheckBox::clicked, this, &MainWindow::profileAutoSelectedEvent);
    connect(ui -> CloseForm, &QPushButton::clicked, this, &MainWindow::closeFormEvent);
    connect(ui -> ProfileSelector, &QComboBox::textActivated, this, &MainWindow::profileSelectedEvent);
}

void MainWindow::tryToStartTuned()
{
    if (serviceManager -> Start())
    {
        // Sleep to allow Tuned service to be initialized correctly.
        QThread::sleep(AppConstants::SleepTime());
    }
    else
    {
        QMessageBox::critical(this, tr("Startup error"), tr("Cannot start Tuned service via D-Bus call. Terminating."));
        exitApplication();
    }
}

void MainWindow::checkTunedRunning()
{
    if (!(tunedManager -> IsOperational() || serviceManager -> IsRunning()))
    {
        if (QMessageBox::question(this, AppConstants::ProductName(), tr("Tuned service is not running. Do you want to start it now?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
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
    connect(tunedManager, &TunedManager::ProfileChangedSignal, this, &MainWindow::profileChangedEvent);
}

void MainWindow::loadFormSettings()
{
    if (settings -> GetGeometrySavingEnabled())
        setSavedFormPosition();
    else
        setDefaultFormPosition();
}

void MainWindow::saveFormSettings()
{
    if (settings -> GetGeometrySavingEnabled())
        settings -> SetWidgetGeometry(saveGeometry());
}

QMenu* MainWindow::createServiceControlSubmenu(QWidget* parent)
{
    QMenu* serviceControlMenu = new QMenu(parent);
    serviceControlMenu -> setTitle(tr("Service control"));

    QAction* enableAction = new QAction(tr("Enable the service"), serviceControlMenu);
    connect(enableAction, &QAction::triggered, this, [this](){ serviceControlEvent(TunedManager::ServiceMethod::MethodEnable); });
    serviceControlMenu -> addAction(enableAction);

    QAction* disableAction = new QAction(tr("Disable the service"), serviceControlMenu);
    connect(disableAction, &QAction::triggered, this, [this](){ serviceControlEvent(TunedManager::ServiceMethod::MethodDisable); });
    serviceControlMenu -> addAction(disableAction);

    QAction* reloadAction = new QAction(tr("Reload the service"), serviceControlMenu);
    connect(reloadAction, &QAction::triggered, this, [this](){ serviceControlEvent(TunedManager::ServiceMethod::MethodReload); });
    serviceControlMenu -> addAction(reloadAction);

    QAction* shutdownAction = new QAction(tr("Shut down the service"), serviceControlMenu);
    connect(shutdownAction, &QAction::triggered, this, [this](){ serviceControlEvent(TunedManager::ServiceMethod::MethodShutdown); });
    serviceControlMenu -> addAction(shutdownAction);

    return serviceControlMenu;
}

QMenu* MainWindow::createMainMenu(QWidget* parent)
{
    QMenu* mainMenu = new QMenu(parent);
    mainMenu -> addMenu(createServiceControlSubmenu(mainMenu));

    QAction* settingsAction = new QAction(tr("Settings"), mainMenu);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::showSettingsEvent);
    mainMenu -> addAction(settingsAction);

    QAction* aboutAction = new QAction(tr("About"), mainMenu);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutEvent);
    mainMenu -> addAction(aboutAction);

    return mainMenu;
}

void MainWindow::setDefaultFormPosition()
{
    setGeometry(GuiHelpers::GetDefaultFormPosition(window()));
}

void MainWindow::setSavedFormPosition()
{
    const QByteArray savedGeometry = settings -> GetWidgetGeometry();
    if (GuiHelpers::CheckGeometryValid(savedGeometry))
        restoreGeometry(savedGeometry);
    else
        setDefaultFormPosition();
}

void MainWindow::setFormStyle()
{
    // Setting form style...
    setWindowIcon(GuiHelpers::GetApplicationIcon());
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // Adding shadows for widgets...
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(ui -> MainWidget);
    shadowEffect -> setBlurRadius(9.0);
    shadowEffect -> setColor(QColor(0, 0, 0, 160));
    shadowEffect -> setOffset(4.0);
    ui -> MainWidget -> setGraphicsEffect(shadowEffect);
}

void MainWindow::setFormControls()
{
    ui -> Advanced -> setMenu(createMainMenu(ui -> Advanced));
}

void MainWindow::setAutoProfileMode(const bool autoMode)
{
    ui -> AutoSelect -> setChecked(autoMode);
    ui -> AutoSelect -> setDisabled(autoMode);
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

void MainWindow::setNotificationsMode()
{
    notifications -> SetNotificationSoundMode(settings -> GetSoundEnabled());
}

void MainWindow::serviceControlEvent(const TunedManager::ServiceMethod method)
{
    if (tunedManager -> RunServiceMethod(method))
        notifications -> ShowNotification(tr("Service control"), tr("The requested service control operation completed successfully."));
    else
        notifications -> ShowNotification(tr("Service control error"), tr("Failed to perform the requested service control operation! Current settings remain unchanged."));
}

void MainWindow::exitApplication()
{
    QTimer::singleShot(AppConstants::TimerDelay(), qApp, &QApplication::quit);
}

void MainWindow::profileChangedEvent(const QString& profile, const bool result, const QString& message)
{
    if (result)
    {
        const bool autoMode = tunedManager -> IsProfileModeAuto();
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

void MainWindow::profileSelectedEvent(const QString& profile)
{
    const QTunedResult result = tunedManager -> SetActiveProfile(profile);
    if (!result.Success)
    {
        notifications -> ShowNotification(tr("Profile switch error"), tr("Failed to switch the active profile: %1").arg(result.Message));
    }
}

void MainWindow::closeFormEvent()
{
    close();
}

void MainWindow::profileAutoSelectedEvent(const bool autoMode)
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

void MainWindow::showSettingsEvent()
{
    Settings* settingsForm = new Settings(this);
    if (settingsForm -> exec() == QDialog::Accepted)
    {
        setNotificationsMode();
        notifications -> ShowNotification(tr("Settings saved"), tr("The application settings have been saved successfully!"));
    }
}

void MainWindow::showAboutEvent()
{
    About* aboutForm = new About(this);
    aboutForm -> exec();
}
