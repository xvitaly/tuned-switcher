/**
 * SPDX-FileCopyrightText: 2021 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H

#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QObject>
#include <QLibraryInfo>
#include <QTranslator>

class TranslationManager : public QObject
{
    Q_OBJECT
public:
    explicit TranslationManager(QObject *parent = nullptr);
    QTranslator* GetQtTranslator();
    QTranslator* GetAppTranslator();
private:
    QStringList GetTranslationPaths() const;
    QString GetTranslationPath() const;
    QTranslator* QtTranslator;
    QTranslator* AppTranslator;
    const QString AppName = QT_STRINGIFY(TS_PROJECT_NAME);
};

#endif // TRANSLATIONMANAGER_H
