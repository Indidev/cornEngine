#include "Kinematic.h"

Kinematic::Kinematic()
{
    render = NULL;
}

KinematicNode *Kinematic::getNode(QString name)
{
    return allNodes[name];
}

KinematicNode *Kinematic::getRootNode()
{
    return rootNode;
}

QList<KinematicNode *> Kinematic::getAllNodes()
{
    return allNodes.values();
}

QImage *Kinematic::getCrop(const QRect &rect, long time, Point &)
{
    //delete previous image
    if (render)
        delete render;

    //create new image
    render = new QImage(rect.size(), QImage::Format_ARGB32);
    render->fill(Qt::transparent);

    Point off;

    QPainter painter(render);

    //paint nodes
    for (KinematicNode *node: allNodes.values()) {
        if (node->isInScreen(rect)) {
            QImage *crop = node->getCrop(rect, time, off);
            painter.drawImage(off, *crop);
        }
    }
    painter.end();

    return render;
}

bool Kinematic::isInScreen(const QRect &rect)
{
    for (KinematicNode *node: allNodes.values())
        if (node->isInScreen(rect)) return true;

    return false;
}

QRect Kinematic::getBB()
{
    QRect bb = rootNode->getBB();
    for (KinematicNode *node : allNodes.values()) {
        if (node != rootNode) {
            Point delta = node->getPos() - rootNode->getPos();
            bb = bb.united(node->getBB().translated(delta));
        }
    }
    return bb;
}

QList<Triangle> Kinematic::colModel(QRect &rect)
{

    QList<Triangle> colM;
    for (KinematicNode *node : allNodes.values()) {
        //Point delta = node->getPos() - rootNode->getPos();
        colM.append(node->colModel(rect));
    }
    return colM;
}

Point Kinematic::rootPoint()
{
    return rootNode->rootPoint();
}
