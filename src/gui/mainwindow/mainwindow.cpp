/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    initializeTuned();
    loadSettings();
    setFormStyle();
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
    QSettings settings(AppProductCompany, AppProductNameInternal);
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.sync();
    QMainWindow::closeEvent(event);
}

void MainWindow::initializeTuned()
{
    tunedManager = new TunedManager();
    availableProfiles = tunedManager -> GetAvailableProfiles();
}

void MainWindow::loadSettings()
{
    QSettings settings(AppProductCompany, AppProductNameInternal);
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
    else
    {
        QMessageBox::critical(this, AppProductName, tr("No profiles found! Please check if the Tuned service is running."));
        exit(EXIT_FAILURE);
    }
}

void MainWindow::on_ButtonApply_clicked()
{
    QString profile = ui -> ProfileSelector -> currentText();
    QTunedResult result = tunedManager -> SetActiveProfile(profile);
    if (result.Success)
        QMessageBox::information(this, AppProductName, tr("The active profile was switched to %1.").arg(profile));
    else
        QMessageBox::critical(this, AppProductName, tr("Failed to switch profile: %1").arg(result.Message));
}

void MainWindow::on_ButtonCancel_clicked()
{
    close();
}
