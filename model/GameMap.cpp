#include "GameMap.h"

const QString GameMap::TAG = "name";
const QString GameMap::DIR = "baseDir";
const QString GameMap::ROW = "row";
const QString GameMap::LOG_TAG = "model/GameMap";
const QString GameMap::TYPE = "GAMEMAP";

GameMap::GameMap(QHash<QString, QString> config):Collisionable(TYPE)
{
    crop = NULL;
    int numRows = -1;

    bool isFirst = true;

    name = config[TAG];
    screenPos = Point();

    //count number of rows:
    while (config.contains(ROW + QString::number(++numRows)));

    for (int i = 0; i < numRows; i++) {
        QString rowS = config[ROW + QString::number(i)];
        QStringList rowSpirits = rowS.split(",");

        //init attributes
        if (isFirst) {
            Spirit *s1 = SpiritManager::getSpirit(rowSpirits[0].split(".")[0]);
            titleSize = s1->getSize();
            gridSize = QSize(rowSpirits.length(), numRows);
            mapSize = QSize(gridSize.width() * titleSize.width(), gridSize.height() * titleSize.height());
            //spirits = new Spirit[gridSize.height()][gridSize.width()];
            //spirits = (Spirit***) malloc(sizeof(Spirit*) * gridSize.height() * gridSize.width());
            isFirst = false;
        } else {
            if (rowSpirits.length() != gridSize.width())
                Log::e(LOG_TAG, "Warning: Size of rows doesn't corespond to each other!", "GameMap(QHash<>)");
        }

        for (int x = 0; x < rowSpirits.size(); x++) {
            QStringList value = rowSpirits[x].split(".");
            spirits[i][x] = SpiritManager::getSpirit(value[0]);
            if (spirits[i][x]->getSize() != titleSize)
                Log::e(LOG_TAG, "Warning: Size of title doesn't correspond to each other!", "GameMap(QHash<>)");

            if (value.length() == 2)
                rots[i][x] = value[1].toInt();
        }
    }

    //init colModels

    //itterate over all spirits of the map
    for (int y = 0; y < gridSize.height(); y++) {
        for (int x = 0; x < gridSize.width(); x++) {
            //get current rectangle
            QRect picR(Point(x * titleSize.width(), y * titleSize.height()), titleSize);
            //check if current rectangle intersects the given one

            //copy, translate and rotate triangles
            if (spirits[y][x]->hasColModel()) {
                //copy collision model
                colModels.append(QPair<QRect, QList<Triangle> >(picR, spirits[y][x]->getColModel()));
                //get pictures center for possible rotation
                Point center(picR.center());
                //do for every triangle of the collision model
                for (Triangle &t : colModels.last().second) {
                    //translate triangle
                    t.translate(picR.topLeft());
                    //rotate if necessary
                    if (rots[y][x])
                        t.rotate(Math::degToRad(rots[y][x]), center);
                }
            }
        }
    }
}

QImage *GameMap::getCrop(const QRect &rect, long time, QPoint &offset)
{
    if (crop)
        delete crop;

    QRect intersected = QRect(screenPos, mapSize).intersected(rect);
    offset = intersected.topLeft() - rect.topLeft(); //global offset

    intersected.translate(-screenPos);

    //init image
    crop = new QImage(intersected.size(), QImage::Format_ARGB32);
    crop->fill(Qt::transparent);

    QPainter painter(crop);

    //itterate over all spirits of the map
    for (int y = 0; y < gridSize.height(); y++) {
        for (int x = 0; x < gridSize.width(); x++) {
            QRect picR(Point(x * titleSize.width(), y * titleSize.height()), titleSize);
            if (picR.intersects(intersected)) {
                //intersect and save where to draw the part of the spirit
                QRect part = picR.intersected(intersected);
                Point drawP = Point(part.topLeft() - intersected.topLeft());

                //translate resulting rectangle into spirits coordinate system
                part.translate(-picR.topLeft());

                int angle = rots[y][x];
                if (angle) {
                    QTransform trans;
                    trans.rotate(angle);
                    painter.drawImage(drawP, spirits[y][x]->getFrame(time).transformed(trans).copy(part));
                } else
                    painter.drawImage(drawP, spirits[y][x]->getFrame(time).copy(part));

                //test: draw collision model on top
                //QList<Triangle> cm = colModel(intersected);
            }
        }
    }
    painter.end();

    return crop;
}

bool GameMap::isInScreen(const QRect &rect)
{
    return QRect(screenPos, mapSize).intersects(rect);
}

QSize GameMap::size()
{
    return mapSize;
}

QList<Triangle> GameMap::colModel(QRect &rect)
{
    QList<Triangle> colModel;

    for (QPair<QRect, QList<Triangle> > &p : colModels) {
        if (rect.intersects(p.first))
            colModel.append(p.second);
    }
    return colModel;
}
