#include "KinematicNode.h"

KinematicNode::KinematicNode(MovableSpirit &spirit) : MovableSpirit(spirit)
{
}

void KinematicNode::setPos(const Point &pos)
{
    MovableSpirit::setPos(pos);
    //update children
    for (KinematicNode *node: children)
        node->setPos(pos + deltas[node].rotated(curAngle));
}

void KinematicNode::translate(const Point delta)
{
    MovableSpirit::translate(delta);
    //update children
    for(KinematicNode *node: children)
        node->translate(delta);
}

void KinematicNode::rotate(float angle, CE::Angle type, bool absolut)
{
    MovableSpirit::rotate(angle, type, absolut);
    //update children
    for (KinematicNode *node : children)
        node->setPos(pos + deltas[node].rotated(curAngle));
}
