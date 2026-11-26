#pragma once

#include <cstdint>
#include <qt6/QtCore/QTimer>
#include <qt6/QtCore/QObject>
#include <qt6/QtCore/QMetaObject>

class Stopwatch : public QObject
{
    Q_OBJECT

    uint32_t __clock_period_ms;
    uint32_t __clock_ms;
    uint32_t __clock_prev_ms;
    QTimer * __clock_timer;

public:
    Stopwatch(uint32_t clock_period_ms = 100, QObject * parent = nullptr);

    void start(void);
    void stop(void);
    void reset(void);
    uint32_t time_seconds_get(void);
    uint32_t time_relative_prev_get_seconds_get(void);
};
