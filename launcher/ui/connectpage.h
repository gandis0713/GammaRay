/*
  connectpage.h

  This file is part of GammaRay, the Qt application inspection and manipulation tool.

  SPDX-FileCopyrightText: 2013-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Volker Krause <volker.krause@kdab.com>

  SPDX-License-Identifier: GPL-2.0-or-later OR LicenseRef-KDAB-GammaRay

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.
*/

#ifndef GAMMARAY_CONNECTPAGE_H
#define GAMMARAY_CONNECTPAGE_H

#include "gammaray_launcher_ui_export.h"

#include <QWidget>
#include <QHostAddress>
#include <QToolButton>
#include <QHostInfo>
#include <QUrl>

class LauncherUiIPTest;
namespace GammaRay {
namespace Ui {
class ConnectPage;
}

/*! UI for connecting to a running GammaRay instance. */
class GAMMARAY_LAUNCHER_UI_EXPORT ConnectPage : public QWidget
{
    Q_OBJECT
    friend class ::LauncherUiIPTest;

public:
    explicit ConnectPage(QWidget *parent = nullptr);
    ~ConnectPage() override;

    bool isValid() const;
    void writeSettings();

    QUrl currentUrl() const;

public slots:
    void launchClient();

signals:
    void userInputParsed();
    void dnsResolved();
    void updateButtonState();
    void activate();

private slots:
    void instanceSelected();
    void hostResponse(const QHostInfo &hostInfo);
    void validateHostAddress(const QString &address);

private:
    void handleLocalAddress(QString &stillToParse, bool &correctSoFar);
    void handleIPAddress(QString &stillToParse, bool &correctSoFar);
    void handleHostName(QString &stillToParse);
    void handleAddressAndPort(QString &stillToParse, bool &correctSoFar, const QString &possibleAddress, bool skipPort = false);
    void handlePortString(QString &stillToParse, bool &correctSoFar);

    void showStandardPortAssumedWarning();
    void showFileIsNotSocketWarning();
    void clearWarnings();

    static const QString localPrefix;
    static const QString tcpPrefix;

    QScopedPointer<Ui::ConnectPage> ui;
    QUrl m_currentUrl;
    bool m_valid;
    QAction *m_implicitPortWarningSign;
    QAction *m_fileIsNotASocketWarning;
};
}

#endif // GAMMARAY_CONNECTPAGE_H
