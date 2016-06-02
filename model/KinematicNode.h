#ifndef KINEMATICNODE_H
#define KINEMATICNODE_H

#include <QList>
#include <QHash>

#include "model/primitives/Point.h"
#include "model/MovableSpirit.h"
#include "model/Types.h"

class KinematicNode : public MovableSpirit
{
public:
    KinematicNode(MovableSpirit &spirit);

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

protected:
    QList<KinematicNode*> children;
    QHash<KinematicNode*, Point> deltas;
};

#endif // KINEMATICNODE_H
