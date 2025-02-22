/*
  enumutil.cpp

  This file is part of GammaRay, the Qt application inspection and manipulation tool.

  SPDX-FileCopyrightText: 2016-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Volker Krause <volker.krause@kdab.com>

  SPDX-License-Identifier: GPL-2.0-or-later OR LicenseRef-KDAB-GammaRay

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.
*/

#include "enumutil.h"
#include "enumrepositoryserver.h"

#include <QDebug>
#include <QMetaEnum>

using namespace GammaRay;

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
namespace GammaRay {
class ProtectedExposer : public QObject
{
public:
    using QObject::staticQtMetaObject;
};
}
#endif

static const QMetaObject *metaObjectForClass(const QByteArray &name)
{
    if (name.isEmpty())
        return nullptr;
    auto mo = QMetaType::metaObjectForType(QMetaType::type(name));
    if (mo)
        return mo;
    mo = QMetaType::metaObjectForType(QMetaType::type(name + '*')); // try pointer version, more likely for QObjects
    return mo;
}

QMetaEnum EnumUtil::metaEnum(const QVariant &value, const char *typeName, const QMetaObject *metaObject)
{
    QByteArray fullTypeName(typeName);
    if (fullTypeName.isEmpty())
        fullTypeName = value.typeName();

    // split class name and enum name
    QByteArray className;
    QByteArray enumTypeName(fullTypeName);
    const int pos = enumTypeName.lastIndexOf("::");
    if (pos >= 0) {
        className = enumTypeName.left(pos);
        enumTypeName = enumTypeName.mid(pos + 2);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        // QVariant::typeName is no longer the flag name, but QFlags<Foo>...
        if (className.startsWith("QFlags<")) {
            className.remove(0, sizeof("QFlags<") - 1);
        }

        if (enumTypeName.endsWith(">")) {
            enumTypeName.chop(1);
        }
#endif
    }

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    const QMetaObject *mo = &Qt::staticMetaObject;
#else
    const QMetaObject *mo = &ProtectedExposer::staticQtMetaObject;
#endif
    int enumIndex = mo->indexOfEnumerator(enumTypeName);
    if (enumIndex < 0 && metaObject) {
        mo = metaObject;
        enumIndex = mo->indexOfEnumerator(enumTypeName);
    }
    if (enumIndex < 0 && (mo = QMetaType::metaObjectForType(QMetaType::type(fullTypeName)))) {
        enumIndex = mo->indexOfEnumerator(enumTypeName);
    }
    if (enumIndex < 0 && (mo = metaObjectForClass(className))) {
        enumIndex = mo->indexOfEnumerator(enumTypeName);
    }

    // attempt to recover namespaces from semi-qualified type names
    if (enumIndex < 0 && metaObject) {
        QByteArray n(metaObject->className());
        const int pos = n.lastIndexOf("::");
        if (pos > 0) {
            n = n.left(pos + 2) + fullTypeName;
            return metaEnum(value, n, nullptr);
        }
    }

    if (enumIndex < 0)
        return {};
    return mo->enumerator(enumIndex);
}

int EnumUtil::enumToInt(const QVariant &value, const QMetaEnum &metaEnum)
{
    // QVariant has no implicit QFlag to int conversion as of Qt 5.7
    if (metaEnum.isFlag() && QMetaType::sizeOf(value.userType()) == sizeof(int)) // int should be enough, QFlag has that hardcoded
        return value.constData() ? *static_cast<const int *>(value.constData()) : 0;
    return value.toInt();
}

QString EnumUtil::enumToString(const QVariant &value, const char *typeName, const QMetaObject *metaObject)
{
    const auto me = metaEnum(value, typeName, metaObject);
    if (me.isValid()) {
        return me.isFlag() ? QString::fromUtf8(me.valueToKeys(enumToInt(value, me))) : QString::fromUtf8(me.valueToKey(enumToInt(value, me)));
    }
    if (EnumRepositoryServer::isEnum(value.userType())) {
        const auto ev = EnumRepositoryServer::valueFromVariant(value);
        const auto def = EnumRepositoryServer::definitionForId(ev.id());
        return def.valueToString(ev);
    }
    return QString();
}
