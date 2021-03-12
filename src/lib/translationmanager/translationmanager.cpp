/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "translationmanager.h"

QStringList TranslationManager::GetTranslationPaths() const
{
    return QStringList()
            << QDir::toNativeSeparators(QFileInfo(qApp -> applicationDirPath()).absoluteFilePath() + "/translations")
            << QDir::toNativeSeparators(QString("%1/%2/translations").arg(QT_STRINGIFY(TS_DATAROOT_PREFIX), AppName))
            << QDir::toNativeSeparators("/usr/share/tuned-switcher/translations");
}

QString TranslationManager::GetTranslationPath() const
{
    foreach (const QString &path, GetTranslationPaths())
    {
        if (QFile::exists(path)) return path;
    }
    return QString();
}

QTranslator* TranslationManager::GetQtTranslator()
{
    return QtTranslator;
}

QTranslator* TranslationManager::GetAppTranslator()
{
    return AppTranslator;
}

TranslationManager::TranslationManager(QObject *parent) : QObject(parent)
{
    QtTranslator = new QTranslator(this);
    QtTranslator -> load(QLocale(), "qt", "_", QLibraryInfo::location(QLibraryInfo::TranslationsPath));

    AppTranslator = new QTranslator(this);
    AppTranslator -> load(QLocale(), AppName, "_", GetTranslationPath());
}
