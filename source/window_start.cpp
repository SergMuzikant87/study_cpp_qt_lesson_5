#include "window_start.h"
#include <qt6/QtCore/QObject>

Window_Start::Window_Start(Stopwatch * stopwatch, uint32_t clock_period_ms, QWidget * parent)
: QWidget(parent)
{
    __circles_counter = 0;

    __stopwatch = stopwatch;
    __clock_timer = new QTimer(this);
    __main_group = new QGroupBox(this);
    __main_layout = new QVBoxLayout(__main_group);
    __time_label = new QLabel(__main_group);
    __circles_time_browser = new QTextBrowser(__main_group);
    __buttons_group = new QGroupBox(__main_group);
    __buttons_layout = new QHBoxLayout(__buttons_group);
    __enable_switch_button = new QPushButton(__buttons_group);
    __circle_next_button = new QPushButton(__buttons_group);
    __results_clear_button = new QPushButton(__buttons_group);

    __main_layout->addWidget(__time_label);
    __main_layout->addWidget(__circles_time_browser);
    __main_layout->addWidget(__buttons_group);
    __buttons_layout->addWidget(__enable_switch_button);
    __buttons_layout->addWidget(__circle_next_button);
    __buttons_layout->addWidget(__results_clear_button);

    __enable_switch_button_tittles[TIMER_ENABLE] = "Старт";
    __enable_switch_button_tittles[TIMER_DISABLE] = "Стоп";
    __enable_switch_buttons_handlers[TIMER_ENABLE] = &Stopwatch::start;
    __enable_switch_buttons_handlers[TIMER_DISABLE] = &Stopwatch::stop;
    __enable_status = TIMER_DISABLE;

    QObject::connect
    (
        __enable_switch_button,
        &QPushButton::clicked,
        this,
        [this](void)
        {
            __enable_status ^= 0x01;
            (__stopwatch->*__enable_switch_buttons_handlers[__enable_status])();
        },
        Qt::QueuedConnection
    );

    QObject::connect
    (
        __circle_next_button,
        &QPushButton::clicked,
        this,
        [this](void)
        {
            __circles_counter++;
            uint32_t circle_time_second = __stopwatch->time_relative_prev_get_seconds_get();
            __circles_time_browser->append
            (
                QString("Круг %1,  Время %2 сек.")
                .arg(__circles_counter)
                .arg(circle_time_second)
            );
        },
        Qt::QueuedConnection
    );

    QObject::connect
    (
        __results_clear_button,
        &QPushButton::clicked,
        this,
        [this](void)
        {
            __circles_counter = 0;
            __stopwatch->reset();
            __circles_time_browser->clear();
        },
        Qt::QueuedConnection
    );

    QObject::connect
    (
        __clock_timer,
        &QTimer::timeout,
        this,
        &Window_Start::__visual_components_update,
        Qt::QueuedConnection
    );

    // Запускаем шарманку
    __clock_timer->start(clock_period_ms);
    __visual_components_update();
}

void Window_Start::__visual_components_update()
{
    uint32_t time_after_start_seconds = __stopwatch->time_seconds_get();
    __time_label->setText(QString("Время после старта %1 сек.").arg(time_after_start_seconds));
    __enable_switch_button->setText(__enable_switch_button_tittles[__enable_status ^ 0x01]);

    static bool first_cycle = true;
    if(first_cycle)
    {
        __circle_next_button->setText("Круг");
        __results_clear_button->setText("Очистить");
        __main_layout->setContentsMargins(10, 10, 10, 10);
    }
    first_cycle ^= first_cycle;
}
