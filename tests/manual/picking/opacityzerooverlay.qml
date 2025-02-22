/*
  opacityzerooverlay.qml

  This file is part of GammaRay, the Qt application inspection and manipulation tool.

  SPDX-FileCopyrightText: 2014-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Christoph <christoph.sterz@kdab.com>

  SPDX-License-Identifier: GPL-2.0-or-later OR LicenseRef-KDAB-GammaRay

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.
*/

import QtQuick 2.0


import QtQuick 2.0

Item {
  width: 100
  height: 100

  Rectangle{
      id: invisibleoverlay

      color:"#ffffffff"
      anchors.fill: parent
      opacity: 0

      Rectangle {
        id: visibleChildOfInvisibleParent

        color: "#ffff0000"
        anchors.fill: parent
        opacity: 1
      }
  }

  Rectangle {
    id: yellowrect

    color: "#ffffff00"
    anchors.centerIn: parent
    z: -40
    width: parent.width/2
    height: parent.height/2
  }
}
