/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file translationmanager/translationmanager.cpp
 * Contains the TranslationManager class implementation.
*/

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QLibraryInfo>
#include <QLocale>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QStringLiteral>
#include <QTranslator>

#include "appconstants/appconstants.h"
#include "translationmanager/translationmanager.h"

QStringList TranslationManager::GetTranslationPaths() const
{
    return QStringList()
            << QDir::toNativeSeparators(QFileInfo(qApp -> applicationDirPath()).absoluteFilePath() + LocaleDirectory)
            << QDir::toNativeSeparators(AppConstants::DataRootPrefix() + AppConstants::ProductNameInternal() + LocaleDirectory)
            << QDir::toNativeSeparators(QStringLiteral("/usr/share/") + AppConstants::ProductNameInternal() + LocaleDirectory);
}

QString TranslationManager::GetTranslationPath() const
{
    for (const QString& path : GetTranslationPaths())
    {
        if (QFile::exists(path)) return path;
    }
    return QString();
}

QString TranslationManager::GetQtTranslationPath() const
{
    return QLibraryInfo::path(QLibraryInfo::TranslationsPath);
}

QTranslator* TranslationManager::GetQtTranslator() const
{
    return QtTranslator;
}

QTranslator* TranslationManager::GetAppTranslator() const
{
    return AppTranslator;
}

QTranslator* TranslationManager::CreateQtTranslator()
{
    QTranslator* Translator = new QTranslator(this);
    return Translator -> load(QLocale(), QStringLiteral("qt"), QStringLiteral("_"), GetQtTranslationPath()) ? Translator : nullptr;
}

QTranslator* TranslationManager::CreateAppTranslator()
{
    QTranslator* Translator = new QTranslator(this);
    return Translator -> load(QLocale(), AppConstants::ProductNameInternal(), QStringLiteral("_"), GetTranslationPath()) ? Translator : nullptr;
}

bool TranslationManager::IsQtTranslatorAvailable() const
{
    return QtTranslator;
}

bool TranslationManager::IsAppTranslatorAvailable() const
{
    return AppTranslator;
}

TranslationManager::TranslationManager(QObject* parent) : QObject(parent)
{
    QtTranslator = CreateQtTranslator();
    AppTranslator = CreateAppTranslator();
}
