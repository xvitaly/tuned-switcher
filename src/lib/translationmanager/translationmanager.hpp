/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef TRANSLATIONMANAGER_HPP
#define TRANSLATIONMANAGER_HPP

/**
 * @file translationmanager/translationmanager.hpp
 * Contains the TranslationManager class definition.
*/

#include <QObject>
#include <QString>
#include <QStringList>
#include <QStringLiteral>
#include <QTranslator>

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
    explicit TranslationManager(QObject* parent = nullptr);

    /**
     * Get Qt translator engine.
     * @returns Pointer to the Qt translation engine.
    */
    QTranslator* GetQtTranslator() const;

    /**
     * Get application translator engine.
     * @returns Pointer to the application translation engine.
    */
    QTranslator* GetAppTranslator() const;

    /**
     * Return information about the availability and readiness
     * of the Qt translator engine.
     * @returns Qt translator engine state.
    */
    bool IsQtTranslatorAvailable() const;

    /**
     * Return information about the availability and readiness
     * of the application translator engine.
     * @returns Application translator engine state.
    */
    bool IsAppTranslatorAvailable() const;
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
     * Get directory with compiled Qt translation files.
     * @returns Full path to compiled Qt translation files.
    */
    QString GetQtTranslationPath() const;

    /**
     * Create the Qt translator engine.
     * @returns Pointer to the Qt translation engine.
    */
    QTranslator* CreateQtTranslator();

    /**
     * Create the application translator engine.
     * @returns Pointer to the application translation engine.
    */
    QTranslator* CreateAppTranslator();

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

#endif // TRANSLATIONMANAGER_HPP
