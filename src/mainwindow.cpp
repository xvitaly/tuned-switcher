#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    initializeTuned();
    showTrayIcon();
    setFormStyle();
    updateProfile();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tunedManager;
}

void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    if (event -> type() == QEvent::WindowStateChange)
    {
        if (isMinimized()) hide();
    }
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

void MainWindow::initializeTuned()
{
    tunedManager = new TunedManager();
    availableProfiles = tunedManager -> GetAvailableProfiles();
}

void MainWindow::setFormStyle()
{
    // Setting form style...
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);

    // Adding shadows for widgets...
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect -> setBlurRadius(9.0);
    shadowEffect -> setColor(QColor(0, 0, 0, 160));
    shadowEffect -> setOffset(4.0);
    ui -> WidgetMain -> setGraphicsEffect(shadowEffect);
}

QMenu* MainWindow::createProfilesSubmenu()
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
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(profileSelected(int)));
    return trayIconProfiles;
}

QMenu* MainWindow::createTrayIconMenu()
{
    // Creating QMenu object...
    QMenu *trayIconMenu = new QMenu(this);

    // Setting actions and slots...
    QAction *showHideAction = new QAction(tr("Show/hide"), this);
    QAction *quitAction = new QAction(tr("Quit"), this);
    connect(showHideAction, SIGNAL(triggered()), this, SLOT(showHideEvent()));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Setting system tray's icon menu...
    trayIconMenu -> addMenu(createProfilesSubmenu());
    trayIconMenu -> addSeparator();
    trayIconMenu -> addAction(showHideAction);
    trayIconMenu -> addAction(quitAction);
    return trayIconMenu;
}

void MainWindow::trayActionExecute()
{
    toggleForm();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            trayActionExecute();
            break;
        default:
            break;
    }
}

void MainWindow::profileSelected(int index)
{
    setProfile(availableProfiles[index]);
    ui -> ProfileSelector -> setCurrentText(availableProfiles[index]);
}

void MainWindow::toggleForm()
{
    if (isHidden()) showNormal(); else hide();
}

void MainWindow::showHideEvent()
{
    toggleForm();
}

void MainWindow::showTrayIcon()
{
    // Setting tray icon...
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/images/icon-48.png");
    trayIcon -> setIcon(trayImage);
    trayIcon -> setContextMenu(createTrayIconMenu());

    // Connecting actions to our icon...
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    // Showing icon...
    trayIcon -> show();
}

void MainWindow::updateProfile()
{
    ui -> ProfileSelector -> addItems(availableProfiles);
    ui -> ProfileSelector -> setCurrentText(tunedManager -> GetActiveProfile());
}

void MainWindow::setProfile(QString name)
{
    if (tunedManager -> SetActiveProfile(name))
    {
        QMessageBox::information(this, "Tuned Switcher", tr("Successfully switched profile!"));
    }
    else
    {
        QMessageBox::warning(this, "Tuned Switcher", tr("Failed to set the required profile!"));
    }
}

void MainWindow::on_ButtonApply_clicked()
{
    setProfile(ui -> ProfileSelector -> currentText());
}

void MainWindow::on_ButtonCancel_clicked()
{
    close();
}
