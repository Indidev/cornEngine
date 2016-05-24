#ifndef GAMEMAPMANAGER_H
#define GAMEMAPMANAGER_H

#include <QHash>
#include <QString>

#include "control/io/Input.h"
#include "control/util/Log.h"
#include "model/GameMap.h"

class GameMapManager
{
public:

    /**
     * @brief get a map by its name/tag
     * @param tag name/tag of the map
     * @return map with the specific name/tag, NULL if not present
     */
    static GameMap *getMap(QString tag);
protected:

    GameMapManager();
    ~GameMapManager();
    static const QString RES_DIR;
    static const QString LOG_TAG;
    static const QString FILE_EX;
    static GameMapManager *self;

    QHash<QString, GameMap*> maps;

    void loadGameMaps(QString curDir);

};

#endif // GAMEMAPMANAGER_H
