#include "trayicon.h"

TrayIcon::TrayIcon(QWidget *parent) : QWidget(parent)
{
    initializeTuned();
    setTrayIcon();
    markCurrentProfile();
    subscribeToEvents();
}

TrayIcon::~TrayIcon()
{
    delete tunedManager;
}

void TrayIcon::initializeTuned()
{
    tunedManager = new TunedManager();
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
    trayIcon -> setToolTip(tr("Tuned profile switcher"));
}

void TrayIcon::subscribeToEvents()
{
    connect(tunedManager, SIGNAL(ProfileChangedSignal(const QString&, const bool, const QString&)), this, SLOT(profileChangedEvent(const QString&, const bool, const QString&)));
}

void TrayIcon::markCurrentProfile()
{
    QAction* profileAction = tunedProfiles[tunedManager -> GetActiveProfile()];
    if (profileAction) profileAction -> setChecked(true);
}

void TrayIcon::profileChangedEvent(const QString& profile, const bool result, const QString& message)
{
    if (result)
    {
        QAction* profileAction = tunedProfiles[profile];
        if (profileAction)
        {
            profileAction -> setChecked(true);
            trayIcon -> showMessage(tr("Profile switched"), QString(tr("The active profile was successfully switched to %1.")).arg(profile), QSystemTrayIcon::Information);
        }
    }
    else
    {
        trayIcon -> showMessage(tr("Profile switch error"), message, QSystemTrayIcon::Critical);
    }
}

QMenu* TrayIcon::createProfilesSubmenu()
{
    QMenu *trayIconProfiles = new QMenu(this);
    QActionGroup *trayIcontGroup = new QActionGroup(trayIconProfiles);
    const QStringList availableProfiles = tunedManager -> GetAvailableProfiles();

    trayIconProfiles -> setTitle(tr("Profiles"));
    trayIcontGroup -> setExclusive(true);

    for(int i = 0; i < availableProfiles.size(); i++)
    {
        QAction* profileAction = new QAction(availableProfiles[i], this);
        profileAction -> setData(availableProfiles[i]);
        profileAction -> setCheckable(true);
        trayIcontGroup -> addAction(profileAction);
        tunedProfiles.insert(availableProfiles[i], profileAction);
    }

    connect(trayIcontGroup, SIGNAL(triggered(QAction*)), this, SLOT(profileSelectedEvent(QAction*)));
    trayIconProfiles -> addActions(trayIcontGroup -> actions());
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
    autoProfile = new QAction(tr("Auto-select profile"), this);
    autoProfile -> setCheckable(true);
    autoProfile -> setChecked(tunedManager -> IsProfileModeAuto());
    if (autoProfile->isChecked())
        autoProfile->setDisabled(true);
    connect(autoProfile, SIGNAL(triggered(bool)), this, SLOT(profileAutoSelectedEvent(bool)));

    trayIconMenu -> addAction(autoProfile);
    trayIconMenu -> addSeparator();
    trayIconMenu -> addMenu(createProfilesSubmenu());
    trayIconMenu -> addSeparator();
    trayIconMenu -> addAction(quitAction);
    return trayIconMenu;
}

void TrayIcon::profileAutoSelectedEvent(bool modeAuto)
{
    if (modeAuto)
    {
        if (!tunedManager -> SetProfileModeAuto())
            trayIcon -> showMessage(tr("Auto profile"), tr("Failed to send the D-Bus event!"), QSystemTrayIcon::Critical);
        else
            autoProfile -> setDisabled(true);
    }
}

void TrayIcon::profileSelectedEvent(QAction* action)
{
    if (!tunedManager -> SetActiveProfile(action -> data().toString()))
        trayIcon -> showMessage(tr("Profile change"), tr("Failed to send the D-Bus event!"), QSystemTrayIcon::Critical);
    else
    {
        autoProfile -> setChecked(false);
        autoProfile -> setDisabled(false);
    }
}

void TrayIcon::exitEvent()
{
    QApplication::exit(0);
}
