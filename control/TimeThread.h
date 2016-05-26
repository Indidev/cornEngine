#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include <QThread>
#include "model/interface/TimeListener.h"

/**
 * @brief The TimeThread class represents a thread to update a timers listeners
 */
class TimeThread : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief constructs a new thread and starts it
     */
    TimeThread();

    /**
     * @brief does an update of the given listeners
     * @param time total time from the timer
     * @param delta time passed since the last update
     * @param listeners listeners to update
     */
    void doUpdate(long time, int delta, QList<TimeListener *> *listeners);

    /**
     * @brief stops the thread (should be called before the timer is deleted)
     */
    void stop();

protected:
    bool update;
    bool stopped;
    bool finished;
    int delta;
    long time;
    QList<TimeListener *> *listeners;

    void start();
    void run();

};

#endif // TIMETHREAD_H
