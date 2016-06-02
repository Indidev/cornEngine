#include "KinematicNode.h"

KinematicNode::KinematicNode(MovableSpirit &spirit, Point delta, KinematicNode *parent) : MovableSpirit(spirit)
{
    this->parent = parent;
    this->delta = delta;
}

void KinematicNode::setPos(const Point &pos)
{
    MovableSpirit::setPos(pos);
    //update children
    for (KinematicNode *node: children)
        node->setPos(pos + node->delta.rotated(curAngle));
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
        node->setPos(pos + node->delta.rotated(curAngle));
}

void KinematicNode::addChildren(QList<KinematicNode *> nodes)
{
    for (KinematicNode *node : nodes)
        addChild(node);
}

void KinematicNode::addChild(KinematicNode *node)
{
    //return if node is already child of this
    if (children.contains(node))
        return;

    //remove as child from other parent if a parent is present
    if (node->parent)
        node->parent->removeChild(node);

    //add node as child
    node->parent = this;
    children.append(node);
}

void KinematicNode::setParent(KinematicNode *node)
{
    if (node)
        node->addChild(this);
    else {
        if (parent)
            parent->removeChild(this);
        parent = NULL;
    }

}

void KinematicNode::removeChild(KinematicNode *node)
{
    children.removeOne(node);
}
