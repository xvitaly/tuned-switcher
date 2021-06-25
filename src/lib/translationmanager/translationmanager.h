/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H

/** @file translationmanager/translationmanager.h
 * This file contains TranslationManager class structure.
*/

#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QObject>
#include <QLibraryInfo>
#include <QTranslator>

#include "appconstants/appconstants.h"

/**
 * Class for working with localizations.
*/
class TranslationManager : public QObject
{
    Q_OBJECT
public:
    /**
     * Main constructor of the TranslationManager class.
     * @param parent Parent.
    */
    explicit TranslationManager(QObject *parent = nullptr);

    /**
     * Get Qt translator engine.
     * @returns Pointer to the Qt translation engine.
    */
    QTranslator* GetQtTranslator();

    /**
     * Get application translator engine.
     * @returns Pointer to the application translation engine.
    */
    QTranslator* GetAppTranslator();
private:
    /**
     * Get pre-defined list of directories with compiled
     * translation files.
     * @returns List of strings with localization directories.
    */
    QStringList GetTranslationPaths() const;

    /**
     * Get existing directory with compiled translation files.
     * @returns Full path to localization files or empty string.
    */
    QString GetTranslationPath() const;

    /**
     * Stores pointer to the Qt translator engine.
    */
    QTranslator* QtTranslator;

    /**
     * Stores pointer to the application translator engine.
    */
    QTranslator* AppTranslator;

    /**
     * Stores an internal translation directory name.
    */
    const QString LocaleDirectory = QStringLiteral("/translations");
};

#endif // TRANSLATIONMANAGER_H
