/*
  associativepropertyadaptor.h

  This file is part of GammaRay, the Qt application inspection and manipulation tool.

  SPDX-FileCopyrightText: 2015-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Volker Krause <volker.krause@kdab.com>

  SPDX-License-Identifier: GPL-2.0-or-later OR LicenseRef-KDAB-GammaRay

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.
*/

#ifndef GAMMARAY_ASSOCIATIVEPROPERTYADAPTOR_H
#define GAMMARAY_ASSOCIATIVEPROPERTYADAPTOR_H

#include "propertyadaptor.h"

#include <QVariant>

namespace GammaRay {
/** Adaptor for recursing into associative container property values. */
class AssociativePropertyAdaptor : public PropertyAdaptor
{
    Q_OBJECT
public:
    explicit AssociativePropertyAdaptor(QObject *parent = nullptr);
    ~AssociativePropertyAdaptor() override;

    int count() const override;
    PropertyData propertyData(int index) const override;

protected:
    void doSetObject(const ObjectInstance &oi) override;

private:
    QVariant m_value;
};
}

#endif // GAMMARAY_ASSOCIATIVEPROPERTYADAPTOR_H
