/**
 * SPDX-FileCopyrightText: 2021-2026 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

/**
 * @file translationmanager/translationmanager.cpp
 * Contains the TranslationManager class implementation.
*/

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QLibraryInfo>
#include <QList>
#include <QLocale>
#include <QObject>
#include <QString>
#include <QStringLiteral>
#include <QTranslator>

#include "appconstants/appconstants.h"
#include "translationmanager/translationmanager.h"

QList<QDir> TranslationManager::GetTranslationPaths() const
{
    return QList<QDir>()
           << QDir(QStringLiteral("%1/translations").arg(QCoreApplication::applicationDirPath()))
           << QDir(QStringLiteral("%1/%2/translations").arg(AppConstants::DataRootPrefix(), AppConstants::ProductNameInternal()))
           << QDir(QStringLiteral("/usr/share/%1/translations").arg(AppConstants::ProductNameInternal()));
}

QString TranslationManager::GetTranslationPath() const
{
    for (const QDir& path : GetTranslationPaths())
    {
        if (path.exists())
            return path.absolutePath();
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
