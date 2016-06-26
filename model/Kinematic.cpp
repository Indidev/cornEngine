#include "Kinematic.h"

Kinematic::Kinematic()
{
    render = NULL;

    //TODO remove after test and implement loading from file etc.
    MovableSpirit s("arm");
    rootNode = new KinematicNode(s, "rootNode", Point(0, 0));
    rootNode->addChild(new KinematicNode(s, "node1", Point(0, -110)));

    //add all children to hashmap
    allNodes[rootNode->getName()] = rootNode;
    allNodes[rootNode->getChildren()[0]->getName()] = rootNode->getChildren()[0];
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

void Kinematic::setPos(const Point &pos)
{
    rootNode->setPos(pos);
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
        } /*else {
            Log::e("Kinematic", "not in screen...");
        }*/
    }
    painter.end();

    //draw col-model
    /*
    QPainter p(render);

    QRect r = getBB();
    QList<Triangle> ts = colModel(r);
    Point of;
    p.drawImage(rootPoint() - rect.topLeft() + of, TriangleFactory::toImg(ts, of));
    p.end();
    */

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
        Point delta = node->getPos() - rootNode->getPos();

        for (Triangle t: node->colModel(rect)) {
            colM.append(t.translated(delta));
        }
    }
    return colM;
}

Point Kinematic::rootPoint()
{
    return rootNode->rootPoint();
}
