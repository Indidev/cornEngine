#include "Collisionable.h"

Collisionable::~Collisionable()
{

}

bool Collisionable::collides(Collisionable &other) {
    QRect oRect = other.getBB(); //other rectangle
    QRect tRect = getBB(); //this rectangle

    //return false if rectangles don't intersect
    if (!oRect.intersects(tRect)) {
        return false;
    }

    QRect intersected = oRect.intersected(tRect);

    oRect = intersected.translated(-oRect.topLeft());
    tRect = intersected.translated(-tRect.topLeft());

    //copy triangle lists
    QList<Triangle> oTs = other.colModel(oRect);
    QList<Triangle> mTs = this->colModel(tRect);

    //transform other.triangles into this.coordination system and check with this.triangles
    for (Triangle &oT: oTs) {
        oT.translate(other.rootPoint() - rootPoint());

        //check every triangle of this object
        for (Triangle mT: mTs) {
            if (mT.intersects(oT))
                return true;
        }
    }

    return false;
}
