/*
  eventtypemodel.h

  This file is part of GammaRay, the Qt application inspection and manipulation tool.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Tim Henning <tim.henning@kdab.com>

  SPDX-License-Identifier: GPL-2.0-or-later OR LicenseRef-KDAB-GammaRay

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.
*/
#ifndef GAMMARAY_EVENTMONITOR_EVENTTYPEMODEL_H
#define GAMMARAY_EVENTMONITOR_EVENTTYPEMODEL_H

#include <common/modelroles.h>

#include <QAbstractTableModel>
#include <QMap>
#include <QEvent>

#include <unordered_set>

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

namespace GammaRay {
struct EventTypeData
{
    QEvent::Type type = QEvent::None;
    int count = 0;
    bool recordingEnabled = true;
    bool isVisibleInLog = true;
    inline bool operator<(const EventTypeData &other) const
    {
        return type < other.type;
    }
    inline bool operator<(QEvent::Type otherType) const
    {
        return type < otherType;
    }
};
}

Q_DECLARE_METATYPE(GammaRay::EventTypeData)
QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(GammaRay::EventTypeData, Q_MOVABLE_TYPE);
QT_END_NAMESPACE

namespace GammaRay {
class EventTypeModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Columns
    {
        Type = 0,
        Count,
        RecordingStatus,
        Visibility,
        COUNT
    };

    enum Role
    {
        MaxEventCount = GammaRay::UserRole + 1,
    };

public:
    explicit EventTypeModel(QObject *parent = nullptr);
    ~EventTypeModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QMap<int, QVariant> itemData(const QModelIndex &index) const override;

public slots:
    void increaseCount(QEvent::Type type);
    void resetCounts();

    bool isRecording(QEvent::Type type) const;
    void recordAll();
    void recordNone();

    bool isVisible(QEvent::Type type) const;
    void showAll();
    void showNone();

signals:
    void typeVisibilityChanged();

private:
    void initEventTypes();
    void emitPendingUpdates();

private:
    std::vector<EventTypeData> m_data;
    std::unordered_set<int> m_pendingUpdates;
    int m_maxEventCount = 0;
    QTimer *m_pendingUpdateTimer = nullptr;
};
}

#endif // GAMMARAY_EVENTMONITOR_EVENTTYPEMODEL_H
