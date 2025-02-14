# This file is part of GammaRay, the Qt application inspection and manipulation tool.
#
# SPDX-FileCopyrightText: 2016-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-or-later OR LicenseRef-KDAB-GammaRay
#
# Licensees holding valid commercial KDAB GammaRay licenses may use this file in
# accordance with GammaRay Commercial License Agreement provided with the Software.
#
# Contact info@kdab.com if any conditions of this licensing are not clear to you.
#
# probe plugin
if(NOT GAMMARAY_CLIENT_ONLY_BUILD)
    set(gammaray_network_srcs
        networksupport.cpp
        networksupportinterface.cpp
        networkinterfacemodel.cpp
        networkreplymodel.cpp
        cookies/cookieextension.cpp
        cookies/cookiejarmodel.cpp
    )
    if(TARGET Qt5::Network)
        list(APPEND gammaray_network_srcs networkconfigurationmodel.cpp)
    endif()
    gammaray_add_plugin(
        gammaray_network
        JSON
        gammaray_network.json
        SOURCES
        ${gammaray_network_srcs}
    )
    target_link_libraries(gammaray_network gammaray_core Qt::Network Qt::CorePrivate)
    set_target_properties(gammaray_network PROPERTIES DISABLE_PRECOMPILE_HEADERS ON)
endif()

# ui plugin
if(GAMMARAY_BUILD_UI)
    set(gammaray_network_ui_srcs
        networkwidget.cpp
        networkinterfacewidget.cpp
        networkconfigurationwidget.cpp
        clientnetworkconfigurationmodel.cpp
        networkreplywidget.cpp
        clientnetworkreplymodel.cpp
        networksupportinterface.cpp
        networksupportclient.cpp
        cookies/cookietab.cpp
    )
    gammaray_add_plugin(
        gammaray_network_ui
        JSON
        gammaray_network.json
        SOURCES
        ${gammaray_network_ui_srcs}
    )
    target_link_libraries(gammaray_network_ui gammaray_ui Qt::Network)
endif()
