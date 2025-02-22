/*
  widgetclientmodel.cpp

  This file is part of GammaRay, the Qt application inspection and manipulation tool.

  SPDX-FileCopyrightText: 2016-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Milian Wolff <milian.wolff@kdab.com>

  SPDX-License-Identifier: GPL-2.0-or-later OR LicenseRef-KDAB-GammaRay

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.
*/

#include "widgetclientmodel.h"
#include "widgetmodelroles.h"

#include <QApplication>
#include <QPalette>

using namespace GammaRay;

WidgetClientModel::WidgetClientModel(QObject *parent)
    : ClientDecorationIdentityProxyModel(parent)
{
}

WidgetClientModel::~WidgetClientModel() = default;

QVariant WidgetClientModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::ForegroundRole) {

        int flags = ClientDecorationIdentityProxyModel::data(index, WidgetModelRoles::WidgetFlags).value<int>();

        if (flags & WidgetModelRoles::Invisible)
            return qApp->palette().color(QPalette::Disabled, QPalette::Text);
    }
    return ClientDecorationIdentityProxyModel::data(index, role);
}
