#ifndef SPIRITMANAGER_H
#define SPIRITMANAGER_H

#include <QHash>
#include <QString>

#include "control/io/Input.h"
#include "control/util/Log.h"
#include "model/Spirit.h"

class SpiritManager
{
public:

    /**
     * @brief returns the spirit with the given tag/name
     * @param tag tag/name of the spirit
     * @return spirit with name/tag, NULL if not present
     */
    static Spirit *getSpirit(QString tag);
protected:

    SpiritManager();
    ~SpiritManager();
    static const QString RES_DIR;
    static const QString LOG_TAG;
    static const QString FILE_EX;
    static SpiritManager *self;

    QHash<QString, Spirit*> spirits;

    void loadSpirits(QString curDir);

};

#endif // SPIRITMANAGER_H
