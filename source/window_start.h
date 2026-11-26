#pragma once

#include "stopwatch.h"
#include <cstdint>
#include <qt6/QtWidgets/qwidget.h>
#include <qt6/QtWidgets/QVBoxLayout>
#include <qt6/QtWidgets/QHBoxLayout>
#include <qt6/QtWidgets/QGroupBox>
#include <qt6/QtWidgets/QLabel>
#include <qt6/QtWidgets/QTextBrowser>
#include <qt6/QtWidgets/QPushButton>
#include <qt6/QtCore/QTimer>

class Window_Start : public QWidget
{
    Q_OBJECT

    QTimer * __clock_timer = nullptr;
    QGroupBox * __main_group = nullptr;
    QVBoxLayout * __main_layout = nullptr;
    QLabel * __time_label = nullptr;
    QTextBrowser * __circles_time_browser = nullptr;
    QGroupBox * __buttons_group = nullptr;
    QHBoxLayout * __buttons_layout = nullptr;
    QPushButton * __enable_switch_button = nullptr;
    QPushButton * __circle_next_button = nullptr;
    QPushButton * __results_clear_button = nullptr;

    Stopwatch * __stopwatch;
    uint32_t __circles_counter;
    typedef enum : uint8_t
    {
        TIMER_DISABLE,
        TIMER_ENABLE,
        TIMER_STATUSES_COUNT
    }timer_statuses_t;
    QString __enable_switch_button_tittles[TIMER_STATUSES_COUNT];
    void (Stopwatch::*__enable_switch_buttons_handlers[TIMER_STATUSES_COUNT])(void);
    bool __enable_status;

signals:

public:
    explicit Window_Start(Stopwatch * stopwatch = nullptr, uint32_t clock_period_ms = 100, QWidget * parent = nullptr);

private slots:
    void __visual_components_update(void);

};
