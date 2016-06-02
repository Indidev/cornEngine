#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QString>
#include <QHash>
#include <QSize>
#include <QImage>
#include <QRect>
#include <QPainter>
#include <QPair>
#include <QTransform>

#include "control/res/SpiritManager.h"
#include "model/interface/Drawable.h"
#include "model/interface/Collisionable.h"
#include "model/primitives/Point.h"
#include "control/util/Math.h"

//todo: remove after test
#include "model/primitives/TriangleFactory.h"

class Collisionable;

class GameMap: public Drawable, Collisionable
{
public:
    static const QString TAG;
    static const QString DIR;
    static const QString ROW;
    static const QString TYPE;

    GameMap(QHash<QString, QString> config);

    /**
     * @brief get the size of this map
     * @return size of this map
     */
    QSize size();

    /**
     * @brief get the bounding box of this map
     * @return bounding box
     */
    QRect getBB() {return QRect(screenPos, mapSize);}

    //implemented from Drawable
    QImage *getCrop(const QRect &rect, long time, Point &offset);
    bool isInScreen(const QRect &rect);

    //implemented from Collisionable
    QList<Triangle> colModel(QRect &rect);
    Point rootPoint() {return screenPos;}

protected:
    static const QString LOG_TAG;

    QString name;
    QSize mapSize;
    QSize gridSize;
    QSize titleSize;
    Point screenPos;
    QHash<int, QHash<int, Spirit*> > spirits;
    QHash<int, QHash<int, int> > rots;
    QList<QPair<QRect, QList<Triangle> > >colModels;
    QImage *crop;
};

#endif // GAMEMAP_H
