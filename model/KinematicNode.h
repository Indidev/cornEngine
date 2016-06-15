#ifndef KINEMATICNODE_H
#define KINEMATICNODE_H

#include <QList>
#include <QHash>

#include "model/primitives/Point.h"
#include "model/MovableSpirit.h"
#include "model/Types.h"
#include "control/util/Log.h"
#include "control/util/Math.h"

/**
 * @brief The KinematicNode class represents a node of a kinematic
 */
class KinematicNode : public MovableSpirit
{
public:
    /**
     * @brief creates a new KinematicNode from a MovableSpirit
     * @param spirit spirit for the node
     * @param delta delta position from the parent's root if the parent's angle = 0
     * @param parent optional parent of this node
     */
    KinematicNode(MovableSpirit &spirit, QString name, Point delta, KinematicNode *parent = NULL);

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
    void rotate(float angle, CE::Angle type = CE::RAD, bool absolut = false);

    /**
     * @brief add a list of children to this node
     * @param nodes children to add
     */
    void addChildren(QList<KinematicNode*> nodes);

    /**
     * @brief add a child to this node (use either this or setParent, not both are necessary)
     * @param node child to add
     */
    void addChild(KinematicNode *node);

    /**
     * @brief setParent sets this node as a child to another node (use either this or addChild, not both are necessary)
     * @param node node of the new parent
     */
    void setParent(KinematicNode *node);

    /**
     * @brief remove a child
     * @param node child to remove
     */
    void removeChild(KinematicNode *node);

    /**
     * @brief get a node's name
     * @return name of this node
     */
    QString getName();

    /**
     * @brief set the node's name
     * @param name name of node
     */
    void setName(QString name);

    /**
     * @brief getChildren
     * @return return children of this node
     */
    QList<KinematicNode*> getChildren();

    /**
     * @brief set the nodes angle
     * @param angle angle to rotate with
     * @param type CE::RAD for Radian or CE::DEG for Degree
     * @param absolut if absolut this will be the absolut angle otherwise the angle will be handled as a delta (default)
     */
    void setAngle(float angle, CE::Angle type = CE::RAD, bool absolut = false);

protected:
    QString name;
    KinematicNode* parent;
    Point delta;
    QList<KinematicNode*> children;
    float nodeAngle;
};

#endif // KINEMATICNODE_H
