#include "TimeThread.h"

TimeThread::TimeThread() {
    update = false;
    stopped = false;

    start();
}

void TimeThread::doUpdate(long time, int delta, QList<TimeListener *> *listeners) {
    if (!update)
        this->delta = delta;
    else
        this->delta += delta;

    this->time = time;
    this->listeners = listeners;
    update = true;
}

void TimeThread::stop()
{
    stopped = true;
    while(!finished)
        msleep(5);
}

void TimeThread::start()
{
    stopped = false;
    QThread::start();
}

void TimeThread::run() {
    while(!stopped) {
        while(!update) {
            if (stopped)
                break;
            msleep(5);
        }

        //copy if new update comes in during update
        int d = delta;
        int t = time;
        QList<TimeListener *> listeners = *(this->listeners);
        update = false;

        for (TimeListener* l: listeners) {
            if (stopped)
                break;
            else
                l->onTime(t, d);
        }

    }
    finished = true;
}
