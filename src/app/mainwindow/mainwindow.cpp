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
    initializeTuned();
    checkTunedRunning();
    getTunedProfiles();
    updateProfile();
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::initializeTuned()
{
    tunedManager = new TunedManager();
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

void MainWindow::on_ButtonApply_clicked()
{
    QString profile = ui -> ProfileSelector -> currentText();
    QTunedResult result = tunedManager -> SetActiveProfile(profile);
    if (result.Success)
        QMessageBox::information(this, AppConstants::ProductName, tr("The active profile was switched to %1.").arg(profile));
    else
        QMessageBox::critical(this, AppConstants::ProductName, tr("Failed to switch profile: %1").arg(result.Message));
}

void MainWindow::on_ButtonCancel_clicked()
{
    close();
}
