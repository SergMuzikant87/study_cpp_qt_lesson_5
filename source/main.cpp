#include "window_start.h"
#include "stopwatch.h"
#include <qt6/QtWidgets/qapplication.h>
#include <qt6/QtWidgets/QVBoxLayout>

#define TIME_CALC_PERIOD_MILLISECONDS (100)
#define VISUAL_COMPONENTS_UPDATE_PERIOD_MILLISECONDS (100)

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    Stopwatch * stopwatch = new Stopwatch(TIME_CALC_PERIOD_MILLISECONDS);
    Window_Start * window_start = new Window_Start(stopwatch, VISUAL_COMPONENTS_UPDATE_PERIOD_MILLISECONDS);
    window_start->show();
    window_start->adjustSize();
    return app.exec();
}
