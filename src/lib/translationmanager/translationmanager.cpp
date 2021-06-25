/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/** @file translationmanager/translationmanager.cpp
 * This file contains implementation of the TranslationManager class.
*/

#include "translationmanager.h"

QStringList TranslationManager::GetTranslationPaths() const
{
    return QStringList()
            << QDir::toNativeSeparators(QFileInfo(qApp -> applicationDirPath()).absoluteFilePath() + LocaleDirectory)
            << QDir::toNativeSeparators(AppConstants::DataRootPrefix + AppConstants::ProductNameInternal + LocaleDirectory)
            << QDir::toNativeSeparators("/usr/share/" + AppConstants::ProductNameInternal + LocaleDirectory);
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
    AppTranslator -> load(QLocale(), AppConstants::ProductNameInternal, "_", GetTranslationPath());
}
