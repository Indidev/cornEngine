#include "Spirit.h"

const QString Spirit::TAG = "tag";
const QString Spirit::FSZE = "fSize";
const QString Spirit::IMG = "img";
const QString Spirit::NUMF = "numF";
const QString Spirit::FPOS = "fPos";
const QString Spirit::COL = "col";
const QString Spirit::FPS = "fps";
const QString Spirit::FTME = "fTime";
const QString Spirit::DIR = "baseDir";

const QString Spirit::LOG_TAG = "model/Spirit";

Spirit::Spirit(QHash<QString, QString> &config)
{
    this->tag = config[TAG];

    //image
    QImage img = Input::loadImage(config[DIR] + "/" + config[IMG]);

    if (img.isNull()) {
        Log::e(LOG_TAG, "could not load image: " + config[DIR] + "/" + config[IMG]);
    }

    //frame Size
    QPoint tmp = splitNum(config[FSZE]);
    if (!tmp.isNull())
        this->frameSize = QSize(tmp.x(), tmp.y());
    else {
        this->frameSize = img.size();
    }

    //collision model
    if (config.contains(COL)) {
        this->hasCol = true;
        QString value = config[COL];
        if (value.endsWith(".col")) {
            //todo load collision model from mash
        } else {
            QImage img = Input::loadImage(config[DIR] + "/" + value);
            if (!img.isNull())
                colModel = TriangleFactory::fromImg(img);
            else {
                this->hasCol = false;
                Log::e(LOG_TAG, "could not load collision model: " + config[DIR] + "/" + value, "Spirit(QHash)");
            }
        }
    } else
        this->hasCol = false;

    //set frame time
    if (config.contains(FTME))
        this->frameTime = config[FTME].toInt();
    else if (config.contains(FPS))
        this->frameTime = 1000 / config[FPS].toFloat();
    else
        this->frameTime = 1;

    //frame positions
    QList<QPoint> framePos;
    if (config.contains(FPOS)) {
        for (QString pos : config[FPOS].split(",")) {
            framePos.append(splitNum(pos));
        }
    } else if (config.contains(NUMF)) {
        int numFrames = config[NUMF].toInt();
        int collumns = img.width() / frameSize.width();
        for (int i = 0; i < numFrames; i++) {
            int x = i % collumns;
            int y = i / collumns;
            x *= frameSize.width();
            y *= frameSize.height();
            framePos.append(QPoint(x, y));
        }
    } else {
        framePos.append(QPoint(0, 0));
    }

    //load frames
    for (QPoint pos : framePos) {
        this->frames.append(img.copy(QRect(pos, frameSize)));
    }
}

QPoint Spirit::splitNum(QString input)
{
    QStringList splitted = input.split(".");
    if (splitted.size() == 2)
        return QPoint(splitted[0].trimmed().toInt(), splitted[1].trimmed().toInt());
    else
        return QPoint(0, 0);
}

const QImage& Spirit::getFrame(long ms) {
    int frameNum = ms % (frames.size() * frameTime);
    frameNum /= frameTime;
    return frames[frameNum];
}

const QSize &Spirit::getSize()
{
    return frameSize;
}

const QList<Triangle> Spirit::getColModel()
{
    return colModel;
}

bool Spirit::hasColModel()
{
    return hasCol;
}


