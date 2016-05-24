#ifndef COLLISIONABLE_H
#define COLLISIONABLE_H

#include <QRect>
#include <QString>
#include <QList>

#include "model/primitives/Triangle.h"
#include "model/primitives/Point.h"

class Collisionable {
public:
    Collisionable(QString type = "NULL") {this->type = type;}
    virtual ~Collisionable();

    /**
     * @brief sets the type of the Drawable (possible need for upcasting)
     * @param type type of drawable
     */
    virtual void setType(QString type) {this->type = type;}

    /**
     * @brief get the type of the Drawable (possible need for upcasting)
     * @return type of drawable
     */
    virtual QString getType() {return type;}

    /**
     * @brief test if this Collidable collides with anotherone
     * @param other other collidable
     * @return true if they collide
     */
    virtual bool collides(Collisionable &other);

    /**
     * @brief return the bounding box of this collidable
     * @return bounding box
     */
    virtual QRect getBB() = 0;

    /**
     * @brief get the collision model of this object
     * @param rect rectangle stuff intersects in (if needed)
     * @return list of triangles as collision model
     */
    virtual QList<Triangle> colModel(QRect &rect) = 0;

    /**
     * @brief get root point of own coordinate system
     * @return root point
     */
    virtual Point rootPoint() = 0;

protected:
    QString type;
};

#endif // COLLISIONABLE_H
