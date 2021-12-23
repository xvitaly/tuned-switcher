/**
 * SPDX-FileCopyrightText: 2021-2022 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/** @file lib/translationmanager/translationmanager.cpp
 * This file contains implementation of the TranslationManager class.
*/

#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QLibraryInfo>

#include "appconstants/appconstants.h"
#include "translationmanager/translationmanager.h"

QStringList TranslationManager::GetTranslationPaths() const
{
    return QStringList()
            << QDir::toNativeSeparators(QFileInfo(qApp -> applicationDirPath()).absoluteFilePath() + LocaleDirectory)
            << QDir::toNativeSeparators(AppConstants::DataRootPrefix + AppConstants::ProductNameInternal + LocaleDirectory)
            << QDir::toNativeSeparators(QStringLiteral("/usr/share/") + AppConstants::ProductNameInternal + LocaleDirectory);
}

QString TranslationManager::GetTranslationPath() const
{
    foreach (const QString &path, GetTranslationPaths())
    {
        if (QFile::exists(path)) return path;
    }
    return QString();
}

QTranslator* TranslationManager::GetQtTranslator() const
{
    return QtTranslator;
}

QTranslator* TranslationManager::GetAppTranslator() const
{
    return AppTranslator;
}

TranslationManager::TranslationManager(QObject *parent) : QObject(parent)
{
    QtTranslator = new QTranslator(this);
    QtTranslator -> load(QLocale(), QStringLiteral("qt"), QStringLiteral("_"), QLibraryInfo::path(QLibraryInfo::TranslationsPath));

    AppTranslator = new QTranslator(this);
    AppTranslator -> load(QLocale(), AppConstants::ProductNameInternal, QStringLiteral("_"), GetTranslationPath());
}
