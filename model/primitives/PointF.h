#ifndef POINTF_H
#define POINTF_H

#include <QPoint>
#include "model/primitives/Point.h"
#include "model/Types.h"
#include "control/util/Math.h"

/**
 * @brief Represents a point class with floating precision
 */
class PointF
{
public:
    /**
     * @brief cunstructs a new point with x=0, y=0
     */
    PointF();
    /**
     * @brief constructs a new point
     * @param xVar x value
     * @param yVar y value
     */
    PointF(float xVar, float yVar);

    /**
     * @brief constructs a new point from a QPoint
     * @param p a qpoint
     */
    PointF(const QPoint &p);

    /**
     * @brief constructs a new point from another Point
     * @param p other point
     */
    PointF(const PointF &p);

    /**
     * @brief constructs a new point from a QPoint pointer
     * @param p pointer to other point
     */
    PointF(const PointF *p);

    /**
     * @brief x
     * @return x value of this point
     */
    float x() const;

    /**
     * @brief y
     * @return y value of this point
     */
    float y() const;

    /**
     * @brief set x value of this point
     * @param xVar new x value
     */
    void setX(float xVar);

    /**
     * @brief set y value of this point
     * @param yVar new y value
     */
    void setY(float yVar);

    /**
     * @brief convert to Point
     * @return point with integer precision (correctly rounded)
     */
    Point toPoint();

    /**
     * @brief rotate this point around another point
     * @param angle angle to rotate
     * @param rotP rotation point (default = 0, 0)
     * @param type radian or degree (default = RAD)
     */
    void rotate(float angle, PointF rotP = PointF(), CE::Angle type = CE::RAD);

    /**
     * @brief get a rotated copy of this point
     * @param angle angle to rotate
     * @param rotP rotation point (default = 0, 0)
     * @param type radian or degree (default = RAD)
     * @return rotated copy
     */
    PointF rotated(float angle, PointF rotP = PointF(), CE::Angle type = CE::RAD);

    /**
     * @brief calculate distance to a QPoint
     * @param other point to calculate distance to
     * @return distance
     */
    float distance(const QPoint other);

    /**
     * @brief calculate distance to another Point
     * @param other point to calculate distance to
     * @return distance
     */
    float distance(const PointF other);

    //-----------------------
    //operatores from here on
    //-----------------------

    PointF operator -(const PointF &other);
    PointF operator -();
    PointF operator +(const PointF &other);
    PointF operator /(float div);
    PointF operator *(float fac);
    void operator -=(const PointF &other);
    void operator +=(const PointF &other);
    void operator /=(float div);
    void operator *=(float fac);
    bool operator==(const PointF& other);
    PointF& operator=(const PointF &other);

protected:
    float mX;
    float mY;

    bool same(float a, float b);
};

#endif // POINTF_H
