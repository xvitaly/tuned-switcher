#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QSignalMapper>
#include <QSystemTrayIcon>

#include "tunedmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private slots:
    void changeEvent(QEvent*);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void profileSelected(int);
    void showHideEvent();
    void on_ButtonApply_clicked();
    void on_ButtonCancel_clicked();

private:
    void initializeTuned();
    void trayActionExecute();
    void showTrayIcon();
    void setFormStyle();
    void updateProfile();
    void setProfile(QString);
    void toggleForm();
    QMenu* createProfilesSubmenu();
    QMenu* createTrayIconMenu();
    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon;
    TunedManager *tunedManager;
    QStringList availableProfiles;
    QPoint mLastMousePosition;
    bool mMoving;
};

#endif // MAINWINDOW_H
