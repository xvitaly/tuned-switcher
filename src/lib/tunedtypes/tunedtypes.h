#ifndef TUNEDTYPES_H
#define TUNEDTYPES_H

#include <QDBusReply>
#include <QObject>

struct QTunedProfile
{
    QString Name;
    QString Description;
    QTunedProfile() : Name(), Description() {}
    friend QDBusArgument &operator<<(QDBusArgument &argument, const QTunedProfile &arg);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, QTunedProfile &arg);
};
Q_DECLARE_METATYPE(QTunedProfile)

typedef QList<QTunedProfile> QTunedProfileList;
Q_DECLARE_METATYPE(QTunedProfileList)

struct QTunedProfileMode
{
    QString Mode;
    QString Reason;
    QTunedProfileMode() : Mode(), Reason() {}
    friend QDBusArgument &operator<<(QDBusArgument &argument, const QTunedProfileMode &arg);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, QTunedProfileMode &arg);
};
Q_DECLARE_METATYPE(QTunedProfileMode)

struct QTunedResult
{
    bool Success;
    QString Message;
    QTunedResult() : Success(false), Message() {}
    QTunedResult(bool success, QString message) : Success(success), Message(message) {}
    operator bool() { return Success; }
    friend QDBusArgument &operator<<(QDBusArgument &argument, const QTunedResult &arg);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, QTunedResult &arg);
};
Q_DECLARE_METATYPE(QTunedResult)

#endif // TUNEDTYPES_H
