/**
 * SPDX-FileCopyrightText: 2021-2025 EasyCoding Team and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <QWidget>

#include "about/about.h"

#include "ui_about.h"

About::About(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}
