/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/** @file app/mainwindow/mainwindow.cpp
 * This file contains implementation of the MainWindow class.
*/

#include "mainwindow.h"
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
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
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
    if (tunedManager -> StartTuned())
    {
        // Sleep to allow Tuned service to be initialized correctly.
        QThread::sleep(AppConstants::SleepTime);
    }
    else
    {
        QMessageBox::critical(this, AppConstants::ProductName, tr("Cannot start Tuned service via D-Bus call. Terminating."));
        exit(EXIT_FAILURE);
    }
}

void MainWindow::checkTunedRunning()
{
    if (!tunedManager -> IsTunedRunning())
    {
        if (QMessageBox::question(this, AppConstants::ProductName, tr("Tuned service is not running. Do you want to start it now?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
            tryToStartTuned();
        else
            exit(EXIT_FAILURE);
    }
}

void MainWindow::getTunedProfiles()
{
    availableProfiles = tunedManager -> GetAvailableProfiles();
}

void MainWindow::loadSettings()
{
    QSettings settings(AppConstants::ProductCompany, AppConstants::ProductNameInternal);
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

void MainWindow::setFormStyle()
{
    // Setting form style...
    setWindowIcon(QIcon::fromTheme(AppConstants::DomainSchemeName, QIcon(":/icons/fallback.png")));
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // Adding shadows for widgets...
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect -> setBlurRadius(9.0);
    shadowEffect -> setColor(QColor(0, 0, 0, 160));
    shadowEffect -> setOffset(4.0);
    ui -> WidgetMain -> setGraphicsEffect(shadowEffect);
}

void MainWindow::updateProfile()
{
    if (availableProfiles.count() > 0)
    {
        ui -> ProfileSelector -> addItems(availableProfiles);
        ui -> ProfileSelector -> setCurrentText(tunedManager -> GetActiveProfile());
    }
}

void MainWindow::on_ProfileSelector_activated(const QString &profile)
{
    QTunedResult result = tunedManager -> SetActiveProfile(profile);
    if (result.Success)
        notifications -> ShowNotification(tr("Profile switched"), tr("The active profile was switched to <b>%1</b>.").arg(profile));
    else
        notifications -> ShowNotification(tr("Profile switch error"), result.Message);
}

void MainWindow::on_ButtonCancel_clicked()
{
    close();
}
