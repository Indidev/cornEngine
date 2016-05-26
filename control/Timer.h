#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QList>
#include <QThread>

#include "model/interface/TimeListener.h"
#include "control/TimeThread.h"

/**
 * @brief The Timer class provides a Timer to register with
 */
class Timer : public QObject
{
    Q_OBJECT
public:

    Timer();

    ~Timer();

    /**
     * @brief starts the timer (interval should be set before
     */
    void start();

    /**
     * @brief starts the timer with an interval
     * @param msec interval in milli seconds
     */
    void start(int msec);

    /**
     * @brief sets the timer's interval
     * @param msec interval in milli seconds
     */
    void setInterval(int msec);

    /**
     * @brief stops the timer (does not reset it)
     */
    void stop();

    /**
     * @brief resets the timers time (does not stop the timer)
     */
    void reset();

    /**
     * @brief subscribe a listener to this timer
     * @param listener listener to subscribe (will not be added if already present or null)
     */
    void subscribe(TimeListener* listener);

    /**
     * @brief removes a listener
     * @param listener listener to remove (if it subscribes)
     */
    void unsubscribe(TimeListener* listener);

signals:

protected slots:
    void onTick();

protected:
    QTimer t;
    QTime lastUp;
    long fullT;
    QList<TimeListener*> listeners;
    TimeThread updater;

};

#endif // TIMER_H
