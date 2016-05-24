#ifndef LOG_H
#define LOG_H

#include <QString>
#include <iostream>
#include <stdlib.h>

using std::cout;
using std::cerr;
using std::endl;

/**
 * @brief Used for printing log messages
 * TODO: add function to log in file(Log::f)
 */
class Log
{
public:

    /**
     * @brief d Print message on screen only when in debug mode
     * @param tag preferable the classpath
     * @param message message
     * @param funcName function the message is thrown from (opt)
     */
    static void d(QString tag, QString message, QString funcName = "");

    /**
     * @brief e Print an error message
     * @param tag preferable the classpath
     * @param message message
     * @param funcName function the message is thrown from (opt)
     */
    static void e(QString tag, QString message, QString funcName = "");

    /**
     * @brief v Print a verbose message
     * @param tag preferable the classpath
     * @param message message
     * @param funcName function the message is thrown from (opt)
     */
    static void v(QString tag, QString message, QString funcName = "");
};

#endif // LOG_H
