#include "trayicon.h"

TrayIcon::TrayIcon(QWidget *parent) : QWidget(parent)
{
    initializeTuned();
    setTrayIcon();
}

TrayIcon::~TrayIcon()
{
    delete tunedManager;
}

void TrayIcon::initializeTuned()
{
    tunedManager = new TunedManager();
    availableProfiles = tunedManager -> GetAvailableProfiles();
}

void TrayIcon::Show()
{
    // Showing icon...
    trayIcon -> show();
}

void TrayIcon::setTrayIcon()
{
    // Setting tray icon...
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/images/icon-48.png");
    trayIcon -> setIcon(trayImage);
    trayIcon -> setContextMenu(createTrayIconMenu());
}

QMenu* TrayIcon::createProfilesSubmenu()
{
    QMenu *trayIconProfiles = new QMenu(this);
    trayIconProfiles -> setTitle(tr("Profiles"));
    QSignalMapper *mapper = new QSignalMapper(this);
    for(int i=0; i < availableProfiles.size(); i++)
    {
        QAction* profileAction = new QAction(availableProfiles[i], this);
        trayIconProfiles -> addAction(profileAction);
        mapper -> setMapping(profileAction, i);
        connect(profileAction, SIGNAL(triggered()), mapper, SLOT(map()));
    }
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(profileSelectedEvent(int)));
    return trayIconProfiles;
}

QMenu* TrayIcon::createTrayIconMenu()
{
    // Creating QMenu object...
    QMenu *trayIconMenu = new QMenu(this);

    // Setting actions and slots...
    QAction *quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(exitEvent()));

    // Setting system tray's icon menu...
    trayIconMenu -> addMenu(createProfilesSubmenu());
    trayIconMenu -> addSeparator();
    trayIconMenu -> addAction(quitAction);
    return trayIconMenu;
}

void TrayIcon::profileSelectedEvent(int index)
{
    tunedManager -> SetActiveProfile(availableProfiles[index]);
}

void TrayIcon::exitEvent()
{
    QApplication::exit(0);
}
