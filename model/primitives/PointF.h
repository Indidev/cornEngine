#ifndef POINTF_H
#define POINTF_H

#include <QPoint>
#include "model/primitives/Point.h"
#include "model/Types.h"
#include "control/util/Math.h"

/**
 * @brief Represents a Point class with floating precision
 * todo: do comments
 */
class PointF
{
public:
    PointF();
    PointF(float xVar, float yVar);
    PointF(const QPoint &p);
    PointF(const PointF &p);
    PointF(const PointF *p);

    float x() const;
    float y() const;

    void setX(float xVar);
    void setY(float yVar);

    Point toPoint();


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

    void rotate(float angle, PointF rotP = PointF(), CE::Angle type = CE::RAD);
    PointF rotated(float angle, PointF rotP = PointF(), CE::Angle type = CE::RAD);
    float distance(QPoint other);
protected:
    float mX;
    float mY;

    bool same(float a, float b);
};

#endif // POINTF_H
