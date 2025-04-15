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
    initializeNotifications();
    initializeTuned();
    checkTunedRunning();
    getTunedProfiles();
    updateProfile();
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
    QSettings settings(AppConstants::ProductCompany, AppConstants::ProductNameInternal);
    settings.setValue(QStringLiteral("geometry"), saveGeometry());
    settings.setValue(QStringLiteral("windowState"), saveState());
    settings.sync();
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
    QSettings settings(AppConstants::ProductCompany, AppConstants::ProductNameInternal);
    restoreGeometry(settings.value(QStringLiteral("geometry")).toByteArray());
    restoreState(settings.value(QStringLiteral("windowState")).toByteArray());
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

void MainWindow::updateProfile()
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
    QTimer::singleShot(AppConstants::SleepTime, qApp, SLOT(quit()));
}

void MainWindow::profileChangedEvent(const QString& profile, const bool result, const QString& message)
{
    if (result)
    {
        if (ui -> ProfileSelector -> findText(profile) > 0)
        {
            ui -> ProfileSelector -> setCurrentText(profile);
            notifications -> ShowNotification(tr("Profile switched"), tr("The active profile was switched to <b>%1</b>.").arg(profile));
        }
        markAutoProfileMode();
    }
    else
    {
        notifications -> ShowNotification(tr("Profile switch error"), message);
    }
}

void MainWindow::on_ProfileSelector_textActivated(const QString &profile)
{
    QTunedResult result = tunedManager -> SetActiveProfile(profile);
    if (!result.Success)
    {
        notifications -> ShowNotification(tr("Profile switch error"), result.Message);
    }
}

void MainWindow::on_ButtonCancel_clicked()
{
    close();
}

void MainWindow::on_AutoSelect_clicked()
{
    if (ui -> AutoSelect -> isChecked())
    {
        QTunedResult result = tunedManager -> SetProfileModeAuto();
        if (!result.Success)
        {
            setAutoProfileMode(false);
            notifications -> ShowNotification(tr("Auto profile"), tr("Failed to enable profile auto-selection: %1").arg(result.Message));
        }
    }
}
