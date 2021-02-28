#ifndef TRAYICON_H
#define TRAYICON_H

#include <QApplication>
#include <QActionGroup>
#include <QMenu>
#include <QSignalMapper>
#include <QSignalMapper>
#include <QSystemTrayIcon>
#include <QWidget>

#include "tunedmanager/tunedmanager.h"

class TrayIcon : public QWidget
{
    Q_OBJECT
public:
    explicit TrayIcon(QWidget *parent = nullptr);
    ~TrayIcon();
    void Show();
private slots:
    void profileSelectedEvent(QAction*);
    void profileChangedEvent(const QString&);
    void exitEvent();
private:
    void initializeTuned();
    void setTrayIcon();
    void markCurrentProfile();
    void subscribeToEvents();
    QMenu* createProfilesSubmenu();
    QMenu* createTrayIconMenu();
    QSystemTrayIcon *trayIcon;
    TunedManager *tunedManager;
    QHash<QString, QAction*> tunedProfiles;
signals:

};

#endif // TRAYICON_H
