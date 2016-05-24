#include "Log.h"


void Log::d(QString tag, QString message, QString funcName)
{
    if (!funcName.isEmpty())
        funcName.prepend("::");
#ifdef DEBUG
    cout << "cornEngine.d: " << (tag + funcName).toStdString() << ": " << message.toStdString() << endl;
#endif
}

void Log::e(QString tag, QString message, QString funcName)
{
    if (!funcName.isEmpty())
        funcName.prepend("::");
    cerr << "cornEngine.e: " << (tag + funcName).toStdString() << ": " << message.toStdString() << endl;
}

void Log::v(QString tag, QString message, QString funcName)
{
    if (!funcName.isEmpty())
        funcName.prepend("::");
    cout << "cornEngine.v: " << (tag + funcName).toStdString() << ": " << message.toStdString() << endl;
}
