/*
  objectid.h

  This file is part of GammaRay, the Qt application inspection and manipulation tool.

  SPDX-FileCopyrightText: 2013-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Kevin Funk <kevin.funk@kdab.com>

  SPDX-License-Identifier: GPL-2.0-or-later OR LicenseRef-KDAB-GammaRay

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.
*/

#ifndef GAMMARAY_OBJECTID_H
#define GAMMARAY_OBJECTID_H

#include <QObject>
#include <QDataStream>
#include <QDebug>
#include <QMetaType>
#include <QVector>

#if QT_VERSION < QT_VERSION_CHECK(5, 6, 0)
#include <algorithm>
#endif

namespace GammaRay {
/** @brief Type-safe and cross-process object identifier vector. */
using ObjectIds = QVector<class ObjectId>;

/** @brief Type-safe and cross-process object identifier. */
class ObjectId
{
public:
    enum Type
    {
        Invalid,
        QObjectType,
        VoidStarType
    };

    explicit ObjectId(void *obj, const QByteArray &typeName)
        : m_type(VoidStarType)
        , m_id(reinterpret_cast<quint64>(obj))
        , m_typeName(typeName)
    {
    }
    explicit ObjectId(QObject *obj)
        : m_type(QObjectType)
        , m_id(reinterpret_cast<quint64>(obj))
    {
    }
    explicit ObjectId() = default;
    inline bool isNull() const
    {
        return m_id == 0;
    }
    inline quint64 id() const
    {
        return m_id;
    }
    inline Type type() const
    {
        return m_type;
    }
    inline QByteArray typeName() const
    {
        return m_typeName;
    }

    inline QObject *asQObject() const
    {
        Q_ASSERT(m_type == QObjectType);
        return reinterpret_cast<QObject *>(m_id);
    }

    template<typename T>
    inline T asQObjectType() const
    {
        return qobject_cast<T>(asQObject());
    }

    inline void *asVoidStar() const
    {
        Q_ASSERT(m_type == VoidStarType);
        return reinterpret_cast<void *>(m_id);
    }

    inline operator quint64() const
    {
        return m_id;
    }

    inline bool operator==(const ObjectId &o2) const
    {
        return m_type == o2.m_type && m_id == o2.m_id && m_typeName == o2.m_typeName;
    }

private:
    friend QDataStream &operator<<(QDataStream &out, const ObjectId &id);
    friend QDataStream &operator>>(QDataStream &out, ObjectId &id);

    Type m_type = Invalid;
    quint64 m_id = 0;
    QByteArray m_typeName;
};

///@cond internal
inline QDebug &operator<<(QDebug dbg, const ObjectId &id)
{
    dbg.nospace() << "ObjectId(" << id.type() << ", " << id.id() << ", " << id.typeName() << ")";
    return dbg.space();
}

#if QT_VERSION < QT_VERSION_CHECK(5, 6, 0)
inline bool operator<(const ObjectIds &lhs, const ObjectIds &rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
#endif

inline QDataStream &operator<<(QDataStream &out, const ObjectId &id)
{
    out << static_cast<quint8>(id.m_type);
    out << id.m_id;
    out << id.m_typeName;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, ObjectId &id)
{
    quint8 u;
    in >> u;
    id.m_type = static_cast<ObjectId::Type>(u);
    in >> id.m_id;
    in >> id.m_typeName;
    return in;
}
///@endcond
}

Q_DECLARE_METATYPE(GammaRay::ObjectId)
Q_DECLARE_METATYPE(GammaRay::ObjectIds)
QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(GammaRay::ObjectId, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(GammaRay::ObjectIds, Q_MOVABLE_TYPE);
QT_END_NAMESPACE

#endif // GAMMARAY_OBJECTID_H
