#include "SpiritManager.h"

QString const SpiritManager::RES_DIR = "res";
QString const SpiritManager::FILE_EX = "*.conf";
QString const SpiritManager::LOG_TAG = "control/res/SpiritManager";
SpiritManager *SpiritManager::self = new SpiritManager;

SpiritManager::SpiritManager()
{
    loadSpirits(RES_DIR);
}

SpiritManager::~SpiritManager()
{
    for (Spirit* spirit : spirits.values()) {
        delete spirit;
    }
}

void SpiritManager::loadSpirits(QString curDir)
{

    //recursive through all subdirectories
    for (QString dir : Input::listDirs(curDir))
        loadSpirits(curDir + "/" + dir);

    //itterate through all .config files in current directory
    for (QString file : Input::listFiles(curDir, FILE_EX)) {
        QHash<QString, QString> config = Input::loadMap(curDir + "/" + file);
        config[Spirit::DIR] = curDir;
        QString tag = config[Spirit::TAG];

        //delete spirit if allready inserted
        if (spirits.contains(tag)) {
            delete spirits[tag];
            Log::v(LOG_TAG, "WARNING: tag(" + tag + ") already exists.", "loadSpirits(QString)");
        }
        //add spirit
        spirits[tag] = new Spirit(config);
    }
}

Spirit *SpiritManager::getSpirit(QString tag) {
    return self->spirits[tag.trimmed()];
}
