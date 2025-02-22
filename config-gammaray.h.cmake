/*
  config-gammaray.h.cmake

  This file is part of GammaRay, the Qt application inspection and manipulation tool.

  SPDX-FileCopyrightText: 2011-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: GPL-2.0-or-later OR LicenseRef-KDAB-GammaRay

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.
*/

#if !defined(CONFIG_GAMMARAY_H)
#define CONFIG_GAMMARAY_H

#cmakedefine GAMMARAY_INSTALL_QT_LAYOUT
#define GAMMARAY_DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}"

// relative install dirs
#define GAMMARAY_PLUGIN_INSTALL_DIR "${PLUGIN_INSTALL_DIR}"
#define GAMMARAY_LIBEXEC_INSTALL_DIR "${LIBEXEC_INSTALL_DIR}"
#define GAMMARAY_BUNDLE_INSTALL_DIR "${BUNDLE_INSTALL_DIR_PRIVATE}"
#define GAMMARAY_BIN_INSTALL_DIR "${BIN_INSTALL_DIR}"
#define GAMMARAY_PROBE_INSTALL_DIR "${PROBE_INSTALL_DIR}"
#define GAMMARAY_TRANSLATION_INSTALL_DIR "${TRANSLATION_INSTALL_DIR}"
#define GAMMARAY_QCH_INSTALL_DIR "${QCH_INSTALL_DIR}"
#define GAMMARAY_TARGET_PLUGIN_INSTALL_DIR "${TARGET_PLUGIN_INSTALL_DIR}"

#define GAMMARAY_PLUGIN_VERSION "${GAMMARAY_PLUGIN_VERSION}"
#define GAMMARAY_PROBE_ABI "${GAMMARAY_PROBE_ABI}${GAMMARAY_PROBE_ABI_POSTFIX}"

// relative inverse install dirs
#define GAMMARAY_INVERSE_BUNDLE_DIR "${GAMMARAY_INVERSE_BUNDLE_DIR}"
#define GAMMARAY_INVERSE_BIN_DIR "${GAMMARAY_INVERSE_BIN_DIR}"
#define GAMMARAY_INVERSE_LIB_DIR "${GAMMARAY_INVERSE_LIB_DIR}"
#define GAMMARAY_INVERSE_PROBE_DIR "${GAMMARAY_INVERSE_PROBE_DIR}"
#define GAMMARAY_INVERSE_LIBEXEC_DIR "${GAMMARAY_INVERSE_LIBEXEC_DIR}"

// probe name
#define GAMMARAY_PROBE_BASENAME "${PROBE_BASENAME}"

// library ABI suffix, as used with >= Qt 5.14 on Android
#define ANDROID_ABI "${ANDROID_ABI}"

// default network properties
#define GAMMARAY_DEFAULT_LOCAL_ADDRESS "127.0.0.1"
#define GAMMARAY_DEFAULT_LOCAL_TCP_URL "tcp://127.0.0.1"
#define GAMMARAY_DEFAULT_ANY_ADDRESS "0.0.0.0"
#define GAMMARAY_DEFAULT_ANY_TCP_URL "tcp://0.0.0.0"

// build options
#cmakedefine HAVE_STDINT_H
#cmakedefine HAVE_BACKTRACE
#cmakedefine HAVE_CXA_DEMANGLE

#cmakedefine HAVE_QT_WIDGETS
#cmakedefine HAVE_QT_SCXML
#cmakedefine HAVE_QT_SVG
#cmakedefine HAVE_QT_DESIGNER

#cmakedefine HAVE_SYNTAX_HIGHLIGHTING

#cmakedefine HAVE_ELF_H
#cmakedefine HAVE_SYS_ELF_H
#cmakedefine HAVE_ELF

#cmakedefine GAMMARAY_ENABLE_GPL_ONLY_FEATURES
#cmakedefine GAMMARAY_CORE_ONLY_LAUNCHER
#cmakedefine GAMMARAY_STATIC_PROBE
#cmakedefine GAMMARAY_DISABLE_FEEDBACK

#define QT_LIBINFIX "@QT_LIBINFIX@"

#endif // CONFIG_GAMMARAY_H
