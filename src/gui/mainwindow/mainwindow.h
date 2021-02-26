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
    void on_ButtonApply_clicked();
    void on_ButtonCancel_clicked();

private:
    void initializeTuned();
    void setFormStyle();
    void updateProfile();
    Ui::MainWindow *ui;
    TunedManager *tunedManager;
    QStringList availableProfiles;
    QPoint mLastMousePosition;
    bool mMoving;
};

#endif // MAINWINDOW_H
