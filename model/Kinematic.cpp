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
