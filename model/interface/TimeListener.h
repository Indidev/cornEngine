#ifndef TIMELISTENER_H
#define TIMELISTENER_H

class TimeListener {
public:
    virtual void onTime(long time, int delta) = 0;
};

#endif // TIMELISTENER_H
