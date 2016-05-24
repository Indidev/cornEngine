#include "GameMapManager.h"

QString const GameMapManager::RES_DIR = "res";
QString const GameMapManager::LOG_TAG = "control/res/GameMapManager";
QString const GameMapManager::FILE_EX = "*.map";
GameMapManager *GameMapManager::self = new GameMapManager;

GameMapManager::GameMapManager()
{
    loadGameMaps(RES_DIR);
}

GameMapManager::~GameMapManager()
{
    for (GameMap* map : maps.values()) {
        delete map;
    }
}

void GameMapManager::loadGameMaps(QString curDir)
{

    //recursive through all subdirectories
    for (QString dir : Input::listDirs(curDir))
        loadGameMaps(curDir + "/" + dir);

    //itterate through all .config files in current directory
    for (QString file : Input::listFiles(curDir, FILE_EX)) {
        QHash<QString, QString> config = Input::loadMap(curDir + "/" + file);
        config[GameMap::DIR] = curDir;
        QString tag = config[GameMap::TAG];

        //delete maps if allready inserted
        if (maps.contains(tag)) {
            delete maps[tag];
            Log::v(LOG_TAG, "WARNING: tag(" + tag + ") already exists.", "loadMaps(QString)");
        }
        //add map
        maps[tag] = new GameMap(config);
    }
}

GameMap *GameMapManager::getMap(QString tag) {
    return self->maps[tag.trimmed()];
}
