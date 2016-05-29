#include "Point.h"

void Point::rotate(float angle, QPoint rotP, CE::Angle type)
{
    //translate to root
    operator -=(rotP);

    if (type == CE::DEG)
        angle = Math::degToRad(angle);

    float oldX = x();
    float oldY = y();

    setX(cos(angle) * oldX - sin(angle) * oldY + 0.5);
    setY(sin(angle) * oldX + cos(angle) * oldY + 0.5);

    //translate back
    operator +=(rotP);
}

Point Point::rotated(float angle, QPoint rotP, CE::Angle type)
{
    Point r(*this);
    r.rotate(angle, rotP, type);
    return r;
}

float Point::distance(QPoint other)
{
    return sqrt((x() - other.x()) * (x() - other.x()) + (y() - other.y()) * (y() - other.y()));
}

Point Point::operator -(const QPoint &other)
{
    return Point(this->x() - other.x(), this->y() - other.y());
}

Point Point::operator +(const QPoint &other)
{
    return Point(this->x() + other.x(), this->y() + other.y());
}
