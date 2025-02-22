/*
  processtracker_windows.h

  This file is part of GammaRay, the Qt application inspection and manipulation tool.

  SPDX-FileCopyrightText: 2016-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Filipe Azevedo <filipe.azevedo@kdab.com>

  SPDX-License-Identifier: GPL-2.0-or-later OR LicenseRef-KDAB-GammaRay

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.
*/

#ifndef GAMMARAY_PROCESSTRACKER_WINDOWS_H
#define GAMMARAY_PROCESSTRACKER_WINDOWS_H

#include "processtracker.h"

namespace GammaRay {

class GAMMARAY_CLIENT_EXPORT ProcessTrackerBackendWindows : public ProcessTrackerBackend
{
    Q_OBJECT

public:
    explicit ProcessTrackerBackendWindows(QObject *parent = nullptr);

public slots:
    void checkProcess(qint64 pid) override;
};

}

#endif // GAMMARAY_PROCESSTRACKER_WINDOWS_H
