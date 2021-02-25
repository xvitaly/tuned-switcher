#ifndef TUNEDMANAGER_H
#define TUNEDMANAGER_H

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QObject>

class TunedManager : public QObject
{
    Q_OBJECT
public:
    explicit TunedManager(QObject *parent = nullptr);
    QString GetActiveProfile();
    QStringList GetAvailableProfiles();
    bool SetActiveProfile(QString);
private:
    const QString BusName = "com.redhat.tuned";
    const QString BusPath = "/Tuned";
    const QString BusInterface = "com.redhat.tuned.control";
    const QString BusProfileNameActive = "active_profile";
    const QString BusProfileNameAvailable = "profiles";
    const QString BusProfileNameSwitch = "switch_profile";
    const QDBusConnection DBusInstance = QDBusConnection::systemBus();

signals:

};

#endif // TUNEDMANAGER_H
