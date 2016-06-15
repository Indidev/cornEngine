#ifndef KINEMATIC_H
#define KINEMATIC_H


#include <QHash>
#include <QString>
#include <QList>

#include "model/KinematicNode.h"
#include "model/interface/Drawable.h"
#include "model/primitives/Point.h"

//TODO: remove after test
#include "model/MovableSpirit.h"

/**
 * @brief Representation of a Kinematic
 */
class Kinematic: public Drawable, Collisionable
{
public:
    Kinematic();

    /**
     * @brief get a specific node of the kinematic
     * @param name name of the node
     * @return node with a specific name
     */
    KinematicNode* getNode(QString name);

    /**
     * @brief getRootNode
     * @return kinematic's root node
     */
    KinematicNode* getRootNode();

    /**
     * @brief getAllNodes
     * @return all nodes of the kinematic
     */
    QList<KinematicNode*> getAllNodes();

    /**
     * @brief sets the position of the kinematic
     * @param pos new position
     */
    void setPos(const Point &pos);

    //----------------------------------
    //inherited functions frome here on
    //----------------------------------
    //implemented from Drawable
    QImage *getCrop(const QRect &rect, long time, Point&);
    bool isInScreen(const QRect &rect);

    //implemented from Collisionable
    QRect getBB();
    QList<Triangle> colModel(QRect&rect);
    Point rootPoint();

protected:
    KinematicNode *rootNode;
    QHash<QString, KinematicNode*> allNodes;
    QImage *render;
};

#endif // KINEMATIC_H
