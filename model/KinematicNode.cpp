#include "KinematicNode.h"

KinematicNode::KinematicNode(MovableSpirit &spirit, QString name, Point delta, KinematicNode *parent) : MovableSpirit(spirit)
{
    this->name = name;
    this->parent = parent;
    this->delta = delta;
    this->nodeAngle = 0.f;
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

void KinematicNode::setAngle(float angle, CE::Angle type, bool absolut) {
    if (type == CE::DEG)
        angle = Math::degToRad(angle);

    float oldAngle = nodeAngle;
    nodeAngle = absolut? angle: nodeAngle + angle;

    rotate(nodeAngle - oldAngle);
}

void KinematicNode::rotate(float angle, CE::Angle type, bool absolut)
{
    float oldAngle = curAngle;

    if (type == CE::DEG)
        angle = Math::degToRad(angle);

    curAngle = absolut? angle + nodeAngle: curAngle + angle;

    float relativeAngle = absolut? curAngle - oldAngle: angle;
    //update children
    for (KinematicNode *node : children) {
        node->rotate(relativeAngle, type);
        node->setPos(pos + node->delta.rotated(curAngle) + node->movP);
    }
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

QString KinematicNode::getName()
{
    return name;
}

void KinematicNode::setName(QString name)
{
    this->name = name;
}

QList<KinematicNode *> KinematicNode::getChildren()
{
    return children;
}
