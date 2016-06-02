#ifndef MOVABLESPIRIT_H
#define MOVABLESPIRIT_H

#include <QRect>
#include <QSize>
#include <QString>
#include <QImage>
#include <QTransform>

#include <math.h>

#include "control/res/SpiritManager.h"
#include "model/Spirit.h"
#include "model/interface/Drawable.h"
#include "model/interface/Collisionable.h"
#include "model/primitives/Point.h"
#include "control/util/Math.h"
#include "model/Types.h"
#include "model/primitives/PointF.h"

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
    void setPos(const Point &pos);

    /**
     * @brief translates the spirit
     * @param delta +- translation
     */
    void translate(const Point delta);

    /**
     * @brief rotate the spirit
     * @param angle angle to rotate with
     * @param type CE::RAD for Radian or CE::DEG for Degree
     * @param absolut if absolut this will be the absolut angle otherwise the angle will be handled as a delta (default)
     */
    void rotate(float angle, CE::Angle type, bool absolut = false);

    //implemented from Drawable
    QImage *getCrop(const QRect &rect, long time, Point &offset);
    bool isInScreen(const QRect &rect);

    //implemented from Collisionable
    QRect getBB() {return bb;}
    QList<Triangle> colModel(QRect&);
    Point rootPoint() {return pos;}

protected:
    Spirit *spirit;
    Point pos;
    PointF rotP;
    Point movP;
    PointF center;
    PointF vecCP;
    QRect bb;
    QImage *img;
    float curAngle; //current angle in radian

private:
    void init();

};

#endif // MOVABLESPIRIT_H
