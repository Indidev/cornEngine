#include "Timer.h"

Timer::~Timer()
{
    updater.stop();

}

void Timer::start()
{
    t.start();
    lastUp.start();
}

void Timer::start(int msec)
{
    t.start(msec);
    lastUp.start();
}

void Timer::setInterval(int msec)
{
    t.setInterval(msec);
}

void Timer::stop()
{
    t.stop();
}

void Timer::reset()
{
    fullT = 0;
    lastUp.restart();
}

void Timer::subscribe(TimeListener *listener)
{
    if (listener && !listeners.contains(listener))
        listeners.append(listener);
}

void Timer::unsubscribe(TimeListener *listener)
{
    listeners.removeOne(listener);
}

void Timer::onTick()
{
    //get elapsed time
    int elapsed = lastUp.elapsed();
    lastUp.restart();
    fullT += elapsed;

    //call new thread to handle all registred elements
    updater.doUpdate(fullT, elapsed, &listeners);
}
