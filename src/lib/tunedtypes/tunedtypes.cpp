#include "tunedtypes.h"

QDBusArgument& operator <<(QDBusArgument& argument, const QTunedProfile& profile)
{
    argument.beginStructure();
    argument << profile.Name;
    argument << profile.Description;
    argument.endStructure();

    return argument;
}

const QDBusArgument& operator >>(const QDBusArgument& argument, QTunedProfile& profile)
{
    argument.beginStructure();
    argument >> profile.Name;
    argument >> profile.Description;
    argument.endStructure();

    return argument;
}
