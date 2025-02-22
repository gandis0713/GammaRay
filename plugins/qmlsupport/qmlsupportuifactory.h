/*
  qmlsupportuifactory.h

  This file is part of GammaRay, the Qt application inspection and manipulation tool.

  SPDX-FileCopyrightText: 2016-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Volker Krause <volker.krause@kdab.com>

  SPDX-License-Identifier: GPL-2.0-or-later OR LicenseRef-KDAB-GammaRay

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.
*/

#ifndef GAMMARAY_QMLSUPPORTUIFACTORY_H
#define GAMMARAY_QMLSUPPORTUIFACTORY_H

#include <ui/tooluifactory.h>

namespace GammaRay {
class QmlSupportUiFactory : public QObject, public ToolUiFactory
{
    Q_OBJECT
    Q_INTERFACES(GammaRay::ToolUiFactory)
    Q_PLUGIN_METADATA(IID "com.kdab.GammaRay.ToolUiFactory" FILE "gammaray_qmlsupport.json")
public:
    QString id() const override;
    void initUi() override;
    QWidget *createWidget(QWidget *) override;
};
}

#endif // GAMMARAY_QMLSUPPORTUIFACTORY_H
