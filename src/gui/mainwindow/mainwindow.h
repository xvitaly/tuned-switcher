/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QLibraryInfo>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTranslator>
#include <QSettings>

#include "tunedmanager/tunedmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void closeEvent(QCloseEvent *event);
    void on_ButtonApply_clicked();
    void on_ButtonCancel_clicked();

private:
    void initializeTuned();
    void loadSettings();
    void setFormStyle();
    void updateProfile();
    Ui::MainWindow *ui;
    TunedManager *tunedManager;
    QStringList availableProfiles;
    QPoint mLastMousePosition;
    bool mMoving;
    const QString AppProductCompany = "EasyCoding";
    const QString AppProductNameInternal = "TunedSwitcher";
    const QString AppProductName = "Tuned Switcher";
};

#endif // MAINWINDOW_H
