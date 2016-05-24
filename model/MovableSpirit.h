#ifndef MOVABLESPIRIT_H
#define MOVABLESPIRIT_H

#include <QRect>
#include <QSize>
#include <QString>
#include <QImage>
#include <QTransform>

#include "control/res/SpiritManager.h"
#include "model/Spirit.h"
#include "model/Drawable.h"
#include "model/interface/Collisionable.h"
#include <math.h>
#include "model/primitives/Point.h"

using std::cos;
using std::sin;
using std::fabs;

/**
 * @brief Represents a spirit which is transformable (move, rotate,...)
 */
class MovableSpirit : public Drawable, Collisionable
{
public:
    /**
     * @brief creates a new MovableSpirit
     * @param spirit
     */
    MovableSpirit(Spirit *spirit);

    /**
     * @brief creates a new MovableSpirit
     * @param name spirit tag/name
     */
    MovableSpirit(QString name);

    /**
     * @brief set the position of this spirit
     * @param pos new position
     */
    void setPos(const QPoint &pos);

    //implemented from Drawable
    QImage *getCrop(const QRect &rect, long time, QPoint &offset);
    bool isInScreen(const QRect &rect);

    //implemented from Collisionable
    QRect getBB() {return bb;}
    QList<Triangle> colModel(QRect&);
    Point rootPoint() {return pos;}

protected:
    Spirit *spirit;
    Point pos;
    Point rotP;
    Point center;
    Point vecCP;
    QRect bb;
    QImage *img;
    float curAngle;

private:
    void init();

};

#endif // MOVABLESPIRIT_H
