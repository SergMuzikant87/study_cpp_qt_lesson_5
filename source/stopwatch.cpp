#include "stopwatch.h"

Stopwatch::Stopwatch(uint32_t clock_period_ms, QObject * parent)
: QObject(parent)
{
    __clock_timer = new QTimer(this);
    __clock_period_ms = clock_period_ms;
    stop();
    reset();
    QObject::connect
    (
        __clock_timer,
        &QTimer::timeout,
        this,
        [this](void){__clock_ms += __clock_period_ms;},
        Qt::QueuedConnection
    );
}

void Stopwatch::start(void)
{
    __clock_timer->start(__clock_period_ms);
}

void Stopwatch::stop(void)
{
    __clock_timer->stop();
}

void Stopwatch::reset(void)
{
    __clock_ms = 0;
    __clock_prev_ms = 0;
}

uint32_t Stopwatch::time_seconds_get(void)
{
    return (__clock_ms  + (__clock_period_ms >> 1)) / 1000;
}

uint32_t Stopwatch::time_relative_prev_get_seconds_get(void)
{
    uint32_t clock_ms = __clock_ms;
    uint32_t clock_relative_prev_ms = clock_ms - __clock_prev_ms;
    __clock_prev_ms = clock_ms;
    return (clock_relative_prev_ms + (__clock_period_ms >> 1)) / 1000;
}

